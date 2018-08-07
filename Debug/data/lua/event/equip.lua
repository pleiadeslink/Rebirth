if(equipItem(emitter, target) == true) then
	message("You equip the " .. getName(target) .. ".")
else
	message("You cannot equip the " .. getName(target) .. ".")
end