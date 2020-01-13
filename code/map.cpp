c_map::c_map() 
: TCODMap(MAPSIZE, MAPSIZE),
  name("The Void"),
  x(0),
  y(0),
  z(0),
  width(MAPSIZE),
  height(MAPSIZE),
  oldXFOV(0),
  oldYFOV(0),
  selectedTileX(0),
  selectedTileY(0),
  ambience("") {
    dirX = -1; // Initial direction vector
    dirY = 0; 
    planeX = 0; // The 2d raycaster version of camera plane
    planeY = 0.66;
    randomSeed = c_helper::random(0, 1000);
}

c_map::~c_map() {
}

void c_map::init() {

    // Default values
    this -> x = 0;
    this -> y = 0;
    this -> z = 0;
    this -> name = "the wilderness";
    this -> width = MAPSIZE;
    this -> height = MAPSIZE;
    this -> oldXFOV = 0;
    this -> oldYFOV = 0;
    selectedTileX = 0;
    selectedTileY = 0;
    genFloor1 = "floor_stone";
    genFloor2 = "floor_grass";
    genFloor3 = "floor_tallGrass";
    genWall1 = "wall_stone";
    genWall2 = "wall_stone";
    genWall3 = "wall_stone";

    // Creates initial matrix
    createMatrix();
    createGenMatrix();
    fill(engine -> assetManager.getTileAsset("floor_grass"));
}

void c_map::save(TCODZip* zip) {
    zip -> putInt(width);
    zip -> putInt(height);
    for(int i1 = 0; i1 < width; ++i1) {
        for(int i2 = 0; i2 < height; ++i2) {
            zip -> putString(matrix[i1][i2] -> getId().c_str());
            zip -> putInt(matrix[i1][i2] -> getExplored());
        }
    }
    zip -> putInt(x);
    zip -> putInt(y);
    zip -> putInt(z);
    zip -> putString(name.c_str());
    zip -> putString(ambience.c_str());
}

void c_map::load(TCODZip* zip) {
    width = zip -> getInt();;
    height = zip -> getInt();
    for(int i1 = 0; i1 < width; ++i1) {
        for(int i2 = 0; i2 < height; ++i2) {
            matrix[i1][i2] -> setAsset(engine -> assetManager.getTileAsset(zip -> getString()));
            bool explored = zip -> getInt();
            if(explored == true) {
                matrix[i1][i2] -> setExplored(true);
                if(matrix[i1][i2] -> getType() != tileType::wall and matrix[i1][i2] -> getType() != tileType::obstacle) {
                    setProperties(i1, i2, true, true);
                }
            }
        }
    }
    x = zip -> getInt();
    y = zip -> getInt();
    z = zip -> getInt();
    name = zip -> getString();
    ambience = zip -> getString();
}

void c_map::parse(std::string path) {
    std::string line;
    std::ifstream file(path);
    int y = 0;
    while(getline(file, line)) {
        for(int i = 0; i < MAPSIZE; ++i) {
            switch(line[i]) {
                case ',': {
                    genMatrix[i][y].tile = "world_grassland";
                    break;
                }
                case '^': {
                    genMatrix[i][y].tile = "world_mountain";
                    break;
                }
                case 'T': {
                    genMatrix[i][y].tile = "world_temperateForest";
                    break;
                }
                case 'Y': {
                    genMatrix[i][y].tile = "world_taigaForest";
                    break;
                }
                case 'F': {
                    genMatrix[i][y].tile = "world_jungle";
                    break;
                }
                case '.': {
                    genMatrix[i][y].tile = "world_desert";
                    break;
                }
                case 'M': {
                    genMatrix[i][y].tile = "world_marsh";
                    break;
                }
                case '-': {
                    genMatrix[i][y].tile = "world_ocean";
                    break;
                }
            }
        }
        ++y;
    }
    build();
}

void c_map::wipe(const int& x, const int& y, const int& z) {
    for(int i1 = 0; i1 < width; ++i1) {
        for(int i2 = 0; i2 < height; ++i2) {
            matrix[i1][i2] -> wipe(engine -> assetManager.getTileAsset("floor_grass"));
            genMatrix[i1][i2].tile = "floor_grass";
            genMatrix[i1][i2].actor = "";
            genMatrix[i1][i2].flag = false;
        }
    }
    this -> x = x;
    this -> y = y;
    this -> z = z;
}

TCODPath* c_map::path(const int& x0, const int& y0, const int& x1, const int& y1) {
    TCODPath* path = new TCODPath(this); // Second value is the diagonal cost
    // Origin and destination tile are set as walkable temporarily for the path to compute
    bool originWasObstacle = false;
    if(matrix[x0][y0] -> isObstacle() or matrix[x0][y0] -> isLocation()) {
        setProperties(x0, y0, true, true);
        originWasObstacle = true; 
    }
    bool destWasObstacle = false;
    if(matrix[x1][y1] -> isObstacle() or matrix[x1][y1] -> isLocation()) {
        setProperties(x1, y1, true, true);
        destWasObstacle = true; 
    }
    path -> compute(x0, y0, x1, y1);
    if(originWasObstacle == true) {
        setProperties(x0, y0, false, false);
    }
    if(destWasObstacle == true) {
        setProperties(x1, y1, false, false);
    }
    return path;
}

