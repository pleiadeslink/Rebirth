c_winMessage::c_winMessage(const int& width, const int& height) {
	this -> width = width;
	this -> height = height;
	console = new TCODConsole(width, height);
}

c_winMessage::~c_winMessage() {
	delete console;
}

TCODConsole* c_winMessage::draw(const std::string& text) {

	// Clear console
	console -> setDefaultBackground(TCODColor::black);
	console -> clear();

	// Draw frame
	//c_interface::drawLine(console, 0, 0, width, 1, global::frameColor);

	// Draw message
	console -> setAlignment(TCOD_CENTER);

	return console;
}