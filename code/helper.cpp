std::vector<std::string> c_helper::split(const std::string& s, char delimiter) {
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter)) {
      tokens.push_back(token);
   }
   return tokens;	
}

int c_helper::random(const int& min, const int& max) {
    TCODRandom* ran = TCODRandom::getInstance();
    return ran -> getInt(min, max);
}

// Splits a string into seperate strings using the pattern string as line break symbol
std::vector<std::string> c_helper::splitter(std::string in_pattern, std::string& content) {
    std::vector<std::string> split_content;
    std::regex pattern(in_pattern);
    copy(std::sregex_token_iterator(content.begin(), content.end(), pattern, -1), std::sregex_token_iterator(), back_inserter(split_content));  
    return split_content;
}

/*/ Justify text adding \n
std::string c_helper::justify(std::string string, const size_t size) {
    int iterator = 0;
	for(int i = 0; i < string.length(); ++i) {
		if(string.at(i) == ' ' and iterator >= size) {
			iterator = 0;
			string.erase(i,1); // Deletes space
			string.insert(i, "\n"); // Adds line break
		}
		++iterator;
	}
    return string;
}*/

// Justify text adding \n
std::string c_helper::justify(std::string string, const size_t size) {
	int iterator = 0;
	for(int i = 0; i < string.length(); ++i) {
		if(iterator == size) {
			for(int j = 0; j < size; ++j) {
				if(string.at(i - j) == ' ') {
					iterator = 0;
					string.erase(i - j, 1); // Deletes space
					string.insert(i - j, "\n"); // Adds line break
					break;
				}
			}	
		}
		++iterator;
	}
    return string;
}

// Logs a game message
void c_helper::message(const std::string& text) {
	
	// Sends message to the system log
	engine -> message("Game: " + text);

	// Sends message to the game log
	if(engine -> game) {
		engine -> game -> message(text);
	}
}

// Refresh gamelog force pushing all buffer
void c_helper::updateGamelog() {
	if(engine -> game) {
		engine -> game -> gamelog.update();
	}
}

// Changes between window and fullscreen mode
void c_helper::toggleFullScreen() {
	if(engine -> screen.isFullScreen() == true) {
		engine -> screen.start(false);
	} else {
		engine -> screen.start(true);
	}
}

void c_helper::talk(const int& actor) {
	engine -> interface.talk(actor);
}

void c_helper::playAmbience(std::string track) {
	engine -> sound.playAmbience(track);
}

void c_helper::showMapInfo() {
	if(!engine -> game or !engine -> game -> map) {
		return;
	}
	std::ostringstream s;
	s << "Map x: " << engine -> game -> map -> getX() << " | Map x: " << engine -> game -> map -> getY() << " | Map z: " << engine -> game -> map -> getZ();
	message(s.str());
}

