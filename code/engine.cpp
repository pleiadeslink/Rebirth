c_engine::c_engine()
:   command(""),
    commandPrompt(false) {
}

c_engine::~c_engine() {
    // Write log to file
    std::ofstream out("log.txt");
    for(unsigned int i = 0; i < v_messageLog.size(); ++i) {
        out << v_messageLog[i] << "\n";
    }
    out.close();
}

void c_engine::start() {
	
    message("---------");
    message(" REBIRTH ");
    message("---------");

    // Load colors
    structEventData eventData;
	eventData.type = "color";
	engine -> game -> runScript(eventData);

    // Load assets
    assetManager.load();

    // Create screen
    screen.start(false);

    // Create game
    game = new c_game();
    game -> newGame();
    interface.init();
    sf::Vector2f v(0, 0);
    //c_fire fire(8,160,90,v);
    //fire.setFireSourceStrength(10);
    // Main loop
    int key = 0;
    while(0 == 0) {

        screen.clear();
        interface.draw();
        //fire.render(*screen.getWindow());
        screen.display();
        
        // We don't receive input if the engine is "loading"
        if(!isLoading()) {
            key = input();
        } else {
            key = 0;
        }
        sound.update();
        if(game and interface.getMode() == imode::game) {
            game -> update(key);
        }
        key = interface.update(key);
        //fire.update();
    }
}

// Adds message to the system log and prints it in the program console
void c_engine::message(std::string message) {
    v_messageLog.push_back(message);
    std::cout << message << std::endl;
}

