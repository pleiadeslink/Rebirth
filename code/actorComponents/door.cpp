c_door::c_door(c_actor* father)
: father(father),
  open(false) {
}

void c_door::toggleOpen() {
	if(open == false) {
		open = true;
		father -> setTile(4, 16);
		if(father -> body) {
			father -> body -> setCanMove(true);
			father -> body -> setCanView(true);
			engine -> game -> map -> getTile(father -> getMapX(), father -> getMapY()) -> updateObstacle();
		}
	} else {
		open = false;
		father -> setTile(3, 16);
		if(father -> body) {
			father -> body -> setCanMove(false);
			father -> body -> setCanView(false);
			engine -> game -> map -> getTile(father -> getMapX(), father -> getMapY()) -> updateObstacle();
		}
	}
}