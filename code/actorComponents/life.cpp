c_life::c_life(c_actor* father, const int& maxHealth, const int& minDamage, const int& maxDamage, const int& speed, const int& attack, const int& defense, const int& protection, const int& block, const int& parry, const int& exp, const s_loot& loot0, const s_loot& loot1, const s_loot& loot2, const s_loot& loot3, const s_loot& loot4)
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
      loot[0] = loot0;
      loot[1] = loot1;
      loot[2] = loot2;
      loot[3] = loot3;
      loot[4] = loot4;
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

void c_life::dropLoot() {
    if(loot[0].actor != "" and c_helper::random(0,100) < loot[0].chance) {
        engine -> game -> actorManager.createActor(loot[0].actor, father -> getMapX(), father -> getMapY());
    }
    if(loot[1].actor != "" and c_helper::random(0,100) < loot[1].chance) {
        engine -> game -> actorManager.createActor(loot[0].actor, father -> getMapX(), father -> getMapY());
    }
    if(loot[2].actor != "" and c_helper::random(0,100) < loot[2].chance) {
        engine -> game -> actorManager.createActor(loot[0].actor, father -> getMapX(), father -> getMapY());
    }
    if(loot[3].actor != "" and c_helper::random(0,100) < loot[3].chance) {
        engine -> game -> actorManager.createActor(loot[0].actor, father -> getMapX(), father -> getMapY());
    }
    if(loot[4].actor != "" and c_helper::random(0,100) < loot[4].chance) {
        engine -> game -> actorManager.createActor(loot[0].actor, father -> getMapX(), father -> getMapY());
    }
}