c_game::~c_game() {
    c_helper::saveMap();
    actorManager.clear();
    if(map) {
        delete map;
    }
}

const bool& c_game::newGame() {

    // Creates map
    map = new c_map();
    map -> init();

    // Creates world map 
    world = new s_worldTile*[MAPSIZE]; // ! I don't like this at all!
	for(int i = 0; i < MAPSIZE; ++i)
		world[i] = new s_worldTile[MAPSIZE];
    for(int i1 = 0; i1 < MAPSIZE; ++i1) {
        for(int i2 = 0; i2 < MAPSIZE; ++i2) {
            world[i1][i2].biome = biome::grassland;
            world[i1][i2].danger = 0;
        }
    }
    updateWorld();

    // Loads initial map
    loadMap(0, 0, 0);
    actorManager.createActor("avatar", 2, 2);
    c_helper::teleportActor(actorManager.getPlayer() -> getUid(), 2, 2, true);
    engine -> sound.playAmbience(engine -> game -> map -> getAmbience());
    return true;
}

const bool& c_game::saveGame() {
    return true;
}

const bool& c_game::loadGame() {
    return true;
}

// Tries to load from saved file, or static map, or generates it
void c_game::loadMap(const int& x, const int& y, const int& z) {
	if(!map) {
		return;
	}

	TCODZip zip;
    map -> wipe(x, y, z);

	// * LOAD SAVED
    std::string savedFilename = "data/save/" + std::to_string(x) + "." + std::to_string(y) + "." + std::to_string(z) + ".sav";
    if(zip.loadFromFile(savedFilename.c_str())) {
        map -> load(&zip);
		actorManager.loadActors(&zip);
		return;
	}

	// * lOAD STATIC
    std::string staticFilename = "data/world";
    if(zip.loadFromFile(staticFilename.c_str())) {
        map -> load(&zip);
		actorManager.loadActors(&zip);
		return;
	}
	
	// * GENERATE MAP
	// World map
	if(x == 0 and y == 0 and z == 0) {
        //map -> genWorld();
        map -> parse("data/world.txt");  
	// Local map
	} else {
		if(getWorldTile(x, y).biome == biome::grassland) {
			engine -> runScript("gen/grassland.lua");
		} else if(getWorldTile(x, y).biome == biome::temperateForest) {
			engine -> runScript("gen/temperateForest.lua");
		} else if(getWorldTile(x, y).biome == biome::taiga) {
			engine -> runScript("gen/taiga.lua");
		} else if(getWorldTile(x, y).biome == biome::jungle) {
			engine -> runScript("gen/jungle.lua");
		} else if(getWorldTile(x, y).biome == biome::desert) {
			engine -> runScript("gen/desert.lua");
		} else if(getWorldTile(x, y).biome == biome::savanna) {
			engine -> runScript("gen/savanna.lua");
		} else if(getWorldTile(x, y).biome == biome::marsh) {
			engine -> runScript("gen/marsh.lua");
		} else if(getWorldTile(x, y).biome == biome::tundra) {
			engine -> runScript("gen/tundra.lua");
		}
	}

	// We set the coords
	map -> setX(x);
	map -> setY(y);
	map -> setZ(z);

	engine -> game -> map -> build();     // ? Useless??
}

