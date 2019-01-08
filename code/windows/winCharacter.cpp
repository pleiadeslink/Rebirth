c_winCharacter::c_winCharacter(const int& x, const int& y, const int& width, const int& height) {
	this -> x = x;
	this -> y = y;
	this -> width = width;
	this -> height = height;
	screen = charScreen::inventory;
	inventoryPos = 0;
	skillsPos = 0;
	conditionPos = 0;
	talentsPos = 0;
	questsPos = 0;
	systemPos = 0;
	inventory = 0;
	v_skills = 0;
}

int c_winCharacter::update(int key) {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return 0;
	}

	inventory = 0;
	v_skills = 0;
	
	// Change screen
	if(key == key::left) {
		--screen;
		if(screen < 0) {
			screen = charScreen::system;
		}
		key = 0;
	} else if(key == key::right) {
		++screen;
		if(screen > charScreen::system) {
			screen = charScreen::inventory;
		}
		key = 0;
	}

	switch(screen) {

		// * INVENTORY
		case charScreen::inventory: {

			// Update inventory list
			inventory = engine -> game -> actorManager.getPlayer() -> player -> getInventory();

			if(inventory -> size() > 0) {

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
						if(inventoryPos < inventory -> size() - 1) {
							++inventoryPos;
						}
						return 0;
					}
				}

				// Item selection
				engine -> interface.selectActor(inventory -> at(inventoryPos).uid);

			}
			break;
		}

		// * SKILLS
		case charScreen::skills: {

			// Update inventory list
			v_skills = engine -> game -> actorManager.getPlayer() -> player -> getSkills();

			if(v_skills -> size() > 0) {

				// Cursor
				switch(key) {
					case key::up: {
						--skillsPos;
						if(skillsPos < 0) {
							skillsPos = 0;
						}
						return 0;
					}
					case key::down: {
						if(skillsPos < v_skills -> size() - 1) {
							++skillsPos;
						}
						return 0;
					}
				}

				// Item selection
				engine -> interface.selectSkill(v_skills -> at(skillsPos));

			}
			break;
		}
	}
	return key;
}

