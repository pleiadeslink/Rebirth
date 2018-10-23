c_map::c_map() 
: TCODMap(global::mapSize, global::mapSize),
  name("The Void"),
  x(0),
  y(0),
  z(0),
  width(global::mapSize),
  height(global::mapSize),
  oldXFOV(0),
  oldYFOV(0),
  selectedTileX(0),
  selectedTileY(0) {
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
    this -> width = global::mapSize;
    this -> height = global::mapSize;
    this -> oldXFOV = 0;
    this -> oldYFOV = 0;
    selectedTileX = 0;
    selectedTileY = 0;
    genFloor1 = "floor_grass";
    genFloor2 = "floor_grass";
    genFloor3 = "floor_grass";
    genWall1 = "wall_rock";
    genWall2 = "wall_rock";
    genWall3 = "wall_rock";

    // Creates initial matrix
    createMatrix();
    createGenMatrix();
    fill(engine -> assetManager.getTileAsset("floor_grass"));
}

void c_map::save(TCODZip* zip) {

    // Save map info
    zip -> putString(name.c_str());
    zip -> putInt(x);
    zip -> putInt(y);
    zip -> putInt(z);
    zip -> putInt(width);
    zip -> putInt(height);

    // Save map tiles 
    for(int i1 = 0; i1 < width; ++i1) {
        for(int i2 = 0; i2 < height; ++i2) {
            zip -> putString(matrix[i1][i2].getId().c_str());
        }
    }
}

void c_map::load(TCODZip* zip) {

    name = zip -> getString();
    x = zip -> getInt();
    y = zip -> getInt();
    z = zip -> getInt();
    width = zip -> getInt();;
    height = zip -> getInt();

    // Load map tiles 
    for(int i1 = 0; i1 < width; ++i1) {
        for(int i2 = 0; i2 < height; ++i2) {
            matrix[i1][i2].setAsset(engine -> assetManager.getTileAsset(zip -> getString()));
        }
    }
}

void c_map::wipe(const int& x, const int& y, const int& z) {
    for(int i1 = 0; i1 < width; ++i1) {
        for(int i2 = 0; i2 < height; ++i2) {
            matrix[i1][i2].wipe(engine -> assetManager.getTileAsset("floor_grass"));
        }
    }
    this -> x = x;
    this -> y = y;
    this -> z = z;
}

TCODPath* c_map::path(const int& x0, const int& y0, const int& x1, const int& y1) {
    TCODPath* path = new TCODPath(this); // Second value is the diagonal cost

    // The origin and destination tile is set as walkable temporarily for the path to compute
    //setProperties(x0, y0, true, true);
    bool wasObstacle = false;
    if(matrix[x1][y1].isObstacle() == true) {
        setProperties(x1, y1, true, true);
        wasObstacle = true;
    }

    path -> compute(x0, y0, x1, y1);

    //setProperties(x0, y0, false, false);
    if(wasObstacle == true) {
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
    return &matrix[dx][dy];
}

void c_map::addScript(s_script script) {
    v_script.push_back(script);
}

// --- BUILD ---

void c_map::createMatrix() {
   	matrix = new c_tile*[width];
	for(int i = 0; i < width; ++i)
		matrix[i] = new c_tile[height];
    for(int i1 = 0; i1 < width; ++i1) {
        for(int i2 = 0; i2 < height; ++i2) {
            matrix[i1][i2].setCoords(i1, i2);
            matrix[i1][i2].setAsset(engine -> assetManager.getTileAsset("floor_grass"));
        }
    }
}

void c_map::createGenMatrix() {
   	genMatrix = new structGenTile*[width];
	for(int i = 0; i < width; ++i)
		genMatrix[i] = new structGenTile[height];
    for(int i1 = 0; i1 < width; ++i1) {
        for(int i2 = 0; i2 < height; ++i2) {
            genMatrix[i1][i2].tile = 0;
            genMatrix[i1][i2].actor = "";
        }
    }
}

void c_map::fill(const structTileAsset* asset) {
	for(int i1 = 0; i1 < width; ++i1) {
		for(int i2 = 0; i2 < height; ++i2) {
			matrix[i1][i2].setAsset(asset);
		}
	}
}

void c_map::flood(const structTileAsset* asset, const int& x, const int& y) {
    for(int i1 = 0; i1 < width; ++i1) {
        for(int i2 = 0; i2 < height; ++i2) {
            matrix[i1][i2].setCheck(false);
        }
    }
    floodAux(asset, x, y);
}

void c_map::floodAux(const structTileAsset* asset, const int& x, const int& y) {
    if(x >= 0 and x < width and y >= 0 and y < height
    and matrix[x][y].getType() != tileType::wall and matrix[x][y].getCheck() == false) {
        matrix[x][y].setAsset(asset);
        matrix[x][y].setInterior(true); // DELETE
        matrix[x][y].setCheck(true);
    }
    else {
        return;
    }
    floodAux(asset, x + 1, y);
    floodAux(asset, x - 1, y);
    floodAux(asset, x, y + 1);
    floodAux(asset, x, y - 1);
}

void c_map::genClear(const int& tile) {
	for(int i1 = 0; i1 < width; ++i1) {
		for(int i2 = 0; i2 < height; ++i2) {
			genMatrix[i1][i2].tile = tile;
            genMatrix[i1][i2].actor = "";
		}
	}
}

void c_map::genCastle(const int& rooms) {
    
    // Pick up a random wall tile
    bool wallFound = false;
    while(wallFound == false) {
        int x = c_helper::random(0, width);
        int y = c_helper::random(0, height);
    }
}

void c_map::build() {
    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            // Delete previous actor, unless it's the actor
            matrix[x][y].removeActors(true);

            // Applies generator tiles to the real matrix
            std::cout << genMatrix[x][y].tile << genFloor2 << std::endl;
            switch(genMatrix[x][y].tile) {
                case genTile::floor1: {
                    matrix[x][y].setAsset(engine -> assetManager.getTileAsset(genFloor1));
                    break;
                }
                case genTile::floor2: {
                    matrix[x][y].setAsset(engine -> assetManager.getTileAsset(genFloor2));
                    break;
                }
                case genTile::floor3: {
                    matrix[x][y].setAsset(engine -> assetManager.getTileAsset(genFloor3));
                    break;
                }
                case genTile::wall1: {
                    matrix[x][y].setAsset(engine -> assetManager.getTileAsset(genWall1));
                    break;
                }
                case genTile::wall2: {
                    matrix[x][y].setAsset(engine -> assetManager.getTileAsset(genWall2));
                    break;
                }
                case genTile::wall3: {
                    matrix[x][y].setAsset(engine -> assetManager.getTileAsset(genWall3));
                    break;
                }
                case genTile::water: {
                    matrix[x][y].setAsset(engine -> assetManager.getTileAsset("water"));
                    break;
                }
                case genTile::lava: {
                    matrix[x][y].setAsset(engine -> assetManager.getTileAsset("lava"));
                    break;
                }
            }
        }
    }
}

