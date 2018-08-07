c_window::c_window(const std::string& id, const int& x, const int& y, const int& width, const int& height) {
	this -> id = id;
	this -> x = x;
	this -> y = y;
	this -> width = width;
	this -> height = height;
}

void c_window::update() {
    /*/ Update items
    if(v_label.size() != 0) {
        for(int i = 0; i < v_label.size(); ++i) {
            v_label[i] -> update();
        }
    }*/
}

void c_window::draw() {

	// Draw background
    /*if(texture == "none") {
        engine -> screen.drawBox(x, y, width, height, 40, 40, 40);
    } else {
        engine -> screen.drawTexture(texture, x, y);
    }*/

    // Gamelog
    /*if(isGamelog == true) {
        switch(engine -> interface.getMode()) {
            case imode::game: {
                for(int i = 0; i < 7; ++i) {
                    if(engine -> game) {
                        engine -> screen.drawText(engine -> game -> getLastMessage(i + 1), x + 12, y + 14 + 6 * 20 - i * 20, 16);
                    }
                }
                break;
            }
            case imode::selectTarget: {
                engine -> screen.drawText(engine -> interface.getTargetText() + "... (select a target)", x + 12, y + 14, 18);
                break;
            }
        }
    }*/
    
    /*/ Draw items
    if(v_label.size() != 0) {
        for(int i = 0; i < v_label.size(); ++i) {
            v_label[i] -> draw();
        }
    }*/
}

/*void c_window::addLabel(const int& x, const int& y, const std::string text) {
	c_label* newLabel = new c_label(this, x, y, text);
	v_label.push_back(newLabel); 
}*/

void c_window::drawFrame() {
    drawFrame(x, y, width, height);
}

void c_window::drawFrame(const int& x, const int& y, const int& width, const int& height) {
    // Draw ribbons
    engine -> screen.drawTexture("ribbon", x * 16, y * 16);
    engine -> screen.drawTexture("ribbon", (x + width - 1) * 16, y * 16);
    engine -> screen.drawTexture("ribbon", x * 16, (y + height - 1) * 16);
    engine -> screen.drawTexture("ribbon", (x + width - 1) * 16, (y + height - 1) * 16);

    // Top bar
    for(int i = 1; i < width - 1; ++i) {
        engine -> screen.drawTexture("hbar", (x + i) * 16, y * 16);
    }
    // Bottom bar
    for(int i = 1; i < width - 1; ++i) {
        engine -> screen.drawTexture("hbar", (x + i) * 16, (y + height - 1) * 16);
    }
    // Up bar
    for(int i = 1; i < height - 1; ++i) {
        engine -> screen.drawTexture("vbar", x * 16, (y + i) * 16);
    }
    // Up bar
    for(int i = 1; i < height - 1; ++i) {
        engine -> screen.drawTexture("vbar", (x + width - 1) * 16, (y + i) * 16);
    }
}

void c_window::drawHBar(const int& hpos) {
    engine -> screen.drawTexture("ribbon", x * 16, (y + hpos) * 16);
    engine -> screen.drawTexture("ribbon", (x + width - 1) * 16, (y + hpos) * 16);   
    for(int i = 1; i < width - 1; ++i) {
        engine -> screen.drawTexture("hbar", (x + i) * 16, (y + hpos) * 16);
    }
}

void c_window::drawVLine(const int& x, const int& y, const int& size) {
    engine -> screen.drawTexture("ribbon", x * 16, y * 16);
    engine -> screen.drawTexture("ribbon", x * 16, (y + size - 1) * 16);   
    for(int i = 1; i < size - 1; ++i) {
        engine -> screen.drawTexture("vbar", x * 16, (y + i) * 16);
    }    
}

void c_window::drawTitle(const std::string text, const int& hpos) {
    engine -> screen.drawBox(x * 16, (y + hpos) * 16, width * 16, 16, color("darker sepia"));
    engine -> screen.drawBox(x * 16, (y + hpos) * 16 + 16 - 2, width * 16, 2, color("darkest sepia"));
    engine -> screen.drawText(text, (x + 1) * 16 + 4, (y + hpos) * 16 - 4, color("lighter sepia"));
}