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
    c_helper::loadMap(64, 64, 0);
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
        actorManager.getPlayer() -> player -> channel(key, map -> isWorldMap());
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