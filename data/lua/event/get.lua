-- We get the name first in case the item is deleted
name = getName(target)
getItemFromFloor(target)
message("You get a " .. name:lower() ..".")