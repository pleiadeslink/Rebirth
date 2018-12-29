c_interface::c_interface() {
    emode = emode::tile;
    editTile = 0;
    editActor = 0;
    editRadius = 1;
}

c_interface::~c_interface() {
    delete map;
    delete gamelog;
    delete character;
    delete sidebar;
    delete info;
    //delete message;
}

void c_interface::init()     {
    mode = imode::game;
    sTile = 0;
    sActor = 0;
    targetText = "";
    inputText = "";
    pasteMode = false;
    info = new c_winInfo(44, 16, 23, 25);
    map = new c_winMap(0, 0, 67, 41);
    gamelog = new c_winGamelog(0, 35, 80, 10);
    //sidebar = new c_winSidebar("sidebar", 0, 43, 80, 2);
    character = new c_winCharacter(0, 0, 67, 41);
    sidebar = new c_winSidebar(67, 0, 13, 45);
    sidebar -> init();
}

int c_interface::update(int key) {
    sTile = 0;
    sActor = 0;
    if(engine -> game -> actorManager.getPlayer()) {
        if(mode == imode::game or mode == imode::edit) {
            key = map -> update(key, engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY(), engine -> getMouse());
        } else if(mode == imode::character) {
            key = character -> update(key);
        }
        key = sidebar -> update(key, engine -> getMouse());
    }
    key = processInput(key);
    return key;
}

void c_interface::draw() {
    switch(mode) {
        case imode::game: {
            if(engine -> game -> actorManager.getPlayer()) {
                map -> draw(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY());
            }
            gamelog -> draw();
            sidebar -> draw();
            break;
        }
        case imode::character: {
            gamelog -> draw();
            sidebar -> draw();
            info -> draw();
            character -> draw();
            break;
        }
        case imode::edit: {
            if(engine -> game -> actorManager.getPlayer()) {
                map -> draw(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY());
            }
            gamelog -> draw();
            sidebar -> draw();
            std::string str = "> " + engine -> getCommand();
            engine -> screen.drawText(str, 4, 4, sf::Color::White);
            break;
        }
        case imode::selectCloseTarget: {
            if(engine -> game -> actorManager.getPlayer()) {
                map -> draw(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY());
            }
            gamelog -> draw();
            sidebar -> draw();
            //drawTargetSelectionMessage();
            break;
        }

    }

    // Draw mouse
    engine -> screen.drawTexture("pointer", engine -> getMouse().x, engine -> getMouse().y);
}

void c_interface::edit() {

    mode = imode::edit;
    if(editTile == 0) {
        editTile = engine -> assetManager.getTileAsset("default");
    }
    if(editActor == 0) {
        editActor = engine -> assetManager.getActorAsset("default");
    }
    while(mode == imode::edit) {
        engine -> game -> gamelog.clear();
        update(engine -> input());
        engine -> game -> gamelog.update();
        engine -> screen.clear();
        draw();
        engine -> screen.display();
    }
    this -> mode = imode::game;
}

int c_interface::selectCloseTarget(const int& prevMode, const std::string& targetText) {
    if(!engine -> game or !engine -> game -> map or !engine -> game -> actorManager.getPlayer()) {
        return 0;
    }
    mode = imode::selectCloseTarget;
    sActor = 0;
    this -> targetText = targetText;
    while(sActor == 0) {
        engine -> game -> gamelog.clear();
        update(engine -> input());
        engine -> game -> gamelog.update();
        engine -> screen.clear();
        draw();
        engine -> screen.display();
    }
    mode = prevMode;
    return sActor;
}

/*c_tile* c_interface::selectTarget(const int& prevMode, const std::string& targetText) {
    if(!engine -> game or !engine -> game -> map or !engine -> game -> actorManager.getPlayer()) {
        return 0;
    }
    mode = imode::selectTarget;
    target = 0;
    this -> targetText = targetText;
    while(target == 0) {
        engine -> screen.clear();
        update(engine -> input());
        draw();
        engine -> screen.display();
    }
    mode = prevMode;
    return target;
}*/

int c_interface::processInput(int key) {

    if(key == 0) {
        return 0;
    }

    switch(mode) {

        case imode::game: {
            switch(key) {

                // Change view
                case key::space: {
                    mode = imode::character;
                    return 0;
                }

                // Edit
                case key::f1: {
                    edit();
                    return 0;
                }

                // Quit
                case key::escape: {
                    engine -> quit();
                    return 0;
                }

                // Screenshot
                case key::p: {
                    engine -> screen.screenshot();
                    return 0;
                }
            }
            return key;
        }

        case imode::character: {
            switch(key) {

                // Change view
                case key::space: {
                    mode = imode::game;
                    return 0;
                }

                // Quit
                case key::escape: {
                    mode = imode::game;
                    return 0;
                }
            }
            return key;
        }

        case imode::edit: {
            switch(key) {
                case key::add: {
                    ++editRadius;
                    return 0;
                }
                case key::subtract: {
                    --editRadius;
                    return 0;
                }
                case key::f1: {
                    mode = imode::game;
                    return 0;
                }
                case key::escape: {
                    mode = imode::game;
                    return 0;
                }
            }
            return key;
        }

        case imode::selectCloseTarget: {
            switch(key) {
                // Directions
                case key::up: {
                    sActor = c_helper::getCreatureFromTile(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY() - 1);
                    return 0;
                }
                case key::down: {
                    sActor = c_helper::getCreatureFromTile(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY() + 1);
                    return 0;
                }
                case key::left: {
                    sActor = c_helper::getCreatureFromTile(engine -> game -> actorManager.getPlayer() -> getMapX() - 1, engine -> game -> actorManager.getPlayer() -> getMapY());
                    return 0;
                }
                case key::right: {
                    sActor = c_helper::getCreatureFromTile(engine -> game -> actorManager.getPlayer() -> getMapX() + 1, engine -> game -> actorManager.getPlayer() -> getMapY());
                    return 0;
                }
            }
            return key;
        }

        case imode::dialogue: {
            switch(key) {
                case key::a: {
                    inputText += "a";
                    return key;
                }
            }
            return key;
        }
    }
    return key;
}