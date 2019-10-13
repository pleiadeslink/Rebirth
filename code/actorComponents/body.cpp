c_body::c_body(c_actor* father, const bool& canMove, const bool& canView, const bool& canPickup, const int& weight)
: father(father),
  canMove(canMove),
  canView(canView),
  canPickup(canPickup),
  weight(weight) {
}