c_tile* c_map::runaway(const int& x1, const int& y1, const int& tx, const int& ty) {
    int addx = 0;
    int addy = 0;
    if(tx > x1) {
        addx = 1;
    }
    else if(tx < x1) {
        addx = -1;
    }
    if(ty > y1) {
        addy = 1;
    }
    else if(ty < y1) {
        addy = -1;
    }
    int dx = x1 - addx;
    int dy = y1 - addy;
    if(dx < 0) {
        dx = 0;
    }
    if(dx > width) {
        dx = width;
    }
    if(dy < 0) {
        dy = 0;
    }
    if(dy > height) {
        dy = height;
    }
    return matrix[dx][dy];
}

void c_map::addScript(s_script script) {
    v_script.push_back(script);
}

// Returns true if current instance is the world map (x=0 y=0 z=0)
const bool& c_map::isWorldMap() {
    if(x == 0 and y == 0 and z == 0) {
        return true;
    } else { 
        return false;
    }
}

// --- BUILD ---

void c_map::createMatrix() {
   	//matrix = new c_tile*[width];
	//for(int i = 0; i < width; ++i)
    //	matrix[i] = new c_tile[height];
    //std::vector<std::vector<c_tile*>> tmatrix(MAPSIZE, std::vector<c_tile*>(MAPSIZE));
    //matrix = tmatrix;
    // Creates matrix
    for(int i1 = 0; i1 < width; ++i1) {
        std::vector<c_tile*> v;
        for(int i2 = 0; i2 < height; ++i2) {
            v.push_back(new c_tile());
        }
        matrix.push_back(v);
    }
    // Init tiles
    for(int i1 = 0; i1 < width; ++i1) {
        for(int i2 = 0; i2 < height; ++i2) {
            matrix[i1][i2] -> setCoords(i1, i2);
            matrix[i1][i2] -> setAsset(engine -> assetManager.getTileAsset("floor_grass"));
        }
    }
}

void c_map::createGenMatrix() {
   	genMatrix = new s_genTile*[width];
	for(int i = 0; i < width; ++i)
		genMatrix[i] = new s_genTile[height];
    for(int i1 = 0; i1 < width; ++i1) {
        for(int i2 = 0; i2 < height; ++i2) {
            genMatrix[i1][i2].tile = "floor_grass";
            genMatrix[i1][i2].actor = "";
        }
    }
}

void c_map::fill(const s_tileAsset* asset) {
	for(int i1 = 0; i1 < width; ++i1) {
		for(int i2 = 0; i2 < height; ++i2) {
			matrix[i1][i2] -> setAsset(asset);
		}
	}
}

void c_map::flood(const s_tileAsset* asset, const int& x, const int& y) {
    for(int i1 = 0; i1 < width; ++i1) {
        for(int i2 = 0; i2 < height; ++i2) {
            matrix[i1][i2] -> setCheck(false);
        }
    }
    floodAux(asset, x, y);
}

void c_map::floodAux(const s_tileAsset* asset, const int& x, const int& y) {
    if(x >= 0 and x < width and y >= 0 and y < height
    and matrix[x][y] -> getType() != tileType::wall and matrix[x][y] -> getCheck() == false) {
        matrix[x][y] -> setAsset(asset);
        matrix[x][y] -> setInterior(true); // DELETE
        matrix[x][y] -> setCheck(true);
    }
    else {
        return;
    }
    floodAux(asset, x + 1, y);
    floodAux(asset, x - 1, y);
    floodAux(asset, x, y + 1);
    floodAux(asset, x, y - 1);
}

void c_map::genClear(std::string tile) {
	for(int i1 = 0; i1 < width; ++i1) {
		for(int i2 = 0; i2 < height; ++i2) {
			genMatrix[i1][i2].tile = tile;
            genMatrix[i1][i2].actor = "";
		}
	}
}

