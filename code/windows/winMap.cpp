c_winMap::c_winMap(const int& x, const int& y, const int& tileWidth, const int& tileHeight)
:   x(x),
    y(y),
    tileWidth(tileWidth),
    tileHeight(tileHeight)
{ }

int c_winMap::update(int key, const int& mapX0, const int& mapY0, sf::Vector2i mousePos) {

    // No need to update if mouse is not inside the area
    if(mousePos.x > tileWidth * global::tileSize or mousePos.y > tileHeight * global::tileSize) {
        return key;
    }

    int yUIOffset = 0;
    int mapX = mapX0 + (x * 16) + mousePos.x / global::tileSize - tileWidth / 2;
    int mapY = mapY0 + (y * 16) + mousePos.y / global::tileSize - tileHeight / 2 + yUIOffset;

    if(mapX >= 0 and mapX < engine -> game -> map -> getWidth()
    and mapY >= 0 and mapY < engine -> game -> map -> getHeight()
    and mousePos.x > x * 16 and mousePos.x < (x + tileWidth) * 16
    and mousePos.y > y * 16 and mousePos.y < (y + tileHeight) * 16) {
        c_tile* tile = engine -> game -> map -> getTile(mapX, mapY);
        switch(engine -> interface.getMode()) {
            case imode::game: {
                if(tile -> getExplored()) {
                    engine -> interface.selectTile(tile);

                    // Left click moves player to position
                    if(key == key::lclick and tile -> getType() != tileType::wall and tile -> isObstacle() == false) {
                        engine -> interface.setTileDestination(tile);
                        return 0;
                    }
                }
                break;
            }
            case imode::edit: {
                engine -> interface.selectTile(tile);

                // Right click removes the actor
                if(key == key::rclick) {
                    tile -> removeActors();
                    return 0;
                }

                switch(engine -> interface.getEmode()) {
                    case emode::tile: {

                        // Left click sets the tile terrain
                        if(key == key::lclick) {
                            tile -> setAsset(engine -> interface.getEditTile());;
                            return 0;
                        }
                        break;
                    }
                    case emode::actor: {

                        // Left click adds the actor
                        if(key == key::lclick and !tile -> hasAnyActor()) {
                            engine -> game -> actorManager.createActor(engine -> interface.getEditActor() -> id, tile -> getX(), tile -> getY());
                            return 0;
                        }

                        break;
                    }
                }
                /*if(key == key::lclick) {
                    int radius = engine -> interface.getEditRadius();
                    for(int i1 = 0; i1 < radius; ++i1) {
                        for(int i2 = 0; i2 < radius; ++i2) {
                            engine -> game -> map -> getTile(tile -> getX() - (radius / 2) + i1, tile -> getY() - (radius / 2)  + i2)  -> setAsset(engine -> interface.getEditTile());;
                        }
                    }
                    return 0;
                }*/
                break;
            }
            case imode::selectCloseTarget: {
                if(c_helper::calculateDistance(mapX, mapY, mapX0, mapY0) == 1 and tile -> hasAnyActor()) {
                    engine -> interface.selectTile(tile);
                    if(key == key::lclick) {
                        engine -> interface.selectActor(c_helper::getCreatureFromTile(mapX, mapY));
                        return 0;
                    }
                }
                break;
            }

        }
        
    }
    return key;
}

void c_winMap::draw(const int& mapX0, const int& mapY0) {
    if(!engine -> game or !engine -> game -> map) {
        return;
    }
    // If player is god or edit mode is on, draw without fog, otherwise draw as default
    bool fog = true;
    c_actor* p_player = 0;
    if(engine -> game -> actorManager.getPlayer()) {
        p_player = engine -> game -> actorManager.getPlayer();
    }
    if(p_player and p_player -> isGod() or engine -> interface.getMode() == imode::edit) {
        fog = false;
    }
    int yUIOffset = 0;
    for(int i1 = 0; i1 < tileWidth; ++i1) {
        for(int i2 = 0; i2 < tileHeight; ++i2) {

            int mapX = mapX0 - tileWidth / 2 + i1;
            int mapY = mapY0 - tileHeight / 2 + i2 + yUIOffset;

            // Draw tile
            if(mapX >= 0 and mapX < engine -> game -> map -> getWidth()
            and mapY >= 0 and mapY < engine -> game -> map -> getHeight()) {
                c_tile* tile = engine -> game -> map -> getTile(mapX0 + i1 - tileWidth / 2, mapY0 + i2 - tileHeight / 2 + yUIOffset);
                tile -> draw((x + i1 - 1) * global::tileSize + 16, (y + i2 - 1) * global::tileSize + 16, tile -> getInterior(), fog);
                if(engine -> interface.getSelectedTile() == tile and engine -> isLoading() == false) {
                    engine -> screen.drawTexture("selectedTile", x + (i1 - 1)  * global::tileSize + 16, y + (i2 - 1) * global::tileSize + 16);
                }
            }
        }
    }
}