void c_helper::loadMap(const int& x, const int& y, const int& z) { // ! Move these to map class no?
	if(!engine -> game or !engine -> game -> map) {
		return;
	}

	TCODZip zip;
    engine -> game -> map -> wipe(x, y, z);


	// * LOAD SAVED
	
    std::string savedFilename = "data/save/" + std::to_string(x) + "." + std::to_string(y) + "." + std::to_string(z) + ".sav";
    if(zip.loadFromFile(savedFilename.c_str())) {
        engine -> game -> map -> load(&zip);
		engine -> game -> actorManager.loadActors(&zip);
		return;
	}


	// * lOAD STATIC
    
	// Load static
    std::string staticFilename = "data/map/" + std::to_string(x) + "." + std::to_string(y) + "." + std::to_string(z) + ".map";
    if(zip.loadFromFile(staticFilename.c_str())) {
        engine -> game -> map -> load(&zip);
		engine -> game -> actorManager.loadActors(&zip);
		return;
	}
	
	
	// * GENERATE MAP

	//s_worldTile = engine -> game -> getWorldTile(x, y); // This needs to include already the biome file, world map needs to be informed when its created from data files + 0.0.0 map
	// For now we say we know already the path file -- WHAT THE FUCK DID I MEAN HERE?
	std::cout << x << y << z << std::endl;
	// World map
	if(x == 0 and y == 0 and z == 0) {
		std::cout << "what?" << std::endl;
		engine -> game -> map -> genWorld();

	// Local map
	} else {
		if(engine -> game -> getWorldTile(x, y).biome == biome::grassland) {
			engine -> runScript("gen/grassland.lua");
		} else if(engine -> game -> getWorldTile(x, y).biome == biome::temperateForest) {
			engine -> runScript("gen/temperateForest.lua");
		} else if(engine -> game -> getWorldTile(x, y).biome == biome::taiga) {
			engine -> runScript("gen/taiga.lua");
		} else if(engine -> game -> getWorldTile(x, y).biome == biome::jungle) {
			engine -> runScript("gen/jungle.lua");
		} else if(engine -> game -> getWorldTile(x, y).biome == biome::desert) {
			engine -> runScript("gen/desert.lua");
		} else if(engine -> game -> getWorldTile(x, y).biome == biome::savanna) {
			engine -> runScript("gen/savanna.lua");
		} else if(engine -> game -> getWorldTile(x, y).biome == biome::marsh) {
			engine -> runScript("gen/marsh.lua");
		} else if(engine -> game -> getWorldTile(x, y).biome == biome::tundra) {
			engine -> runScript("gen/tundra.lua");
		}
	}

	// We set the coords
	engine -> game -> map -> setX(x);
	engine -> game -> map -> setY(y);
	engine -> game -> map -> setZ(z);
	
	engine -> game -> map -> build();
}

// Saves as default map if parameter is true
void c_helper::saveMap(const bool& default) {
	if(!engine -> game or !engine -> game -> map) {
		return;
	}

    TCODZip zip;
    engine -> game -> map -> save(&zip);
    engine -> game -> actorManager.saveMapActors(&zip);
    std::string filename;
    if(default == true) {
        filename = "data/map/" + std::to_string(engine -> game -> map -> getX()) + "." + std::to_string(engine -> game -> map -> getY()) + "." + std::to_string(engine -> game -> map -> getZ()) + ".map";
    } else {
        filename = "data/save/" + std::to_string(engine -> game -> map -> getX()) + "." + std::to_string(engine -> game -> map -> getY()) + "." + std::to_string(engine -> game -> map -> getZ()) + ".sav";
    }
    zip.saveToFile(filename.c_str());
	return;
}

void c_helper::changeMap(const int& x, const int& y, const int& z, int startX, int startY) {
	if(!engine -> game or !engine -> game -> map) {
		return;
	}
	engine -> setLoading(true);
	engine -> screen.clear();
    engine -> interface.draw();
    engine -> screen.display();
	engine -> interface.setTileDestination(0);
    saveMap(false);
    //engine -> game -> actorManager.savePlayer();
    engine -> game -> actorManager.clear();
    loadMap(x, y, z);
	//engine -> game -> actorManager.loadPlayer();
	if(startX == 0 and startY == 0) { // If starting position tile is empty, we teleport to the middle of the map
		startX = engine -> game -> map -> getWidth() / 2;
		startY = engine -> game -> map -> getHeight() / 2;
	}
	teleportActor(engine -> game -> actorManager.getPlayer() -> getUid(), startX, startY, true);
	engine -> sound.playAmbience(engine -> game -> map -> getAmbience());
	engine -> setLoading(false);

}

void c_helper::worldMap(const int& mapX, const int& mapY) {
    if(!engine -> game or !engine -> game -> map) {
        return;
    }
	engine -> setLoading(true);
	engine -> screen.clear();
    engine -> interface.draw();
    engine -> screen.display();
	engine -> interface.setTileDestination(0);

    saveMap(false);
    //engine -> game -> actorManager.savePlayer();
	
    engine -> game -> actorManager.clear();

    loadMap(0, 0, 0);
    //engine -> game -> actorManager.loadPlayer();
    teleportActor(engine -> game -> actorManager.getPlayer() -> getUid(), mapX, mapY, true);
	//engine -> sound.playAmbience(engine -> game -> map -> getAmbience());
	engine -> setLoading(false);
}

