if(isPlayer(emitter)) then
	message("You drink a " .. getName(target) .. ".")
end
consume(emitter, target)