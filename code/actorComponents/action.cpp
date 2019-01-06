c_action::c_action(c_actor* father)
: father(father),
  active(false) {
}

bool c_action::isRunning() {
    return active;
}

bool c_action::start(const structEventData& eventData) {
    if(active) {
        return false;
    }

    this -> eventData = eventData;
    this -> eventData.emitter = father -> getUid();
    duration = 1;

    // Checks if it's a skill
    s_skillAsset* skillAsset = engine -> assetManager.getSkillAsset(eventData.type);
    if(skillAsset -> duration != 0) {
        
        // Check if player can perform skill
        duration = father -> checkSkill(skillAsset);
        if(duration == 0) {
            return false;
        }
    }

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