// Returns true if it finds a location actor in the tile
const bool& c_helper::isLocation(const int& x, const int& y) {
	if(!engine -> game or !engine -> game -> map) {
		return false;
	}
	// Check if there's a location there
	std::vector<int> actorList = engine -> game -> map -> getTile(x, y) -> getActorList();
	for(int i = 0; i < actorList.size(); ++i) {
		
		if(engine -> game -> actorManager.getActor(actorList[i]) -> getType() == actorType::location) {
			return true;
		}
	}
	return false;
}

const bool& c_helper::isWorldMap() {
    if(!engine -> game or !engine -> game -> map) {
        return false;
    }
	if(engine -> game -> map -> getX() == 0 and engine -> game -> map -> getY() == 0) {
		return true;
	}
	return false;
}

void c_helper::resetMap() {
    if(!engine -> game or !engine -> game -> map) {
        return;
    }

    engine -> game -> actorManager.clear();
    std::string defaultFilename = "data/map/" + std::to_string(engine -> game -> map -> getX()) + "." + std::to_string(engine -> game -> map -> getY()) + "." + std::to_string(engine -> game -> map -> getZ()) + ".map";
    TCODZip zip;
    if(zip.loadFromFile(defaultFilename.c_str())) {
        engine -> game -> map -> load(&zip);
    }
}

void c_helper::createMapScript(std::string command, const bool& autodelete) {
	if(!engine -> game or !engine -> game -> map) {
		return;
	}
	s_script script;
	script.command = command;
	script.autodelete = autodelete;
	engine -> game -> map -> addScript(script);
	engine -> interface.setEditScript(1);
}

