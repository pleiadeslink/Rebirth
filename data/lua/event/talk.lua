-- Distance is 1?
if(calculateDistance(getActorMapX(emitter), getActorMapY(emitter), getActorMapX(target), getActorMapY(target)) ~= 1) then
	message("You are too far away.")
	return false;
end

dofile("data/lua/dialogue.lua")
