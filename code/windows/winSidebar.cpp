c_winSidebar::c_winSidebar(const int& x, const int& y, const int& width, const int& height) {
	this -> x = x;
	this -> y = y;
	this -> width = width;
	this -> height = height;
	this -> tileButtonWidth = 11;
	this -> tileButtonHeight = 8;
	this -> actorButtonWidth = 11;
	this -> actorButtonHeight = 14;
}

void c_winSidebar::init() {

	// Create tile button matrix
	m_tileButtons = new c_winButton*[tileButtonWidth];
	for(int i = 0; i < tileButtonWidth; ++i) {
		m_tileButtons[i] = new c_winButton[tileButtonHeight];
	}
    for(int i1 = 0; i1 < tileButtonWidth; ++i1) {
        for(int i2 = 0; i2 < tileButtonHeight; ++i2) {
            m_tileButtons[i1][i2].init(x + i1 + 1, y + i2 + 9, global::tileSize, global::tileSize, buttonType::tile);
        }
    }

	// Create actor button matrix
	m_actorButtons = new c_winButton*[actorButtonWidth];
	for(int i = 0; i < actorButtonWidth; ++i) {
		m_actorButtons[i] = new c_winButton[actorButtonHeight];
	}
    for(int i1 = 0; i1 < actorButtonWidth; ++i1) {
        for(int i2 = 0; i2 < actorButtonHeight; ++i2) {
            m_actorButtons[i1][i2].init(x + i1 + 1, y + i2 + 13, global::tileSize, global::tileSize, buttonType::actor);
        }
    }
}

int c_winSidebar::update(int key, sf::Vector2i mousePos) {
	switch(engine -> interface.getMode()) {
		case imode::game: {
			break;
		}
		case imode::edit: {

			// Update tile buttons
			int index = 0;
			std::vector<std::string> v_tileIdList = engine -> assetManager.getTileIdList();
			if(v_tileIdList.size() != 0) {
				for(int i2 = 0; i2 < tileButtonHeight; ++i2) {
					for(int i1 = 0; i1 < tileButtonWidth; ++i1) {
				
						// Sets id
						if(index <= v_tileIdList.size() - 1) {
							m_tileButtons[i1][i2].setId(v_tileIdList[index]);
						}
						++index;

						// If mouse is inside the area, check input
						if(mousePos.x > x * 16 and mousePos.y > y * 16
						and mousePos.x < (x + width) * 16 and mousePos.y < (y + height) * 16) {
							key = m_tileButtons[i1][i2].update(key, mousePos);
						}
					}
				}
			}

			// Update actor buttons
			index = 0;
			std::vector<std::string> v_actorIdList = engine -> assetManager.getActorIdList();
			if(v_actorIdList.size() != 0) {
				for(int i2 = 0; i2 < actorButtonHeight; ++i2) {
					for(int i1 = 0; i1 < actorButtonWidth; ++i1) {
				
						// Sets id
						if(index <= v_actorIdList.size() - 1) {
							m_actorButtons[i1][i2].setId(v_actorIdList[index]);
						}
						++index;

						// If mouse is inside the area, check input
						if(mousePos.x > x * 16 and mousePos.y > y * 16
						and mousePos.x < (x + width) * 16 and mousePos.y < (y + height) * 16) {
							key = m_actorButtons[i1][i2].update(key, mousePos);
						}
					}
				}
			}

			break;
		}
	}

	// Deletes input before returning if cursor is inside area
	if(mousePos.x > x * 16 and mousePos.y > y * 16 and mousePos.x < (x + width) * 16 and mousePos.y < (y + height) * 16) {
		key = 0;
	}
	return key;
}

