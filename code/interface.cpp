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
    sAbility = "";
    targetText = "";
    inputText = "";
    pasteMode = false;
    info = new c_winInfo(44, 16, 23, 24);
    map = new c_winMap(0, 0, 67, 39);
    //gamelog = new c_winGamelog(0, 39, 67, 6);
    //sidebar = new c_winSidebar("sidebar", 0, 43, 80, 2);
    character = new c_winCharacter(0, 0, 67, 40);
    character -> init();
    sidebar = new c_winSidebar(66, 0, 14, 45);
    sidebar -> init();
    death = new c_winDeath(25, 5, 17, 10);
}

int c_interface::update(int key) {

    // We reset selections
    sTile = 0;
    sActor = 0;
    sAbility = "";
    //f_help = false;

    if(engine -> game -> actorManager.getPlayer()) {
        key = sidebar -> update(key, engine -> getMouse());
        if(mode == imode::game or mode == imode::edit) {
            key = map -> update(key, engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY(), engine -> getMouse());
        } else if(mode == imode::character) {
            key = character -> update(key);
        }
    }
    key = processInput(key);
    return key;
}

void c_interface::draw() {
    switch(mode) {

        // MAIN SCREEN
        case imode::game: {
            if(engine -> game -> actorManager.getPlayer()) {
                map -> draw(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY());
            }
            sidebar -> draw();
            engine -> game -> gamelog.draw();
            if(f_help) {
                info -> draw(true);
            }
                
            // Draw debug info
            if(engine -> game and engine -> game -> map) {
                engine -> screen.drawText(std::to_string(engine -> game -> map -> getX()) + "." + std::to_string(engine -> game -> map -> getY()) + "." + std::to_string(engine -> game -> map -> getZ()), 1042, 4, sf::Color::White, textAlign::left);
                engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> getMapX()) + "." + std::to_string(engine -> game -> actorManager.getPlayer() -> getMapY()), 1042, 20, sf::Color::White, textAlign::left);
            }
            break;
        }

        // CHARACTER SCREEN
        case imode::character: {
            sidebar -> draw();
            engine -> game -> gamelog.draw();
            info -> draw(false);
            character -> draw();
            break;
        }

        // EDIT MODE
        case imode::edit: {
            if(engine -> game -> actorManager.getPlayer()) {
                map -> draw(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY());
            }
            sidebar -> draw();
            engine -> game -> gamelog.draw();
            std::string str = "> " + engine -> getCommand();
            engine -> screen.drawText(str, 4, 4, sf::Color::White);
            break;
        }

        // TARGET SELECTION
        case imode::selectCloseTarget: {
            if(engine -> game -> actorManager.getPlayer()) {
                map -> draw(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY());
            }
            sidebar -> draw();
            engine -> game -> gamelog.draw();
            //drawTargetSelectionMessage();
            break;
        }
    }

    // Draw mouse
    drawMouse();
}

void c_interface::drawMouse() {
if(engine -> isLoading()) {
        engine -> screen.drawTexture("sandglass", engine -> getMouse().x, engine -> getMouse().y);
    } else if(f_help) {
        engine -> screen.drawTexture("cursor-help", engine -> getMouse().x, engine -> getMouse().y);
    } else {
        engine -> screen.drawTexture("cursor", engine -> getMouse().x, engine -> getMouse().y);
    }
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
        engine -> sound.update();
        update(engine -> input());
        engine -> game -> gamelog.update();
        engine -> screen.clear();
        draw();
        engine -> screen.display();
    }
    this -> mode = imode::game;
}

// Opens a talk window in the interface with several dialogue options
void c_interface::talk(const int& actor) {
    std::string path = "data/dialogue/" + engine -> game -> actorManager.getActor(actor) -> getId() + ".dat";
    if(!TCODSystem::fileExists(path.c_str())) {
        engine -> message(path + " does not exist.");
        return;
    }
    
}

const int& c_interface::selectCloseTarget(const int& prevMode, const std::string& targetText, const int& type) {
    if(!engine -> game or !engine -> game -> map or !engine -> game -> actorManager.getPlayer()) {
        return 0;
    }
    mode = imode::selectCloseTarget;
    sActor = 0;
    this -> targetText = targetText;
    this -> targetType = type;
    while(sActor == 0) {
        engine -> game -> gamelog.clear();
        engine -> sound.update();
        update(engine -> input());
        engine -> game -> gamelog.update();
        engine -> screen.clear();
        draw();
        engine -> screen.display();
    }
    mode = prevMode;
    return sActor;
}

// Wait for enter key and deletes game
void c_interface::gameOver() {
    if(!engine -> game) {
        return;
    }
    //mode = imode::gameOver;
    bool loop = true;
    while(loop == true) {
        if(engine -> input() == key::enter) {
            loop = false;
        } else {
            engine -> screen.clear();
            engine -> sound.update();
            update(0);
            if(engine -> game -> actorManager.getPlayer()) {
                map -> draw(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY());
            }
            sidebar -> draw();
            engine -> game -> gamelog.draw();
            death -> draw();
            drawMouse();
            engine -> screen.display();
        } 
    }
}

int c_interface::processInput(int key) {

    if(key == 0) {
        return 0;
    }

    // We check help first, as it's viable in every screen, or at least it should (usability you fool!)
    if(key == key::rclick) {
        if(f_help) {
            f_help = false;
        } else {
            f_help = true;
        }
        return 0;
    }

    switch(mode) {

        case imode::game: {
            switch(key) {

                // Change view
                case key::space: {
                    mode = imode::character;
                    character -> update(0);
                    return 0;
                }

                // Edit
                case key::f1: {
                    edit();
                    return 0;
                }

                // Quit
                case key::escape: {
                    exit(EXIT_SUCCESS);
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
                    sActor = c_helper::getActorFromTile(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY() - 1, targetType);
                    return 0;
                }
                case key::down: {
                    sActor = c_helper::getActorFromTile(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY() + 1, targetType);
                    return 0;
                }
                case key::left: {
                    sActor = c_helper::getActorFromTile(engine -> game -> actorManager.getPlayer() -> getMapX() - 1, engine -> game -> actorManager.getPlayer() -> getMapY(), targetType);
                    return 0;
                }
                case key::right: {
                    sActor = c_helper::getActorFromTile(engine -> game -> actorManager.getPlayer() -> getMapX() + 1, engine -> game -> actorManager.getPlayer() -> getMapY(), targetType);
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