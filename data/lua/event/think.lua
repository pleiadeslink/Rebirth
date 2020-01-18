THINK = 0
WANDER = 1
state = THINK

while true do

	-- THINK
	while(state == THINK) do

		-- If player is passive, wander
		if(getActorFlag(emitter, PASSIVE) == true) then
			state = WANDER
			break
		end

		-- Remembers target
		target = getActorTarget(emitter)

		-- Check if the target still exists
		if(target ~= 0) then
			if(actorExists(target) == false) then
				target = 0
				setActorTarget(emitter, 0)
			end
		end

		-- Check if the target is still visible from the emitter position
		if(target ~= 0) then
			if(los(getActorMapX(emitter), getActorMapY(emitter), getActorMapX(target), getActorMapY(target)) == false) then
				target = 0
				setActorTarget(emitter, 0)
			end
		end

		-- If there is no target, search for a new one
		if(target == 0) then
			target = findTarget(emitter, HOSTILE)
		end

		-- If no target was found, wander
		if(target == 0) then
			state = WANDER
			break
		end

		-- If hostile target is within range, attack
		if(calculateDistance(getActorMapX(emitter), getActorMapY(emitter), getActorMapX(target), getActorMapY(target)) == 1) then
			data = s_data.new()
			data:setEmitter(emitter)
			data:setTarget(target)
			data:setType("hit")
			startAction(data)
			return	
		
		-- Move to target
		else
			data = s_data.new()
			data:setEmitter(emitter)
			data:setValue1(getDirectionToActor(emitter, target))
			data:setType("walk")
			startAction(data)
			return
		end

		state = WANDER
	end

	-- WANDER
	while(state == WANDER) do
		if(math.random(0, 6) == 0) then
			data = s_data.new()
			data:setEmitter(emitter)
			data:setValue1(11)
			data:setType("walk")
			startAction(data)
			return
		else
			data = s_data.new()
			data:setEmitter(emitter)
			data:setValue1(11)
			data:setType("wait")
			startAction(data)
			return		
		end	
	end
end