void c_winSidebar::draw() {
	if(!engine -> game or !engine -> game -> map) {
		return;
	}

	// Edit mode
	if(engine -> interface.getMode() == imode::edit) {

		// Draw title
		engine -> screen.drawText("EDIT MODE", x * 16 + ((width * 16) / 2), (y + 1) * 16 + 8 - 2, sf::Color::White, textAlign::center);

		// Draw active edit element icon and name
		switch(engine -> interface.getEmode() ) {
			case emode::tile: {
				structTileAsset* p_tile = engine -> interface.getEditTile();
				if(p_tile != 0) {
					int xf = x * 16 + ((width * 16) / 2) - 16;
					int yf = (y + 3) * 16 + 4;
					//engine -> screen.drawTexture(p_tile -> texture, xf, yf);
                	//p_tile -> drawOverlay(xf, yf, p_tile -> type, p_tile -> olcolor, 2);
					engine -> screen.drawText(p_tile -> name, xf + 16, (y + 5) * 16 + 8, sf::Color::White, textAlign::center);
				}
				break;
			}
			case emode::actor: {
				structActorAsset* p_actor = engine -> interface.getEditActor();
				if(p_actor != 0) {
					int xf = x * 16 + ((width * 16) / 2) - 16;
					int yf = (y + 3) * 16 + 4;
					//engine -> screen.drawTexture(p_actor -> texture, xf, yf);
					engine -> screen.drawText(p_actor -> name, xf + 16, (y + 5) * 16 + 8, sf::Color::White, textAlign::center);
				}
				break;
			}
		}

		// Draw tile buttons
		for(int i1 = 0; i1 < tileButtonWidth; ++i1) {
			for(int i2 = 0; i2 < tileButtonHeight; ++i2) {
				m_tileButtons[i1][i2].draw();
			}
		}

		// Draw actor buttons
		for(int i1 = 0; i1 < actorButtonWidth; ++i1) {
			for(int i2 = 0; i2 < actorButtonHeight; ++i2) {
				m_actorButtons[i1][i2].draw();
			}
		}

		// Draw external frame
		drawHBar(7);
		drawTitle("Tiles", 8);
		drawHBar(11);
		drawTitle("Actors", 12);
		drawFrame();
		return;
	}

    c_actor* p_player = engine -> game -> actorManager.getPlayer();

	if(!engine -> game or !p_player) {
		return;
	}

	std::string str;

	// << HEALTH BARS >>

	// Health bar
	str = std::to_string(p_player -> life -> getHealth()) + "/" + std::to_string(p_player -> life -> getMaxHealth());
	engine -> screen.drawBox(x * 16, (y + 1) * 16, width * 16, 32, color("darkest red"));
	engine -> screen.drawBox(x * 16, (y + 1) * 16, (width * 16) * p_player -> life -> getHealth() / p_player -> life -> getMaxHealth() , 32, color("darker red"));
	engine -> screen.drawTexture("healthbar", x * 16 + 2, (y + 1) * 16);
	engine -> screen.drawText(str, x * 16 + ((width * 16) / 2) + 1, (y + 1) * 16 + 4 + 1, sf::Color::Black, textAlign::center);
	engine -> screen.drawText(str, x * 16 + ((width * 16) / 2), (y + 1) * 16 + 4, sf::Color::White, textAlign::center);

	// Stamina bar
	str = std::to_string(p_player -> life -> getHealth()) + "/" + std::to_string(p_player -> life -> getMaxHealth());
	engine -> screen.drawBox(x * 16, (y + 3) * 16, width * 16, 32, color("darkest amber"));
	engine -> screen.drawBox(x * 16, (y + 3) * 16, (width * 16) * p_player -> life -> getHealth() / p_player -> life -> getMaxHealth() , 32, color("darker amber"));
	engine -> screen.drawTexture("healthbar", x * 16 + 2, (y + 3) * 16);
	engine -> screen.drawText(str, x * 16 + ((width * 16) / 2) + 1, (y + 3) * 16 + 4 + 1, sf::Color::Black, textAlign::center);
	engine -> screen.drawText(str, x * 16 + ((width * 16) / 2), (y + 3) * 16 + 4, sf::Color::White, textAlign::center);

	// Mana bar
	str = std::to_string(p_player -> life -> getHealth()) + "/" + std::to_string(p_player -> life -> getMaxHealth());
	engine -> screen.drawBox(x * 16, (y + 5) * 16, width * 16, 32, color("darkest azure"));
	engine -> screen.drawBox(x * 16, (y + 5) * 16, (width * 16) * p_player -> life -> getHealth() / p_player -> life -> getMaxHealth() , 32, color("darker azure"));
	engine -> screen.drawTexture("healthbar", x * 16 + 2, (y + 5) * 16);
	engine -> screen.drawText(str, x * 16 + ((width * 16) / 2) + 1, (y + 5) * 16 + 4 + 1, sf::Color::Black, textAlign::center);
	engine -> screen.drawText(str, x * 16 + ((width * 16) / 2), (y + 5) * 16 + 4, sf::Color::White, textAlign::center);

	// << TARGETS >>

	if(engine -> game -> map -> isWorldMap() == false) {

		drawTitle("Creatures", 8);
		std::vector<int> creatures = engine -> game -> actorManager.getActiveActors();
				
		if(creatures.size() > 0) {
			int counter = 0;
			for(int i = 0; i < creatures.size(); ++i) {

				// If the creature is on a visible tile, draw panel
				c_actor* p_actor = engine -> game -> actorManager.getActor(creatures[i]);
				if(engine -> game -> map -> getTile(p_actor -> getMapX(), p_actor -> getMapY()) -> getVisible() == true) {
							
					// Health bar
					engine -> screen.drawBox((x + 1) * 16, (y + 7 + counter) * 22 - 10, (width - 2) * 16, 22, color("darkest red"));
					engine -> screen.drawBox((x + 1) * 16, (y + 7 + counter) * 22 - 10, ((width - 2) * 16) * p_actor -> life -> getHealth() / p_actor -> life -> getMaxHealth(), 22, color("darker red"));
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

	// << FRAME >>

	drawFrame();
	drawHBar(7);
	return;
}