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
    c_helper::loadMap(1, 1, 0);
    actorManager.createActor("avatar", 24, 24);
    c_helper::teleportActor(actorManager.getPlayer() -> getUid(), 24, 24, true);
    return true;
}

const bool& c_game::saveGame() {
    return true;
}

const bool& c_game::loadGame() {
    return true;
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
        actorManager.getPlayer() -> player -> channel(key, map -> isWorldMap());
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