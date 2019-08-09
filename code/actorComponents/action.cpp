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

    // If it's an ability, we get the energy required
    s_abilityAsset* abilityAsset = engine -> assetManager.getAbilityAsset(eventData.type);
    if(abilityAsset != NULL) {
        
        // Check for player if the skill is learned
        if(father -> player and father -> player -> hasAbility(eventData.type) == false) {
            engine -> game -> gamelog.message("You need to learn that ability first.");
            return false;
        }

        duration = abilityAsset -> duration;
        energy = abilityAsset -> energy;
    } else {
        duration = 1;
        energy = 0;
    }

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

        // Burn energy for player
        if(engine -> game -> actorManager.getActor(eventData.emitter) and engine -> game -> actorManager.getActor(eventData.emitter) -> player) {
            engine -> game -> actorManager.getActor(eventData.emitter) -> player -> consumeEnergy(energy);
        }

        engine -> game -> runEvent(eventData);
        active = false;
        energy = 0;
    }
}