const bool& c_map::genDigRoom(const int& x0, const int& y0, const int& rwidth, const int& rheight, const int& direction, const bool& digStartingTile) {

    // Check free (wall) space
    for(int i = -1; i < rwidth + 1; ++i) {
        for(int j = -1; j < rheight + 1; ++j) {
            switch(direction) {
                case direction::north: {
                    // If even number
                    //if(rwidth % 2 != 0) {
                        
                    int x = x0 - ((rwidth - 1) / 2) + i;
                    int y = y0 - 1 - j;
                    if(x < 2 or
                       y < 2 or 
                       x > width - 2 or
                       y > height - 2 or
                       genIsWall(x, y) == false) {
                        return false;
                    }
                    break;
                }
                case direction::south: {
                    int x = x0 - ((rwidth - 1) / 2) + i;
                    int y = y0 + 1 + j;
                    if(x < 2 or
                       y < 2 or 
                       x > width - 2 or
                       y > height - 2 or
                       genIsWall(x, y) == false) {
                        return false;
                    }
                    break;
                }
                case direction::west: {
                    int x = x0 - 1 - i;
                    int y = y0 - ((rheight - 1) / 2) + j;
                    if(x < 2 or
                       y < 2 or 
                       x > width - 2 or
                       y > height - 2 or
                       genIsWall(x, y) == false) {
                        return false;
                    }
                    break;
                }
                case direction::east: {
                    int x = x0 + 1 + i;
                    int y = y0 - ((rheight - 1) / 2) + j;
                    if(x < 2 or
                       y < 2 or 
                       x > width - 2 or
                       y > height - 2 or
                       genIsWall(x, y) == false) {
                        return false;
                    }
                    break;
                }
            }
        }
    }

    /*/ Dig room
    if(digStartingTile == true) {
        genMatrix[x0][y0].tile = genTile::floor1;
    }
    for(int i = 0; i < rwidth; ++i) {
        for(int j = 0; j < rheight; ++j) {
            switch(direction) {
                case direction::north: {
                    genMatrix[x0 - ((rwidth - 1) / 2) + i][y0 - 1 - j].tile = genTile::floor1;
                    break;
                }
                case direction::south: {
                    genMatrix[x0 - ((rwidth - 1) / 2) + i][y0 + 1 + j].tile = genTile::floor1;
                    break;
                }
                case direction::west: {
                    genMatrix[x0 - 1 - i][y0 - ((rheight - 1) / 2) + j].tile = genTile::floor1;
                    break;
                }
                case direction::east: {
                    genMatrix[x0 + 1 + i][y0 - ((rheight - 1) / 2) + j].tile = genTile::floor1;
                    break;
                }
            }
        }
    }*/
    return true;
}

// Returns a cellular automata generated map with 0s and 1s
s_map c_map::getCellularMap(const int& iterations, const int& birthLimit, const int& deathLimit, const int& chanceToStartAlive) {

    // Create map and place random flags
    s_map map;
    for(int i = 0; i < MAPSIZE; ++i) {
        for(int j = 0; j < MAPSIZE; ++j) {
            if(c_helper::random(0, 100) < chanceToStartAlive) {
                map.tile[i][j] = true;
            } else {
                map.tile[i][j] = false;
            }            
        }
    }
    
    // Conway's Game of Life
    for(int i = 0; i < iterations; ++i) {
        map = cellularIteration(map, birthLimit, deathLimit);
    }

    return map;
}

// Conway's Game of Life rules
s_map c_map::cellularIteration(s_map oldMap, const int& birthLimit, const int& deathLimit) {
    
    // Create new map
    s_map newMap;
    for(int i = 0; i < MAPSIZE; ++i) {
        for(int j = 0; j < MAPSIZE; ++j) {
            newMap.tile[i][j] = false;
        }
    }

    // Loop over each row and column of the map
    for(int x = 0; x < MAPSIZE; ++x){
        for(int y = 0; y < MAPSIZE; ++y){
            int nbs = countNeighbours(oldMap, x, y);
            // The new value is based on our simulation rules
            // First, if a cell is alive but has too few neighbours, kill it.
            if(oldMap.tile[x][y]) {
                if(nbs < deathLimit) {
                    newMap.tile[x][y] = false;
                }
                else {
                    newMap.tile[x][y] = true;
                }
            } // Otherwise, if the cell is dead now, check if it has the right number of neighbours to be 'born'
            else {
                if(nbs > birthLimit) {
                    newMap.tile[x][y] = true;
                }
                else {
                    newMap.tile[x][y] = false;
                }
            }
        }
    }
    return newMap;
}

// Used in cellular automata generation
int c_map::countNeighbours(s_map map, const int& x, const int& y) {
    int count = 0;
    for(int i=-1; i<2; i++) {
        for(int j=-1; j<2; j++) {
            int neighbour_x = x + i;
            int neighbour_y = y + j;

            // If we're looking at the middle point
            if(i == 0 && j == 0) {
                // Do nothing, we don't want to add ourselves in!
            }

            // In case the index we're looking at it off the edge of the map
            else if(neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= MAPSIZE || neighbour_y >= MAPSIZE){
                count = count + 1;
            }

            // Otherwise, a normal check of the neighbour
            else if(map.tile[neighbour_x][neighbour_y]){
                count = count + 1;
            }
        }
    }
    return count;
}

