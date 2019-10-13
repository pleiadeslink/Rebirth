c_winCharacter::c_winCharacter(const int& x, const int& y, const int& width, const int& height) {
	this -> x = x;
	this -> y = y;
	this -> width = width;
	this -> height = height;
	screen = charScreen::inventory;
	itemPos = 0;
	abilityPos = 0;
	conditionPos = 0;
	talentPos = 0;
	questPos = 0;
	systemPos = 0;
    v_item = 0;
	v_ability = 0;
}

void c_winCharacter::init() {
    //map = new c_winMap(0, 0, 33, 13);
    a_menuBar = new c_winMenuBar[MAXMENUBAR];
	for(int i = 0; i < MAXMENUBAR; ++i) {
		a_menuBar[i].init(x + 1, y + 18 + i, 43, 1);
	}
}

int c_winCharacter::update(int key) {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return 0;
	}
 
	v_item = 0;
	v_ability = 0;

	//key = map -> update(key, engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY(), engine -> getMouse());
	
	// Change screen
	if(key == key::left) {
		--screen;
		if(screen < 0) {
			screen = charScreen::system;
		}
		key = 0;
		for(int i = 0; i < MAXMENUBAR; ++i) {
			a_menuBar[i].clear();
		}
	} else if(key == key::right) {
		++screen;
		if(screen > charScreen::system) {
			screen = charScreen::inventory;
		}
		key = 0;
		for(int i = 0; i < MAXMENUBAR; ++i) {
			a_menuBar[i].clear();
		}
	}

	switch(screen) {

		// * INVENTORY
		case charScreen::inventory: {

			// Update inventory list
			v_item = engine -> game -> actorManager.getPlayer() -> player -> getInventory();

			if(v_item -> size() > 0) {

                if(itemPos > v_item -> size() - 1) {
				    itemPos = v_item -> size() - 1;
			    } 

                // Cursor
				switch(key) {
					case key::up: {
						--itemPos;
						if(itemPos < 0) {
							itemPos = v_item -> size() - 1;
						}
						key = 0;
						break;
					}
					case key::down: {
						++itemPos;
						if(itemPos > v_item -> size() - 1) {
							itemPos = 0;
						}
						key = 0;
						break;
					}
				}

                // Update menu
                for(int i = 0; i < MAXMENUBAR; ++i) {
					if(i <= v_item -> size() - 1) {
                        a_menuBar[i].setActor(v_item -> at(i).uid, v_item -> at(i).quantity);
                    }
				}
                for(int i = 0; i < MAXMENUBAR; ++i) {
					if(i <= v_item -> size() - 1) {
                        if(i == itemPos) {
                            key = a_menuBar[i].update(key, true);
                        } else {
                            key = a_menuBar[i].update(key, false);
                        }
                    }
				}
			}
			return key;
		}

		// * WORDS
		case charScreen::abilities: {

			// Update inventory list
			v_ability = engine -> game -> actorManager.getPlayer() -> player -> getAbilities();

			if(v_ability -> size() > 0) {

				if(abilityPos > v_ability -> size() - 1) {
				    abilityPos = v_ability -> size() - 1;
			    } 

				// Cursor
				switch(key) {
					case key::up: {
						--abilityPos;
						if(abilityPos < 0) {
							abilityPos = v_ability -> size() - 1;
						}
						key = 0;
						break;
					}
					case key::down: {
						if(abilityPos < v_ability -> size() - 1) {
							++abilityPos;
						} else {
							abilityPos = 0;
						}
						key = 0;
						break;
					}
				}

                // Update menu
                for(int i = 0; i < MAXMENUBAR; ++i) {
					if(i <= v_ability -> size() - 1) {
                        a_menuBar[i].setAbility(v_ability -> at(i));
                    }
				}
                for(int i = 0; i < MAXMENUBAR; ++i) {
					if(i <= v_ability -> size() - 1) {
                        if(i == abilityPos) {
                            key = a_menuBar[i].update(key, true);
                        } else {
                            key = a_menuBar[i].update(key, false);
                        }
                    }
				}

			}
			return key;
		}
	}
	return key;
}

