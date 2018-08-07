c_action::c_action(c_actor* father)
: father(father),
  active(false) {
}

bool c_action::isRunning() {
    return active;
}

bool c_action::start(const int& duration, const structEventData& eventData) {
    if(active) {
        return false;
    }
    this -> duration = duration;
    this -> eventData = eventData;
    this -> eventData.emitter = father -> getUid();
    energyLost = 1;
    active = true;
    return true;
}

void c_action::timeUpdate() {
    if(!active) {
        return;
    }
    
    --duration;
    
    // If the action has finished
    if(duration <= 0) {
        if(engine -> game -> actorManager.getActor(eventData.emitter) and engine -> game -> actorManager.getActor(eventData.emitter) -> life) {
            engine -> game -> actorManager.getActor(eventData.emitter) -> life -> consumeEnergy(energyLost);
        }
        engine -> game -> runEvent(eventData);
        active = false;
        energyLost = 0;
    }
}
