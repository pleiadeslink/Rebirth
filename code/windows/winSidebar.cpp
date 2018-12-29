c_winSidebar::c_winSidebar(const int& x, const int& y, const int& width, const int& height) {
	this -> x = x;
	this -> y = y;
	this -> width = width;
	this -> height = height;
	this -> tileButtonWidth = 8;
	this -> tileButtonHeight = 8;
}

void c_winSidebar::init() {

	// Create tile button matrix
	m_tileButtons = new c_winButton*[tileButtonWidth];
	for(int i = 0; i < tileButtonWidth; ++i) {
		m_tileButtons[i] = new c_winButton[tileButtonHeight];
	}
    for(int i1 = 0; i1 < tileButtonWidth; ++i1) {
        for(int i2 = 0; i2 < tileButtonHeight; ++i2) {
            m_tileButtons[i1][i2].init(x + i1 + 1, y + i2 + 8, global::tileSize, global::tileSize, buttonType::tile);
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
						if(mousePos.x > x * global::tileSize and mousePos.y > y * global::tileSize
						and mousePos.x < (x + width) * global::tileSize and mousePos.y < (y + height) * global::tileSize) {
							key = m_tileButtons[i1][i2].update(key, mousePos);
						}
					}
				}
			}

			// Key input
			switch(key) {
				case key::num1: {
					engine -> interface.setEmode(emode::tile);
					return 0;
				}
				case key::num2: {
					engine -> interface.setEmode(emode::actor);
					return 0;
				}
				case key::num3: {
					engine -> interface.setEmode(emode::script);
					return 0;
				}
				case key::left: {
					switch(engine -> interface.getEmode()) {
						case emode::tile: {
							engine -> interface.setEditTile(engine -> assetManager.getPreviousTileAsset());
							break;
						}
						case emode::actor: {
							engine -> interface.setEditActor(engine -> assetManager.getPreviousActorAsset());
							break;
						}
						case emode::script: {
							std::vector<s_script> v_script = engine -> game -> map -> getScripts();
							if(v_script.size() != 0 and engine -> interface.getEditScript() > 1) {
								std::cout << engine -> interface.getEditScript() - 1 << std::endl;
								engine -> interface.setEditScript(engine -> interface.getEditScript() - 1);
							}
							break;
						}
					}
					return 0;
				}
				case key::right: {
					switch(engine -> interface.getEmode()) {
						case emode::tile: {
							engine -> interface.setEditTile(engine -> assetManager.getNextTileAsset());
							break;
						}
						case emode::actor: {
							engine -> interface.setEditActor(engine -> assetManager.getNextActorAsset());
							break;
						}
						case emode::script: {
							std::vector<s_script> v_script = engine -> game -> map -> getScripts();
							if(v_script.size() != 0 and engine -> interface.getEditScript() < v_script.size()) {
								std::cout << engine -> interface.getEditScript() + 1 << std::endl;
								engine -> interface.setEditScript(engine -> interface.getEditScript() + 1);
							}
							break;
						}
					}
					return 0;
				}
			}
			break;
		}
	}
	return key;
}