const int& c_helper::calculateDistance(const int& x1, const int& y1, const int& x2, const int& y2) {
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

const int&  c_helper::getMapSeed() {
    if(!engine -> game or !engine -> game -> map) {
    	return 0;
    }
    return engine -> game -> map -> getRandomSeed();
}

const int& c_helper::getMapWidth() {
    if(!engine -> game or !engine -> game -> map) {
    	return 0;
    }
    return engine -> game -> map -> getWidth();
}

const int& c_helper::getMapHeight() {
    if(!engine -> game or !engine -> game -> map) {
    	return 0;
    }
    return engine -> game -> map -> getHeight();
}

const int& c_helper::getMapX() {
    if(!engine -> game or !engine -> game -> map) {
    	return 0;
    }
    return engine -> game -> map -> getX();
}

const int& c_helper::getMapY() {
    if(!engine -> game or !engine -> game -> map) {
    	return 0;
    }
    return engine -> game -> map -> getY();
}

const int& c_helper::getMapZ() {
    if(!engine -> game or !engine -> game -> map) {
    	return 0;
    }
    return engine -> game -> map -> getZ();
}

// Returns true if the tile in location has the same name as parameter
const bool& c_helper::findTileByName(const int& x, const int& y, std::string name) {
    if(!engine -> game or !engine -> game -> map) {
    	return false;
	}
	if(engine -> game -> map -> getTile(x, y) -> getId() == name) {
		return true;
	}
	return false;
}

const int& c_helper::genClear(const int& value) {
	if(!engine -> game or !engine -> game -> map) {
		return 0;
	}
	engine -> game -> map -> genClear(value);
	return 0;
}

const bool& c_helper::genDigRoom(const int& x0, const int& y0, const int& width, const int& height, const int& direction, const bool& digStartingTile) {
	if(!engine -> game or !engine -> game -> map) {
		return false;
	}
	return engine -> game -> map -> genDigRoom(x0, y0, width, height, direction, digStartingTile);
}

const bool& c_helper::genDungeon(const int& value) {
	if(!engine -> game or !engine -> game -> map) {
		return false;
	}
	message("Generating dungeon...");
	for(int i = 0; i < 100; ++i) {
		if(engine -> game -> map -> genDungeon(value) == true) {
			c_helper::message("OK");
			return true;
		}
	}
	c_helper::message("FAIL");
	return false;
}

const bool& c_helper::genCave() {
	if(!engine -> game or !engine -> game -> map) {
		return false;
	}
	message("Generating cave...");
	for(int i = 0; i < 100; ++i) {
		if(engine -> game -> map -> genCave() == true) {
			c_helper::message("OK");
			return true;
		}
	}
	c_helper::message("FAIL");
	return false;
}

const bool& c_helper::genWild(const int& type) {
	if(!engine -> game or !engine -> game -> map) {
		return false;
	}
	message("Generating wilderness...");
	for(int i = 0; i < 100; ++i) {
		if(engine -> game -> map -> genWild(type) == true) {
			c_helper::message("OK");
			return true;
		}
	}
	c_helper::message("FAIL");
	return false;
}

const bool& c_helper::genWorld() {
	if(!engine -> game or !engine -> game -> map) {
		return false;
	}
	message("Generating world map...");
	for(int i = 0; i < 100; ++i) {
		if(engine -> game -> map -> genWorld() == true) {
			c_helper::message("OK");
			return true;
		}
	}
	c_helper::message("FAIL");
	return false;
}

const int& c_helper::setGenFloor1(std::string value) {
	if(!engine -> game or !engine -> game -> map) {
		return 0;
	}
	engine -> game -> map -> setGenFloor1(value);
	return 0;
}

const int& c_helper::setGenFloor2(std::string value) {
	if(!engine -> game or !engine -> game -> map) {
		return 0;
	}
	engine -> game -> map -> setGenFloor2(value);
	return 0;
}

const int& c_helper::setGenFloor3(std::string value) {
	if(!engine -> game or !engine -> game -> map) {
		return 0;
	}
	engine -> game -> map -> setGenFloor3(value);
	return 0;
}

const int& c_helper::setGenWall1(std::string value) {
	if(!engine -> game or !engine -> game -> map) {
		return 0;
	}
	engine -> game -> map -> setGenWall1(value);
	return 0;
}

const int& c_helper::setGenWall2(std::string value) {
	if(!engine -> game or !engine -> game -> map) {
		return 0;
	}
	engine -> game -> map -> setGenWall2(value);
	return 0;
}

const int& c_helper::setGenWall3(std::string value) {
	if(!engine -> game or !engine -> game -> map) {
		return 0;
	}
	engine -> game -> map -> setGenWall3(value);
	return 0;
}

void c_helper::setAmbience(std::string track) {
	engine -> game -> map -> setAmbience(track);
	engine -> sound.playAmbience(track);
}

const int& c_helper::build() {
	if(!engine -> game or !engine -> game -> map) {
		return 0;
	}
	engine -> game -> map -> build();
	message("Map rebuilt.");
	return 0;
}

void c_helper::forgetMap() {
	if(!engine -> game or !engine -> game -> map) {
		return;
	}
	engine -> game -> map -> forget();
	message("You forget how you came here.");
}

// Updates world map from map 0.0.0 stored locally
void c_helper::updateWorld() {
	if(!engine -> game) {
		return;
	}
	engine -> game -> updateWorld();
}

// Returns the biome of the selected location of the world map
int c_helper::getBiome(const int& x, const int& y) {
	if(!engine -> game) {
		return 0;
	}
	return engine -> game -> getBiome(x, y);
}

// Adds a patch of the specified tile using a cellular automata generated pattern
void c_helper::genAddCellularPatch(std::string tile, const int& size) {
	if(!engine -> game or !engine -> game -> map) {
		return;
	}
	engine -> game -> map -> genAddCellularPatch(tile, size);
}

// Plants trees randomly on grass tiles (if dead is true, there is a small chance every round of a dead tree being plant in a dirt tile if found
void c_helper::genPlantTrees(std::string tree, const int& size, const bool& dead) {
	if(!engine -> game or !engine -> game -> map) {
		return;
	}
	engine -> game -> map -> genPlantTrees(tree, size, dead);	
}

// Places actor in a free random position
void c_helper::genPlaceActorSomewhere(std::string actor, const int& quantity) {
	if(!engine -> game or !engine -> game -> map) {
		return;
	}
	engine -> game -> map -> genPlaceActorSomewhere(actor, quantity);		
}

const int& c_helper::findActorByName(const int& x, const int&y, std::string name) {
	if(!engine -> game or !engine -> game -> map) {
		return 0;
	}
	int result = engine -> game -> map -> getTile(x, y) -> findActorByName(name);
    return result;		
}

const bool& c_helper::isObstacle(const int& x, const int& y) {
	return engine -> game -> map -> getTile(x, y) -> isObstacle();
}

// Returns uid of first actor of type, if no type first actor
const int& c_helper::getActorFromTile(const int& x, const int& y, const int& type) {
	if(!engine -> game or !engine -> game -> map) {
		return 0;
	}
	return engine -> game -> map -> getActorFromTile(x, y, type);
}

const bool& c_helper::actorTypeInTile(std::string type, const int& x, const int& y) {
	if(!engine -> game or !engine -> game -> map) {
		return false;
	}
	bool result = engine -> game -> map -> getTile(x, y) -> hasActorType(type);
    return result;
}

/*const int& c_helper::getFirstActorInTile(const int& emitter, const int& x, const int& y) {
	if(!engine -> game or !engine -> game -> map) {
		return 0;
	}
	std::vector<int> actorList = engine -> game -> map -> getTile(x, y) -> getActorList();
	if(actorList.size() != 0) {
		for(int i = 0; i < actorList.size(); ++i) {
			if(actorList[i] != emitter and !engine -> game -> actorManager.getActor(actorList[i]) -> door
			and engine -> game -> actorManager.actorExists(actorList[i])) {
				return actorList[i];
			}
		}
	}
	return 0;
}*/

void c_helper::teleportActor(const int& actor, const int& mapX, const int& mapY, const bool& recalculateFOV) {
	if(!engine -> game or !engine -> game -> map) {
		return;
	}

	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
 
    // Get last position
    int oldX = p_actor -> getMapX();
    int oldY = p_actor -> getMapY();

    // Change values from actor
    p_actor -> setMapX(mapX);
    p_actor -> setMapY(mapY);
            
    // Recalculate FOV (smaller range for world map)
    if(recalculateFOV == true and p_actor == engine -> game -> actorManager.getPlayer()) {
		if(c_helper::isWorldMap() == true) {
        	engine -> game -> map -> fov(mapX, mapY, 11, true);
		} else {
			engine -> game -> map -> fov(mapX, mapY, p_actor -> life -> getViewRange(), true);
		}
    }

    // Remove from last position and add to the new one
    engine -> game -> map -> removeActorFromTile(actor, oldX, oldY);
    engine -> game -> map -> addActorToTile(actor, mapX, mapY);

	// If it's the player, check for a script
	/*int script = engine -> game -> map -> getTile(mapX, mapY) -> getScript();
	if(script != 0 ) {

	}*/
}

const int& c_helper::createActor(std::string id, const int& x, const int& y) {
	if(!engine -> game) {
		return false;
	}
	return engine -> game -> actorManager.createActor(id, x, y);
}

void c_helper::startAction(const structEventData& eventData) {
	if(!engine -> game or !engine -> game -> actorManager.getActor(eventData.emitter) -> action) {
		return;
	}
	engine -> game -> actorManager.getActor(eventData.emitter) -> action -> start(eventData);
}

const int& c_helper::findEnemy(const int& actor) {

	if(!engine -> game or !engine -> game -> map) {
		return 0;
	}
	
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);

	// Get actor list
	std::vector<int> actorList = engine -> game -> map -> fov(p_actor -> getMapX(), p_actor -> getMapY(), p_actor -> life -> getViewRange(), false);
	
	if(actorList.size() != 0) {
		for(int i = 0; i < actorList.size(); ++i) {
			if(isEnemy(actor, actorList.at(i)) == true) {

				// Sets enemy as target


				return actorList.at(i);
			}
		}
	}
	return 0;
}

