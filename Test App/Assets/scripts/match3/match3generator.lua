local match3element = load_script('scripts/match3/match3element.lua')

local elements_generator = {
	config = {
		[element_type.red] = 20,
		[element_type.green] = 20,
		[element_type.blue] = 20,
		[element_type.yellow] = 20,
		[element_type.orange] = 20
	}
}

function elements_generator:generate_element()
	local summ = 0

	for k, v in pairs(self.config) do
		summ = summ + v
	end

	local r = math.random(summ)

	for k, v in pairs(self.config) do
		if r <= v then
			return match3element.new(k)
		end
		r = r - v
	end

	return nil
end

function elements_generator:load_config(config)
	self.config = config
end

return elements_generator