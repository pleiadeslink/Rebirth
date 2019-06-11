c_game::~c_game() {
    c_helper::saveMap();
    actorManager.clear();
    if(map) {
        delete map;
    }
}

const bool& c_game::newGame() {

    map = new c_map();
    map -> init();
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
void updateWorld() {

    TCODZip zip;
    std::string defaultFilename = "data/map/0.0.0.map";
    if(zip.loadFromFile(defaultFilename.c_str())) {

        // Load dimension
        int width = zip.getInt();;
        int height = zip.getInt();

        // Load map tiles 
        for(int i1 = 0; i1 < width; ++i1) {
            for(int i2 = 0; i2 < height; ++i2) {
                zip.getString();
                zip.getInt(); // Explored flag
            }
        }
    } else {
        engine -> message("World update failed because map 0.0.0 was not found.");
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