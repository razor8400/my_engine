
local content = {
	[element_type.red] = 'red.png',
	[element_type.blue] = 'blue.png',
	[element_type.green] = 'green.png',
	[element_type.yellow] = 'yellow.png',
	[element_type.orange] = 'orange.png'
}

local match3element_loader = {

}

function match3element_loader:load_element(element)
	local view = sprite.create(content[element.element_type])
	element.view = view
	return view
end

return match3element_loader

