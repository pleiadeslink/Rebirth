-- Distance is 1?
if(calculateDistance(getActorMapX(emitter), getActorMapY(emitter), getActorMapX(target), getActorMapY(target)) ~= 1) then
	if(isPlayer(emitter)) then
		message("You %1miss%0 the " .. getName(target):lower() .. ".")
	end
	return false
end

-- Chance to hit
chance = 75 + ((getAttack(emitter) - (getDefense(target))) / 4) -- Each difference point is +0.25% chance
if(chance > 95) then
	chance = 95
end
if(chance < 5) then
	chance = 5
end
if(math.random(0, 100) > chance) then
	if(isPlayer(emitter)) then
		message("You %1miss%0 the " .. getName(target) .. ".")
	end
	return false
end

-- Calculate damage
damage = math.random(getMinDamage(emitter), getMaxDamage(emitter))

-- Substract protection value
damage = damage * (100 / (100 + getProtection(target))) 

-- Round to integrer
damage = math.floor(damage+0.5)

if(isPlayer(emitter)) then
	message("You %1hit%0 the " .. getName(target) .. " for %1-" .. damage .. "\003%0.")
elseif(isPlayer(target)) then
	message("The " .. getName(emitter) .. " %2hits%0 you for %1-" .. damage .. "\003%0!")
else
	message("The " .. getName(emitter) .. " hits the " .. getName(target) .. " for -" .. damage .. ".")
end

data = s_data.new()
data:setEmitter(emitter)
data:setTarget(target)
data:setType("damage")
data:setValue1(damage)
runEvent(data)
return true