c_winTalk::c_winTalk(const int& x, const int& y, const int& width, const int& height) {
	this -> x = x;
	this -> y = y;
	this -> width = width;
	this -> height = height;
	pos = 0;
}

int c_winTalk::update(int key) {
	if(!engine -> game or !engine -> game -> actorManager.getPlayer()) {
		return 0;
	}
    return key;
}