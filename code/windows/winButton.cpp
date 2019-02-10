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
    int xf = x * global::tileSize / 2;
    int yf = y * global::tileSize / 2;

    // If mouse is inside button area
    selected = false;
    if(mousePos.x > xf and mousePos.x < xf + width
    and mousePos.y > yf and mousePos.y < yf + height) {
        selected = true;
        if(key == key::lclick and id != "") {
            switch(type) {
                case buttonType::tile: {
                    engine -> interface.setEmode(emode::tile);
                    engine -> interface.setEditTile(engine -> assetManager.getTileAsset(id));
                    key = 0;
                    break;
                }
                case buttonType::actor: {
                    engine -> interface.setEmode(emode::actor);
                    engine -> interface.setEditActor(engine -> assetManager.getActorAsset(id));
                    key = 0;
                    break;
                }
            }
        }
    }
    return key;
}

void c_winButton::draw() {

    if(id != "") {

        int xf = x * global::tileSize / 2;
        int yf = y * global::tileSize / 2;
        
        switch(type) {

            // Draw tile
            case buttonType::tile: {
                structTileAsset* asset = engine -> assetManager.getTileAsset(id);
                engine -> screen.drawTexture(asset -> texture, xf, yf);
                //c_tile::drawOverlay(xf, yf, asset -> type, asset -> olcolor);
                break;
            }

            // Draw actor
            case buttonType::actor: {
                structActorAsset* asset = engine -> assetManager.getActorAsset(id);
                engine -> screen.drawTexture(asset -> texture, xf, yf);
                break;
            }
        }

        // If selected, draw selection square
        if(selected == true) {
            engine -> screen.drawTexture("selectedTile", xf, yf);
        }
    }
}
