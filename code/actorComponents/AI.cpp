c_AI::c_AI(c_actor* father)
: father(father) {
}

bool c_AI::think() {
    structEventData eventData;
    eventData.emitter = father -> getUid();
    eventData.type = "think";
    engine -> game -> runEvent(eventData);
    return true;
}
