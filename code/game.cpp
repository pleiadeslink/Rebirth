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
    c_helper::loadMap(0, 0, 0);
    actorManager.createActor("avatar", 24, 24);
    c_helper::teleportActor(actorManager.getPlayer() -> getUid(), 24, 24, true);
    engine -> sound.playAmbience(engine -> game -> map -> getAmbience());
    return true;
}

const bool& c_game::saveGame() {
    return true;
}

const bool& c_game::loadGame() {
    return true;
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
        // We choose biome depending on tile type, actor, etc. (for example, if we find a certain tree, we select certain biome, etc)
        for(int i = 0; i < width; ++i) {
            for(int j = 0; j < height; ++j) {

                // BOREAL FOREST
                if(tempMap[i][j].v_actor.size() != 0) {
                    for(int k = 0; k < tempMap[i][j].v_actor.size(); ++k) {
                        if(tempMap[i][j].v_actor[k] == "pineTree") {
                            world[i][j].biome = biome::borealForest;
                        }
                    }
                }
            }
        }
    } else {
        engine -> message("World update failed because map 0.0.0 was not found.");
    }
    engine -> message("World updated!");
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