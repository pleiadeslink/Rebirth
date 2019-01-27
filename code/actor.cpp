c_actor::c_actor(const int& uid)
:	uid(uid),
    action(0),
	player(0),
	AI(0),
	body(0),
	life(0),
    door(0),
    consumable(0),
    staircase(0),
    weapon(0),
    armor(0) {
}

c_actor::~c_actor() {
	if(action) {
		delete action;
	}
	if(player) {
		delete player;
	}	
	if(AI) {
		delete AI;
	}
	if(body) {
		delete body;
	}
	if(life) {
		delete life;
	}
    if(door) {
        delete door;
    }
    if(consumable) {
        delete consumable;
    }
    if(staircase) {
        delete staircase;
    }
    if(weapon) {
        delete weapon;
    }
    if(armor) {
        delete armor;
    }
}

void c_actor::init(structActorAsset* asset) {

    id = asset -> id;
    type = asset -> type;
    name = asset -> name;
    plural = asset -> plural;
    description = asset -> description;
    tileX = asset -> tx;
    tileY = asset -> ty;
    color = asset -> color;
    faction = asset -> faction;
    shadow = asset -> shadow;

    switch(type) {
        case actorType::avatar: {
            action = new c_action(this);
            player = new c_player(this);
            body = new c_body(this, false, true, false, asset -> mass);
            life = new c_life(this, asset -> health, asset -> minDamage, asset -> maxDamage, asset -> speed, asset -> attackSpeed, asset -> accuracy, asset -> dodge, asset -> parry, asset -> exp);
            c_helper::calculateAttributes();
            break;
        }
        case actorType::creature: {
            action = new c_action(this);
            AI = new c_AI(this);
            body = new c_body(this, false, true, false, asset -> mass);
            life = new c_life(this, asset -> health, asset -> minDamage, asset -> maxDamage, asset -> speed, asset -> attackSpeed, asset -> accuracy, asset -> dodge, asset -> parry, asset -> exp);
            break;
        }
        case actorType::weapon: {
            body = new c_body(this, true, true, true, asset -> mass);
            weapon = new c_weapon(this, asset -> wType, asset -> wCategory, asset -> minDamage, asset -> maxDamage, asset -> speed);
            break;
        }
        case actorType::armor: {
            body = new c_body(this, true, true, true, asset -> mass);
            armor = new c_armor(this, asset -> protection, asset -> slot, asset -> penalty);
            break;
        }
        case actorType::food: {
            body = new c_body(this, true, true, true, asset -> mass);
            break;
        }
        case actorType::potion: {
            body = new c_body(this, true, true, true, asset -> mass);
            consumable = new c_consumable(this, asset -> effect[0], asset -> effect[1], asset -> effect[2], asset -> effect[3]);
            break;
        }
        case actorType::scroll: {
            body = new c_body(this, true, true, true, asset -> mass);
            break;
        }
        case actorType::staircase: {
            body = new c_body(this, true, false, false, asset -> mass);
            staircase = new c_staircase(this, asset -> direction);
            break;
        }
        case actorType::door: {
            body = new c_body(this, false, false, false, asset -> mass);
            door = new c_door(this);
            break;
        }
        case actorType::misc: {
            body = new c_body(this, asset -> canMove, asset -> canView, asset -> canGet, asset -> mass);
            break;
        }
    }    
}

void c_actor::timeUpdate() {

    if(action) {

        action -> timeUpdate();

     	if(AI and action -> isRunning() == false) {
        	AI -> think();
        }
    }
}

/*
    string id
    int mapX
    int mapY
    ------------------------- from here, parameters for load()
    int hasLife
    ? int health (life)
*/
void c_actor::save(TCODZip* zip) {
    zip -> putString(id.c_str());
    zip -> putInt(mapX);
    zip -> putInt(mapY);
    if(life) {
        zip -> putInt(1);
        zip -> putInt(life -> getHealth());
    } else {
        zip -> putInt(0);
    }
    if(door and door -> isClosed() == false) {
        zip -> putInt(1);
    } else {
        zip -> putInt(0);
    }
}

void c_actor::load(TCODZip* zip) {
    int hasLife = zip -> getInt();
    if(hasLife == 1) {
        life -> setHealth(zip -> getInt());
    }
    int openedDoor = zip -> getInt();
    if(openedDoor == 1) {
        door -> toggleOpen();
    }
}

bool c_actor::playerAction(const bool& fromWalk, c_actor* p_player) {

    if(!p_player or p_player -> action -> isRunning()) {
        return false;
    }
    
    // Creature
    if(life) {
        structEventData eventData;
        eventData.type = "attack";
        eventData.target = uid;
        eventData.mapX = mapX;
        eventData.mapY = mapY;
        p_player -> action -> start(eventData);
        return true;
                        
    // Door
    } else if(door) {
        if(door -> isClosed()) {
            structEventData eventData;
            eventData.type = "open";
            eventData.target = uid;
            p_player -> action -> start(eventData);
            return true;                               
        }
    
    // Consumable
    }/* else if(consumable and fromWalk == false) {
        switch(consumable -> getAction()) {
            case event::drink: {
                structEventData eventData;
                eventData.type = "drink";
                eventData.target = uid;
                p_player -> action -> start(eventData);
                return true;
            }
        }

    // Weapon / armor
    } else if(weapon and fromWalk == false) {

        // If the item is equipped, remove, if not, equip
        if(p_player -> player -> getEquippedItem(bodySlot::mainHand) == uid) {
            structEventData eventData;
            eventData.type = "remove";
            eventData.target = uid;
            p_player -> action -> start(eventData);
            return true;       
        } else {
            structEventData eventData;
            eventData.type = "equip";
            eventData.target = uid;
            p_player -> action -> start(eventData);
            return true;  
        }
               
    }*/
    return false;
}


// Checks if the actor can perform the skill, returns how long it takes (if 0, cannot perform)
const int& c_actor::checkSkill(s_skillAsset* skillAsset) {

    // If player, does he know the skill?
    if(type == actorType::avatar) {
        if(player -> hasSkill(skillAsset -> id) == false) {
            c_helper::gameMessage("You need to learn that skill first.");
            return 0;
        }
    }

    return skillAsset -> duration;
}