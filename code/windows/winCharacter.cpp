c_winCharacter::c_winCharacter(const int& x, const int& y, const int& width, const int& height) {
	this -> x = x;
	this -> y = y;
	this -> width = width;
	this -> height = height;
	screen = charScreen::inventory;
	inventoryPos = 0;
	abilitiesPos = 0;
	conditionPos = 0;
	skillsPos = 0;
	talentsPos = 0;
	questlogPos = 0;
}

int c_winCharacter::update(int key) {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return 0;
	}

	// Change screen
	if(key == key::left) {
		--screen;
		if(screen < 0) {
			screen = charScreen::questlog;
		}
		return 0;
	} else if(key == key::right) {
		++screen;
		if(screen > charScreen::questlog) {
			screen = charScreen::inventory;
		}
		return 0;
	}

	switch(screen) {
		case charScreen::inventory: {

			// Update inventory list
			inventory = engine -> game -> actorManager.getPlayer() -> life -> getInventory();

			if(inventory.size() > 0) {

				// Cursor
				switch(key) {
					case key::up: {
						--inventoryPos;
						if(inventoryPos < 0) {
							inventoryPos = 0;
						}
						return 0;
					}
					case key::down: {
						if(inventoryPos < inventory.size() - 1) {
							++inventoryPos;
						}
						return 0;
					}
				}

				// Item selection
				engine -> interface.selectActor(inventory[inventoryPos].uid);

			}
		}
	}
	return key;
}

