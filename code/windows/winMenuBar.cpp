void c_winMenuBar::init(const int& x, const int& y, const int& width, const int& height) {
    this -> x = x;
    this -> y = y;
    this -> width = width;
    this -> height = height;
    actor = 0;
	ability = "";
	quantity = 0;
	selected = 0;
}

// Updates text and checks for player input
const int& c_winMenuBar::update(int key, const bool& s) {

	text = "";
	if(s == true) {
		selected = true;

	} else {
		selected = false;
	}
	int c = 0;

	/*/ Mouse input
	sf::Vector2i mousePos = engine -> getMouse();
	if(mousePos.x > x * 16 and mousePos.x < x * 16 + width * 16 and mousePos.y > y * 16 and mousePos.y < y * 16 + height * 16 + 1) {

		// Selects the item
		/*if(actor and engine -> interface.isHelpActivated()) {
			engine -> interface.selectActor(actor);
		}
		//return key;
	} */

	if(actor != 0) {

		if(selected == true) {
			engine -> interface.selectActor(actor);
		}

		c_actor* p_player = engine -> game -> actorManager.getPlayer();
		c_actor* p_actor = engine -> game -> actorManager.getActor(actor);

		// Name
		c = PDNAM - text.length();
		for(int i = 0; i < c; ++i) {
			text.append(" ");
		}
		if(p_actor -> weapon) {
			if(engine -> game -> actorManager.getPlayer() -> player -> getEquippedItem(bodySlot::mainHand) == p_actor -> getUid()) {
				text.append("[");
				text.append(p_actor -> getName());
				text.append("]");
			} else {
				text.append(p_actor -> getName());
			}
		} else if(p_actor -> armor) {
			if(engine -> game -> actorManager.getPlayer() -> player -> getEquippedItem(p_actor -> armor -> getSlot()) == p_actor -> getUid()) {
				text.append("[");
				text.append(p_actor -> getName());
				text.append("]");
			} else {
				text.append(p_actor -> getName());
			}							
		} else {
			text.append(p_actor -> getName());
		}

		// Quantity
		c = PDQUA - text.length();
		for(int i = 0; i < c; ++i) {
			text.append(" ");
		}
		text.append(std::to_string(quantity));

		// Type
		c = PDTYP - text.length();
		for(int i = 0; i < c; ++i) {
			text.append(" ");
		}
		std::string str1 = "Null";
		switch(p_actor -> getType()) {
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
		text.append(str1);

		// Damage
		c = PDDAM - text.length();
		for(int i = 0; i < c; ++i) {
			text.append(" ");
		}
		if(p_actor -> weapon) {
			text.append(std::to_string(p_actor -> weapon -> getMinDamage()));
			text.append("-");
			text.append(std::to_string(p_actor -> weapon -> getMaxDamage()));
		}

		// Protection
		c = PDPRO - text.length();
		for(int i = 0; i < c; ++i) {
			text.append(" ");
		}
		if(p_actor -> armor) {
			text.append(std::to_string(p_actor -> armor -> getProtection()));
		}

		// Mass
		c = PDWGT - text.length();
		for(int i = 0; i < c; ++i) {
			text.append(" ");
		}
		if(p_actor -> body) {
			text.append(std::to_string(p_actor -> body -> getMass()));
		}

		// Keyboard input
		if(selected == true) {
			switch(key) {
				case key::d: {
					if((p_actor -> weapon and p_player -> player -> getEquippedItem(bodySlot::mainHand) == actor)
					or (p_actor -> armor and p_player -> player -> getEquippedItem(p_actor -> armor -> getSlot()) == actor)) {
						c_helper::message("You cannot drop equipped items.", true);
						return 0;
					}
					structEventData eventData;
					eventData.type = "drop";
					eventData.target = actor;
					engine -> game -> actorManager.getPlayer() -> action -> start(eventData);
					engine -> game -> update(0);
					return 0;						
				}
				case key::c: {
					if(p_actor -> consumable) {
						structEventData eventData;
						eventData.type = "consume";
						eventData.target = actor;
						p_player -> action -> start(eventData);
						engine -> game -> update(0);
					}
					return 0;						
				}
				case key::e: {
					if(p_actor -> weapon) {
						if(p_player -> player -> getEquippedItem(bodySlot::mainHand) == actor) {
							c_helper::message("It is already equipped.", true);
							return 0;
						}
						if(p_actor -> weapon -> getType() == weaponType::oneHanded) {
							if(p_player -> player -> getEquippedItem(bodySlot::mainHand)) {
								c_helper::message("You need to remove your " +  engine -> game -> actorManager.getActor(p_player -> player -> getEquippedItem(bodySlot::mainHand)) -> getName() + " first.", true);
								return 0;
							}
						} else if(p_actor -> weapon -> getType() == weaponType::twoHanded) {
							if(p_player -> player -> getEquippedItem(bodySlot::mainHand)) {
								c_helper::message("You need to remove your " +  engine -> game -> actorManager.getActor(p_player -> player -> getEquippedItem(bodySlot::mainHand)) -> getName() + " first.", true);
								return 0;
							} else if(p_player -> player -> getEquippedItem(bodySlot::offHand)) {
								c_helper::message("You need to remove your " +  engine -> game -> actorManager.getActor(p_player -> player -> getEquippedItem(bodySlot::offHand)) -> getName() + " first.", true);
								return 0;
							}
						}
					} else if(p_actor -> armor) {
						if(p_player -> player -> getEquippedItem(p_actor -> armor -> getSlot()) == actor) {
							c_helper::message("It is already equipped.", true);
							return 0;
						}
					} else {
						return 0;
					}
					structEventData eventData;
					eventData.type = "equip";
					eventData.target = actor;
					engine -> game -> actorManager.getPlayer() -> action -> start(eventData);
					engine -> game -> update(0);
					return 0;						
				}
				case key::r: {
					if(p_actor -> weapon and p_player -> player -> getEquippedItem(bodySlot::mainHand) == actor)  {
						structEventData eventData;
						eventData.type = "remove";
						eventData.target = actor;
						engine -> game -> actorManager.getPlayer() -> action -> start(eventData);
						engine -> game -> update(0);
						return 0;
					} else if(p_actor -> armor and p_player -> player -> getEquippedItem(p_actor -> armor -> getSlot()) == actor)  {
						structEventData eventData;
						eventData.type = "remove";
						eventData.target = actor;
						engine -> game -> actorManager.getPlayer() -> action -> start(eventData);
						engine -> game -> update(0);
						return 0;
					}
					return 0;
				}
			}
		}
		return key;
	} else if(ability != "") {
		
	 	if(selected == true) {
			engine -> interface.selectAbility(ability);
		}
		
		const std::string ab = ability;
		s_abilityAsset* ability = engine -> assetManager.getAbilityAsset(ab);
		
		// Name
		c = PDNAM - text.length();
		for(int i = 0; i < c; ++i) {
			text.append(" ");
		}
		text.append(ability -> name);
		c = PDTIM - text.length();
		for(int i = 0; i < c; ++i) {
			text.append(" ");
		}
		text.append(std::to_string(ability -> duration));
		c = PDENE - text.length();
		for(int i = 0; i < c; ++i) {
			text.append(" ");
		}
		text.append(std::to_string(ability -> energy));
		return key;
	}
	return key;
}

void c_winMenuBar::draw() {
	if(selected == true) {
		engine -> screen.drawTexture("listbar_s", x * 16, y * 16 );
		engine -> screen.drawText(text, x * 16, y * 16 - 3, sf::Color::White);
	} else {
		engine -> screen.drawTexture("listbar", x * 16, y * 16 );
		engine -> screen.drawText(text, x * 16, y * 16 - 3, color("light grey"));
	}	
}

void c_winMenuBar::clear() {
	actor = 0;
	ability = "";
	text = "";
}

void c_winMenuBar::setActor(const int& uid, const int& q) {
	actor = uid;
	quantity = q;
}

void c_winMenuBar::setAbility(std::string ab) {
	ability = ab;
}