const bool& c_helper::isEnemy(const int& emitter, const int& target) {

	int fac = engine -> game -> actorManager.getActor(target) -> getFaction();
	switch(engine -> game -> actorManager.getActor(emitter) -> getFaction()) {

		// ANIMAL
		case faction::animal: {
			if(fac == faction::avatar) {
				return true;
			}
			break;
		}
	}
	return false;
}

// Shows actor's coordinates in the game console
void c_helper::showActorPosition(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor) {
		return;
	} 
	std::ostringstream s;
	s << p_actor -> getName() << " is located at " << p_actor -> getMapX() << "x" << p_actor -> getMapY() << ".";
	message(s.str());
}

// Shows player's coordinates in the game console
void c_helper::showPlayerPosition() {
	c_actor* p_actor = engine -> game -> actorManager.getPlayer();
	if(!p_actor) {
		return;
	} 
	std::ostringstream s;
	s << p_actor -> getName() << " is located at " << p_actor -> getMapX() << "x" << p_actor -> getMapY() << ".";
	message(s.str());
}

const int& c_helper::getDirectionToActor(const int& emitter, const int& target) {
	c_actor* p_emitter = engine -> game -> actorManager.getActor(emitter);
	c_actor* p_target = engine -> game -> actorManager.getActor(target);
	TCODPath* path = engine -> game -> map -> path(p_emitter -> getMapX(), p_emitter -> getMapY(), p_target -> getMapX(), p_target -> getMapY());
    if(path -> size()) {
        int dx = 0;
        int dy = 0;
        path -> walk(&dx, &dy, true);
        if(dy == p_emitter -> getMapY()) {
        	if(dx < p_emitter -> getMapX()) {
        		return direction::west;
        	} else {
        		return direction::east;
        	}
        } else if(dy > p_emitter -> getMapY()) {
        	if(dx == p_emitter -> getMapX()) {
        		return direction::south;
        	} else if(dx > p_emitter -> getMapX()) {
        		return direction::southeast;
        	} else {
        		return direction::southwest;
        	}
        } else if(dy < p_emitter -> getMapY()) {
        	if(dx == p_emitter -> getMapX()) {
        		return direction::north;
        	} else if(dx > p_emitter -> getMapX()) {
        		return direction::northeast;
        	} else {
        		return direction::northwest;
        	}
        }
    }
    return 0;
}

