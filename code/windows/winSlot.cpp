c_winSlot::c_winSlot(const int& x, const int& y, const int& width, const int& height) {
	this -> x = x;
	this -> y = y;
	this -> width = width;
	this -> height = height;
}

int c_winSlot::update(int key) {

	if(item != 0) {

		sf::Vector2i mousePos = engine -> getMouse();
		c_actor* p_item = engine -> game -> actorManager.getActor(item);

		// If mouse is in active area
		if(mousePos.x > x and mousePos.x < x + width and mousePos.y > y and mousePos.y < y + height) {

			// Left click activates the item
			if(key == key::lclick) {
				p_item -> playerAction(false);
			}
			return 0;
		}
	}
	return key;
}

void c_winSlot::draw() {

	std::ostringstream oss;
	if(item != 0 and engine -> game -> actorManager.actorExists(item)) {
		c_actor* p_item = engine -> game -> actorManager.getActor(item);
		engine -> screen.drawTile(p_item -> getTileX(), p_item -> getTileY(), x + 4, y + 6, p_item -> getColor());
		if(itemEquipped == true) {
			if(itemQuantity > 1) {
				oss << "(" << itemQuantity << " " << p_item -> getPlural() << ")";
				engine -> screen.drawText(oss.str(), x + 24, y + 3, sf::Color::White);
			} else {
				oss << "(A " << p_item -> getName() << ")";
				engine -> screen.drawText(oss.str(), x + 24, y + 3, sf::Color::White);
			}
		} else {
			if(itemQuantity > 1) {
				oss << itemQuantity << " " << p_item -> getPlural();
				engine -> screen.drawText(oss.str(), x + 24, y + 3, sf::Color::White);
			} else {
				oss << "A " << p_item -> getName();
				engine -> screen.drawText(oss.str(), x + 24, y + 3, sf::Color::White);
			}
		}
		engine -> screen.drawTexture("horizontalBarSidebar", x + 2, y + 24);
	}
}

void c_winSlot::drawOverlay() {
	sf::Vector2i mousePos = engine -> getMouse();
	if(item != 0 and mousePos.x > x and mousePos.x < x + width and mousePos.y > y and mousePos.y < y + height) {
		engine -> screen.drawBox(x, y, 240, 24, color("darkest grey"));
	}
}

void c_winSlot::clear() {
	item = 0;
	itemQuantity = 0;
}

void c_winSlot::setItem(const int& uid, const int& quantity, const bool& equipped) {
	item = uid;
	itemQuantity = quantity;
	itemEquipped = equipped;
}