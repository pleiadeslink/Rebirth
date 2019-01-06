c_player::c_player(c_actor* father) {
    this -> father = father;
    key = 0;
    god = false;
    carried = 0;
	equipment[0] = 0;
	equipment[1] = 0;
	equipment[2] = 0;
	equipment[3] = 0;
	equipment[4] = 0;
	equipment[5] = 0;
	equipment[6] = 0;

    // Learns basic skills
    learnSkill("walk");
    learnSkill("wait");
}

bool c_player::channel(const int& key, const bool& worldMap) {
    
    // Checks destination tile
    engine -> setLoading(false);
    if(engine -> interface.getTileDestination()) {
        int destX = engine -> interface.getTileDestination() -> getX();
        int destY = engine -> interface.getTileDestination() -> getY();
        if((destX == father -> getMapX()
        and destY == father -> getMapY()) 
        or engine -> interface.getTileDestination() -> isObstacle()) {
            engine -> interface.setTileDestination(0);

        // If the distance is 1 and it's a location
        // ! This is dirty as fuck and needs refactoring but hey man it works so good job bro
        } if(c_helper::calculateDistance(father -> getMapX(), father -> getMapY(), destX, destY) == 1
        and engine -> interface.getTileDestination() -> isLocation()) {
            structEventData eventData;
            eventData.type = "walk";
            eventData.mapX = destX;
            eventData.mapY = destY;
            return father -> action -> start(eventData); 
        } else {
            bool destWasObstacle = false;
            if(engine -> game -> map -> getTile(destX, destY) -> isObstacle()
            or engine -> game -> map -> getTile(destX, destY) -> isLocation()) {
                engine -> game -> map -> setProperties(destX, destY, true, true);
                destWasObstacle = true; 
            }
            TCODPath* path = engine -> game -> map -> path(father -> getMapX(), father -> getMapY(), destX, destY);
            if(path -> size()) {
                int dx = 0;
                int dy = 0;
                path -> walk(&dx, &dy, true);
                structEventData eventData;
                eventData.type = "walk";
                eventData.mapX = dx;
                eventData.mapY = dy;
                father -> action -> start(eventData); 
                engine -> setLoading(true);
                return true;
            } else {
                engine -> interface.setTileDestination(0);
                
            }
            if(destWasObstacle == true) {
                engine -> game -> map -> setProperties(destX, destY, false, false);
            }
            delete path;
        }
    }

    // Reads input
	if(key) {

        // World map input
        switch(key) {

            case key::up: {

                int x = father -> getMapX();
                int y = father -> getMapY();

                // Out limits
                if(y == 0) {
                    engine -> game -> gamelog.message("That's out limits!");
                    return false;
                }

                return engine -> game -> map -> getTile(x, y - 1) -> playerAction(father);
            }

            case key::down: {

                int x = father -> getMapX();
                int y = father -> getMapY();

                // Out limits
                if(y > engine -> game -> map -> getHeight()) {
                    engine -> game -> gamelog.message("That's out limits!");
                    return false;
                }

                return engine -> game -> map -> getTile(x, y + 1) -> playerAction(father);
            }

            case key::right: {

                int x = father -> getMapX();
                int y = father -> getMapY();

                // Out limits
                if(x > engine -> game -> map -> getWidth()) {
                    engine -> game -> gamelog.message("That's out limits!");
                    return false;
                }

                return engine -> game -> map -> getTile(x + 1, y) -> playerAction(father);
            }

            case key::left: {

                int x = father -> getMapX();
                int y = father -> getMapY();

                // Out limits
                if(x == 0) {
                    engine -> game -> gamelog.message("That's out limits!");
                    return false;
                }

                return engine -> game -> map -> getTile(x - 1, y) -> playerAction(father);
            }

            case key::t: {

                std::vector<int> actorList = engine -> game -> map -> countActorsAround(father -> getMapX(), father -> getMapY());
                std::vector<int> creatureList;

                if(actorList.size() > 0) {
                    for(int i = 0; i < actorList.size(); ++i) {
                        if(engine -> game -> actorManager.getActor(actorList[i]) -> life) {
                            creatureList.push_back(actorList[i]);
                        }
                    }
                }

                if(creatureList.size() > 0) {
                    // Only one creature
                    if(creatureList.size() == 1) {
                        structEventData eventData;
                        eventData.type = "talk";
                        eventData.target = creatureList[0];
                        father -> action -> start(eventData);
                        return true;
                    // Several creatures
                    } else {
                        structEventData eventData;
                        eventData.type = "talk";
                        eventData.target = engine -> interface.selectCloseTarget(imode::game, "Talk to");
                        father -> action -> start(eventData);
                        return true;
                    }
                }

                engine -> game -> gamelog.message("There is nobody you can talk to.");
                return false;
            }

            case key::period: {
                structEventData eventData;
                eventData.type = "wait";
                father -> action -> start(eventData);
                return true;
            }

            case key::comma: {
                std::vector<int> actorList = engine -> game -> map -> getTile(father -> getMapX(), father -> getMapY()) -> getActorList();
                bool actor = false;
                for(int i = 0; i < actorList.size(); ++i) {
                    if(engine -> game -> actorManager.getActor(actorList[i]) -> body and engine -> game -> actorManager.getActor(actorList[i]) -> body -> getCanPickup() == true) {
                        actor = true;
                    }
                }
                if(actor == true) {
                    structEventData eventData;
                    eventData.type = "get";
                    eventData.target = actorList[0];
                    father -> action -> start(eventData);
                    return true;                
                } else {
                    engine -> game -> gamelog.message("There is nothing to pick up.");
                    return false;
                }
            }
        }
    }     
    return false;    
}

