

c_gamelog::c_gamelog() {
    x = 0;
    y = 39;
    width = 67;
    height = 6;
	scroll = 0;
    text = "";
    v_gamelog.push_back("");
    v_gamelog.push_back("");
    v_gamelog.push_back("");
    v_gamelog.push_back("");
    v_gamelog.push_back("");
}

void c_gamelog::update() {
    if(newMessage == true) {
        for(int j = 0; j < 3; ++j) {
            std::string str = c_helper::removeColor(v_gamelog[j]);
            str.insert(0, "%7");
            v_gamelog[j] = str;
        }
        const int maxChar = 130;
        currentMessage.str = c_helper::justify(currentMessage.str, maxChar);
        int tagCounter = 0;
        int pushCounter = 0;
        if(currentMessage.cstr.size() <= maxChar) {
            v_gamelog.insert(v_gamelog.begin(), currentMessage.cstr);
            return;
        } else {
            for(int i = 0; i < currentMessage.str.size(); ++i) {
                if(currentMessage.cstr[i] == '%') {
                    ++tagCounter;
                }
                if(currentMessage.str[i] == '/' and currentMessage.str[i + 1] == 'n') {
                    std::string line = currentMessage.cstr.substr(0, i + (tagCounter * 2));
                    currentMessage.str.erase(0, i + 2);
                    currentMessage.cstr.erase(0, i + (tagCounter * 2));
                    if(currentMessage.cstr[1] != ' ') {
                        currentMessage.cstr.insert(0, " ");
                    }
                    if(currentMessage.cstr[0] == ' ') {
                        currentMessage.cstr.erase(0, 1);
                    }                    
                    v_gamelog.insert(v_gamelog.begin(), line);
                    ++pushCounter;
                    tagCounter = 0;
                    newMessage = false;
                    i = 0;

                    
                } else if(i + 1 == currentMessage.str.size()) {
                    v_gamelog.insert(v_gamelog.begin(), currentMessage.cstr);
                    return;
                }
            }
        }
    }
}

void c_gamelog::message(std::string str) {
    newMessage = true;
    str.insert(0, "%0");

    currentMessage.cstr = currentMessage.cstr + " " + str;

    // Remove color codes from string and stores it in str
    str = c_helper::removeColor(str);

    currentMessage.str = currentMessage.str + " " + str;

    updateStatText();
}

std::string c_gamelog::getLastMessage(const int& position) {
    int size = v_gamelog.size();
    if(size == 0 or position > size - 1) {
        return "";
    }
    return v_gamelog[position];
}

void c_gamelog::clear() {
	currentMessage.str = "";
    currentMessage.cstr = "";
    newMessage = false;
}

void c_gamelog::draw() {
    if(!engine -> game) {
		return;
	}

    // Frame
    for(int i = 0; i < width - 1; ++i) {
        engine -> screen.drawTexture("hbar", (x + i) * 16, y * 16);
    }
    engine -> screen.drawTexture("ribbon", (x + width - 1) * 16, y * 16);
    engine -> screen.drawTexture("ribbon", (x + width - 1) * 16, (y + height - 1) * 16);
    engine -> screen.drawBox(x * 16, (y + 1) * 16, width * 16 - 16, 16, color("darker sepia"));
    engine -> screen.drawBox(x * 16, (y + 1) * 16 + 16 - 2, width * 16 - 16, 2, color("darkest sepia"));
	if(engine -> game and engine -> game -> actorManager.getPlayer()) {
		engine -> screen.drawText(text, (x) * 16 + 4, (y + 1) * 16 - 4, color("lighter sepia"));
	}

    // Messages
	engine -> screen.drawCText(getLastMessage(0).c_str(), x * 16 - 4, (y + height - 1) * 16 - 4);
	engine -> screen.drawCText(getLastMessage(1).c_str(), x * 16 - 4, (y + height - 2) * 16 - 4);
	engine -> screen.drawCText(getLastMessage(2).c_str(), x * 16 - 4, (y + height - 3) * 16 - 4);
	engine -> screen.drawCText(getLastMessage(3).c_str(), x * 16 - 4, (y + height - 4) * 16 - 4);
}

void c_gamelog::updateStatText() {
    if(engine -> game and engine -> game -> actorManager.getPlayer()) {
        c_actor* p_player = engine -> game -> actorManager.getPlayer();
        text = "";
        text.append("\003 ");
        text.append(std::to_string(p_player -> life -> getHealth()));
        text.append("/");
        text.append(std::to_string(p_player -> life -> getMaxHealth()));
        text.append(" | ");
        text.append("\004 ");
        text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getHealth()));
        text.append("/");
        text.append(std::to_string(p_player -> life -> getMaxHealth()));
        text.append(" | ");
        text.append("\016 ");
        text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getHealth()));
        text.append("/");
        text.append(std::to_string(p_player -> life -> getMaxHealth()));
        text.append(" | Str ");
        text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> player -> getConstitution()));
        text.append(" | Agi ");
        text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> player -> getAgility()));
        text.append(" | Int ");
        text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> player -> getSpirit()));
        text.append(" | Luc ");
        text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> player -> getLuck()));
        text.append(" | Dam ");
        text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getMinDamage()));
        text.append("/");
        text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getMaxDamage()));
        /*text.append(" | Acc ");
        text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getAttack()));
        text.append(" | Def ");
        text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getDefense()));
        text.append(" | Pro ");
        text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getProtection()));
        */text.append(" | Weight: 13/50");
    }
}