std::string c_helper::getActorId(const int& actor) {
	return engine -> game -> actorManager.getActor(actor) -> getId();
}

int c_helper::getActorType(const int& actor) {
	return engine -> game -> actorManager.getActor(actor) -> getType();
}

std::string c_helper::getName(const int& actor) {
	c_actor* p_actor = engine->game->actorManager.getActor(actor);
	return engine -> game -> actorManager.getActor(actor) -> getName();
}

const int& c_helper::getActorMapX(const int& actor) {
	return engine -> game -> actorManager.getActor(actor) -> getMapX();
}

const int& c_helper::getActorMapY(const int& actor) {
	return engine -> game -> actorManager.getActor(actor) -> getMapY();
}

const int& c_helper::getConstitution() {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return 0;
	} 
	return engine -> game -> actorManager.getPlayer() -> player -> getConstitution();
}

const int& c_helper::getAgility() {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return 0;
	} 
	return engine -> game -> actorManager.getPlayer() -> player -> getAgility();
}

const int& c_helper::getSpirit() {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return 0;
	} 
	return engine -> game -> actorManager.getPlayer() -> player -> getSpirit();
}

const int& c_helper::getLuck() {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return 0;
	} 
	return engine -> game -> actorManager.getPlayer() -> player -> getLuck();
}

void c_helper::setConstitution(const int& value) {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return;
	} 
	engine -> game -> actorManager.getPlayer() -> player -> setConstitution(value);
}

void c_helper::setAgility(const int& value) {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return;
	} 
	engine -> game -> actorManager.getPlayer() -> player -> setAgility(value);
}

void c_helper::setSpirit(const int& value) {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return;
	} 
	engine -> game -> actorManager.getPlayer() -> player -> setSpirit(value);
}

void c_helper::setLuck(const int& value) {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return;
	} 
	engine -> game -> actorManager.getPlayer() -> player -> setLuck(value);
}

const int& c_helper::getHealth(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getHealth();
}

const int& c_helper::getMaxHealth(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getMaxHealth();
}

const int& c_helper::getMinDamage(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getMinDamage();
}

const int& c_helper::getMaxDamage(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getMaxDamage();
}

const int& c_helper::getAttack(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getAttack();
}

const int& c_helper::getDefense(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getDefense();
}

const int& c_helper::getProtection(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getProtection();
}

const int& c_helper::getBlock(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getBlock();
}

const int& c_helper::getParry(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getParry();
}

