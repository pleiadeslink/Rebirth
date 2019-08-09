

c_gamelog::c_gamelog() {
    x = 0;
    y = 39;
    width = 67;
    height = 6;
	scroll = 0;
    text = "";
}

void c_gamelog::update() {
    if(newMessage == true) {
        v_gamelog.push_back(currentMessage);
    }
}

void c_gamelog::message(std::string str) {
    newMessage = true;
    str.insert(0, "%0");

    currentMessage.cstr = currentMessage.cstr + " " + str;

    // Remove color codes from string and stores it in str
    for(int i = 0; i < str.size(); ++i) {
        if(str[i] == '%') {
            str.erase(i, 2);
            i = 0;
        }
    }

    currentMessage.str = currentMessage.str + " " + str;

    // Updates stat bar
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
        text.append(" | Acc ");
		text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getAttack()));
        text.append(" | Def ");
		text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getDefense()));
        text.append(" | Pro ");
		text.append(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getProtection()));
        text.append(" | Weight: 13/50");
    }
}

s_message c_gamelog::getLastMessage(const int& position) {
    int size = v_gamelog.size();
    s_message emptyMessage;
    emptyMessage.str = "";
    emptyMessage.cstr = "";
    if(size == 0 or position > size - 1) {
        return emptyMessage;
    }
    return v_gamelog[size - 1 - position];
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
	engine -> screen.drawCText(getLastMessage(0).cstr.c_str(), x * 16 - 4, (y + height - 1) * 16 - 4);
	engine -> screen.drawText(getLastMessage(1).str.c_str(), x * 16 - 4, (y + height - 2) * 16 - 4, color("dark grey"));
	engine -> screen.drawText(getLastMessage(2).str.c_str(), x * 16 - 4, (y + height - 3) * 16 - 4, color("dark grey"));
	engine -> screen.drawText(getLastMessage(3).str.c_str(), x * 16 - 4, (y + height - 4) * 16 - 4, color("dark grey"));
	//engine -> screen.drawText(engine -> game -> gamelog.getLastMessage(4).str.c_str(), x * 16, (y + height - 5) * 16 - 4, color("dark grey"));

}