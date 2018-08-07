std::vector<std::string> c_helper::split(const std::string& s, char delimiter) {
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter)) {
      tokens.push_back(token);
   }
   return tokens;	
}

const int&  c_helper::random(const int& min, const int& max) {
    TCODRandom* ran = TCODRandom::getInstance();
    return ran -> getInt(min, max);
}

void c_helper::changeMap(const int& direction, const int& mapX, const int& mapY) {
	if(!engine -> game or !engine -> game -> map) {
		return;
	}
	switch(direction) {
		case direction::east: {
			engine -> game -> changeMap(engine -> game -> map -> getX() + 1, engine -> game -> map -> getY(), engine -> game -> map -> getZ(), mapX, mapY);
			return;
		}
		case direction::west: {
			engine -> game -> changeMap(engine -> game -> map -> getX() - 1, engine -> game -> map -> getY(), engine -> game -> map -> getZ(), mapX, mapY);
			return;
		}
		case direction::north: {
			engine -> game -> changeMap(engine -> game -> map -> getX(), engine -> game -> map -> getY() - 1, engine -> game -> map -> getZ(), mapX, mapY);
			return;
		}
		case direction::south: {
			engine -> game -> changeMap(engine -> game -> map -> getX(), engine -> game -> map -> getY() + 1, engine -> game -> map -> getZ(), mapX, mapY);
			return;
		}
		case direction::up: {
			engine -> game -> changeMap(engine -> game -> map -> getX(), engine -> game -> map -> getY(), engine -> game -> map -> getZ() + 1, mapX, mapY);
			return;
		}
		case direction::down: {
			engine -> game -> changeMap(engine -> game -> map -> getX(), engine -> game -> map -> getY(), engine -> game -> map -> getZ() - 1, mapX, mapY);
			return;
		}
	}
}

void c_helper::gameMessage(const std::string& text) {
	if(!engine -> game) {
		return;
	}
	engine -> game -> gamelog.message(text);
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

const bool& c_helper::isObstacle(const int& x, const int& y) {
	return engine -> game -> map -> getTile(x, y) -> isObstacle();
}

const int& c_helper::getCreatureFromTile(const int& x, const int& y) {
	if(!engine -> game or !engine -> game -> map) {
		return 0;
	}
	std::vector<int> actorList = engine -> game -> map -> getTile(x, y) -> getActorList();
	for(int i = 0; i < actorList.size(); ++i) {
		if(engine -> game -> actorManager.getActor(actorList[i]) -> life) {
			return actorList[i];
		}
	}
	return 0;
}

const bool& c_helper::actorTypeInTile(std::string type, const int& x, const int& y) {
	if(!engine -> game or !engine -> game -> map) {
		return false;
	}
	bool result = engine -> game -> map -> getTile(x, y) -> hasActorType(type);
    return result;
}

const int& c_helper::getFirstActorInTile(const int& emitter, const int& x, const int& y) {
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
}

void c_helper::teleportActor(const int& actor, const int& mapX, const int& mapY) {
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
            
    // Recalculate FOV
    if(p_actor == engine -> game -> actorManager.getPlayer()) {
        engine -> game -> map -> fov(mapX, mapY, p_actor -> life -> getViewRange(), true);
    }

    // Remove from last position and add to the new one
    engine -> game -> map -> removeActorFromTile(actor, oldX, oldY);
    engine -> game -> map -> addActorToTile(actor, mapX, mapY);
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
	engine -> game -> actorManager.getActor(eventData.emitter) -> action -> start(1, eventData);
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
			if(isEnemy(actor, actorList[i]) == true) {

				// Sets enemy as target


				return actorList[i];
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

std::string c_helper::getName(const int& actor) {
	std::cout << actor << std::endl;
	c_actor* p_actor = engine->game->actorManager.getActor(actor);
	return engine -> game -> actorManager.getActor(actor) -> getName();
}

const int& c_helper::getActorMapX(const int& actor) {
	return engine -> game -> actorManager.getActor(actor) -> getMapX();
}

const int& c_helper::getActorMapY(const int& actor) {
	return engine -> game -> actorManager.getActor(actor) -> getMapY();
}

const int& c_helper::getHealth(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getHealth();
}

const int& c_helper::getConstitution(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor and !p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getConstitution();
}

const int& c_helper::getMaxHealth(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	} 
	return p_actor -> life -> getMaxHealth();
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

const bool& c_helper::getItemFromFloor(const int& emitter, const int& target) {
	c_actor* p_emitter = engine -> game -> actorManager.getActor(emitter);
	c_actor* p_target = engine -> game -> actorManager.getActor(target);
	if(!p_emitter -> life or p_target -> life) {
		return false;
	}

    // If the same item already existed in the inventory, we remove this one (quantity increased in inventory)
    if(p_emitter -> life -> addToInventory(target) == true) {
        engine -> game -> actorManager.deleteActor(target);
        return true;
    } else {
	    engine -> game -> map -> removeActorFromTile(target, p_target -> getMapX(), p_target -> getMapY());
	    p_target -> setMapX(-1);
	    p_target -> setMapY(-1);
	    return true;   
    }  
    return false;	
}

void c_helper::consume(const int& emitter, const int& target) {
	c_actor* p_emitter = engine -> game -> actorManager.getActor(emitter);
	c_actor* p_target = engine -> game -> actorManager.getActor(target);
	if(!p_emitter -> life or !p_target -> consumable) {
		return;
	}
	p_target -> consumable -> consume(emitter);
	if(p_emitter -> life -> deleteFromInventory(target) == true) { // Returns true if it was the last item, therefore we delete it
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
	if(!p_emitter -> life) {
		return false;
	}
	return p_emitter -> life -> equipItem(item);
}

const bool& c_helper::removeItem(const int& emitter, const int& item) {
	c_actor* p_emitter = engine -> game -> actorManager.getActor(emitter);
	if(!p_emitter -> life) {
		return false;
	}
	return p_emitter -> life -> removeItem(item);
}

const int& c_helper::getDamage(const int& actor) {
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(!p_actor -> life) {
		return 0;
	}
	//int baseDamage = p_actor -> life
}

void c_helper::give(std::string item) {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return;
	}
	int actor = createActor(item, -1, -1);
	if(actor != 0 and engine -> game -> actorManager.getPlayer() -> life -> addToInventory(actor) == true) {
	        engine -> game -> actorManager.deleteActor(actor);
	}
}

const int& c_helper::calculateHitDamage(const int& actor) {
	if(!engine -> game or !engine -> game -> actorManager.getActor(actor)) {
		return 0;
	}
	c_actor* p_actor = engine -> game -> actorManager.getActor(actor);
	if(p_actor and p_actor -> life) {
		return p_actor -> life -> getHitDamage();
	}
	return 0;
}