void c_winCharacter::draw() {

	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return;
	}

	// << STATS >>
	c_actor* player = engine -> game -> actorManager.getPlayer();
	if(player) {

		engine -> screen.drawText(engine -> game -> actorManager.getPlayer() -> getName(), (x + 46) * 16 - 8, (y + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("the novice", (x + 46) * 16 - 8, (y + 2) * 16 + 4, color("light grey"));

		engine -> screen.drawText("Level:            1", (x + 46) * 16 - 8, (y + 4) * 16 + 4, color("light grey"));
		engine -> screen.drawText("Exp:            356", (x + 46) * 16 - 8, (y + 5) * 16 + 4, color("light grey"));
		engine -> screen.drawText("Next level:   sleep", (x + 46) * 16 - 8, (y + 6) * 16 + 4, color("light grey"));
		
		engine -> screen.drawText("Strength:", (x + 46) * 16 - 8, (y + 8) * 16 + 4, color("light grey"));
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> player -> getConstitution()), (x + 46 + 9) * 16 - 8, (y + 8) * 16 + 4, sf::Color::White, textAlign::left);
		engine -> screen.drawText("Agility:", (x + 46) * 16 - 8, (y + 9) * 16 + 4, color("light grey"));
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> player -> getAgility()), (x + 46 + 9) * 16 - 8, (y + 9) * 16 + 4, sf::Color::White, textAlign::left);
		engine -> screen.drawText("Willpower:", (x + 46) * 16 - 8, (y + 10) * 16 + 4, color("light grey"));
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> player -> getSpirit()), (x + 46 + 9) * 16 - 8, (y + 10) * 16 + 4, sf::Color::White, textAlign::left);
		engine -> screen.drawText("Luck:", (x + 46) * 16 - 8, (y + 11) * 16 + 4, color("light grey"));
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> player -> getLuck()), (x + 46 + 9) * 16 - 8, (y + 11) * 16 + 4, sf::Color::White, textAlign::left);
		
		engine -> screen.drawText("Damage:", (x + 34 + 22) * 16, (y + 1) * 16 + 4, color("light grey"));
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getMinDamage()) + "-" + std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getMaxDamage()), (x + 34 + 22 + 9) * 16, (y + 1) * 16 + 4, sf::Color::White, textAlign::left);
		engine -> screen.drawText("(melee)", (x + 34 + 22 + 9) * 16, (y + 2) * 16 + 4, sf::Color::White, textAlign::left);
		engine -> screen.drawText("Accuracy:", (x + 34 + 22) * 16, (y + 3) * 16 + 4, color("light grey"));
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getAttack()), (x + 34 + 22 + 9) * 16, (y + 3) * 16 + 4, sf::Color::White, textAlign::left);
		engine -> screen.drawText("Defense:         14", (x + 34 + 22) * 16, (y + 4) * 16 + 4, color("light grey"));
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getDefense()), (x + 34 + 22 + 9) * 16, (y + 4) * 16 + 4, sf::Color::White, textAlign::left);
		engine -> screen.drawText("Protection:", (x + 34 + 22) * 16, (y + 5) * 16 + 4, color("light grey"));
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getProtection()), (x + 34 + 22 + 9) * 16, (y + 5) * 16 + 4, sf::Color::White, textAlign::left);
		engine -> screen.drawText("Resist heat:      8", (x + 34 + 22) * 16, (y + 7) * 16 + 4, color("light grey"));
		engine -> screen.drawText("Resist cold:      8", (x + 34 + 22) * 16, (y + 8) * 16 + 4, color("light grey"));
		engine -> screen.drawText("Resist poison:    8", (x + 34 + 22) * 16, (y + 9) * 16 + 4, color("light grey"));
		engine -> screen.drawText("Weight:       13/50", (x + 34 + 22) * 16, (y + 11) * 16 + 4, color("light grey"));
	}


	// << MENU >>

	engine -> screen.drawText("ITEMS", (x + 2 + 4) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("WORDS", (x + 13 + 4) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("CONDITION", (x + 23 + 4 + 1) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("CHAKRAS", (x + 33 + 4 + 2) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("QUESTS", (x + 43 + 4 + 3) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("SYSTEM", (x + 53 + 4 + 4) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);

	// Title bar
	engine -> screen.drawBox((x + 1) * 16, (y + 17) * 16, (width - 24) * 16, 16, color("darker sepia"));
	engine -> screen.drawBox((x + 1) * 16, (y + 17) * 16 + 16 - 2, (width - 24) * 16, 2, color("darkest sepia"));
    //engine -> screen.drawText("Details", (x + 45) * 16 + 4, (y + 16) * 16 - 4, color("lighter sepia"));

	switch(screen) {
		case charScreen::inventory: {

			// Menu label
			engine -> screen.drawText("ITEMS", (x + 2 + 4) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);

			if(!v_item or v_item -> size() == 0) {
				engine -> screen.drawText("You are not carrying anything.", (x + 2) * 16, (y + 19) * 16 - 4, color("light grey"));
			} else {

				// Title bar
				std::string title;
				int c = 0;
				c = PDNAM - title.length();
				for(int i = 0; i < c; ++i) {
					title.append(" ");
				}
				title.append("Name");
				c = PDQUA - title.length();
				for(int i = 0; i < c; ++i) {
					title.append(" ");
				}
				title.append("Qty.");
				c = PDTYP - title.length();
				for(int i = 0; i < c; ++i) {
					title.append(" ");
				}			
				title.append("Type");
				c = PDDAM - title.length();
				for(int i = 0; i < c; ++i) {
					title.append(" ");
				}
				title.append("Dam.");
				c = PDPRO - title.length();
				for(int i = 0; i < c; ++i) {
					title.append(" ");
				}
				title.append("Prot.");
				c = PDWGT - title.length();
				for(int i = 0; i < c; ++i) {
					title.append(" ");
				}
				title.append("Wgt.");
				engine -> screen.drawText(title, (x + 1) * 16, (y + 17) * 16 - 4, color("lighter sepia"));

				// Draw menu
                for(int i = 0; i < MAXMENUBAR; ++i) {
					if(i <= v_item -> size() - 1) {
                        a_menuBar[i].draw();
                    }
				}
			}
			break;
		}
		case charScreen::abilities: {

			// Menu label
			engine -> screen.drawText("WORDS", (x + 13 + 4) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);

			// Title bar
			std::string title;
			int c = 0;
			c = PDNAM - title.length();
			for(int i = 0; i < c; ++i) {
				title.append(" ");
			}
			title.append("Name");
			c = PDTIM - title.length();
			for(int i = 0; i < c; ++i) {
				title.append(" ");
			}
			title.append("Duration");
			c = PDENE - title.length();
			for(int i = 0; i < c; ++i) {
				title.append(" ");
			}
			title.append("Energy");
			engine -> screen.drawText(title, (x + 1) * 16, (y + 17) * 16 - 4, color("lighter sepia"));

			// Draw menu
			if(!v_ability or v_ability -> size() == 0) {
				engine -> screen.drawText("You don't know any abilities, WTF?", (x + 2) * 16 + 4, (y + 19) * 16 - 4, sf::Color::White);
			} else {
                for(int i = 0; i < MAXMENUBAR; ++i) {
					if(i <= v_ability -> size() - 1) {
                        a_menuBar[i].draw();
                    }
				}
			}
			break;
		}
		case charScreen::condition: {
			engine -> screen.drawText("CONDITION", (x + 23 + 4 + 1) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
			//engine -> screen.drawTexture("menuCursor", (x + 24) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawTexture("menuCursor", (x + 24 + 7) * 16, (y + 13 + 1) * 16 + 7);
			break;
		}
		case charScreen::talents: {
			engine -> screen.drawText("CHAKRAS", (x + 33 + 4 + 2) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
			//engine -> screen.drawTexture("menuCursor", (x + 35) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawTexture("menuCursor", (x + 35 + 7) * 16, (y + 13 + 1) * 16 + 7);
			break;
		}
		case charScreen::quests: {
			engine -> screen.drawText("QUESTS", (x + 43 + 4 + 3) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
			//engine -> screen.drawTexture("menuCursor", (x + 46) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawTexture("menuCursor", (x + 46 + 7) * 16, (y + 13 + 1) * 16 + 7);
			break;
		}
		case charScreen::system: {
			engine -> screen.drawText("SYSTEM", (x + 53 + 4 + 4) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
			//engine -> screen.drawTexture("menuCursor", (x + 57) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawTexture("menuCursor", (x + 57 + 7) * 16, (y + 13 + 1) * 16 + 7);
			break;
		}
	}

	// << FRAME >>

	drawFrame();
	//drawVLine(0, 13, 28);
	//drawVLine(60, 0, 28);
	//drawHLine(33, 0, 34);
	//drawHBar(40);

	// Menu
	//drawHBar(5);
	drawHBar(13);
	drawHBar(16);
	drawVLine(11, 13, 4);
	drawVLine(22, 13, 4);
	drawVLine(33, 13, 4);
	drawVLine(44, 0, 14);
	drawVLine(44, 13, 4);
	drawVLine(55, 13, 4);
	drawVLine(66, 13, 4);

	// Abajo
	drawVLine(44, 16, height - 16);

	// Map
	//map -> draw(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY());

	return;
}