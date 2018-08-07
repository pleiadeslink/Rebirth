c_game::~c_game() {
    saveMap();
    actorManager.clear();
    if(map) {
        delete map;
    }
}

const bool& c_game::newGame() {

    map = new c_map();
    map -> init();
    loadMap(0, 0, 0);
    actorManager.createActor("avatar", 24, 24);
    return true;
}

const bool& c_game::saveGame() {
    return true;
}

const bool& c_game::loadGame() {
    return true;
}

void c_game::saveMap(const bool& default) {

    if(!map) {
        return;
    }

    TCODZip zip;
    map -> save(&zip);
    actorManager.saveMapActors(&zip);
    std::string filename;
    if(default == true) {
        filename = "data/map/" + std::to_string(map -> getX()) + "." + std::to_string(map -> getY()) + "." + std::to_string(map -> getZ()) + ".map";
    } else {
        filename = "data/save/" + std::to_string(map -> getX()) + "." + std::to_string(map -> getY()) + "." + std::to_string(map -> getZ()) + ".sav";
    }
    zip.saveToFile(filename.c_str());
}

void c_game::loadMap(const int& x, const int& y, const int& z) {

    TCODZip zip;

    // Load saved
    std::string savedFilename = "data/save/" + std::to_string(x) + "." + std::to_string(y) + "." + std::to_string(z) + ".sav";
    if(zip.loadFromFile(savedFilename.c_str())) {
        map -> load(&zip);
        actorManager.loadActors(&zip);
    
    // Load default
    } else {
        std::string defaultFilename = "data/map/" + std::to_string(x) + "." + std::to_string(y) + "." + std::to_string(z) + ".map";
        if(zip.loadFromFile(defaultFilename.c_str())) {
            map -> load(&zip);
            actorManager.loadActors(&zip);
            //map -> create(x, y, z, engine -> assetManager.getMapAsset(x, y, z));
        }
    }
}

void c_game::changeMap(const int& x, const int& y, const int& z, const int& playerX, const int& playerY) {
    
    if(!map) {
        return;
    }

    saveMap();
    actorManager.savePlayer();
    actorManager.clear();
    map -> wipe(x, y, z);
    loadMap(x, y, z);
    actorManager.loadPlayer();
    c_helper::teleportActor(actorManager.getPlayer() -> getUid(), playerX, playerY);
}

void c_game::resetMap() {
    
    if(!map) {
        return;
    }

    actorManager.clear();
    std::string defaultFilename = "data/map/" + std::to_string(map -> getX()) + "." + std::to_string(map -> getY()) + "." + std::to_string(map -> getZ()) + ".map";
    TCODZip zip;
    if(zip.loadFromFile(defaultFilename.c_str())) {
        map -> load(&zip);
    }
}

void c_game::update(const int& key) {
    if(!actorManager.getPlayer() or !actorManager.getPlayer() -> action or !actorManager.getPlayer() -> player) {
        return;
    }

    gamelog.clear();

    // If the player is doing something, update time till he finishes
    if(actorManager.getPlayer() -> action -> isRunning()) {
        do {
            
            // Update player
            actorManager.getPlayer() -> timeUpdate();
            
            // Update active actors
            actorManager.timeUpdate();

        } while(actorManager.getPlayer() -> action -> isRunning());

    // If he's not, check if he can channel the human player
    } else {
        actorManager.getPlayer() -> player -> channel(key);
    }

    gamelog.update();
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