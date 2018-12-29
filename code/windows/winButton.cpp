c_winButton::c_winButton() 
: x(0),
  y(0),
  width(global::tileSize),
  height(global::tileSize),
  type(0),
  id(""),
  selected(false) {
}

void c_winButton::init(const int& x, const int& y, const int& width, const int& height, const int& type) {
    this -> x = x;
    this -> y = y;
    this -> width = width;
    this -> height = height;
    this -> type = type;
}

int c_winButton::update(int key, sf::Vector2i mousePos) {
    int xf = x * global::tileSize;
    int yf = y * global::tileSize;

    // If mouse is inside button area
    selected = false;
    if(mousePos.x > xf and mousePos.x < xf + width
    and mousePos.y > yf and mousePos.y < yf + height) {
        selected = true;
        if(key == key::lclick) {
            engine -> interface.setEmode(emode::tile);
            engine -> interface.setEditTile(engine -> assetManager.getTileAsset(id));
            key = 0;
        }
    }
    return key;
}

void c_winButton::draw() {
    switch(type) {
        case buttonType::tile: {
            if(id != "") {
                structTileAsset* asset = engine -> assetManager.getTileAsset(id);
                int xf = x * global::tileSize;
                int yf = y * global::tileSize;
                
                // Draw tile
                engine -> screen.drawTile(11, 13, xf, yf, asset -> bgcolor);
                c_tile::drawOverlay(xf, yf, asset -> type, asset -> olcolor);
                engine -> screen.drawTile(asset -> tileX, asset -> tileY, xf, yf, asset -> color);

                // If selected, draw selection square
                if(selected == true) {
                    engine -> screen.drawTexture("selectedTile", xf, yf);
                }
            }
            break;
        }
    }
}
