c_screen::c_screen() {
    xRes = 1280;
    yRes = 720;
    fullScreen = false;
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

void c_screen::start(bool fullscreen) {
    sf::VideoMode videoMode(xRes, yRes);
    if(fullScreen == true) {
        window.create(videoMode, "Rebirh", sf::Style::Fullscreen);
        fullScreen = false;
    } else {
        window.create(videoMode, "Rebirh", sf::Style::Titlebar);
        fullScreen = true;    
    }  
    window.setFramerateLimit(0);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(0);
}

void c_screen::screenshot() {
    sf::Image screenshot = window.capture();
    screenshot.saveToFile("screenshot.png");
    engine -> message("Screenshot saved.");
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

void c_screen::drawTexture(const std::string& id, const int& x, const int& y, const float& scale, const sf::Uint8& light) {

	sf::Sprite sprite;
	sprite.setTexture(*(engine -> assetManager.getTextureAsset(id)));
	sprite.setPosition(x, y);
    if(scale != 1) {
        sprite.setScale(scale, scale);
    }
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
    
    sf::Text text;
    text.setFont(*(engine -> assetManager.getFont()));
    //str.insert(0, "%4");
    text.setString(str);
    text.setCharacterSize(size);
    text.setColor(color);
    switch(align) {
        case textAlign::left: {
            x = x - (text.getLocalBounds().width) + 6;
            break;
        }
        case textAlign::center: {
            x = x - (text.getLocalBounds().width / 2);
            break;
        }
        case textAlign::justify: {
            std::vector<std::string> lines = c_helper::splitter("/n", str);
            for(int j = 0; j < lines.size(); ++j) {
                sf::Text ltext;
                ltext.setFont(*(engine -> assetManager.getFont()));
                ltext.setString(lines[j]);
                ltext.setCharacterSize(size);
                ltext.setColor(color);
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

// Parse text for color codes and applies them (slower than drawText)
const int& c_screen::drawCText(std::string str, int x, const int& y, const int& align, const int& width, const int& size) {
    
    FText text;
    text.setFont(*(engine -> assetManager.getFont()));
    //str.insert(0, "%4");
    text.setString(str);
    text.setCharacterSize(size);
    switch(align) {
        case textAlign::left: {
            x = x - (text.getLocalBounds().width) + 6;
            break;
        }
        case textAlign::center: {
            x = x - (text.getLocalBounds().width / 2);
            break;
        }
        case textAlign::justify: {
            std::vector<std::string> lines = c_helper::splitter("/n", str);
            for(int j = 0; j < lines.size(); ++j) {
                FText ltext;
                ltext.setFont(*(engine -> assetManager.getFont()));
                ltext.setString(lines[j]);
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

void c_screen::drawPLine(const int& x1, const int& y1, const int& x2, const int& y2, const sf::Color color) {
    sf::VertexArray lines(sf::LinesStrip, 2);;
    lines[0].position = sf::Vector2f(x1, y1);
    lines[0].color = color;
    lines[1].position = sf::Vector2f(x2, y2);
    lines[1].color = color;
    window.draw(lines);
}