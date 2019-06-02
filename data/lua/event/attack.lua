-- Distance is 1?
if(calculateDistance(getActorMapX(emitter), getActorMapY(emitter), getActorMapX(target), getActorMapY(target)) ~= 1) then
	if(isPlayer(emitter)) then
		message("You missed the " .. getName(target):lower() .. ".")
	end
	return false
end

-- Calculate damage
damage = math.random(getMinDamage(emitter), getMaxDamage(emitter))

-- Round to integrer
damage = math.floor(damage+0.5)

-- Chance to hit
if(math.random(0, 100) > getAccuracy(emitter)) then
	if(isPlayer(emitter)) then
		message("You miss the " .. getName(target) .. ".")
		return false
	elseif(isPlayer(target)) then
		message("The " .. getName(emitter) .. " misses you.")
		return false
	else
		message("The " .. getName(emitter) .. " misses the " .. getName(target) .. ".")
		return false
	end	
end

-- Chance to dodge
if(math.random(0, 100) > getDodge(target)) then
	if(isPlayer(emitter)) then
		message("The " .. getName(target) .. " dodges you!")
		return false
	elseif(isPlayer(target)) then
		message("You dodge the " .. getName(emitter) .. "!")
		return false
	else
		message("The " .. getName(emitter) .. " dodges the " .. getName(target) .. ".")
		return false
	end	
end

if(isPlayer(emitter)) then
	message("You hit the " .. getName(target) .. ". [-" .. damage .. "HP]")
elseif(isPlayer(target)) then
	message("The " .. getName(emitter) .. " hits you! [-" .. damage .. "HP]")
else
	message("The " .. getName(emitter) .. " hits the " .. getName(target) .. " [-" .. damage .. "HP]")
end	

data = s_data.new()
data:setEmitter(emitter)
data:setTarget(target)
data:setType("damage")
data:setValue1(damage)
runEvent(data)
return true