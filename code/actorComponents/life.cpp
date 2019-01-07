c_life::c_life(c_actor* father)
: father(father),
  health(1),
  maxHealth(1) {
}

void c_life::init() {
	//health = getMaxHealth();
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

