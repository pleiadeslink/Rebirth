void c_winTarget::init(const int& x, const int& y, const int& width, const int& height) {
	this -> x = x;
	this -> y = y;
	this -> width = width;
	this -> height = height;
	this -> actor = 0;
}

const int& c_winTarget::update(int key) {

	if(actor != 0) {

		sf::Vector2i mousePos = engine -> getMouse();

		// If mouse is in active area
		if(mousePos.x > x * 16 and mousePos.x < x * 16 + width * 16 and mousePos.y > y * 16 and mousePos.y < y * 16 + height * 16 + 1) {

			// Selects the item
			if(engine -> interface.isHelpActivated()) {
            	engine -> interface.selectActor(actor);
			}
			return key;
		}
	}
	return key;
}
/*
	// << LOCATIONS >>

	} else {
		drawTitle("Locations", 8);
		std::vector<int> locations = engine -> game -> actorManager.getLocations();
				
		if(locations.size() > 0) {
			int counter = 0;
			for(int i = 0; i < locations.size(); ++i) {

				// If the location is on a visible tile, draw panel
				c_actor* p_actor = engine -> game -> actorManager.getActor(locations[i]);
				if(engine -> game -> map -> getTile(p_actor -> getMapX(), p_actor -> getMapY()) -> getVisible() == true) {
							
					// Bar
					engine -> screen.drawBox((x + 1) * 16, (y + 7 + counter) * 22 - 10, (width - 2) * 16, 22, color("dark sepia"));
					engine -> screen.drawTexture("targetbar", (x + 1) * 16, (y + 7 + counter) * 22 - 10);

					// Symbol
					engine -> screen.drawTile(p_actor -> getTileX(), p_actor -> getTileY(), (x + 1) * 16 + 3 + 1, (y + 7 + counter) * 22 - 9 + 1, sf::Color::Black);
					engine -> screen.drawTile(p_actor -> getTileX(), p_actor -> getTileY(), (x + 1) * 16 + 3, (y + 7 + counter) * 22 - 9, p_actor -> getColor());
							

					// Name
					engine -> screen.drawText(p_actor -> getName(), (x + 3) * 16 + 1 - 8, (y + 7 + counter) * 22 - 11 + 1, sf::Color::Black);
					engine -> screen.drawText(p_actor -> getName(), (x + 3) * 16 - 8, (y + 7 + counter) * 22 - 11, sf::Color::White);

					++counter;
				}
			}
		}	
	}
    */

void c_winTarget::draw() {
	if(actor == 0) {
		return;
	}

    c_actor* p_actor = engine -> game -> actorManager.getActor(actor);

    // Health bar
	if(p_actor -> life) {
		engine -> screen.drawBox(x  * 16, y * 16, width * 16, height * 16, color("darkest red"));
		engine -> screen.drawBox(x * 16, y * 16, width * 16 * p_actor -> life -> getHealth() / p_actor -> life -> getMaxHealth(), height * 16, color("darker red"));
	}
	
	engine -> screen.drawTexture("targetbar", x * 16, y * 16 );

    // Symbol
    engine -> screen.drawTile(p_actor -> getTileX(), p_actor -> getTileY(), x * 16 + 3 + 1, y * 16 + 1, sf::Color::Black);
    engine -> screen.drawTile(p_actor -> getTileX(), p_actor -> getTileY(), x * 16 + 3, y * 16, p_actor -> getColor());
            
    // Name
    engine -> screen.drawText(p_actor -> getName(), (x + 2) * 16 + 1 - 8, y * 16 + 1 - 3, sf::Color::Black);
    engine -> screen.drawText(p_actor -> getName(), (x + 2) * 16 - 8, y * 16 - 3, color("lightest grey"));
}

/*void c_winTarget::drawOverlay() {
	sf::Vector2i mousePos = engine -> getMouse();
	if(item != 0 and mousePos.x > x and mousePos.x < x + width and mousePos.y > y and mousePos.y < y + height) {
		engine -> screen.drawBox(x, y, 240, 24, color("darkest grey"));
	}
}*/

void c_winTarget::clear() {
	actor = 0;
}

void c_winTarget::setActor(const int& uid) {
	actor = uid;
}