void c_winSidebar::draw() {
	if(!engine -> game or !engine -> game -> map) {
		return;
	}

	// Edit mode
	if(engine -> interface.getMode() == imode::edit) {
		/*switch(engine -> interface.getEmode()) {
			case emode::tile: {
				engine -> screen.drawText(">", (x + 1) * 16, (y) * 16, sf::Color::White);
				break;
			}
			case emode::actor: {
				engine -> screen.drawText(">", (x + 1) * 16, (y + 1) * 16, sf::Color::White);
				break;
			}
			case emode::script: {
				engine -> screen.drawText(">", (x + 1) * 16, (y + 2) * 16, sf::Color::White);
				break;
			}
		}
		engine -> screen.drawText(engine -> interface.getEditTile() -> name, (x + 2) * 16, (y) * 16, sf::Color::White);
		engine -> screen.drawText(engine -> interface.getEditActor() -> name, (x + 2) * 16, (y + 1) * 16, sf::Color::White);
		std::vector<s_script> v_script = engine -> game -> map -> getScripts();
		if(v_script.size() > 0) {
			engine -> screen.drawText(v_script[engine -> interface.getEditScript() - 1].command, (x + 2) * 16, (y + 2) * 16, sf::Color::White);
		}*/

		// Draw title
		engine -> screen.drawText("EDIT MODE", x * 16 + ((width * 16) / 2), (y + 1) * 16 + 8 - 2, sf::Color::White, textAlign::center);

		// Draw active edit element icon
		switch(engine -> interface.getEmode() ) {
			case emode::tile: {
				structTileAsset* p_tile = engine -> interface.getEditTile();
				if(p_tile != 0) {
					int xf = x * 16 + ((width * 16) / 2) - 16;
					int yf = (y + 3) * 16 + 4;
					engine -> screen.drawTile(11, 13, xf, yf, p_tile -> bgcolor, 2);
                	c_tile::drawOverlay(xf, yf, p_tile -> type, p_tile -> olcolor, 2);
                	engine -> screen.drawTile(p_tile -> tileX, p_tile -> tileY, xf, yf, p_tile -> color, 2);
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

		// Draw external frame
		drawTitle("Tiles", 7);
		drawFrame();
		drawHBar(6);
		
		return;
	}

    c_actor* p_player = engine -> game -> actorManager.getPlayer();

	if(!engine -> game or !p_player) {
		return;
	}

	std::string str;

	// << HEALTH BARS >>

	// Health bar
	str = "H:" + std::to_string(p_player -> life -> getHealth()) + "/" + std::to_string(p_player -> life -> getMaxHealth());
	engine -> screen.drawBox(x * 16, (y + 1) * 16, width * 16, 32, color("darkest red"));
	engine -> screen.drawBox(x * 16, (y + 1) * 16, (width * 16) * p_player -> life -> getHealth() / p_player -> life -> getMaxHealth() , 32, color("darker red"));
	engine -> screen.drawTexture("healthbar", x * 16 + 2, (y + 1) * 16);
	engine -> screen.drawText(str, x * 16 + ((width * 16) / 2) + 1, (y + 1) * 16 + 4 + 1, sf::Color::Black, textAlign::center);
	engine -> screen.drawText(str, x * 16 + ((width * 16) / 2), (y + 1) * 16 + 4, sf::Color::White, textAlign::center);

	// Stamina bar
	str = "S:" + std::to_string(p_player -> life -> getHealth()) + "/" + std::to_string(p_player -> life -> getMaxHealth());
	engine -> screen.drawBox(x * 16, (y + 3) * 16, width * 16, 32, color("darkest amber"));
	engine -> screen.drawBox(x * 16, (y + 3) * 16, (width * 16) * p_player -> life -> getHealth() / p_player -> life -> getMaxHealth() , 32, color("darker amber"));
	engine -> screen.drawTexture("healthbar", x * 16 + 2, (y + 3) * 16);
	engine -> screen.drawText(str, x * 16 + ((width * 16) / 2) + 1, (y + 3) * 16 + 4 + 1, sf::Color::Black, textAlign::center);
	engine -> screen.drawText(str, x * 16 + ((width * 16) / 2), (y + 3) * 16 + 4, sf::Color::White, textAlign::center);

	// Mana bar
	str = "M:" + std::to_string(p_player -> life -> getHealth()) + "/" + std::to_string(p_player -> life -> getMaxHealth());
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
					engine -> screen.drawBox((x + 1) * 16, (y + 9 + counter) * 16, (width - 2) * 16, 16, color("darkest red"));
					engine -> screen.drawBox((x + 1) * 16, (y + 9 + counter) * 16, ((width - 2) * 16) * p_actor -> life -> getHealth() / p_actor -> life -> getMaxHealth(),
					16, color("darker red"));
					engine -> screen.drawTexture("targetbar", (x + 1) * 16, (y + 9 + counter) * 16);

					// Symbol
					engine -> screen.drawTile(p_actor -> getTileX(), p_actor -> getTileY(), (x + 1) * 16 + 1, (y + 9 + counter) * 16 + 1, sf::Color::Black);
					engine -> screen.drawTile(p_actor -> getTileX(), p_actor -> getTileY(), (x + 1) * 16, (y + 9 + counter) * 16, p_actor -> getColor());
							

					// Name
					engine -> screen.drawText(p_actor -> getName(), (x + 3) * 16 + 1 - 8, (y + 9 + counter) * 16 - 3 + 1, sf::Color::Black);
					engine -> screen.drawText(p_actor -> getName(), (x + 3) * 16 - 8, (y + 9 + counter) * 16 - 3, sf::Color::White);

					++counter;
				}
			}
		}

	// << LOCATIONS >>

	} else {
		drawTitle("Locations", 8);
		std::vector<int> creatures = engine -> game -> actorManager.getActiveActors();
				
		if(creatures.size() > 0) {
			int counter = 0;
			for(int i = 0; i < creatures.size(); ++i) {

				// If the creature is on a visible tile, draw panel
				c_actor* p_actor = engine -> game -> actorManager.getActor(creatures[i]);
				if(engine -> game -> map -> getTile(p_actor -> getMapX(), p_actor -> getMapY()) -> getVisible() == true) {
							
					// Health bar
					engine -> screen.drawBox((x + 1) * 16, (y + 9 + counter) * 16, (width - 2) * 16, 16, color("darkest red"));
					engine -> screen.drawBox((x + 1) * 16, (y + 9 + counter) * 16, ((width - 2) * 16) * p_actor -> life -> getHealth() / p_actor -> life -> getMaxHealth(),
					16, color("darker red"));
					engine -> screen.drawTexture("targetbar", (x + 1) * 16, (y + 9 + counter) * 16);

					// Symbol
					engine -> screen.drawTile(p_actor -> getTileX(), p_actor -> getTileY(), (x + 1) * 16 + 1, (y + 9 + counter) * 16 + 1, sf::Color::Black);
					engine -> screen.drawTile(p_actor -> getTileX(), p_actor -> getTileY(), (x + 1) * 16, (y + 9 + counter) * 16, p_actor -> getColor());
							

					// Name
					engine -> screen.drawText(p_actor -> getName(), (x + 3) * 16 + 1 - 8, (y + 9 + counter) * 16 - 3 + 1, sf::Color::Black);
					engine -> screen.drawText(p_actor -> getName(), (x + 3) * 16 - 8, (y + 9 + counter) * 16 - 3, sf::Color::White);

					++counter;
				}
			}
		}		
	}

	// << QUICK MENU >>

	drawTitle("Quick menu", 32);
	engine -> screen.drawText("1: empty", (x + 2) * 16, (y + 33) * 16 + 4, sf::Color::White);
	engine -> screen.drawText("2: empty", (x + 2) * 16, (y + 34) * 16 + 4, sf::Color::White);
	engine -> screen.drawText("3: empty", (x + 2) * 16, (y + 35) * 16 + 4, sf::Color::White);
	engine -> screen.drawText("4: empty", (x + 2) * 16, (y + 36) * 16 + 4, sf::Color::White);
	engine -> screen.drawText("5: empty", (x + 2) * 16, (y + 37) * 16 + 4, sf::Color::White);
	engine -> screen.drawText("6: empty", (x + 2) * 16, (y + 38) * 16 + 4, sf::Color::White);
	engine -> screen.drawText("7: empty", (x + 2) * 16, (y + 39) * 16 + 4, sf::Color::White);
	engine -> screen.drawText("8: empty", (x + 2) * 16, (y + 40) * 16 + 4, sf::Color::White);
	engine -> screen.drawText("9: empty", (x + 2) * 16, (y + 41) * 16 + 4, sf::Color::White);
	engine -> screen.drawText("0: empty", (x + 2) * 16, (y + 42) * 16 + 4, sf::Color::White);

	// << FRAME >>

	drawFrame();
	drawHBar(7);
	drawHBar(31);
	return;
}