const int& c_helper::getExpReward(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getExp();
}

const int& c_helper::getViewRange(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getViewRange();
}

std::string c_helper::getPlayerName() {
	return engine -> game -> actorManager.getPlayer() -> getName();
}

const int& c_helper::getPlayer() {
	return engine -> game -> actorManager.getPlayer() -> getUid();
}

const bool& c_helper::isPlayer(const int& actor) {
	if(!engine -> game or !engine -> game -> map) {
		return false;
	}
	if(engine -> game -> actorManager.getActor(actor) ==  engine -> game -> actorManager.getPlayer()) {
		return true;
	} else {
		return false;
	}
}

/*/ -20% MaxMeleeDamage
const int& c_helper::getMinMeleeDamage(const int& actor) {
	int damage = getMaxMeleeDamage(actor);
	return damage - (damage * 20 / 100);
}

// melee = constitution / 4
const int& c_helper::getMaxMeleeDamage(const int& actor) {
if(!engine -> game or !engine -> game -> actorManager.getActor(actor)) {
		return 0;
	}
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(p_actor and p_actor -> life) {
		return p_actor -> life -> getConstitution() / 4;;
	}
	return 0;
}

// How much damage does the actor deal?
const int& c_helper::getMeleeDamage(const int& actor) {
	if(!engine -> game or !engine -> game -> actorManager.getActor(actor)) {
		return 0;
	}
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor or !p_actor -> life) {
		return 0;
	}

	int minDamage = getMinMeleeDamage(actor);
	int maxDamage = getMaxMeleeDamage(actor);
	int baseDamage = c_helper::random(minDamage, maxDamage);

	// If it's a creature
	if(p_actor != engine -> game -> actorManager.getPlayer()) {
		return baseDamage;

	// If it's the player
	} else {

		// No weapon
		if(p_actor -> player -> getEquippedItem(bodySlot::mainHand) == 0) {
			return baseDamage;

		// Has weapon
		} else {
			c_actor* p_weapon = engine -> game -> actorManager.getActor(p_actor -> player -> getEquippedItem(bodySlot::mainHand));
			if(p_weapon -> weapon and (p_weapon -> weapon -> getType() == weaponType::oneHanded or p_weapon -> weapon -> getType() == weaponType::twoHanded)) {
				int weaponDamage = c_helper::random(p_weapon -> weapon -> getMinDamage(), p_weapon -> weapon -> getMaxDamage());
				return baseDamage + weaponDamage;
			}	
			return baseDamage;
		}
	}
	return 0;
}*/

void c_helper::setAttributes(const int& maxHealth, const int& minDamage, const int& maxDamage, const int& speed, const int& attack, const int& defense, const int& protection, const int& block, const int& parry) {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return;
	} 
	engine -> game -> actorManager.getPlayer() -> life -> set(maxHealth, minDamage, maxDamage, speed, attack, defense, protection, block, parry);
}

void c_helper::calculateAttributes() {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return;
	}
	    
	structEventData eventData;
	eventData.type = "calculateAttributes";
	eventData.emitter = engine -> game -> actorManager.getPlayer() -> getUid();
	engine -> game -> runScript(eventData);
}

void c_helper::restoreHealth(const int& actor, const int& points) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(p_actor -> life) {
		p_actor -> life -> restoreHealth(points);
	}
}

void c_helper::damage(const int& actor, const int& value) {
	if(!engine -> game) {
		return;
	}
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(p_actor -> life) {
		p_actor -> life -> damageHealth(value);
	}
}

void c_helper::kill(const int& actor) {
	if(!engine -> game) {
		return;
	}
	engine -> game -> actorManager.deleteActor(actor);	
}

void c_helper::openCloseDoor(const int& emitter, const int& door) {
	c_actor* p_emitter = engine -> game -> actorManager.getActor(emitter);
	c_actor* p_door = engine -> game -> actorManager.getActor(door);
	if(!p_door -> door) {
		return;
	}
	p_door -> door -> toggleOpen();

	// Recalculate FOV
    if(p_emitter == engine -> game -> actorManager.getPlayer()) {
        engine -> game -> map -> fov(p_emitter -> getMapX(), p_emitter -> getMapY(), p_emitter -> life -> getViewRange(), true);
    }
}

