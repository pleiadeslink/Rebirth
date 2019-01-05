c_life::c_life(c_actor* father)
: father(father),
  constitution(100),
  agility(100),
  intelligence(100),
  health(0),
  energy(0),
  frequency(0) {
	constitution = 100;
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

void c_life::changeFrequency(const int& points) {
	energy += points;
	if(energy < 0) {
		energy = 0;
	} else if(energy > 100) {
		energy = 100;
	}
}

