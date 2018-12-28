if(removeItem(emitter, target) == true) then
	message("You remove the " .. getName(target) .. ".")
else
	message("You cannot remove the " .. getName(target) .. ".")
end