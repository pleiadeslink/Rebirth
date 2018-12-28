-- Distance is 1?
if(calculateDistance(getActorMapX(emitter), getActorMapY(emitter), getActorMapX(target), getActorMapY(target)) ~= 1) then
	if(isPlayer(emitter)) then
		message("You missed the " .. getName(target):lower() .. " (" .. damage .. ").")
	end
	return false;
end

damage = getMeleeDamage(emitter)

if(isPlayer(emitter)) then
	message("You hit the " .. getName(target):lower() .. " (" .. damage .. " damage).")
else
	message("The " .. getName(emitter) .. " hits the " .. getName(target):lower() .. " (" .. damage .. " damage).")
end

data = s_data.new()
data:setEmitter(emitter)
data:setTarget(target)
data:setType("damage")
data:setValue1(damage)
runEvent(data)