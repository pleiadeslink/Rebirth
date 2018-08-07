c_life::c_life(c_actor* father)
: father(father),
  constitution(100),
  agility(100),
  intelligence(100),
  health(0),
  energy(0),
  frequency(0),
  carried(0) {
	  constitution = 100;
	equipment[0] = 0;
	equipment[1] = 0;
	equipment[2] = 0;
	equipment[3] = 0;
	equipment[4] = 0;
	equipment[5] = 0;
	equipment[6] = 0;
}

void c_life::init() {
	health = getMaxHealth();
	energy = getMaxEnergy();
}

const int& c_life::getMaxHealth() {
	return constitution * 5;
}

void c_life::restoreHealth(const int& points) {
	health += points;
	int maxHealth = getMaxHealth();
	if(health > maxHealth) {
		health = maxHealth;
	}
}

void c_life::damageHealth(const int& points) {
	health -= points;
	if(health < 0) {
		health = 0;
	}
}

const int& c_life::getMaxEnergy() {
	return (constitution + agility + intelligence) * 10;
}

void c_life::consumeEnergy(const int& points) {
    energy -= points;
    if(energy < 0) {
        energy = 0;
    }
}

const int& c_life::getMaxHitDamage() {
	int damage = 0;
	int weaponDamage = 0;

	// No weapon
	if(equipment[bodySlot::mainHand] == 0) {
		damage = constitution / 4;
		return damage;

	// Has weapon
	} else {
		c_actor* p_weapon = engine -> game -> actorManager.getActor(equipment[bodySlot::mainHand]);
		if(p_weapon -> weapon and (p_weapon -> weapon -> getType() == weaponType::oneHanded or p_weapon -> weapon -> getType() == weaponType::twoHanded)) {
			weaponDamage = p_weapon -> weapon -> getMinDamage();
		}	
		return (constitution / 2) + weaponDamage;	
	}
}

// -20% hit damage
const int& c_life::getMinHitDamage() {
	return getMaxHitDamage() - (getMaxHitDamage() * 20 / 100);
}

const int& c_life::getHitDamage() {
	int minDam = getMinHitDamage();
	int maxDam = getMaxHitDamage();
	return c_helper::random(minDam, maxDam);
}

void c_life::changeFrequency(const int& points) {
	energy += points;
	if(energy < 0) {
		energy = 0;
	} else if(energy > 100) {
		energy = 100;
	}
}

const bool& c_life::addToInventory(const int& uid, const int& quantity) {

	c_actor* p_item = engine -> game -> actorManager.getActor(uid);

	// Check if another item of the same type is already in the inventory
	for(int i = 0; i < inventory.size(); ++i) {
		if(p_item -> getId() == engine -> game -> actorManager.getActor(inventory[i].uid) -> getId()) {

			// It is, we increment quantity of existing item and remove the one to add
			inventory[i].quantity += quantity;
			if(p_item -> body) {
				carried += p_item -> body -> getMass();
			}			
			engine -> game -> actorManager.deleteActor(uid);
			return true;
		}
	}

	// No other item of the same type is in the inventory, so we add the current one
	s_invItem item;
	item.uid = uid;
	item.quantity = quantity;
	item.equipped = false;
	inventory.push_back(item);
	if(p_item -> body) {
		carried += p_item -> body -> getMass();
	}	
	return false;
}

const bool& c_life::deleteFromInventory(const int& item) {
	c_actor* p_item = engine -> game -> actorManager.getActor(item);
	for(int i = 0; i < inventory.size(); ++i) {
		if(p_item -> getId() == engine -> game -> actorManager.getActor(inventory[i].uid) -> getId()) {
			if(inventory[i].quantity > 1) {
				--inventory[i].quantity;
				return false;
			} else {
				inventory.erase(inventory.begin() + i);
				return true;
			}
		}
	}
	return false;
}

const bool& c_life::equipItem(const int& item) {
	for(int i = 0; i < inventory.size(); ++i) {
		if(inventory[i].uid == item) {
			c_actor* p_item = engine -> game -> actorManager.getActor(item);
			if(p_item -> weapon) {
				equipment[bodySlot::mainHand] = item;
				inventory[i].equipped = true;
				return true;
			}
		}
	}
	return false;
}

const bool& c_life::removeItem(const int& item) {
	for(int i = 0; i < inventory.size(); ++i) {
		if(inventory[i].uid == item) {
			c_actor* p_item = engine -> game -> actorManager.getActor(item);
			if(p_item -> weapon) {
				equipment[bodySlot::mainHand] = 0;
				inventory[i].equipped = false;
				return true;
			}
		}
	}
	return false;
}

const bool& c_life::isInInventory(const int& item) {
	for(int i = 0; i < inventory.size(); ++i) {
		if(inventory[i].uid == item) {
			return true;
		}
	}
	return false;
}