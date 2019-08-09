c_winDeath::c_winDeath(const int& x, const int& y, const int& width, const int& height) {
	this -> x = x;
    this -> y = y;
	this -> width = width;
    this -> height = height;
}

void c_winDeath::draw() {
    engine -> screen.drawBox(x * 16, y * 16, width * 16, height * 16, sf::Color::Black);
    drawFrame();
    std::string text = "%1YOU ARE %6DEAD%1.";
    engine -> screen.drawCText(text, (x + (width / 2)) * 16 + 8, (y + 2) * 16 - 4, textAlign::center, 20, 32);
    engine -> screen.drawTile(7, 17, (x + (width / 2)) * 16 - 8, (y + 5) * 16 - 4, sf::Color::White, 2);
    engine -> screen.drawText("Press [return] to quit.", (x + (width / 2)) * 16 + 8, (y + 7) * 16 + 4, color("light grey"), textAlign::center);
}