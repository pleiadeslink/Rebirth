state = 0
think = 0
wander = 1

-- Check if there are enemies
while true do

	-- THINK
	while(state == think) do

		-- If player is too far away, wander
		if(calculateDistance(getActorMapX(emitter), getActorMapY(emitter), getActorMapX(getPlayer()), getActorMapY(getPlayer())) > getViewRange(emitter)) then
			state = wander
			break
		end
		
		-- Check if there are visible enemies
		enemyFound = findEnemy(emitter)
		if(enemyFound ~= 0) then

			-- If the enemy is close, attack
			if(calculateDistance(getActorMapX(emitter), getActorMapY(emitter), getActorMapX(enemyFound), getActorMapY(enemyFound)) == 1) then
				data = s_data.new()
				data:setEmitter(emitter)
				data:setTarget(enemyFound)
				data:setType("hit")
				startAction(data)
				
				return	
			else
				-- Move to target
				data = s_data.new()
				data:setEmitter(emitter)
				data:setValue1(getDirectionToActor(emitter, enemyFound))
				data:setType("walk")
				startAction(data)
				return
			end
		else
			state = wander
		end
	end

	-- WANDER
	while(state == wander) do
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