void c_map::updateWallStack() {
	for(int i1 = 1; i1 < width - 1; ++i1) {
		for(int i2 = 1; i2 < height - 1; ++i2) {
			if((genIsWall(i1, i2) == false and 
            genIsWall(i1 - 1, i2) == false and
            genIsWall(i1 + 1, i2) == true and
            genIsWall(i1, i2 - 1) == true and
            genIsWall(i1, i2 + 1) == true) or
            (genIsWall(i1, i2) == true and 
            genIsWall(i1 - 1, i2) == true and
            genIsWall(i1 + 1, i2) == false and
            genIsWall(i1, i2 - 1) == true and
            genIsWall(i1, i2 + 1) == true) or 
            (genIsWall(i1, i2) == true and 
            genIsWall(i1 - 1, i2) == true and
            genIsWall(i1 + 1, i2) == true and
            genIsWall(i1, i2 - 1) == false and
            genIsWall(i1, i2 + 1) == true) or
            (genIsWall(i1, i2) == true and 
            genIsWall(i1 - 1, i2) == true and
            genIsWall(i1 + 1, i2) == true and
            genIsWall(i1, i2 - 1) == true and
            genIsWall(i1, i2 + 1) == false)) {
                s_coordinates coord;
                coord.x = x;
                coord.y = y;
                v_genWallStack.push_back(coord);
            }
		}
	}    
}

void c_map::genCleanCorridors() {
    bool found = true;
    while(found == true) {
        found = false;
        for(int i1 = 1; i1 < width - 1; ++i1) {
            for(int i2 = 1; i2 < height - 1; ++i2) {
                if((genIsWall(i1, i2) == false and 
                genIsWall(i1 - 1, i2) == false and
                genIsWall(i1 + 1, i2) == true and
                genIsWall(i1, i2 - 1) == true and
                genIsWall(i1, i2 + 1) == true) or
                (genIsWall(i1, i2) == false and 
                genIsWall(i1 - 1, i2) == true and
                genIsWall(i1 + 1, i2) == false and
                genIsWall(i1, i2 - 1) == true and
                genIsWall(i1, i2 + 1) == true) or 
                (genIsWall(i1, i2) == false and 
                genIsWall(i1 - 1, i2) == true and
                genIsWall(i1 + 1, i2) == true and
                genIsWall(i1, i2 - 1) == false and
                genIsWall(i1, i2 + 1) == true) or
                (genIsWall(i1, i2) == false and 
                genIsWall(i1 - 1, i2) == true and
                genIsWall(i1 + 1, i2) == true and
                genIsWall(i1, i2 - 1) == true and
                genIsWall(i1, i2 + 1) == false)) {
                    genMatrix[i1][i2].tile = genTile::wall1;
                    genMatrix[i1][i2].actor = "";
                    found = true;
                }
            }
        }
    }
}

// Generates a dungeon map
const bool& c_map::genDungeon(const int& rooms) {
/*
    // Clears tile stack (useful to store possible starting tiles for digging rooms)
    v_genWallStack.clear();

    // Fills whole map with wall
    genClear(genTile::wall1);

    // Dig random initial room
    genDigRoom(c_helper::random(1, width - 1), c_helper::random(1, height - 1), c_helper::random(7, 15), c_helper::random(7, 15), c_helper::random(1, 4), false);

    // Update wall stack with new candidates from previous room
    updateWallStack();
    int rounds = 0;
    std::vector<s_coordinates> v_doorTile;

    // Dig room and corridors
    for(int i = 0; i < rooms; ++i) {
        bool ok = false;
        while(ok == false) {

            // Check if max rounds has been reached
            if(rounds > global::maxRounds) {
                genClear(genTile::wall1);
                return false;
            }

            // Choose random tile
            int x = c_helper::random(2, width - 2);
            int y = c_helper::random(2, height - 2);
            int w = 1;
            int h = 1;

            // Check if random tile is wall
            if(genIsWall(x, y) == true) {
        
                // Choose room type (25% room, 75% corridor)
                int roomType = 0;
                if(c_helper::random(0, 100) > 25) {
                    roomType = 1;
                }
                
                // Square room
                if(roomType == 0) {
                    w = c_helper::random(3, 9);
                    h = c_helper::random(3, 9);

                // Corridor
                } else if(roomType == 1) {

                    // Choose direction
                    int corridorDirection = c_helper::random(0, 1);
                    if(corridorDirection == 0) {
                        w = 1;
                        h = c_helper::random(3, 9);
                    } else {
                        w = c_helper::random(3, 9);
                        h = 1; 
                    }                                         
                }
            
                // * Dig room *

                // North
                if(genIsWall(x - 1, y - 1) == true and
                genIsWall(x - 1, y) == true and
                genIsWall(x - 1, y + 1) == false and
                genIsWall(x, y - 1) == true and
                genIsWall(x, y + 1) == false and
                genIsWall(x + 1, y - 1) == true and
                genIsWall(x + 1, y) == true and
                genIsWall(x + 1, y + 1) == false) {
                    ok = genDigRoom(x, y, w, h, direction::north, true);
                }

                // East
                else if(genIsWall(x - 1, y - 1) == false and
                genIsWall(x - 1, y) == false and
                genIsWall(x - 1, y + 1) == false and
                genIsWall(x, y - 1) == true and
                genIsWall(x, y + 1) == true and
                genIsWall(x + 1, y - 1) == true and
                genIsWall(x + 1, y) == true and
                genIsWall(x + 1, y + 1) == true) {
                    ok = genDigRoom(x, y, w, h, direction::east, true);
                }

                // South
                else if(genIsWall(x - 1, y - 1) == false and
                genIsWall(x - 1, y) == true and
                genIsWall(x - 1, y + 1) == true and
                genIsWall(x, y - 1) == false and
                genIsWall(x, y + 1) == true and
                genIsWall(x + 1, y - 1) == false and
                genIsWall(x + 1, y) == true and
                genIsWall(x + 1, y + 1) == true) {
                    ok = genDigRoom(x, y, w, h, direction::south, true);
                }

                // West
                else if(genIsWall(x - 1, y - 1) == true and
                genIsWall(x - 1, y) == true and
                genIsWall(x - 1, y + 1) == true and
                genIsWall(x, y - 1) == true and
                genIsWall(x, y + 1) == true and
                genIsWall(x + 1, y - 1) == false and
                genIsWall(x + 1, y) == false and
                genIsWall(x + 1, y + 1) == false) {
                    ok = genDigRoom(x, y, w, h, direction::west, true);
                }

                // Add door (40% chance)
                if(ok and c_helper::random(0, 100) > 60) {
                    genMatrix[x][y].actor = "door";
                }
            }
            ++rounds;
        }
    }

    // Cleans dead-end corridors
    genCleanCorridors();

    // Renders gen map in real map
    build();
*/
    return true;
}

