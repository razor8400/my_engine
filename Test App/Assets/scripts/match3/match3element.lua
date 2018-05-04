element_type = {
    red = "red", green = "green", blue = "blue", yellow = "yellow", orange = "orange", unknown = "unknown"
}

element_layer = {
	underground = "underground",
	background = "background",
	gameplay = "gameplay",
	blockers = "blockers",
	top = "top"
}

local elements = 
{
	[element_type.blue] = {
		element_type = element_type.blue,
		element_layer = element_layer.gameplay,
		handle_input = true,
		droppable = true
	},
	[element_type.red] = {
		element_type = element_type.red,
		element_layer = element_layer.gameplay,
		handle_input = true,
		droppable = true
	},
	[element_type.green] = {
		element_type = element_type.green,
		element_layer = element_layer.gameplay,
		handle_input = true,
		droppable = true
	},
	[element_type.yellow] = {
		element_type = element_type.yellow,
		element_layer = element_layer.gameplay,
		handle_input = true,
		droppable = true
	},
	[element_type.orange] = {
		element_type = element_type.orange,
		element_layer = element_layer.gameplay,
		handle_input = true,
		droppable = true
	},
}

local match3element = {

}

match3element.new = function(family)
	local config = assert(elements[family])

	local element = {
		element_type = config.element_type,
		element_layer = config.element_layer,
		handle_input = config.handle_input,
		droppable = config.droppable,
		cell = nil,
		view = nil,
		path = {}
	}

	setmetatable(element, { __index = match3element })

	return element
end

function match3element:remove_from_cell()
	if self.cell then
		self.cell:remove_element(self)
	end
end

return match3element

