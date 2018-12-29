-- N
if(value1 == 1) then
	mapX = getActorMapX(emitter)
	mapY = getActorMapY(emitter) - 1
-- NE
elseif(value1 == 2) then
	mapX = getActorMapX(emitter) + 1
	mapY = getActorMapY(emitter) - 1
-- E
elseif(value1 == 3) then
	mapX = getActorMapX(emitter) + 1
	mapY = getActorMapY(emitter)
-- SE
elseif(value1 == 4) then
	mapX = getActorMapX(emitter) + 1
	mapY = getActorMapY(emitter) + 1
-- S
elseif(value1 == 5) then
	mapX = getActorMapX(emitter)
	mapY = getActorMapY(emitter) + 1
-- SW
elseif(value1 == 6) then
	mapX = getActorMapX(emitter) - 1
	mapY = getActorMapY(emitter) + 1
-- W
elseif(value1 == 7) then
	mapX = getActorMapX(emitter) - 1
	mapY = getActorMapY(emitter)
-- NW
elseif(value1 == 8) then
	mapX = getActorMapX(emitter) - 1
	mapY = getActorMapY(emitter) - 1
-- Random
elseif(value1 == 9) then
	mapX = getActorMapX(emitter) + math.random(-1, 1)
	mapY = getActorMapY(emitter) + math.random(-1, 1)
end

-- Distance is 1?
if(calculateDistance(getActorMapX(emitter), getActorMapY(emitter), mapX, mapY) ~= 1) then
	return
end

-- Is there an obstacle?
if(isPlayer(emitter)) then
	if(isObstacle(mapX, mapY) and isPlayerGod() == false) then
		return
	end
elseif(isObstacle(mapX, mapY)) then
	return
end

-- Check conditions

-- Go west
if(mapX == 0) then
	if(isPlayer(emitter) == true) then
		worldMap(getMapX() - 1, getMapY())
		message("You travel to the west.")
	end
	return

-- Go east
elseif(mapX == getMapWidth() - 1) then
	if(isPlayer(emitter) == true) then
		worldMap(getMapX() + 1, getMapY())
		message("You travel to the east.")
	end
	return

-- Go north
elseif(mapY == 0) then
	if(isPlayer(emitter) == true) then
		worldMap(getMapX(), getMapY() - 1)
		message("You travel to the north.")
	end
	return

-- Go south
elseif(mapY == getMapWidth() - 1) then
	if(isPlayer(emitter) == true) then
		worldMap(getMapX(), getMapY() + 1)
		message("You travel to the south.")
	end
	return

-- Staircase
else
	direction = findStaircase(mapX, mapY)
	if(direction ~= 0) then
		if(isPlayer(emitter) == true) then

			-- Up
			if(direction == 9) then
				changeMap(9, mapX, mapY)
				message("You travel up.")

			-- Down
			elseif(direction == 10) then
				changeMap(10, mapX, mapY)
				message("You travel down.")
			end
		else

			-- If it's not player, we don't allow to move here
			return
		end
		
	-- Walk
	else
		teleportActor(emitter, mapX, mapY, true)

		-- Check if there's an item on the new tile
		--item = getFirstActorInTile(emitter, mapX, mapY)
		--if(item ~= 0) then
		--	message("You see a " .. getName(item) .. ".")
		--end
	end
end