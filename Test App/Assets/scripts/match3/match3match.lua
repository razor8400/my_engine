local config = load_script('scripts/match3/match3config.lua')

local match = {
	match = {

	},
	width = 0,
	height = 0
}

local match3match_handler =  {
	matches = {

	}
}

function match:get_value(x, y)
	return self.match[(y - 1) * self.width + x]
end

function match:set_value(x, y, v)
	self.match[(y - 1) * self.width + x] = v
end

function match:iterate(handler)
	for y = 0, self.height - 1 do
		for x = 0, self.width - 1 do
			local i = y * self.width + x + 1
			handler(x + 1, y + 1, i)
		end
	end
end

function match:print()
	local string = ''
	local y1 = -1
	
	self:iterate(function(x, y, i)
		if y > y1 then
			string = string .. '\n'
			y1 = y
		end
		string = string .. self.match[i] .. ','
	end)

	debug_log(string)
end

function match:rotate()
	local m = {}

	setmetatable(m, { __index = match })

	m.match = {}
	m.width = self.height
	m.height = self.width

	self:iterate(function(x, y, i)
		local v = self:get_value(x, y)
		m:set_value(y, self.width - (x - 1), v)
	end)
	return m
end

function match.new(config)
	local m = {}
	
	setmetatable(m, { __index = match })

	m.match = {}
	m.width = config.width
	m.height = config.height

	m:iterate(function(x, y, i)
		m.match[i] = config.match[i]
	end)

	return m
end

function match:size()
	local size = 0
	self:iterate(function(x, y, i)
		if self.match[i] > 0 then
			size = size + 1
		end
	end)
	return size
end

local function compare_elements(cell, match)
	for k, v in pairs(match) do
		local element = cell:find_element(v.element_type, v.element_layer)
		if element then
			return element
		end
	end
	return nil
end

function match3match_handler:load_config()
	for i = #config, 1, -1 do
		local m = match.new(config[i])

		for j = 1, config[i].rotations do
			table.insert(self.matches, m)
			m = m:rotate()
		end
	end

	for k, v in pairs(self.matches) do
		v:print()
	end
end

function match3match_handler:match(field, match, x, y)
	local result = {}

	match:iterate(function(i, j, k)
		if match.match[k] > 0 then
			local x2 = x + (i - 1)
			local y2 = y + (j - 1)

			local cell = field:get_cell(x2, y2)
			if cell then
				local element = nil
				if #result > 0 then
					element = compare_elements(cell, result)
				else
					element = cell:get_element_at(element_layer.gameplay)
				end

				if element then
					table.insert(result, element)
				end
			end
		end
	end)
		
	if #result == match:size() then
		return result
	end

	return nil
end

function match3match_handler:check_match(field, x, y)
	for k, v in pairs(self.matches) do
		for i = 0, v.height - 1 do
			for j = 0, v.width - 1 do
				local x1 = x - j
				local y1 = y - i

				local match = self:match(field, v, x1, y1)

				if match then
					return match
				end
			end
		end
	end

	return nil
end

function match3match_handler:find_matches(field, find_callback, finish_callback)
	self.thread = coroutine.create(function()
		for y = 1, field.rows do
			local matches = {}
			for x = 1, field.colls do
				local match = self:check_match(field, x, y)
				if match then
					table.insert(matches, match)
				end
			end
			if find_callback then
				find_callback(matches)
			end
			coroutine.yield()
		end

		if finish_callback then
			finish_callback()
		end
		self.thread = nil
	end)
end

function match3match_handler:update()
	if self.thread then
		coroutine.resume(self.thread)
	end
end

return match3match_handler