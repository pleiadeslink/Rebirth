c_life::c_life(c_actor* father, const int& maxHealth, const int& minDamage, const int& maxDamage, const int& speed, const int& attack, const int& defense, const int& protection, const int& block, const int& parry, const int& exp)
: father(father),
  health(maxHealth),
  maxHealth(maxHealth),
  minDamage(minDamage),
  maxDamage(maxDamage),
  speed(speed),
  attack(attack),
  defense(defense),
  protection(protection),
  block(block),
  parry(parry),
  exp(exp) {
}

void c_life::set(const int& maxHealth, const int& minDamage, const int& maxDamage, const int& speed, const int& attack, const int& defense, const int& protection, const int& block, const int& parry) {
    this -> maxHealth = maxHealth;
    this -> health = maxHealth;
    this -> minDamage = minDamage;
    this -> maxDamage = maxDamage;
    this -> speed = speed;
    this -> attack = attack;
    this -> defense = defense;
    this -> protection = protection;
    this -> block = block;
    this -> parry = parry;
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