c_weapon::c_weapon(c_actor* father, const int& type, const int& category, const int& minDamage, const int& maxDamage, const int& speed) {
	this -> father = father;
	this -> type = type;
	this -> category = category;
	this -> minDamage = minDamage;
	this -> maxDamage = maxDamage;
	this -> speed = speed;
}