const bool& c_helper::getItemFromFloor(const int& target) {
	c_actor* p_emitter = engine -> game -> actorManager.getPlayer();
	c_actor* p_target = engine -> game -> actorManager.getActor(target);
	if(!p_emitter -> player or p_target -> life) {
		return false;
	}

    // If the same item already existed in the inventory, we remove this one (quantity increased in inventory)
    if(p_emitter -> player-> addToInventory(target) == true) {
        engine -> game -> actorManager.deleteActor(target);
        return true;

	// The item did not exist
    } else {
	    engine -> game -> map -> removeActorFromTile(target, p_target -> getMapX(), p_target -> getMapY());
	    p_target -> setMapX(-1);
	    p_target -> setMapY(-1);
		engine -> game -> actorManager.removeFromMap(target);
		engine -> game -> actorManager.addToInventory(target);
	    return true;   
    }  
    return false;	
}

const bool& c_helper::dropItemFromInventory(const int& target) {
	c_actor* p_emitter = engine -> game -> actorManager.getPlayer();
	c_actor* p_target = engine -> game -> actorManager.getActor(target);
	if(!p_emitter -> player or p_target -> life) {
		return false;
	}

    // If there is > 1 item in inventory, we create a new actor on ground)
    if(p_emitter -> player-> deleteFromInventory(target) == false) {
        engine -> game -> actorManager.createActor(p_target -> getId(), p_emitter -> getMapX(), p_emitter -> getMapY());
		return true;

	// If it was the last item in inventory
    } else {
		teleportActor(target, p_emitter -> getMapX(), p_emitter -> getMapY(), false);
		engine -> game -> actorManager.removeFromInventory(target);
		engine -> game -> actorManager.addToMap(target);
	    return true;   
    }  
    return false;	
}

void c_helper::consume(const int& emitter, const int& target) {
	c_actor* p_emitter = engine -> game -> actorManager.getActor(emitter);
	c_actor* p_target = engine -> game -> actorManager.getActor(target);
	if(!p_emitter -> player or !p_target -> consumable) {
		return;
	}
	p_target -> consumable -> consume(emitter);
	if(p_emitter -> player -> deleteFromInventory(target) == true) { // Returns true if it was the last item, therefore we delete it
		engine -> game -> actorManager.deleteActor(target);
	}
}

const int& c_helper::findStaircase(const int& x, const int& y) {
	if(!engine -> game or !engine -> game -> map) {
		return false;
	}
	int result = engine -> game -> map -> getTile(x, y) -> findStaircase();
    return result;
}

const bool& c_helper::equipItem(const int& emitter, const int& item) {
	c_actor* p_emitter = engine -> game -> actorManager.getActor(emitter);
	if(!p_emitter -> player) {
		return false;
	}
	return p_emitter -> player -> equipItem(item);
}

const bool& c_helper::removeItem(const int& emitter, const int& item) {
	c_actor* p_emitter = engine -> game -> actorManager.getActor(emitter);
	if(!p_emitter -> player) {
		return false;
	}
	return p_emitter -> player -> removeItem(item);
}

void c_helper::give(std::string item) {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return;
	}
	int actor = createActor(item, -1, -1);
	if(actor != 0 and engine -> game -> actorManager.getPlayer() -> player -> addToInventory(actor) == true) {
	        engine -> game -> actorManager.deleteActor(actor);
	}
}

void c_helper::toggleGodMode() {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return;
	}
	bool god = engine -> game -> actorManager.getPlayer() -> player -> toggleGodMode();
	if(god == true) {
		message("God mode enabled. Have fun!");
	} else {
		message("God mode disabled. Run for your life!");
	}
}

const bool& c_helper::isPlayerGod() {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return false;
	}
	return engine -> game -> actorManager.getPlayer() -> isGod();
}

// Teaches the player a ability
const bool& c_helper::learn(std::string id) {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return false;
	}
	return engine -> game -> actorManager.getPlayer() -> player -> learnAbility(id);
}

// // Wait for enter key and deletes game
void c_helper::gameOver() {
	engine -> interface.gameOver();
}