// Generates a cave map
const bool& c_map::genCave() {

    // Gets cellular map
    genClear("wall_stone");
    s_map celMap = getCellularMap(5, 4, 3, 45);

    for(int i = 0; i < MAPSIZE; ++i) {
        for(int j = 0; j < MAPSIZE; ++j) {
            if(celMap.tile[i][j] == false) {
                genMatrix[i][j].tile = "floor_stone";
            } else {
                genMatrix[i][j].tile = "wall_stone";
            }
        }
    }

    build();

    return true;
}

// Generates a plains map
const bool& c_map::genWild(const int& type) {
/*
    genClear(genTile::floor2);

    // Makes tall grass patches with cellular automata
    if(type != wildernessType::desert) {
        s_map celMap = getCellularMap(5, 4, 3, 45);
        for(int i = 0; i < MAPSIZE; ++i) {
            for(int j = 0; j < MAPSIZE; ++j) {
                if(celMap.tile[i][j] == false) {
                    genMatrix[i][j].tile = genTile::floor3;
                } else {
                    genMatrix[i][j].tile = genTile::floor2;
                }
            }
        }
    }

    build();*/
    return true;
}

// Generates world map
const bool& c_map::genWorld() {

    /*s_map elevationMap;

    // Generates noise
    FastNoise noise;
    noise.SetNoiseType(FastNoise::SimplexFractal);
    noise.SetFrequency(0.03);

    float exponent = 1.60;

    for (int x = 0; x < MAPSIZE; ++x) {
        for (int y = 0; y < MAPSIZE; ++y) {      
                                                    // Rescale from -1.0:+1.0 to 0.0:1.0
            elevationMap.tile[x][y] = pow(noise.GetNoise(x, y) / 2.0 + 0.5, exponent);

            // Sets biomes
            if (elevationMap.tile[x][y] < 0.1) matrix[x][y] -> setAsset(engine -> assetManager.getTileAsset("world_water"));
            else if (elevationMap.tile[x][y] < 0.2) matrix[x][y] -> setAsset(engine -> assetManager.getTileAsset("world_desert"));
            else if (elevationMap.tile[x][y] < 0.3) matrix[x][y] -> setAsset(engine -> assetManager.getTileAsset("world_plains"));
            else if (elevationMap.tile[x][y] < 0.6) matrix[x][y] -> setAsset(engine -> assetManager.getTileAsset("world_forest"));
            else if (elevationMap.tile[x][y] < 0.8) matrix[x][y] -> setAsset(engine -> assetManager.getTileAsset("world_desert"));
            else matrix[x][y] -> setAsset(engine -> assetManager.getTileAsset("world_snow"));
        }
    }*/

    /*static const char *biomeNames[] = {
    "Tundra","Cold desert","Grassland", "Boreal forest",
    "Temperate forest", "Tropical/Montane forest",
    "Hot desert", "Savanna", "Tropical dry forest", "Tropical evergreen forest",
    "Thorn forest"
    };*/

    static const char *biomeNames[] = {
        "world_tundra","world_grassland","world_grassland", "world_taiga",
        "world_temperateForest", "world_temperateForest",
        "world_desert", "world_savanna", "world_jungle", "world_grassland",
        "world_marsh"
    };

    worldGen.generate(NULL);

    for(int i = 0; i < MAPSIZE; ++i) {
        for(int j = 0; j < MAPSIZE; ++j) {
            genMatrix[i][j].tile = biomeNames[worldGen.getBiome(i, j)];
        }
    }

    build();
    return true;
}

