c_armor::c_armor(c_actor* father, const int& protection, const int& slot, const int& penalty) {
	this -> father = father;
	this -> protection = protection;
	this -> slot = slot;
	this -> penalty = penalty;
}