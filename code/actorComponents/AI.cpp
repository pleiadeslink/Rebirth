c_AI::c_AI(c_actor* father, const int& faction)
: father(father),
  faction(faction),
  target(0) {
}

const bool& c_AI::think() {
    structEventData eventData;
    eventData.emitter = father -> getUid();
    eventData.type = "think";
    engine -> game -> runEvent(eventData);
    return true;
}