void c_winCharacter::draw() {

	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return;
	}

	engine -> screen.drawTexture("background", (x + 1) * 16, (y + 1) * 16);

	engine -> screen.drawText("@", (x + 3) * 16 - 4, (y + 3) * 16 + 12, sf::Color::White, 0, 0, 128);

	// << STATS >>
	c_actor* player = engine -> game -> actorManager.getPlayer();
	if(player) {
		engine -> screen.drawText("SEIKKEN", (x + 8) * 16, (y + 8) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("the novice", (x + 8) * 16, (y + 9) * 16 + 4, sf::Color::White);

		engine -> screen.drawText("Health:", (x + 16) * 16, (y + 5 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getHealth()) + "/" + std::to_string(engine -> game -> actorManager.getPlayer() -> life -> getMaxHealth()), (x + 16 + 9) * 16, (y + 5 + 1) * 16 + 4, sf::Color::White, textAlign::left);
		engine -> screen.drawText("Stamina:", (x + 16) * 16, (y + 6 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Spirit:", (x + 16) * 16, (y + 7 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Level:", (x + 16) * 16, (y + 8 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> player -> getLevel()), (x + 16 + 9) * 16, (y + 8 + 1) * 16 + 4, sf::Color::White, textAlign::left);
		engine -> screen.drawText("Exp:           356", (x + 16) * 16, (y + 9 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText("Next level:  sleep", (x + 16) * 16, (y + 10 + 1) * 16 + 4, sf::Color::White);

		engine -> screen.drawText("Constitution:", (x + 16 + 10) * 16, (y + 5 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> player -> getConstitution()), (x + 16 + 19) * 16, (y + 5 + 1) * 16 + 4, sf::Color::White, textAlign::left);
		engine -> screen.drawText("Agility:", (x + 16 + 10) * 16, (y + 6 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> player -> getAgility()), (x + 16 + 19) * 16, (y + 6 + 1) * 16 + 4, sf::Color::White, textAlign::left);
		engine -> screen.drawText("Spirit:", (x + 16 + 10) * 16, (y + 7 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> player -> getSpirit()), (x + 16 + 19) * 16, (y + 7 + 1) * 16 + 4, sf::Color::White, textAlign::left);
		engine -> screen.drawText("Luck:", (x + 16 + 10) * 16, (y + 8 + 1) * 16 + 4, sf::Color::White);
		engine -> screen.drawText(std::to_string(engine -> game -> actorManager.getPlayer() -> player -> getLuck()), (x + 16 + 19) * 16, (y + 8 + 1) * 16 + 4, sf::Color::White, textAlign::left);
		//engine -> screen.drawText("Luck:            0", (x + 16 + 10) * 16, (y + 9 + 1) * 16 + 4, sf::Color::White);

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
	engine -> screen.drawText("SKILLS", (x + 13 + 4) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("CONDITION", (x + 23 + 4 + 1) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("TALENTS", (x + 33 + 4 + 2) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("QUESTS", (x + 43 + 4 + 3) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("SYSTEM", (x + 53 + 4 + 4) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);

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
			if(!inventory or inventory -> size() == 0) {
				engine -> screen.drawText("You don't have anything.", (x + 2) * 16 + 4, (y + 19) * 16 - 4, sf::Color::White);
			} else {
				for(int i = 0; i < inventory -> size(); ++i) {
					int offset = 0;
					if(engine -> game -> actorManager.actorExists(inventory -> at(i).uid)) {
						c_actor* p_item = engine -> game -> actorManager.getActor(inventory -> at(i).uid);

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
						engine -> screen.drawText(std::to_string(inventory -> at(i).quantity), (x + 20) * 16 + 4, ypos, color("lighter grey"));

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
		case charScreen::skills: {

			// Menu label
			engine -> screen.drawText("SKILLS", (x + 13 + 4) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
			//engine -> screen.drawTexture("menuCursor", (x + 13) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawTexture("menuCursor", (x + 13 + 7) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawCenteredText(">           <", (x + 13 + 4) * 16, (y + 12 + 1) * 16 + 4, sf::Color::White);

			// Skill list
			if(!v_skills or v_skills -> size() == 0) {
				engine -> screen.drawText("You don't know any skills.", (x + 2) * 16 + 4, (y + 19) * 16 - 4, sf::Color::White);
			} else {
				for(int i = 0; i < v_skills -> size(); ++i) {
					int offset = 0;
					s_skillAsset* skill = engine -> assetManager.getSkillAsset(v_skills -> at(i));
					if(skill -> duration != 0) {

						int ypos = (y + 18 + i) * 16 - 4 + (4 * i) + 1;

						// Backgound
						engine -> screen.drawTexture("listbar", (x + 1) * 16, (y + 18 + i) * 16 + (4 * i));

						// Icon
						//engine -> screen.drawTile(p_item -> getTileX(), p_item -> getTileY(), (x + 2) * 16 + 12, (y + 18 + i) * 16 + (4 * i), p_item -> getColor());

						// Name
						engine -> screen.drawText("Name", (x + 4) * 16 + 4, (y + 17) * 16 - 4, color("lighter sepia"));
						engine -> screen.drawText(skill -> name, (x + 4) * 16 + 4, ypos, sf::Color::White);

						// Quantity
						//engine -> screen.drawText("Qty.", (x + 20) * 16 + 4, (y + 17) * 16 - 4, color("lighter sepia"));
						//engine -> screen.drawText(std::to_string(inventory -> at(i).quantity), (x + 20) * 16 + 4, ypos, color("lighter grey"));

						// Type
						/*offset += 5;
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
						}*/
					}
				}
				engine -> screen.drawTexture("menuCursor", (x + 1) * 16 + 4, (y + 18 + skillsPos) * 16 + (skillsPos) * 4);
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
			engine -> screen.drawText("TALENTS", (x + 33 + 4 + 2) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
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