dofile("data/lua/rules.lua")

damage(target, value1)

if(getHealth(target) == 0) then
	data = s_data.new()
	data:setEmitter(target)
	data:setType("death")
	runEvent(data)
end