// --- ACTOR ---

const bool& c_map::addActorToTile(const int& actor, const int& x, const int& y) {
	if(x < 0 || x > width || y < 0 || y > height) {
		return false;
	}
	matrix[x][y].addActor(actor);
	return true;
}

const bool& c_map::removeActorFromTile(const int& actor, const int& x, const int& y) {
    if(x < 0 or x > width or y < 0 or y > height) {
        return false;
    }
    return matrix[x][y].removeActor(actor);
}

std::vector<int> c_map::countActorsAround(const int& x, const int& y) {

    std::vector<int> actorList;

    if(x < 0 or x > width or y < 0 or y > height) {
        return actorList;
    }

    if(x - 1 > 0 and matrix[x - 1][y].getActorList().size() > 0) {
        std::vector<int> actorList1 = matrix[x - 1][y].getActorList();
        for(int i = 0; i < actorList1.size(); ++i) {
            actorList.push_back(actorList1[i]);
        }
    }
    if(x + 1 < width and matrix[x + 1][y].getActorList().size() > 0) {
        std::vector<int> actorList1 = matrix[x + 1][y].getActorList();
        for(int i = 0; i < actorList1.size(); ++i) {
            actorList.push_back(actorList1[i]);
        }
    }
    if(y - 1 > 0 and matrix[x][y - 1].getActorList().size() > 0) {
        std::vector<int> actorList1 = matrix[x][y - 1].getActorList();
        for(int i = 0; i < actorList1.size(); ++i) {
            actorList.push_back(actorList1[i]);
        }
    }
    if(y + 1 < height and matrix[x][y + 1].getActorList().size() > 0) {
        std::vector<int> actorList1 = matrix[x][y + 1].getActorList();
        for(int i = 0; i < actorList1.size(); ++i) {
            actorList.push_back(actorList1[i]);
        }
    }  

    return actorList;
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
    				matrix[x1][y1].setVisible(false);
                }
            }
        }
        
        // Sets old FOV coordinates
        oldXFOV = x;
        oldYFOV = y;

        // Show starting tile
        matrix[x][y].setVisible(true);
        matrix[x][y].explore();

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
					   matrix[x - viewRange / 2 + i1][y - viewRange / 2 + i2].setVisible(true);
					   matrix[x - viewRange / 2 + i1][y - viewRange / 2 + i2].explore();
                    }
                    std::vector<int> actorsInTile = matrix[x - viewRange / 2 + i1][y - viewRange / 2 + i2].getActorList();
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

    // Copies real map to tcodmap
    for(int i1 = 0; i1 < viewRange; ++i1) {
        for(int i2 = 0; i2 < viewRange; ++i2) {
            if(x - viewRange / 2 + i1 > 0
            && x - viewRange / 2 + i1 < width
            && y - viewRange / 2 + i2 > 0
            && y - viewRange / 2 + i2 < height) {
                bool actorBlocksView = false;
                std::vector<int> actorsInTile = matrix[x - viewRange / 2 + i1][y - viewRange / 2 + i2].getActorList();
                if(actorsInTile.size() != 0) {
                    for(int i = 0; i < actorsInTile.size(); ++i) {
                            if(engine -> game -> actorManager.getActor(actorsInTile[i]) -> body and !engine -> game -> actorManager.getActor(actorsInTile[i]) -> body -> getCanView()) {
                                actorBlocksView = true;
                            }
                        }
                    }
                if(matrix[x - viewRange / 2 + i1][y - viewRange / 2 + i2].getType() == tileType::wall
                or matrix[x - viewRange / 2 + i1][y - viewRange / 2 + i2].getType() == tileType::obstacle
                or actorBlocksView == true) {
                    tcodmap -> setProperties(i1, i2, false, false);
                } else {
                    tcodmap -> setProperties(i1, i2, true, true);
                }
            }
        }
    }
    
    // Computes fov
    tcodmap -> computeFov(viewRange / 2, viewRange / 2, viewRange, true, FOV_SHADOW);
    
    // Copies tcodmap to fovmap
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


// --- GETS ----

c_tile* c_map::getTile(const int& x, const int&y) {
    if(x < 0 or x > width or y < 0 or y > height) {
        return 0;
    }
    return &matrix[x][y];
}