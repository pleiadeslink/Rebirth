c_winCharacter::c_winCharacter(const int& x, const int& y, const int& width, const int& height) {
	this -> x = x;
	this -> y = y;
	this -> width = width;
	this -> height = height;
	screen = charScreen::inventory;
	inventoryPos = 0;
	abilitiesPos = 0;
	conditionPos = 0;
	talentsPos = 0;
	questsPos = 0;
	systemPos = 0;
	inventory = 0;
	v_abilities = 0;
}

void c_winCharacter::init()     {
    map = new c_winMap(0, 0, 33, 13);
}

int c_winCharacter::update(int key) {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return 0;
	}
 
	inventory = 0;
	v_abilities = 0;

	key = map -> update(key, engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY(), engine -> getMouse());
	
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
			if(inventoryPos > inventory -> size() - 1) {
				inventoryPos = inventory -> size() - 1;
			} 

			if(inventory -> size() > 0) {

				// Item selection
				engine -> interface.selectActor(inventory -> at(inventoryPos).uid);
				c_actor* player = engine -> game -> actorManager.getPlayer();
				c_actor* item = engine -> game -> actorManager.getActor(inventory -> at(inventoryPos).uid);

				// Cursor
				switch(key) {
					case key::up: {
						--inventoryPos;
						if(inventoryPos < 0) {
							inventoryPos = 0;
						}
						engine -> interface.selectActor(inventory -> at(inventoryPos).uid);
						return 0;
					}
					case key::down: {
						if(inventoryPos < inventory -> size() - 1) {
							++inventoryPos;
						}
						engine -> interface.selectActor(inventory -> at(inventoryPos).uid);
						return 0;
					}
					case key::d: {
						if((item -> weapon and player -> player -> getEquippedItem(bodySlot::mainHand) == item -> getUid())
						or (item -> armor and player -> player -> getEquippedItem(item -> armor -> getSlot()) == item -> getUid())) {
							c_helper::gameMessage("You need to remove it first.", true);
							return 0;
						}
                        structEventData eventData;
                        eventData.type = "drop";
                        eventData.target = inventory -> at(inventoryPos).uid;
                        engine -> game -> actorManager.getPlayer() -> action -> start(eventData);
						engine -> game -> update(0);
                        return 0;						
					}
					case key::c: {
						if(!engine -> game -> actorManager.getActor(inventory -> at(inventoryPos).uid) -> consumable) {
							return 0;
						}
                        structEventData eventData;
                        eventData.type = "consume";
                        eventData.target = inventory -> at(inventoryPos).uid;
                        engine -> game -> actorManager.getPlayer() -> action -> start(eventData);
						engine -> game -> update(0);
                        return 0;						
					}
					case key::e: {
						if(item -> weapon) {
							if(player -> player -> getEquippedItem(bodySlot::mainHand) == item -> getUid()) {
								c_helper::gameMessage("It is already equipped.", true);
								return 0;
							}
							if(item -> weapon -> getType() == weaponType::oneHanded) {
								if(player -> player -> getEquippedItem(bodySlot::mainHand)) {
									c_helper::gameMessage("You need to remove the " +  engine -> game -> actorManager.getActor(player -> player -> getEquippedItem(bodySlot::mainHand)) -> getName() + " first.", true);
									return 0;
								}
							} else if(item -> weapon -> getType() == weaponType::twoHanded) {
								if(player -> player -> getEquippedItem(bodySlot::mainHand)) {
									c_helper::gameMessage("You need to remove the " +  engine -> game -> actorManager.getActor(player -> player -> getEquippedItem(bodySlot::mainHand)) -> getName() + " first.", true);
									return 0;
								} else if(player -> player -> getEquippedItem(bodySlot::offHand)) {
									c_helper::gameMessage("You need to remove the " +  engine -> game -> actorManager.getActor(player -> player -> getEquippedItem(bodySlot::offHand)) -> getName() + " first.", true);
									return 0;
								}
							}
						} else if(item -> armor) {
							if(player -> player -> getEquippedItem(item -> armor -> getSlot()) == item -> getUid()) {
								c_helper::gameMessage("It is already equipped.", true);
								return 0;
							}
						} else {
							return 0;
						}
                        structEventData eventData;
                        eventData.type = "equip";
                        eventData.target = item -> getUid();
                        engine -> game -> actorManager.getPlayer() -> action -> start(eventData);
						engine -> game -> update(0);
                        return 0;						
					}
					case key::r: {
						if(item -> weapon and player -> player -> getEquippedItem(bodySlot::mainHand) == item -> getUid())  {
							structEventData eventData;
							eventData.type = "remove";
							eventData.target = item -> getUid();
							engine -> game -> actorManager.getPlayer() -> action -> start(eventData);
							engine -> game -> update(0);
							return 0;
						} else if(item -> armor and player -> player -> getEquippedItem(item -> armor -> getSlot()) == item -> getUid())  {
							structEventData eventData;
							eventData.type = "remove";
							eventData.target = item -> getUid();
							engine -> game -> actorManager.getPlayer() -> action -> start(eventData);
							engine -> game -> update(0);
							return 0;
						}
						return 0;
					}
				}



			}
			break;
		}

		// * SKILLS
		case charScreen::abilities: {

			// Update inventory list
			v_abilities = engine -> game -> actorManager.getPlayer() -> player -> getAbilities();

			if(v_abilities -> size() > 0) {

				// Cursor
				switch(key) {
					case key::up: {
						--abilitiesPos;
						if(abilitiesPos < 0) {
							abilitiesPos = 0;
						}
						engine -> interface.selectAbility(v_abilities -> at(abilitiesPos));
						return 0;
					}
					case key::down: {
						if(abilitiesPos < v_abilities -> size() - 1) {
							++abilitiesPos;
						}
						engine -> interface.selectAbility(v_abilities -> at(abilitiesPos));
						return 0;
					}
				}

				// Item selection
				engine -> interface.selectAbility(v_abilities -> at(abilitiesPos));

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

	// << STATS >>
	c_actor* player = engine -> game -> actorManager.getPlayer();
	if(player) {
		//engine -> screen.drawTexture("statsBackground", (x + 1) * 16, (y + 1) * 16);
		//engine -> screen.drawTexture("statsTitle", (x + 34) * 16, (y + 1) * 16);
		//engine -> screen.drawText("SEIKKEN the novice (level 1)", (x + 35) * 16 + 8 + 1, (y + 1) * 16 + 4 + 1, sf::Color::Black);
		//engine -> screen.drawText("SEIKKEN the novice (level 1)", (x + 35) * 16 + 8, (y + 1) * 16 + 4, sf::Color::White);
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
		
		
		

		engine -> screen.drawText("Damage:       13-15", (x + 34 + 22) * 16, (y + 1) * 16 + 4, color("light grey"));
		engine -> screen.drawText("            (melee)", (x + 34 + 22) * 16, (y + 2) * 16 + 4, color("light grey"));
		engine -> screen.drawText("Attack:          27", (x + 34 + 22) * 16, (y + 3) * 16 + 4, color("light grey"));
		engine -> screen.drawText("Defense:         14", (x + 34 + 22) * 16, (y + 4) * 16 + 4, color("light grey"));
		engine -> screen.drawText("Protection:       3", (x + 34 + 22) * 16, (y + 5) * 16 + 4, color("light grey"));
		engine -> screen.drawText("Resist heat:      8", (x + 34 + 22) * 16, (y + 7) * 16 + 4, color("light grey"));
		engine -> screen.drawText("Resist cold:      8", (x + 34 + 22) * 16, (y + 8) * 16 + 4, color("light grey"));
		engine -> screen.drawText("Resist poison:    8", (x + 34 + 22) * 16, (y + 9) * 16 + 4, color("light grey"));
		engine -> screen.drawText("Weight:       13/50", (x + 34 + 22) * 16, (y + 11) * 16 + 4, color("light grey"));
	}


	// << MENU >>

	engine -> screen.drawText("INVENTORY", (x + 2 + 4) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("ABILITIES", (x + 13 + 4) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("CONDITION", (x + 23 + 4 + 1) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
	engine -> screen.drawText("SKILLS", (x + 33 + 4 + 2) * 16, (y + 13 + 1) * 16 + 4, color("light grey"), textAlign::center);
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
						engine -> screen.drawTexture(p_item -> getTexture(), (x + 2) * 16 + 12, (y + 18 + i) * 16 + (4 * i), 0.5);

						// Name (brackets if equipped)
						engine -> screen.drawText("Name", (x + 4) * 16 + 4, (y + 17) * 16 - 4, color("lighter sepia"));
						if(p_item -> weapon) {
							if(engine -> game -> actorManager.getPlayer() -> player -> getEquippedItem(bodySlot::mainHand) == p_item -> getUid()) {
								engine -> screen.drawText("[" + p_item -> getName() + "]", (x + 4) * 16 + 4, ypos, sf::Color::White);
							} else {
								engine -> screen.drawText(p_item -> getName(), (x + 4) * 16 + 4, ypos, sf::Color::White);
							}
						} else if(p_item -> armor) {
							if(engine -> game -> actorManager.getPlayer() -> player -> getEquippedItem(p_item -> armor -> getSlot()) == p_item -> getUid()) {
								engine -> screen.drawText("[" + p_item -> getName() + "]", (x + 4) * 16 + 4, ypos, sf::Color::White);
							} else {
								engine -> screen.drawText(p_item -> getName(), (x + 4) * 16 + 4, ypos, sf::Color::White);
							}							
						} else {
							engine -> screen.drawText(p_item -> getName(), (x + 4) * 16 + 4, ypos, sf::Color::White);
						}

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
				engine -> screen.drawTexture("gui/cursor", (x + 1) * 16 + 4, (y + 18 + inventoryPos) * 16 + (inventoryPos) * 4);
			}
			break;
		}
		case charScreen::abilities: {

			// Menu label
			engine -> screen.drawText("ABILITIES", (x + 13 + 4) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
			//engine -> screen.drawTexture("menuCursor", (x + 13) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawTexture("menuCursor", (x + 13 + 7) * 16, (y + 13 + 1) * 16 + 7);
			//engine -> screen.drawCenteredText(">           <", (x + 13 + 4) * 16, (y + 12 + 1) * 16 + 4, sf::Color::White);

			// Ability list
			if(!v_abilities or v_abilities -> size() == 0) {
				engine -> screen.drawText("You have only learned how to walk.", (x + 2) * 16 + 4, (y + 19) * 16 - 4, sf::Color::White);
			} else {
				for(int i = 0; i < v_abilities -> size(); ++i) {
					int offset = 0;
					s_abilityAsset* ability = engine -> assetManager.getAbilityAsset(v_abilities -> at(i));
					if(ability -> duration != 0) {

						int ypos = (y + 18 + i) * 16 - 4 + (4 * i) + 1;

						// Backgound
						engine -> screen.drawTexture("listbar", (x + 1) * 16, (y + 18 + i) * 16 + (4 * i));

						// Icon
						//engine -> screen.drawTile(p_item -> getTileX(), p_item -> getTileY(), (x + 2) * 16 + 12, (y + 18 + i) * 16 + (4 * i), p_item -> getColor());

						// Name
						engine -> screen.drawText("Name", (x + 3) * 16 + 4, (y + 17) * 16 - 4, color("lighter sepia"));
						engine -> screen.drawText(ability -> name, (x + 3) * 16 + 4, ypos, sf::Color::White);

						// Duration
						engine -> screen.drawText("Time", (x + 20) * 16 + 4, (y + 17) * 16 - 4, color("lighter sepia"));
						engine -> screen.drawText(std::to_string(ability -> duration) + "s", (x + 20) * 16 + 4, ypos, color("lighter grey"));

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
				engine -> screen.drawTexture("gui/cursor", (x + 1) * 16 + 4, (y + 18 + abilitiesPos) * 16 + (abilitiesPos) * 4);
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
			engine -> screen.drawText("SKILLS", (x + 33 + 4 + 2) * 16, (y + 13 + 1) * 16 + 4, sf::Color::White, textAlign::center);
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