// Returns noise in specific location
double c_map::getNoise(double nx, double ny, TCODNoise* noise) {
    float p[2] = {nx, ny};
    return noise -> getFbm(p, 32.0f) / 2.0 + 0.5; // Rescale from -1.0:+1.0 to 0.0:1.0
}

const bool& c_map::genIsFloor(const int& x, const int& y) {
    if(engine -> assetManager.getTileAsset(genMatrix[x][y].tile) -> type == tileType::floor) {
        return true;
    }
    return false;
}

const bool& c_map::genIsWall(const int& x, const int& y) {
    if(engine -> assetManager.getTileAsset(genMatrix[x][y].tile) -> type == tileType::wall) {
        return true;
    }
    return false;
}

// Adds a patch of the specified tile using a cellular automata generated pattern
void c_map::genAddCellularPatch(std::string tile, const int& size) {

    int iterations = 0;
    int birthLimit = 0;
    int deathLimit = 0;
    int chanceToStartAlive = 0;

    // Set generation values depending on size
    switch(size) {
        case size::tiny: {
            iterations = 5;
            birthLimit = 4;
            deathLimit = 3;
            chanceToStartAlive = 45;
            break;
        }
        case size::small: {
            iterations = 4;
            birthLimit = 3;
            deathLimit = 3;
            chanceToStartAlive = 40;
            break;
        }
        case size::medium: {
            iterations = 5;
            birthLimit = 4;
            deathLimit = 3;
            chanceToStartAlive = 45;
            break;
        }
        case size::big: {
            iterations = 5;
            birthLimit = 4;
            deathLimit = 3;
            chanceToStartAlive = 45;
            break;
        }
        case size::huge: {
            iterations = 5;
            birthLimit = 4;
            deathLimit = 3;
            chanceToStartAlive = 45;
            break;
        }
    }

    // Makes cellular map
    s_map celMap = getCellularMap(iterations, birthLimit, deathLimit, chanceToStartAlive);

    // Applies it to the generator map
    for(int i = 0; i < MAPSIZE; ++i) {
        for(int j = 0; j < MAPSIZE; ++j) {
            if(celMap.tile[i][j] == false) {
                genMatrix[i][j].tile = tile;
            }
        }
    }
}

// Plants trees randomly on grass tiles (if dead is true, there is a small chance every round of a dead tree being plant in a dirt tile if found (not implemented yet)
void c_map::genPlantTrees(std::string tree, const int& size, const bool& dead) {

    int trees = 0;
    int maxTrees = 0;
    int x = 0;
    int y = 0;    

    // Tree quantity depends on size parameter
    switch(size) {
        case size::tiny: {
            maxTrees = MAPSIZE / 8 + c_helper::random(0, MAPSIZE / 16) - c_helper::random(0, MAPSIZE / 16);
            break;
        }
        case size::small: {
            maxTrees = MAPSIZE + c_helper::random(0, MAPSIZE / 2) - c_helper::random(0, MAPSIZE / 2);
            break;
        }
        case size::medium: {
            maxTrees = MAPSIZE * 4 + c_helper::random(0, MAPSIZE * 2) - c_helper::random(0, MAPSIZE * 2);
            break;
        }
        case size::big: {
            maxTrees = MAPSIZE * 8 + c_helper::random(0, MAPSIZE * 4) - c_helper::random(0, MAPSIZE * 4);
            break;
        }
        case size::huge: {
            maxTrees = MAPSIZE * 16 + c_helper::random(0, MAPSIZE * 8) - c_helper::random(0, MAPSIZE * 8);
            break;
        }
    }

    while(trees != maxTrees) {
        
        // Gets random position
        x = c_helper::random(1, MAPSIZE - 2); 
        y = c_helper::random(1, MAPSIZE - 2);
        
        // Checks if the position and adjacent tiles are free
        if(genMatrix[x][y].actor == ""
           and genMatrix[x][y - 1].actor == ""
           and genMatrix[x + 1][y - 1].actor == ""
           and genMatrix[x + 1][y].actor == ""
           and genMatrix[x + 1][y + 1].actor == ""
           and genMatrix[x][y + 1].actor == ""
           and genMatrix[x - 1][y + 1].actor == ""
           and genMatrix[x - 1][y].actor == ""
           and genMatrix[x - 1][y - 1].actor == ""
           and genMatrix[x][y].tile != "floor_tallGrass") {
            genMatrix[x][y].actor = tree;
            ++trees;
        }
    }
}

