c_player::c_player(c_actor* father) {
    this -> father = father;
    key = 0;
    god = false;
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
            father -> action -> start(1, eventData); 
            return true;

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
                father -> action -> start(1, eventData); 
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
                        father -> action -> start(1, eventData);
                        return true;
                    // Several creatures
                    } else {
                        structEventData eventData;
                        eventData.type = "talk";
                        eventData.target = engine -> interface.selectCloseTarget(imode::game, "Talk to");
                        father -> action -> start(1, eventData);
                        return true;
                    }
                }

                engine -> game -> gamelog.message("There is nobody you can talk to.");
                return false;
            }

            case key::period: {
                structEventData eventData;
                eventData.type = "wait";
                father -> action -> start(1, eventData);
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
                    father -> action -> start(1, eventData);
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