math.randomseed(getMapSeed())

local function pre()
	return getName(target) .. " says: '"
end

local function post()
	return "'"
end

local function send(mes)
	message(pre() .. mes .. post())
end

-- RESPONSES

-- Per character
local id = getActorId(target)
if(id == "dog") then
	send("Woof, woof! Arf, arf, arf...")
	return
elseif(id == "humusi") then
	-- Random gossip
	send("My name is Humusi, I am at your service.")
	return
end

-- Generic gossip
local random = math.random(3)
if random == 1 then
	send("Thoughts unify all reality in existence and are all shared.")
	return
elseif random == 2 then
	send("All reality is created by thought.")
	return
elseif random == 3 then
	send("Accident means something happening to you without relation to your action.")
	return
end
