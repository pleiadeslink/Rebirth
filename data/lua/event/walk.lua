-- N
if(value1 == NORTH) then
	mapX = getActorMapX(emitter)
	mapY = getActorMapY(emitter) - 1
-- NE
elseif(value1 == NORTHEAST) then
	mapX = getActorMapX(emitter) + 1
	mapY = getActorMapY(emitter) - 1
-- E
elseif(value1 == EAST) then
	mapX = getActorMapX(emitter) + 1
	mapY = getActorMapY(emitter)
-- SE
elseif(value1 == SOUTHEAST) then
	mapX = getActorMapX(emitter) + 1
	mapY = getActorMapY(emitter) + 1
-- S
elseif(value1 == SOUTH) then
	mapX = getActorMapX(emitter)
	mapY = getActorMapY(emitter) + 1
-- SW
elseif(value1 == SOUTHWEST) then
	mapX = getActorMapX(emitter) - 1
	mapY = getActorMapY(emitter) + 1
-- W
elseif(value1 == WEST) then
	mapX = getActorMapX(emitter) - 1
	mapY = getActorMapY(emitter)
-- NW
elseif(value1 == NORTHWEST) then
	mapX = getActorMapX(emitter) - 1
	mapY = getActorMapY(emitter) - 1
-- Random
elseif(value1 == RANDOM) then
	repeat
		mapX = getActorMapX(emitter) + math.random(-1, 1)
		mapY = getActorMapY(emitter) + math.random(-1, 1)
	until(mapX ~= 0 and mapY ~= 0 and mapX ~= getMapWidth() and mapY ~= getMapHeight())
end

-- Distance is 1?
if(calculateDistance(getActorMapX(emitter), getActorMapY(emitter), mapX, mapY) ~= 1) then
	return
end

if(isPlayer(emitter)) then
	
	-- World map
	if(isWorldMap() == true) then

		-- Location
		if(getBiome(mapX, mapY) == 1) then
			changeMap(mapX, mapY, getMapZ(), 0, 0)
			return
		end

		-- Mountain
		if(findActorByName(mapX, mapY, "mountain") ~= 0) then
			message("The mountain in front of you is too steep to be traversed.")
			return
		end

		-- Ocean
		if(findTileByName(mapX, mapY, "water")) then
			message("The water is too deep, you don't wanna drown do you?")
			return
		end
	
	-- Regular map
	else
		-- Is there an obstacle?
		if(isObstacle(mapX, mapY) and isPlayerGod() == false) then
			return
		end
	end
elseif(isObstacle(mapX, mapY)) then
	return
end

-- If out limits, travel to the world map
if(isWorldMap() == false) then
	if(getMapZ() == 0) then
		if(mapX == 0) then
			if(isPlayer(emitter) == true) then
				changeMap(getMapX() - 1, getMapY(), getMapZ(), getMapWidth() - 2, getActorMapY(emitter))
				message("You travel to the west.")
			end
			return

		-- Go east
		elseif(mapX == getMapWidth() - 1) then
			if(isPlayer(emitter) == true) then
				changeMap(getMapX() + 1, getMapY(), getMapZ(), 1, getActorMapY(emitter))
				message("You travel to the east.")
			end
			return

		-- Go north
		elseif(mapY == 0) then
			if(isPlayer(emitter) == true) then
				changeMap(getMapX(), getMapY() - 1, getMapZ(), getActorMapX(emitter), getMapHeight() - 2)
				message("You travel to the north.")
			end
			return

		-- Go south
		elseif(mapY == getMapWidth() - 1) then
			if(isPlayer(emitter) == true) then
				changeMap(getMapX(), getMapY() + 1, getMapZ(), mapX, 1)
				message("You travel to the south.")
			end
			return
		end
	end

	-- Staircase
	direction = findStaircase(mapX, mapY)
	if(direction ~= 0) then
		if(isPlayer(emitter) == true) then

			-- Up
			if(direction == 9) then
				changeMap(getMapX(), getMapY(), getMapZ() - 1, getActorMapX(emitter), getActorMapY(emitter))
				message("You travel up.")
				return

			-- Down
			elseif(direction == 10) then
				changeMap(getMapX(), getMapY(), getMapZ() + 1, getActorMapX(emitter), getActorMapY(emitter))
				message("You travel down.")
				return
			end
		else

			-- If it's not player, we don't allow to move here
			return
		end
	end
end

-- Walk
teleportActor(emitter, mapX, mapY, true)