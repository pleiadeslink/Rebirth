c_body::c_body(c_actor* father, const bool& canMove, const bool& canView, const bool& canPickup, const float& weight)
: father(father),
  canMove(canMove),
  canView(canView),
  canPickup(canPickup),
  weight(weight) {
}