// Updates world from map 0.0.0
// ! Careful with this shit because the world map is created with defines, but here it will be related to the stored map created with the stored dimensions
// I mean, it's all ok if all maps share the same size, which is what I should probably do anyways
void c_game::updateWorld() {

    TCODZip zip;
    std::string defaultFilename = "data/map/0.0.0.map";

    // First we need to load a temporal map with the info from 0.0.0
    if(zip.loadFromFile(defaultFilename.c_str())) {

        typedef struct s_temp {
            std::string tile;
            std::vector<std::string> v_actor;
        };
        const int width = zip.getInt();;
        const int height = zip.getInt();
        s_temp tempMap[MAPSIZE][MAPSIZE];
        
        for(int i1 = 0; i1 < width; ++i1) {
            for(int i2 = 0; i2 < height; ++i2) {

                // We assign the tile from the data file
                tempMap[i1][i2].tile = zip.getString();

                // We need to do this to respect the order of the stored data
                zip.getInt(); 
            }
        }

        // Again, we need to do this to respect the order of the stored data
        zip.getInt();
        zip.getInt();
        zip.getInt();
        zip.getString();
        zip.getString();

        // We load the actors
        int size = zip.getInt();
        if(size > 0) {
            for(int i = 0; i < size; ++i) {

                std::string id = zip.getString();
                int x = zip.getInt();
                int y = zip.getInt();
                int actor = actorManager.createActor(id, x, y); // We need to create the actor so that it loads and respect the data file...
                actorManager.getActor(actor) -> load(&zip);
                actorManager.deleteActor(actor); // We delete the actor and make sure nobody saw us

                // We add the actor to its tile in the temp map
                tempMap[x][y].v_actor.push_back(id);
            }
        }

        // All right, so we have a temporal map with tile ids and actor vectors
        // Now here goes the meat, it's what everyone was waiting for, you, your mother, everyone
        // We choose biome depending on tile type, actor, etc. 
        
        // Well actually we will only use the actors to check for locations
        
        for(int i = 0; i < width; ++i) {
            for(int j = 0; j < height; ++j) {

                // GRASSLAND (default)
                world[i][j].biome = biome::grassland;
                world[i][j].danger = 0;

                // Look for locations
                if(tempMap[i][j].v_actor.size() != 0) {
                    for(int k = 0; k < tempMap[i][j].v_actor.size(); ++k) {
                        if(engine -> assetManager.getActorAsset(tempMap[i][j].v_actor[k]) -> type == actorType::location) {
                            world[i][j].biome = biome::location;
                        } 
                    }
                }

                // Select biome by tile

                // MOUNTAIN
                if(tempMap[i][j].tile == "world_mountain") {
                    world[i][j].biome = biome::mountain;
                }

                // TEMPERATE FOREST
                if(tempMap[i][j].tile == "world_temperateForest") {
                    world[i][j].biome = biome::temperateForest;
                }

                // TAIGA
                if(tempMap[i][j].tile == "world_taiga") {
                    world[i][j].biome = biome::taiga;
                }

                // JUNGLE  
                if(tempMap[i][j].tile == "world_jungle") {
                    world[i][j].biome = biome::jungle;
                }

                // DESERT   
                if(tempMap[i][j].tile == "world_desert") {
                    world[i][j].biome = biome::desert;
                }

                // SAVANNA
                if(tempMap[i][j].tile == "world_savanna") {
                    world[i][j].biome = biome::savanna;
                }

                // MARSH
                if(tempMap[i][j].tile == "world_marsh") {
                    world[i][j].biome = biome::marsh;
                }              

                // TUNDRA
                if(tempMap[i][j].tile == "world_tundra") {
                    world[i][j].biome = biome::tundra;
                }

                // OCEAN
                if(tempMap[i][j].tile == "world_ocean") {
                    world[i][j].biome = biome::ocean;
                }
            }
        }
        engine -> message("World updated!");
    } else {
        engine -> message("World update failed because map 0.0.0 was not found.");
    }
}

// Returns the biome of the selected location of the world map
int c_game::getBiome(const int& x, const int& y) {
    if(x > 0 and y > 0 and x < MAPSIZE and y < MAPSIZE) {
        return world[x][y].biome;
    }
}

void c_game::update(const int& key) {
    if(!actorManager.getPlayer() or !actorManager.getPlayer() -> action or !actorManager.getPlayer() -> player) {
        return;
    }

    gamelog.clear();

    // If the player is doing something, update time till he finishes
    if(actorManager.getPlayer() -> action -> isRunning()) {
        turn();

    // If he's not, check if he can channel the human player
    } else {
        actorManager.getPlayer() -> player -> channel(key);
    }

    gamelog.update();
}

// Runs turns till the player finishes his action
void c_game::turn() {
    if(!actorManager.getPlayer() -> action -> isRunning()) {
        return;
    }

    do {
        // Update player
        actorManager.getPlayer() -> timeUpdate();
        
        // Update active actors
        actorManager.timeUpdate();

    } while(actorManager.getPlayer() -> action -> isRunning());
}

// Prints a message in the game console
void c_game::message(std::string text) {
    gamelog.message(text);
}

bool c_game::runScript(structEventData& data) {  
    std::string path = data.type + ".lua";
    c_engine::runScript(path, data);
    return false;
}

bool c_game::runEvent(structEventData& data) {  
    if(!engine -> game -> map) {
        return false;
    }
    std::string path = "event/" + data.type + ".lua";
    c_engine::runScript(path, data);
    return false;
}

bool c_game::runEffect(structEventData& data) {  
    if(!engine -> game -> map) {
        return false;
    }
    std::string path = "effect/" + data.type + ".lua";
    c_engine::runScript(path, data);
    return false;
}

s_worldTile c_game::getWorldTile(const int& x, const int& y) {
    if(x >= 0 and y >= 0 and x <= MAPSIZE and y <= MAPSIZE) {
        return world[x][y];
    }
    return world[0][0];
}