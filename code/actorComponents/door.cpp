c_door::c_door(c_actor* father)
: father(father),
  closed(true) {
}

void c_door::toggleOpen() {
	if(closed == true) {
		closed = false;
		father -> setTile(12, 5);
		if(father -> body) {
			father -> body -> setCanMove(true);
			father -> body -> setCanView(true);
			engine -> game -> map -> getTile(father -> getMapX(), father -> getMapY()) -> updateObstacle();
		}
	} else {
		closed = true;
		father -> setTile(11, 2);
		if(father -> body) {
			father -> body -> setCanMove(false);
			father -> body -> setCanView(false);
			engine -> game -> map -> getTile(father -> getMapX(), father -> getMapY()) -> updateObstacle();
		}
	}
}