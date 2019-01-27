-- This goes first in case the item is deleted to avoid a null reference
if(isPlayer(emitter)) then
	message("You drink a " .. getName(target) .. ".")
end
consume(emitter, target)