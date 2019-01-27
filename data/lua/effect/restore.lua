-- RESTORE (effect)
-- Restores attributes (health, energy, etc.)
-- value1: restored points
-- string1: restored attribute

if(string1 == "health") then
	if(getHealth(emitter) < getMaxHealth(emitter)) then
		restoreHealth(emitter, value1)
		if(isPlayer(emitter)) then
			message("Your health has been restored.")
		end
	end
end