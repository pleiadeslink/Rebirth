

-- Distance is 1?
if(calculateDistance(getActorMapX(emitter), getActorMapY(emitter), getActorMapX(target), getActorMapY(target)) ~= 1) then
	if(isPlayer(emitter)) then
		message("You missed the " .. getName(target):lower() .. ".")
	end
	return false
end

-- Is it a makku tree? Very small chance of getting an apple
if(getActorId(target) == "tree_makku") then
	if(math.random(0,100) < 1 and math.random(0,100) < 10) then
		createActor("apple", getActorMapX(emitter), getActorMapY(emitter))
		message("You kick the makku tree violently.")
		message("An apple has fallen from it!")
		return true
	end
end

-- Is it anything but a creature? We just kick it, nothing really happens
if(getActorType(target) ~= CREATURE) then
	message("You kick the " .. getName(target):lower() .. " violently.")
	return true
end

-- Calculate damage
damage = math.random(getMinDamage(emitter), getMaxDamage(emitter))

-- Round to integrer
damage = math.floor(damage+0.5)

-- Chance to hit
if(math.random(0, 100) > getAccuracy(emitter)) then
	if(isPlayer(emitter)) then
		message("You kick the " .. getName(target) .. ".")
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
		message("The " .. getName(target) .. " dodges your foot!")
		return false
	elseif(isPlayer(target)) then
		message("You dodge the " .. getName(emitter) .. "'s foot!")
		return false
	else
		message("The " .. getName(emitter) .. " dodges the " .. getName(target) .. ".")
		return false
	end	
end

if(isPlayer(emitter)) then
	message("You kick the " .. getName(target) .. ". [-" .. damage .. "HP]")
elseif(isPlayer(target)) then
	message("The " .. getName(emitter) .. " kicks you! [-" .. damage .. "HP]")
else
	message("The " .. getName(emitter) .. " kicks the " .. getName(target) .. " [-" .. damage .. "HP]")
end	

data = s_data.new()
data:setEmitter(emitter)
data:setTarget(target)
data:setType("damage")
data:setValue1(damage)
runEvent(data)
return true