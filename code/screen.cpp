c_screen::c_screen() {
    xRes = 1280;
    yRes = 720;
}

c_screen::~c_screen() {
	window.close();
}

void c_screen::clear() {
    window.clear();
}

void c_screen::display() {
    window.display();
}

void c_screen::drawTile(const int& charX, const int& charY, const int& x, const int& y, const sf::Color color, const int& scale) {
    sf::IntRect rect;
    rect.left = charX * global::tileSize;
    rect.top = charY * global::tileSize;
    rect.width = global::tileSize;
    rect.height = global::tileSize;
    sf::Sprite sprite(*(engine -> assetManager.getTileset()), rect);
    sprite.setPosition(x, y);
    sprite.setColor(color);
    if(scale != 1) {
        sprite.setScale(scale, scale);
    }
    window.draw(sprite);
}

void c_screen::drawTexture(const std::string& id, const int& x, const int& y, const sf::Uint8& light) {

	sf::Sprite sprite;
	sprite.setTexture(*(engine -> assetManager.getTextureAsset(id)));
	sprite.setPosition(x, y);
    window.draw(sprite);
}

void c_screen::drawLine(const int& x1, const int& y1, const int& x2, const int& y2) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(x1, y1)),
        sf::Vertex(sf::Vector2f(x2, y2))
    };
    window.draw(line, 2, sf::Lines);
}

void c_screen::drawBox(const int& x, const int& y, const int& width, const int& height, const sf::Color color) {
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(color);
    window.draw(rectangle);
}

const int& c_screen::drawText(std::string str, int x, const int& y, const sf::Color color, const int& align, const int& width, const int& size) {
    
    sfe::RichText text(*(engine -> assetManager.getFont()));
    text << color << str;
    text.setCharacterSize(size);
    int lineCounter = 1;

    switch(align) {
        case textAlign::left: {
            x = x - (text.getLocalBounds().width);
            break;
        }
        case textAlign::center: {
            x = x - (text.getLocalBounds().width / 2);
            break;
        }
        case textAlign::justify: {
            x = x - (text.getLocalBounds().width);
            break;
            std::vector<std::string> lines;
            std::string nstr = "";
            bool fin = false;
            bool f = true;
            int i = 0;
            if(str.length() < 3) {
                break;
            }
            while(fin == false) {
                f = true;
                if(i == str.length()) {
                    lines.push_back(nstr);
                    fin = true;
                }
                if(str[i] == '/' and str[i + 1] == 'n') {
                    lines.push_back(nstr);
                    nstr = "";
                    str.erase(0, i + 2);
                    i = 0;
                    f = false;
                }
                if(i == width) {
                    for(int k = 0; k < 20; ++k) {
                        if(str[i - k] == ' ') {
							std::string ostr;
							for (int h = 0; h < i - k; ++h) {
								ostr.push_back(str[h]);
							}
                            str.erase(0, i - k + 1);
                            lines.push_back(ostr);
                            nstr = "";
                            i = 0;
                        }
                    }
                }
               
                
                if(f == true) {
                    nstr.push_back(str[i]);
                    ++i;
                }
            }
            for(int j = 0; j < lines.size(); ++j) {
                sfe::RichText ltext(*(engine -> assetManager.getFont()));
                ltext << color << lines[j];
                ltext.setCharacterSize(size);
                ltext.setPosition(x, y + (j * size));
                window.draw(ltext);
            }
            return lines.size();
        }
    }

    text.setPosition(x, y);
    window.draw(text);
    return 1;
}

void c_screen::screenshot() {
    sf::Image screenshot = window.capture();
    screenshot.saveToFile("screenshot.png");
    engine -> message("Screenshot saved.");
}

void c_screen::start() {
    sf::VideoMode videoMode(xRes, yRes);
	window.create(videoMode, "Rebirh");
    //window.create(videoMode, "Rebirh",sf::Style::Fullscreen);
    window.setFramerateLimit(0);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(0);
}
