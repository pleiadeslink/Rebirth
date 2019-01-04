c_actorManager::c_actorManager() {
    for(int i = 0; i < 32766; ++i) {
        a_uid[i] = 0;
    }
    player = 0;
    icounter = 2;
}

c_actorManager::~c_actorManager() {
    clear();
    delete player;   
}

void c_actorManager::savePlayer() {
    if(!player) {
        return;
    }

    TCODZip zip;

    player -> save(&zip);
    int invSize = player -> life -> getInventorySize();

    if(invSize > 0) {

        zip.putInt(1);

        std::vector<s_invItem> inv = player -> life -> getInventory();
        zip.putInt(inv.size());

        for(int i = 0; i < inv.size(); ++i) {
            zip.putInt(inv[i].quantity);
            if(inv[i].equipped == true) {
                zip.putInt(1);
            } else {
                zip.putInt(0);
            }
            getActor(inv[i].uid) -> save(&zip);
        }

    } else {
        zip.putInt(0);
    }
    std::string filename = "data/save/player.sav";

    zip.saveToFile(filename.c_str());
}

void c_actorManager::loadPlayer() {

    TCODZip zip;

    std::string filename = "data/save/player.sav";

    if(zip.loadFromFile(filename.c_str())) {

        std::string id = zip.getString();
        int x = zip.getInt();
        int y = zip.getInt();
        int player = createActor(id, x, y);
        c_actor* p_player = getActor(player);

        p_player -> load(&zip);

        if(zip.getInt() == 1) {

            int invSize = zip.getInt();

            for(int i = 0; i < invSize; ++i) {
                s_invItem item;
                item.quantity = zip.getInt();
                int equipped = zip.getInt();
                if(equipped == 0) {
                    item.equipped = false;
                } else {
                    item.equipped = true;
                }
                std::string id1 = zip.getString();
                int x1 = zip.getInt();
                int y1 = zip.getInt();
                item.uid = createActor(id1, x1, y1);
                getActor(item.uid) -> load(&zip);
                p_player -> life -> addToInventory(item.uid, item.quantity);
                if(item.equipped == true) {
                    p_player -> life -> equipItem(item.uid);
                }
            }
        }
    }
}

// Saves actors which are not in the inventory
/*
    int size of actors not in inv
    save actors
*/
void c_actorManager::saveMapActors(TCODZip* zip) {
    
    if(v_map.size() > 0) {
        int size = v_map.size();
        for(int i = 0; i < v_map.size(); ++i) {
            if(player -> life -> isInInventory(v_map[i])) {
                --size;
            }
        }
        zip -> putInt(size);
        for(int i = 0; i < v_map.size(); ++i) {
            if(!player -> life -> isInInventory(v_map[i])) {
                getActor(v_map[i]) -> save(zip);
            }
        }
    } else {
        zip -> putInt(0); // 0 size
    }
}

void c_actorManager::loadActors(TCODZip* zip) {
    int size = zip -> getInt();
    if(size > 0) {
        for(int i = 0; i < size; ++i) {
            std::string id = zip -> getString();
            int x = zip -> getInt();
            int y = zip -> getInt();
            int actor = createActor(id, x, y);
            getActor(actor) -> load(zip);
        }
    }
}

void c_actorManager::clear() {

    int size = v_map.size();
    for(int i = 1; i < size; ++i) {
        c_actor* actor = getActor(v_map[i]);
        if(actor != 0) {
            if(engine -> game -> map) {
                engine -> game -> map -> removeActorFromTile(v_map[i], actor -> getMapX(), actor -> getMapY());
            }
        }     
        delete actor;
    }

    memset(a_uid, 0, sizeof(a_uid));
    v_map.clear();
    v_active.clear();
    v_locations.clear();
}

void c_actorManager::timeUpdate() {
    int size = v_active.size();
    if(size == 0) {
        return;
    }
    for(int i = 0; i < size; ++i) {
        c_actor* actor = getActor(v_active[i]);
        if(actor != 0) {
            actor ->  timeUpdate();
        }
    }
}

c_actor* c_actorManager::getActor(const int& uid) {
    if(uid == 1) {
        return player;
    }
    /*/if(v_uid.size() <= uid) {
    if(a_uid[uid] != 0) {
        std::cout << "buah" << std::endl;
        return a_uid[uid];
    }
    }*/
    
    return a_uid[uid];
}

const int& c_actorManager::createActor(const std::string& id, const int& mapX, const int& mapY) {

	// Load data from asset
    kaguya::State state;
    structActorAsset* asset = engine -> assetManager.getActorAsset(id);
    if(!asset) {
        return 0;
    }

    // Create instance
    c_actor* newActor;
    if(id == "avatar") {
        newActor = new c_actor(1);
        newActor -> init(asset);
        player = newActor;
        a_uid[1] = newActor;
    } else {
        newActor = new c_actor(icounter);
        newActor -> init(asset);
        v_map.push_back(icounter);
        if(newActor -> AI) {
            v_active.push_back(icounter);    
        }
        if(newActor -> getType() == actorType::location) {
            v_locations.push_back(icounter);
        }  
        a_uid[icounter] = newActor;
        ++icounter;
    }

    // Teleport to position
    c_helper::teleportActor(newActor -> getUid(), mapX, mapY, false);

    engine -> message("Actor '" + id + "' created.");
    return newActor -> getUid();
}

void c_actorManager::deleteActor(const int& uid) {

    c_actor* actor = getActor(uid);
    if(actor == 0) {
        return;
    }

    // Delete actor from tile
    if(engine -> game -> map) {
        engine -> game -> map -> removeActorFromTile(uid, actor -> getMapX(), actor -> getMapY());
    }

    // Delete actor from lists
    for(int i = 0; i < static_cast<int>(v_active.size()); ++i) {
        if(v_active[i] == uid) {
            v_active.erase(v_active.begin() + i);
            break;
        }
    }
    for(int i = 0; i < static_cast<int>(v_map.size()); ++i) {
        if(v_map[i] == uid) {
            v_map.erase(v_map.begin() + i);
            break;
        }
    }
    for(int i = 0; i < static_cast<int>(v_locations.size()); ++i) {
        if(v_locations[i] == uid) {
            v_locations.erase(v_locations.begin() + i);
            break;
        }
    }
    a_uid[uid] = 0;

    // Update visible creatures
    //engine -> game -> map -> fov(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY(),
   // engine -> game -> actorManager.getPlayer() -> life -> getViewRange());

    engine -> message(actor -> getName() + " deleted.");

    // Delete actor instance
    delete actor;
}

const bool& c_actorManager::actorExists(const int& uid) {
    if(a_uid[uid] == 0) {
        return false;
    }
    return true;
}

void c_actorManager::actorGoesToInventory() {

    // If the actor goees to inventory, it needs to be removed from 

}