const bool& c_player::addToInventory(const int& uid, const int& quantity) {

	c_actor* p_item = engine -> game -> actorManager.getActor(uid);

	// Check if another item of the same type is already in the inventory
	for(int i = 0; i < inventory.size(); ++i) {
		if(p_item -> getId() == engine -> game -> actorManager.getActor(inventory[i].uid) -> getId()) {

			// It is, we increment quantity of existing item and remove the one to add
			inventory[i].quantity += quantity;
			if(p_item -> body) {
				carried += p_item -> body -> getMass();
			}			
			engine -> game -> actorManager.deleteActor(uid);
			return true;
		}
	}

	// No other item of the same type is in the inventory, so we add the current one
	s_invItem item;
	item.uid = uid;
	item.quantity = quantity;
	item.equipped = false;
	inventory.push_back(item);
	if(p_item -> body) {
		carried += p_item -> body -> getMass();
	}	
	return false;
}

const bool& c_player::deleteFromInventory(const int& item) {
	c_actor* p_item = engine -> game -> actorManager.getActor(item);
	for(int i = 0; i < inventory.size(); ++i) {
		if(p_item -> getId() == engine -> game -> actorManager.getActor(inventory[i].uid) -> getId()) {
			if(inventory[i].quantity > 1) {
				--inventory[i].quantity;
				return false;
			} else {
				inventory.erase(inventory.begin() + i);
				return true;
			}
		}
	}
	return false;
}

const bool& c_player::equipItem(const int& item) {
	for(int i = 0; i < inventory.size(); ++i) {
		if(inventory[i].uid == item) {
			c_actor* p_item = engine -> game -> actorManager.getActor(item);
			if(p_item -> weapon) {
				equipment[bodySlot::mainHand] = item;
				inventory[i].equipped = true;
				return true;
			}
		}
	}
	return false;
}

const bool& c_player::removeItem(const int& item) {
	for(int i = 0; i < inventory.size(); ++i) {
		if(inventory[i].uid == item) {
			c_actor* p_item = engine -> game -> actorManager.getActor(item);
			if(p_item -> weapon) {
				equipment[bodySlot::mainHand] = 0;
				inventory[i].equipped = false;
				return true;
			}
		}
	}
	return false;
}

const bool& c_player::isInInventory(const int& item) {
	for(int i = 0; i < inventory.size(); ++i) {
		if(inventory[i].uid == item) {
			return true;
		}
	}
	return false;
}

// Adds the skill to the skill memory
const bool& c_player::learnSkill(std::string id) {

    // First checks if the skill exists
    s_skillAsset* skill = engine -> assetManager.getSkillAsset(id);
    if(skill -> duration == 0) {
        c_helper::gameMessage("That skill does not exist!");
        return false;
    }

    // Adds the skill to the skill memory
    v_learnedSkills.push_back(id);

    c_helper::gameMessage("You have learned '" + id + "'.");
    return true;
}

const bool& c_player::hasSkill(std::string id) {
    for(int i = 0; i < v_learnedSkills.size(); ++i) {
        if(v_learnedSkills.at(i) == id) {
            return true;
        }
    }
    return false;
}