int c_engine::input() {
    sf::Event event;
    sf::RenderWindow* rwindow = screen.getWindow();
    while (rwindow -> pollEvent(event)) {

        // Mouse event.type == sf::Event::MouseButtonReleased
        if(event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Left) {
                return key::lclick;
            } else if(event.mouseButton.button == sf::Mouse::Right) {
                return key::rclick;
            }
        }

        // Edit
        if(interface.getMode() == imode::edit and event.type == sf::Event::TextEntered) {
            if(event.text.unicode == 8 and command.size() != 0) { // Backspace key
                command.pop_back();
            } else if(event.text.unicode == 13) { // Return key
                std::string str = "Command run: " + command;
                kaguya::State state;
                #include "luabind.cpp"
                state.dostring(command);
                message(str);
                commandHistory.push_back(command);
                commandIndex = commandHistory.size() - 1;
                command = "";
            } else if(event.text.unicode == 9) { // Tab key
                if(commandHistory.size() != 0) {
                    command = commandHistory[commandIndex];
                    if(commandIndex > 0) {
                        --commandIndex;
                    }
                }
            } else if(event.text.unicode < 128 and event.text.unicode != 8) {
                command.push_back((char)event.text.unicode);
            }

        // Normal
        } else if(event.type == sf::Event::KeyPressed) {
            switch(event.key.code) {
                case sf::Keyboard::A: {
                    return key::a;
                }
                case sf::Keyboard::B: {
                    return key::b;
                }
                case sf::Keyboard::C: {
                    return key::c;
                }
                case sf::Keyboard::D: {
                    return key::d;
                }
                case sf::Keyboard::E: {
                    return key::e;
                }
                case sf::Keyboard::F: {
                    return key::f;
                }
                case sf::Keyboard::G: {
                    return key::g;
                }
                case sf::Keyboard::H: {
                    return key::h;
                }
                case sf::Keyboard::I: {
                    return key::i;
                }
                case sf::Keyboard::J: {
                    return key::j;
                }
                case sf::Keyboard::K: {
                    return key::k;
                }
                case sf::Keyboard::L: {
                    return key::l;
                }
                case sf::Keyboard::M: {
                    return key::m;
                }
                case sf::Keyboard::N: {
                    return key::n;
                }
                case sf::Keyboard::O: {
                    return key::o;
                }
                case sf::Keyboard::P: {
                    return key::p;
                }
                case sf::Keyboard::Q: {
                    return key::q;
                }
                case sf::Keyboard::R: {
                    return key::r;
                }
                case sf::Keyboard::S: {
                    return key::s;
                }
                case sf::Keyboard::T: {
                    return key::t;
                }
                case sf::Keyboard::U: {
                    return key::u;
                }
                case sf::Keyboard::V: {
                    return key::v;
                }
                case sf::Keyboard::W: {
                    return key::w;
                }
                case sf::Keyboard::X: {
                    return key::x;
                }
                case sf::Keyboard::Y: {
                    return key::y;
                }
                case sf::Keyboard::Z: {
                    return key::z;
                }
                case sf::Keyboard::Num0: {
                    return key::num0;
                }
                case sf::Keyboard::Num1: {
                    return key::num1;
                }
                case sf::Keyboard::Num2: {
                    return key::num2;
                }
                case sf::Keyboard::Num3: {
                    return key::num3;
                }
                case sf::Keyboard::Num4: {
                    return key::num4;
                }
                case sf::Keyboard::Num5: {
                    return key::num5;
                }
                case sf::Keyboard::Num6: {
                    return key::num6;
                }
                case sf::Keyboard::Num7: {
                    return key::num7;
                }
                case sf::Keyboard::Num8: {
                    return key::num8;
                }
                case sf::Keyboard::Num9: {
                    return key::num9;
                }
                case sf::Keyboard::F1: {
                    return key::f1;
                }
                case sf::Keyboard::Up: {
                    return key::up;
                }
                case sf::Keyboard::Down: {
                    return key::down;
                }
                case sf::Keyboard::Left: {
                    return key::left;
                }
                case sf::Keyboard::Right: {
                    return key::right;
                }
                case sf::Keyboard::Space: {
                    return key::space;
                }
                case sf::Keyboard::Escape: {
                    return key::escape;
                }
                case sf::Keyboard::Return: {
                    return key::enter;
                }
                case sf::Keyboard::LControl: {
                    return key::lcontrol;
                }
                case sf::Keyboard::Tab: {
                    return key::tab;
                }
                case sf::Keyboard::BackSpace: {
                    return key::backspace;
                }
                case sf::Keyboard::Add: {
                    return key::add;
                }
                case sf::Keyboard::Subtract: {
                    return key::subtract;
                }
                case sf::Keyboard::Comma: {
                    return key::comma;
                }
                case sf::Keyboard::Period: {
                    return key::period;
                }
            }
        } else if(event.type == sf::Event::Closed) {
            exit(EXIT_SUCCESS);
        }
    }
}

void c_engine::runScript(const std::string& path) {
    structEventData data;
    data.type = "none";
    runScript(path, data);
 }

 void c_engine::runScript(const std::string& path, const structEventData& data) {

    kaguya::State state;
    #include "luabind.cpp"

    // Bind event data
    state["s_data"].setClass(kaguya::UserdataMetatable<structEventData>()
                            .setConstructors<structEventData()>()
                            .addFunction("setEmitter", &structEventData::setEmitter)
                            .addFunction("setTarget", &structEventData::setTarget)
                            .addFunction("setType", &structEventData::setType)
                            .addFunction("setMapX", &structEventData::setMapX)
                            .addFunction("setMapY", &structEventData::setMapY)
                            .addFunction("setValue1", &structEventData::setValue1)
                            .addFunction("setString1", &structEventData::setString1));
    state["emitter"] = data.emitter;
    state["target"] = data.target;
    state["type"] = data.type;
    state["mapX"] = data.mapX;
    state["mapY"] = data.mapY;
    state["value1"] = data.value1;
    state["string1"] = data.string1;
    
    // Run file
    state.dofile("data/lua/enum.lua");
    std::stringstream str;
    str << "data/lua/" << path;
    state.dofile(str.str());
 }