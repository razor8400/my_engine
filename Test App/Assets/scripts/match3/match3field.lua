local match3cell = load_script('scripts/match3/match3cell.lua')
local match3generator = load_script('scripts/match3/match3generator.lua')
local match3match = load_script('scripts/match3/match3match.lua')

local event_generate = {

}

event_generate.new = function(element, x, y)
	local e = {
		element = element,
		x = x,
		y = y
	}

	return e
end

local event_destroy = {

}

event_destroy.new = function(element)
	local e = {
		element = element
	}
	
	return e
end

local event_drop = {

}

event_drop.new = function(tick, element)
	local e = {
		tick = tick,
		element = element
	}

	return e
end

local match3field = {
	colls = 0,
	rows = 0,
	cell = 0,
	cells = {},
	delegate = nil
}

local function round(x)
	return math.ceil(x)
end

function match3field:get_cell(x, y)
	if x >= 1 and x <= self.colls and y >= 1 and y <= self.rows then
		return self.cells[(y - 1) * self.colls + x]
	end

	return nil
end

function match3field:size()
	return { x = self.colls * self.cell, y = self.rows * self.cell }
end

function match3field:convert_cell_to_world(x, y)
	return { x = (x - 1) * self.cell, y = (y - 1) * self.cell }
end

function match3field:convert_world_to_cell(x, y)
	return { x = round(x / self.cell), y = round(y / self.cell) }
end

function match3field:get_element(x, y, layer)
	local cell = self:get_cell(x, y)
	if cell then
		return cell:get_element_at(layer)
	end
	return nil
end

function match3field:generate_element(x, y)
	local cell = assert(self:get_cell(x, y))
	local element = nil

	repeat
		if element ~= nil then
			cell:remove_element(element)
		end
		element = assert(match3generator:generate_element())
		cell:add_element(element)
	until match3match:check_match(self, cell.x, cell.y) == nil

	return element
end

function match3field:generate_field()
	match3match:load_config()

	for x = self.colls, 1, -1 do
		for y = self.rows, 1, -1 do
			local element = self:generate_element(x, y)
			table.insert(self.generate_events, event_generate.new(element, x, y))
		end
	end

	self.send_events = true
end

function match3field:swipe(a, b)
	local cell1 = assert(self:get_cell(a.x, a.y))
	local cell2 = assert(self:get_cell(b.x, b.y))

	local el1 = cell1:get_element_at(element_layer.gameplay)
	local el2 = cell2:get_element_at(element_layer.gameplay)

	local function do_swipe(el1, el2)
		el1:remove_from_cell()
		el2:remove_from_cell()

		cell1:add_element(el2)
		cell2:add_element(el1)
	end

	if el1 and el2 then
		do_swipe(el1, el2)

		if match3match:check_match(self, a.x, a.y) ~= nil or match3match:check_match(self, b.x, b.y) ~= nil then
			return true
		end

		do_swipe(el2, el1)
	end
	return false
end

function match3field:events_count()
	return #self.generate_events + #self.destroy_events + #self.drop_events
end

function match3field:process()
	local field_changed = false

	local find_callback = function(matches)
		for k, v in pairs(matches) do
			for k1, v1 in pairs(v) do
				v1:remove_from_cell()
				
				table.insert(self.destroy_events, event_destroy.new(v1))
			end
		end
		
		field_changed = #matches > 0	
	end

	local finish_callback = function()
		local tick = 1

		function drop_element(element, x, y)
			if #element.path == 0 then
				table.insert(self.drop_events, event_drop.new(tick, element))
			end
			
			table.insert(element.path, { x = x, y = y })
			field_changed = true
		end
	
		repeat
			local drop_elements = false

			for x = 1, self.colls do
				for y = 1, self.rows - 1 do
					local cell = assert(self:get_cell(x, y))
	
					if cell:get_element_at(element_layer.gameplay) == nil then
						local top = assert(self:get_cell(x, y + 1))
						local element = top:get_element_at(element_layer.gameplay)
	
						if element and element.droppable then
							cell:add_element(element)
							drop_elements = true
							drop_element(element, x, y)
						end
					end
				end
			end
	
			for x = 1, self.colls do
				for y = 1, self.rows do
					local cell = assert(self:get_cell(x, y))
					if cell:get_element_at(element_layer.gameplay) == nil and cell.generate_elements then
						local element = self:generate_element(x, y)
	
						table.insert(self.generate_events, event_generate.new(element, x, y + 1))
						drop_element(element, x, y)
					end
				end
			end
	
			tick = tick + 1
		until not drop_elements

		self.send_events = true	
	end

	self.thread = coroutine.create(function()
		repeat
			field_changed = false
			match3match:find_matches(self, find_callback, finish_callback)

			coroutine.yield()
		until not field_changed
		
		self.thread = nil
	end)
	
	coroutine.resume(self.thread)
end

function match3field:update()
	match3match:update()

	if self.send_events then
		if self.delegate then
			for k, v in pairs(self.destroy_events) do
				self.delegate:on_destroy_element(v)
			end

			for k, v in pairs(self.generate_events) do
				self.delegate:on_generate_element(v)
			end
	
			for k, v in pairs(self.drop_events) do
				self.delegate:on_drop_element(v)
			end

			self.delegate:handle_events()
		end

		self.send_events = false
		self.drop_events = {}
		self.generate_events = {}
		self.destroy_events = {}
		
		if self.thread then
			coroutine.resume(self.thread)
		end
	end
end

function match3field.new(colls, rows, cell)
	local field = {}

	debug_log('[match3field] new rows:' .. rows .. ',' .. 'colls:' .. colls)

	field.colls = colls
	field.rows = rows
	field.cell = cell
	field.cells = {}
	field.destroy_events = {}
	field.generate_events = {}
	field.drop_events = {}
	field.send_events = false
	
	setmetatable(field, { __index = match3field })

	for i = 1, colls do
		for j = 1, rows do
			local cell = match3cell.new(j, i)
			cell.field = field
			table.insert(field.cells, cell)
			assert(field:get_cell(j, i))
		end
	end

	for i = 1, colls do
		local cell = assert(field:get_cell(i, field.rows))
		cell.generate_elements = true
	end

	return field
end

return match3field