c_life::c_life(c_actor* father, const int& maxHealth, const int& minDamage, const int& maxDamage, const int& speed, const int& attackSpeed, const int& accuracy, const int& dodge, const int& parry, const int& exp)
: father(father),
  health(maxHealth),
  maxHealth(maxHealth),
  minDamage(minDamage),
  maxDamage(maxDamage),
  speed(speed),
  attackSpeed(attackSpeed),
  accuracy(accuracy),
  dodge(dodge),
  parry(parry),
  exp(exp) {
}

void c_life::set(const int& maxHealth, const int& minDamage, const int& maxDamage, const int& speed, const int& attackSpeed, const int& accuracy, const int& dodge, const int& parry) {
    this -> maxHealth = maxHealth;
    this -> health = maxHealth;
    this -> minDamage = minDamage;
    this -> maxDamage = maxDamage;
    this -> speed = speed;
    this -> attackSpeed = attackSpeed;
    this -> accuracy = accuracy;
    this -> dodge = dodge;
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