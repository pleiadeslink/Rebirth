c_winGamelog::c_winGamelog(const int& x, const int& y, const int& width, const int& height) {
	this -> x = x;
	this -> y = y;
	this -> width = width;
	this -> height = height;
	scroll = 0;
}

void c_winGamelog::draw() {

	// Draw frame
	//c_interface::drawLine(console, 0, 0, width, 1, global::frameColor);

	if(!engine -> game) {
		return;
	}

	// Shade
	for(int i = 0; i < 80; ++i) {
		engine -> screen.drawTexture("fog", (x + i) * 16, (y + height - 1) * 16);
		engine -> screen.drawTexture("fog", (x + i) * 16, (y + height - 2) * 16);
		engine -> screen.drawTexture("fog", (x + i) * 16, (y + height - 3) * 16);
		engine -> screen.drawTexture("fog", (x + i) * 16, (y + height - 4) * 16);
	}

	engine -> screen.drawText(engine -> game -> gamelog.getLastMessage(0).c_str(), x * 16, (y + height - 1) * 16 - 4, color("white"));
	engine -> screen.drawText(engine -> game -> gamelog.getLastMessage(1).c_str(), x * 16, (y + height - 2) * 16 - 4, color("light grey"));
	engine -> screen.drawText(engine -> game -> gamelog.getLastMessage(2).c_str(), x * 16, (y + height - 3) * 16 - 4, color("dark grey"));
	engine -> screen.drawText(engine -> game -> gamelog.getLastMessage(3).c_str(), x * 16, (y + height - 4) * 16 - 4, color("darker grey"));
	/*} else {
		if(tile -> hasAnyActor() == true) {
			std::vector<int> actors = tile -> getActorList();
			c_actor* p_actor = engine -> game -> actorManager.getActor(actors[actors.size() - 1]);
			engine -> screen.drawText(p_actor -> getName(), x + 8, (y + height - 3) * 16 - 6, sf::Color::White);
			engine -> screen.drawText(p_actor -> getDescription(), x + 8, (y + height - 2) * 16 - 6, color("light grey"));
		} else {
			engine -> screen.drawText(tile -> getName(), x + 8, (y + height - 3) * 16 - 6, sf::Color::White);	
		}
	}*/
}