void c_winCharacter::draw() {

	engine -> screen.drawTexture("background", (x + 1) * 16, (y + 1) * 16);

	engine -> screen.drawText("@", (x + 3) * 16 - 4, (y + 3) * 16 + 12, sf::Color::White, 0, 0, 128);

	// << STATS >>
	c_actor* player = engine -> game -> actorManager.getPlayer();
	if(player) {
		engine -> screen.drawText("SEIKKEN", (x + 8) * 16, (y + 8) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("the novice", (x + 8) * 16, (y + 9) * 16 + 4, sf::Color::White);

		engine -> screen.drawText("Health:      27/60", (x + 16) * 16, (y + 5 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Mana:        24/24", (x + 16) * 16, (y + 6 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Stamina:   100/100", (x + 16) * 16, (y + 7 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Level:           1", (x + 16) * 16, (y + 8 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Exp:           356", (x + 16) * 16, (y + 9 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Next level:  sleep", (x + 16) * 16, (y + 10 + 1) * 16 + 4, sf::Color::White);

		engine -> screen.drawText("Constitution:   30", (x + 16 + 10) * 16, (y + 5 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Swiftness:      24", (x + 16 + 10) * 16, (y + 6 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Perception:     18", (x + 16 + 10) * 16, (y + 7 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Willpower:       8", (x + 16 + 10) * 16, (y + 8 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Luck:            0", (x + 16 + 10) * 16, (y + 9 + 1) * 16 + 4, sf::Color::White);

		engine -> screen.drawText("Damage:      13-15", (x + 16 + 10 * 2) * 16, (y + 5 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Melee:         30%", (x + 16 + 10 * 2) * 16, (y + 6 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Projectile:    24%", (x + 16 + 10 * 2) * 16, (y + 7 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Dodge:         18%", (x + 16 + 10 * 2) * 16, (y + 8 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Parry:          8%", (x + 16 + 10 * 2) * 16, (y + 9 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Block:         14%", (x + 16 + 10 * 2) * 16, (y + 10 + 1) * 16 + 4, sf::Color::White);

		engine -> screen.drawText("Armor:          27", (x + 16 + 10 * 3) * 16, (y + 5 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Resist heat:    24", (x + 16 + 10 * 3) * 16, (y + 6 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Resist cold:     0", (x + 16 + 10 * 3) * 16, (y + 7 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Resist poison:   8", (x + 16 + 10 * 3) * 16, (y + 8 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Temple:          0", (x + 16 + 10 * 3) * 16, (y + 9 + 1) * 16 + 4, sf::Color::White);

		engine -> screen.drawText("Spell power:    10", (x + 16 + 10 * 4) * 16, (y + 5 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Frequency:    high", (x + 16 + 10 * 4) * 16, (y + 6 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Appearance:      0", (x + 16 + 10 * 4) * 16, (y + 7 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Fame:            1", (x + 16 + 10 * 4) * 16, (y + 8 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Bounty:          0", (x + 16 + 10 * 4) * 16, (y + 9 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Gold:          146", (x + 16 + 10 * 4) * 16, (y + 10 + 1) * 16 + 4, sf::Color::White);
	}


	// << MENU >>

	engine -> screen.drawText("INVENTORY", (x + 2 + 4) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("ABILITIES", (x + 13 + 4) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("CONDITION", (x + 23 + 4 + 1) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("SKILLS", (x + 33 + 4 + 2) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("TALENTS", (x + 43 + 4 + 3) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("QUESTS", (x + 53 + 4 + 4) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);

	// Title bar
	engine -> screen.drawBox((x + 1) * 16, (y + 17) * 16, (width - 24) * 16, 16, color("darker sepia"));
	engine -> screen.drawBox((x + 1) * 16, (y + 17) * 16 + 16 - 2, (width - 24) * 16, 2, color("darkest sepia"));
    //engine -> screen.drawText("Details", (x + 45) * 16 + 4, (y + 16) * 16 - 4, color("lighter sepia"));

	switch(screen) {
		case charScreen::inventory: {

			// Menu label
			engine -> screen.drawText("INVENTORY", (x + 2 + 4) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
			//engine -> screen.drawTexture("menuCursor", (x + 1 + 1) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawTexture("menuCursor", (x + 1 + 1 + 7) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawCenteredText(">           <", (x + 2 + 4) * 16, (y + 12 + 1) * 16 + 4, sf::Color::White);

			// Item list
			if(inventory.size() == 0) {
				engine -> screen.drawText("You don't have anything.", (x + 2) * 16 + 4, (y + 19) * 16 - 4, sf::Color::White);
			} else {
				for(int i = 0; i < inventory.size(); ++i) {
					int offset = 0;
					if(engine -> game -> actorManager.actorExists(inventory[i].uid)) {
						c_actor* p_item = engine -> game -> actorManager.getActor(inventory[i].uid);

						int ypos = (y + 18 + i) * 16 - 4 + (4 * i) + 1;

						// Backgound
						engine -> screen.drawTexture("listbar", (x + 1) * 16, (y + 18 + i) * 16 + (4 * i));

						// Icon
						engine -> screen.drawTile(p_item -> getTileX(), p_item -> getTileY(), (x + 2) * 16 + 12, (y + 18 + i) * 16 + (4 * i), p_item -> getColor());

						// Name
						engine -> screen.drawText("Name", (x + 4) * 16 + 4, (y + 17) * 16 - 4, color("lighter sepia"));
						engine -> screen.drawText(p_item -> getName(), (x + 4) * 16 + 4, ypos, sf::Color::White);

						// Quantity
						engine -> screen.drawText("Qty.", (x + 20) * 16 + 4, (y + 17) * 16 - 4, color("lighter sepia"));
						engine -> screen.drawText(std::to_string(inventory[i].quantity), (x + 20) * 16 + 4, ypos, color("lighter grey"));

						// Type
						offset += 5;
						engine -> screen.drawText("Type", (x + 20 + offset) * 16 - 8, (y + 17) * 16 - 4, color("lighter sepia"));
						std::string str1 = "Null";
						switch(p_item -> getType()) {
							case actorType::weapon: {
								str1 = "Weapon";
								break;
							}
							case actorType::armor: {
								str1 = "Armor";
								break;
							}
							case actorType::misc: {
								str1 = "Misc";
								break;
							}
							case actorType::potion: {
								str1 = "Potion";
								break;
							}
							case actorType::scroll: {
								str1 = "Scroll";
								break;
							}
							case actorType::food: {
								str1 = "Food";
								break;
							}
							case actorType::staircase: {
								str1 = "Staircase";
								break;
							}
							case actorType::container: {
								str1 = "Container";
								break;
							}
							case actorType::door: {
								str1 = "Door";
								break;
							}
							case actorType::avatar: {
								str1 = "Avatar";
								break;
							}
							case actorType::creature: {
								str1 = "Creature";
								break;
							}
						}
						engine -> screen.drawText(str1, (x + 20 + offset) * 16 - 8, ypos, color("lighter grey"));

						// Damage
						offset += 7;
						engine -> screen.drawText("Dam.", (x + 20 + offset) * 16 - 8, (y + 17) * 16 - 4, color("lighter sepia"));
						if(p_item -> weapon) {
							std::string str2 = std::to_string(p_item -> weapon -> getMinDamage());
							str2.append("-");
							str2.append(std::to_string(p_item -> weapon -> getMaxDamage()));
							engine -> screen.drawText(str2, (x + 20 + offset) * 16 - 8, ypos, color("lighter grey"));
						}

						// Protection
						offset += 5;
						engine -> screen.drawText("Prot.", (x + 20 + offset) * 16 - 8, (y + 17) * 16 - 4, color("lighter sepia"));
						if(p_item -> armor) {
							engine -> screen.drawText(std::to_string(p_item -> armor -> getProtection()), (x + 20 + offset) * 16 - 8, ypos, color("lighter grey"));
						}

						// Mass
						offset += 5;
						engine -> screen.drawText("Mass", (x + 20 + offset) * 16 - 8, (y + 17) * 16 - 4, color("lighter sepia"));
						if(p_item -> body) {
							engine -> screen.drawText(std::to_string(p_item -> body -> getMass()), (x + 20 + offset) * 16 - 8, ypos, color("lighter grey"));
						}
					}
				}
				engine -> screen.drawTexture("menuCursor", (x + 1) * 16 + 4, (y + 18 + inventoryPos) * 16 + (inventoryPos) * 4);
			}
			break;
		}
		case charScreen::abilities: {
			engine -> screen.drawText("ABILITIES", (x + 13 + 4) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
			//engine -> screen.drawTexture("menuCursor", (x + 13) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawTexture("menuCursor", (x + 13 + 7) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawCenteredText(">           <", (x + 13 + 4) * 16, (y + 12 + 1) * 16 + 4, sf::Color::White);
			break;
		}
		case charScreen::condition: {
			engine -> screen.drawText("CONDITION", (x + 23 + 4 + 1) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
			//engine -> screen.drawTexture("menuCursor", (x + 24) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawTexture("menuCursor", (x + 24 + 7) * 16, (y + 13 + 1) * 16 + 7);
			break;
		}
		case charScreen::skills: {
			engine -> screen.drawText("SKILLS", (x + 33 + 4 + 2) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
			//engine -> screen.drawTexture("menuCursor", (x + 35) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawTexture("menuCursor", (x + 35 + 7) * 16, (y + 13 + 1) * 16 + 7);
			break;
		}
		case charScreen::talents: {
			engine -> screen.drawText("TALENTS", (x + 43 + 4 + 3) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
			//engine -> screen.drawTexture("menuCursor", (x + 46) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawTexture("menuCursor", (x + 46 + 7) * 16, (y + 13 + 1) * 16 + 7);
			break;
		}
		case charScreen::questlog: {
			engine -> screen.drawText("QUESTS", (x + 53 + 4 + 4) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
			//engine -> screen.drawTexture("menuCursor", (x + 57) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawTexture("menuCursor", (x + 57 + 7) * 16, (y + 13 + 1) * 16 + 7);
			break;
		}
	}

	// << FRAME >>

	drawFrame();

	// Menu
	drawHBar(5);
	drawHBar(13);
	drawHBar(16);
	drawVLine(11, 13, 4);
	drawVLine(22, 13, 4);
	drawVLine(33, 13, 4);
	drawVLine(44, 13, 4);
	drawVLine(55, 13, 4);
	drawVLine(66, 13, 4);

	// Abajo
	drawVLine(44, 16, height - 16);
	return;
}