// Places actor in a free random position
void c_map::genPlaceActorSomewhere(std::string actor, const int& quantity, std::string forbiddenTile) {
    
    int actors = 0;

    while(actors != quantity) {
        
        // Gets random position
        x = c_helper::random(1, MAPSIZE - 2); 
        y = c_helper::random(1, MAPSIZE - 2);
        
        // Checks if the position is free and it's not the forbidden tile woah
        if(genMatrix[x][y].actor == "" and genMatrix[x][y].tile != forbiddenTile) {
            genMatrix[x][y].actor = actor;
            ++actors;
        }
    }    
}

void c_map::build() {
    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {

            // Delete previous actor, unless it's the actor
            matrix[x][y] -> removeActors(true);

            // Applies generator map tiles to the real map
            matrix[x][y] -> setAsset(engine -> assetManager.getTileAsset(genMatrix[x][y].tile));

            // Creates actors
            if(genMatrix[x][y].actor != "") {
                engine -> game -> actorManager.createActor(genMatrix[x][y].actor, x, y);
            }
        }
    }
}

// --- ACTOR ---

const bool& c_map::addActorToTile(const int& actor, const int& x, const int& y) {
	if(x < 0 || x > width || y < 0 || y > height) {
		return false;
	}
	matrix[x][y] -> addActor(actor);
	return true;
}

const bool& c_map::removeActorFromTile(const int& actor, const int& x, const int& y) {
    if(x < 0 or x > width or y < 0 or y > height) {
        return false;
    }
    return matrix[x][y] -> removeActor(actor);
}

// Returns a list with the uids of all actors around the tile
std::vector<int> c_map::countActorsAround(const int& x, const int& y) {

    std::vector<int> actorList;

    if(x < 0 or x > width or y < 0 or y > height) {
        return actorList;
    }

    if(x - 1 > 0 and matrix[x - 1][y] -> getActorList().size() > 0) {
        std::vector<int> actorList1 = matrix[x - 1][y] -> getActorList();
        for(int i = 0; i < actorList1.size(); ++i) {
            actorList.push_back(actorList1[i]);
        }
    }
    if(x + 1 < width and matrix[x + 1][y] -> getActorList().size() > 0) {
        std::vector<int> actorList1 = matrix[x + 1][y] -> getActorList();
        for(int i = 0; i < actorList1.size(); ++i) {
            actorList.push_back(actorList1[i]);
        }
    }
    if(y - 1 > 0 and matrix[x][y - 1] -> getActorList().size() > 0) {
        std::vector<int> actorList1 = matrix[x][y - 1] -> getActorList();
        for(int i = 0; i < actorList1.size(); ++i) {
            actorList.push_back(actorList1[i]);
        }
    }
    if(y + 1 < height and matrix[x][y + 1] -> getActorList().size() > 0) {
        std::vector<int> actorList1 = matrix[x][y + 1] -> getActorList();
        for(int i = 0; i < actorList1.size(); ++i) {
            actorList.push_back(actorList1[i]);
        }
    }  

    return actorList;
}

/*/ Returns uid of actor in 1 tile distance, if many, it makes you choose using directional keys
const int& c_map::getActorInRange(const int& x, const int& y, const int& type) {
    std::vector<int> tempList = engine -> game -> map -> countActorsAround(x, y);
    std::vector<int> actorList;

    // We select neraby actors of one type (if no type, all nearby actors are selected)
    if(tempList.size() > 0) {
        for(int i = 0; i < tempList.size(); ++i) {
            if(type == 0) {
                actorList.push_back(tempList[i]);
            } else if(engine -> game -> actorManager.getActor(tempList[i]) -> getType() == type) {
                actorList.push_back(tempList[i]);
            }
        }
    }
    std::cout << "................." << actorList.size() << "............." << tempList.size();
    // We select one actor from the list
    if(actorList.size() > 0) {

        // Only one creature
        if(actorList.size() == 1) {
            return actorList[0];

        // Several creatures
        } else {
            int actor = engine -> interface.selectCloseTarget(imode::game, "Kick", type);
            if(engine -> game -> actorManager.getActor(actor) -> getType() == type) {
                return actor;
            }
        }
    }    
    return 0;
}*/

