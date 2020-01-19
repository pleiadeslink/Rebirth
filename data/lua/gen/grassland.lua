genAddCellularPatch("floor_tallGrass", 1)
if(getBiome(getMapX(), getMapY() - 1) == MOUNTAIN) then
    genAddBorder("wall_stone", NORTH, 2, 16)
end
if(getBiome(getMapX(), getMapY() + 1) == MOUNTAIN) then
    genAddBorder("wall_stone", SOUTH, 2, 16)
end
if(getBiome(getMapX() - 1, getMapY()) == MOUNTAIN) then
    genAddBorder("wall_stone", WEST, 2, 16)
end
if(getBiome(getMapX() + 1, getMapY()) == MOUNTAIN) then
    genAddBorder("wall_stone", EAST, 2, 16)
end
genPlantTrees("tree_oak", 1, false)
genPlaceActorSomewhere("rock", math.random(40, 60))
build()
populate("butterfly")
populate("butterfly")
populate("smallWolfPack")