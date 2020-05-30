genAddCellularPatch("floor_tallGrass", 1)

-- Mountain borders
if(getBiome(getMapX(), getMapY() - 1) == MOUNTAIN) then
    genAddBorder("wall_stone", NORTH, 10, 20)
end
if(getBiome(getMapX(), getMapY() + 1) == MOUNTAIN) then
    genAddBorder("wall_stone", SOUTH, 10, 20)
end
if(getBiome(getMapX() - 1, getMapY()) == MOUNTAIN) then
    genAddBorder("wall_stone", WEST, 16, 26)
end
if(getBiome(getMapX() + 1, getMapY()) == MOUNTAIN) then
    genAddBorder("wall_stone", EAST, 16, 26)
end

-- Ocean coast
if(getBiome(getMapX(), getMapY() - 1) == OCEAN) then
    genAddBorder("water", NORTH, 20, 30)
end
if(getBiome(getMapX(), getMapY() + 1) == OCEAN) then
    genAddBorder("water", SOUTH, 20, 30)
end
if(getBiome(getMapX() - 1, getMapY()) == OCEAN) then
    genAddBorder("water", WEST, 26, 36)
end
if(getBiome(getMapX() + 1, getMapY()) == OCEAN) then
    genAddBorder("water", EAST, 26, 36)
end

-- Generate river
if(getBiome(getMapX(), getMapY() - 1) == RIVER and getBiome(getMapX(), getMapY() + 1) == RIVER) then
    genAddRiver("water", NORTH)
elseif(getBiome(getMapX() - 1, getMapY()) == RIVER and getBiome(getMapX() + 1, getMapY()) == RIVER) then
    genAddBorder("water", EAST)
end

genPlantTrees("tree_oak", 1, false)
genPlaceActorSomewhere("rock", math.random(40, 60))

build()

populate("butterfly")
populate("butterfly")
populate("smallWolfPack")