// Returns uid of first actor of type, if no type first actor
const int& c_map::getActorFromTile(const int& x, const int& y, const int& type) {

    std::vector<int> actorList = getTile(x, y) -> getActorList();
    if(actorList.size() == 0) {
        return 0;
    } else if(type == 0) {
        if(engine -> game -> actorManager.actorExists(actorList[0])) {
            return actorList[0];
        } else {
            return 0;
        }
    }

	for(int i = 0; i < actorList.size(); ++i) {
        if(engine -> game -> actorManager.getActor(actorList[i]) -> getType() == type) {
			if(engine -> game -> actorManager.actorExists(actorList[i])) {
                return actorList[i];
            }
		}
	}
    return 0;
}

// --- FOV ---

std::vector<int> c_map::fov(const int& x, const int& y, const int& viewRange, const bool& isPlayer) {

    std::vector<int> visibleActors;

    if(x < 0 or x > width or y < 0 or y > height) {
        return visibleActors;
    }

    if(isPlayer == true) {

        // Reset last position
        for(int i1 = 0; i1 < viewRange; ++i1) {
            for(int i2 = 0; i2 < viewRange; ++i2) {
                int x1 = oldXFOV - viewRange / 2 + i1;
    			int y1 = oldYFOV - viewRange / 2 + i2;
    			if(x1 >= 0 and y1 >= 0 and x1 <= width - 1 and y1 <= height - 1) {
    				matrix[x1][y1] -> setVisible(false);
                }
            }
        }
        
        // Sets old FOV coordinates
        oldXFOV = x;
        oldYFOV = y;

        // Show starting tile
        matrix[x][y] -> setVisible(true);
        matrix[x][y] -> explore();

    }
    
    // Show viewable tiles
	structFOVMap FOVMap = computeFOV(x, y, viewRange);
	for(int i1 = 0; i1 < viewRange; ++i1) {
		for (int i2 = 0; i2 < viewRange; ++i2) {
			if(FOVMap.val[i1][i2] == true) {
				if(x - viewRange / 2 + i1 >= 0
                and x - viewRange / 2 + i1 < width
                and y - viewRange / 2 + i2 >= 0
                and y - viewRange / 2 + i2 < height
                and c_helper::calculateDistance(x, y, x - viewRange / 2 + i1, y - viewRange / 2 + i2) < (viewRange - 1) / 2) {
                    if(isPlayer == true) {
					   matrix[x - viewRange / 2 + i1][y - viewRange / 2 + i2] -> setVisible(true);
					   matrix[x - viewRange / 2 + i1][y - viewRange / 2 + i2] -> explore();
                    }
                    std::vector<int> actorsInTile = matrix[x - viewRange / 2 + i1][y - viewRange / 2 + i2] -> getActorList();
                    if(actorsInTile.size() != 0) {
                        for(int i = 0; i < actorsInTile.size(); ++i) {
                            visibleActors.push_back(actorsInTile[i]);
                        }
                    }
				}
			}
        }
    }
    
    return visibleActors;
}

// This can possibly be optimized
const structFOVMap& c_map::computeFOV(const int& x, const int& y, const int& viewRange) {
    structFOVMap FOVMap;
    TCODMap* tcodmap;
    tcodmap = new TCODMap(viewRange, viewRange);
    for(int i1 = 0; i1 < viewRange; ++i1) {
        for(int i2 = 0; i2 < viewRange; ++i2) {
            if(x - viewRange / 2 + i1 > 0
            && x - viewRange / 2 + i1 < width
            && y - viewRange / 2 + i2 > 0
            && y - viewRange / 2 + i2 < height) {
                if(matrix[x - viewRange / 2 + i1][y - viewRange / 2 + i2] -> blocksView() == true) {
                    tcodmap -> setProperties(i1, i2, false, false);
                } else {
                    tcodmap -> setProperties(i1, i2, true, true);
                }
            }
        }
    }
    tcodmap -> computeFov(viewRange / 2, viewRange / 2, viewRange, true, FOV_PERMISSIVE_8);
    for(int i1 = 0; i1 < viewRange; ++i1) {
        for(int i2 = 0; i2 < viewRange; ++i2) {
            if(tcodmap -> isInFov(i1, i2)) {
                FOVMap.val[i1][i2] = true;
            } else {
                FOVMap.val[i1][i2] = false;
            }
        }
    }
    delete tcodmap;
    return FOVMap;    
}

void c_map::forget() {
    for(int i1 = 0; i1 < width; ++i1) {
        for(int i2 = 0; i2 < height; ++i2) {
            matrix[i1][i2] -> setExplored(false);
            setProperties(i1, i2, true, true);
        }
    }
}

const bool& c_map::los(int x1, int y1, const int& x2, const int& y2) {
    TCODLine::init(x1, y1, x2, y2);
    do {
        if(matrix[x1][y1] -> blocksView()) {
            return false;
        }
    } while (!TCODLine::step(&x1, &y1));
    return true;
}

// --- GETS ----

c_tile* c_map::getTile(const int& x, const int&y) {
    if(x < 0 or x > width or y < 0 or y > height) {
        return 0;
    }
    return matrix[x][y];
}