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
    player -> save(&zip); // * Save actor (id, x, y + modules)
    //saveInventoryActors(&zip);
    /*/ Inventory
    std::vector<s_invItem> inv = player -> life -> getInventory();
    if(inv.size() > 0) {
        zip.putInt(inv.size()); // * Save int inventory size
        for(int i = 0; i < inv.size(); ++i) {
            zip.putInt(inv[i].quantity); // * Save int quantity
            if(inv[i].equipped == true) { // * Save int equipped
                zip.putInt(1);
            } else {
                zip.putInt(0);
            }
            getActor(inv[i].uid) -> save(&zip); // * Save actor (id, x, y + modules)
        }

    } else {
        zip.putInt(0); // * Save int inventory size (0)
    }*/
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
        p_player -> load(&zip); // * Load actor (id, x, y + modules)
        //loadActors(&zip, true);
        /*/ Inventory
        int invSize = zip.getInt(); // * Load int inventory size
        if(invSize != 0) {
            for(int i = 0; i < invSize; ++i) {

                int quantity = zip.getInt(); // * Load int quantity
                int equipped = zip.getInt(); // * Load int equipped

                std::string id1 = zip.getString(); // * Load string id
                int x1 = zip.getInt(); // * Load int x
                int y1 = zip.getInt(); // * Load int y
                int uid = createActor(id1, x1, y1, true);

                /*s_invItem item;
                item.quantity = zip.getInt();
                int equipped = zip.getInt();
                if(equipped == 0) {
                    item.equipped = false;
                } else {
                    item.equipped = true;
                }

                item.uid = createActor(id1, x1, y1);
                getActor(item.uid) -> load(&zip);
                p_player -> life -> addToInventory(item.uid, item.quantity);
                if(item.equipped == true) {
                    p_player -> life -> equipItem(item.uid);
                }
            }
        }*/
    }
}

void c_actorManager::storeMapActors(std::string path) {
    std::ofstream outfile(path);
    for(int i = 0; i < v_map.size(); ++i) {
        c_actor* p_actor = a_uid[v_map[i]];
        
        outfile << "[" << p_actor -> getId() << "]" << std::endl;
        outfile << "x: " << p_actor -> getMapX() << std::endl;
        outfile << "y: " << p_actor -> getMapY() << std::endl;
        outfile << "name: " << p_actor -> getName() << std::endl;
        if(p_actor -> life) {
            outfile << "health: " << p_actor -> life -> getHealth() << std::endl;
        }
        if(p_actor -> door) {
            if(p_actor -> door -> getOpen() == true) {
                outfile << "open: true" << std::endl;
            } else {
                outfile << "open: false" << std::endl;
            }
        }
    }
    outfile << "[end]" << std::endl;
    outfile.close();
}

void c_actorManager::saveMapActors(TCODZip* zip) {
    if(v_map.size() > 0) {
        int size = v_map.size();
        zip -> putInt(size);
        for(int i = 0; i < v_map.size(); ++i) {
            getActor(v_map[i]) -> save(zip);
        }
    } else {
        zip -> putInt(0); // 0 size
    }
}

void c_actorManager::saveInventoryActors(TCODZip* zip) {
    
    if(v_inventory.size() > 0) {
        int size = v_inventory.size();
        zip -> putInt(size);
        for(int i = 0; i < v_inventory.size(); ++i) {
            getActor(v_inventory[i]) -> save(zip);
        }
    } else {
        zip -> putInt(0); // 0 size
    }
}

void c_actorManager::loadActorsFromText(std::string path) {
	std::string line;
	std::string key;
	bool n = true;
	std::ifstream file(path);
    c_actor* p_actor = 0;
    int x = 0;
    int y = 0;
    while(getline(file, line)) {
		if(line[0] == '[') {
			// Save previous dump and clear asset
			if(n == false) {
				c_helper::teleportActor(p_actor -> getUid(), x, y, false);

                p_actor = 0;
                if(line == "[end]") {
                    return;
                }
			}
            if(line == "[end]") {
                return;
            }
			bool found = false;
			int i = 1;
			std::string id;
			while(found == false) {
				id.push_back(line[i]);
				if(line[i + 1] == ']') {
					found = true;
				}
				++i;
			}
			n = false;
			int uid = createActor(id, 0, 0);
            p_actor = a_uid[uid];
		}
		key = "x: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			x = atof(line.c_str());
		}
		key = "y: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			y = atof(line.c_str());
		}
        // Warning! Field names must be unique
		if(p_actor != 0) {
            key = "name: ";
            if(line.find(key) != std::string::npos) {
                line.erase(0, key.length());
                p_actor -> setName(line);
            }
            key = "health: ";
            if(line.find(key) != std::string::npos) {
                line.erase(0, key.length());
                p_actor -> life -> setHealth(atof(line.c_str()));
            }
            key = "open: true";
            if(line.find(key) != std::string::npos) {
                p_actor -> door -> setOpen(true);
            }
		}
    }
    if(file.is_open()) {
        file.close();
	}
}

void c_actorManager::loadActorsFromBinary(TCODZip* zip) {
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
            delete actor;
        }         
    }

    //memset(a_uid, 0, sizeof(a_uid));
    v_map.clear();
    v_active.clear();
    v_creature.clear();
    v_locations.clear();
}

void c_actorManager::timeUpdate() {
    int size = v_active.size();
    if(size == 0 or player == 0) {
        return;
    }
    for(int i = 0; i < size; ++i) {
        c_actor* actor = getActor(v_active[i]);
        if(actor != 0 and c_helper::calculateDistance(actor -> getMapX(), actor -> getMapY(), player -> getMapX(), player -> getMapY()) < global::maxFOVRange / 2 + 8) {
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
    kaguya::State state;
    s_actorAsset* asset = engine -> assetManager.getActorAsset(id);
    if(!asset) {
        return 0;
    }
    c_actor* newActor;
    if(id == "avatar") {
        newActor = new c_actor(1);
        a_uid[1] = newActor;
        player = newActor;
        newActor -> init(asset);
    } else {
        newActor = new c_actor(icounter);
        a_uid[icounter] = newActor;
        newActor -> init(asset);
        v_map.push_back(icounter);
        if(newActor -> AI) {
            v_active.push_back(icounter);
            v_creature.push_back(icounter);
        }
        if(newActor -> getType() == actorType::location) {
            v_locations.push_back(icounter);
        }  
        ++icounter;
    }
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
    removeFromMap(uid);
    removeFromActive(uid);
    removeFromCreature(uid);
    removeFromLocations(uid);
    removeFromInventory(uid);

    a_uid[uid] = 0;

    // Update visible creatures
    //engine -> game -> map -> fov(engine -> game -> actorManager.getPlayer() -> getMapX(), engine -> game -> actorManager.getPlayer() -> getMapY(),
   // engine -> game -> actorManager.getPlayer() -> life -> getViewRange());

    //engine -> message(actor -> getName() + " deleted.");

    // Delete actor instance
    delete actor;
}

std::vector<int> c_actorManager::getVisibleActors() {
    std::vector<int> v_visibleActors;
    for(int i = 0; i < v_active.size(); ++i) {
        if(engine -> game -> map -> getTile(a_uid[v_active[i]] -> getMapX(), a_uid[v_active[i]] -> getMapY()) -> getVisible() == true) {
            v_visibleActors.push_back(v_active[i]);
        }
    }
    return v_visibleActors;
}

const bool& c_actorManager::actorExists(const int& uid) {
    if(a_uid[uid] == 0) {
        return false;
    }
    return true;
}

void c_actorManager::addToMap(const int& uid) {
    v_map.push_back(uid);
}

void c_actorManager::addToInventory(const int& uid) {
    v_inventory.push_back(uid);
}

const bool& c_actorManager::removeFromMap(const int& uid) {
    for(int i = 0; i < static_cast<int>(v_map.size()); ++i) {
        if(v_map[i] == uid) {
            v_map.erase(v_map.begin() + i);
            return true;
        }
    }
    return false;
}

const bool& c_actorManager::removeFromActive(const int& uid) {
    for(int i = 0; i < static_cast<int>(v_active.size()); ++i) {
        if(v_active[i] == uid) {
            v_active.erase(v_active.begin() + i);
            return true;
        }
    }
    return false;
}

const bool& c_actorManager::removeFromCreature(const int& uid) {
    for(int i = 0; i < static_cast<int>(v_creature.size()); ++i) {
        if(v_creature[i] == uid) {
            v_creature.erase(v_creature.begin() + i);
            return true;
        }
    }
    return false;
}

const bool& c_actorManager::removeFromLocations(const int& uid) {
    for(int i = 0; i < static_cast<int>(v_locations.size()); ++i) {
        if(v_locations[i] == uid) {
            v_locations.erase(v_locations.begin() + i);
            return true;
        }
    }
    return false;
}

const bool& c_actorManager::removeFromInventory(const int& uid) {
    for(int i = 0; i < static_cast<int>(v_inventory.size()); ++i) {
        if(v_inventory[i] == uid) {
            v_inventory.erase(v_inventory.begin() + i);
            return true;
        }
    }
    return false;
}

/*void c_actorManager::updateInventory() {
    int size = v_inventory.size();
    if(size == 0) {
        return;
    }
    for(int i = 0; i < size; ++i) {
        player -> player -> addToInventory(v_inventory[i]);
    }    
}*/

const int& c_actorManager::findTarget(const int& emitter, const int& diplomacy) {
    if(a_uid[emitter] == 0 or v_creature.size() == 0) {
        return 0;
    }
    std::map<int, int> m_target;
    const int aggro_base = 100;
    const int aggro_avatar = 100;
    // Add the avatar if criteria is met (diplomacy is as desired, actor is in distance and visible from source)
    if(engine -> game -> diplomacy.getStance(a_uid[emitter] -> AI -> getFaction(), faction::avatar) == diplomacy
    and c_helper::calculateDistance(a_uid[emitter] -> getMapX(), a_uid[emitter] -> getMapY(), player -> getMapX(), player -> getMapY()) <= 16
    and engine -> game -> map -> los(a_uid[emitter] -> getMapX(), a_uid[emitter] -> getMapY(), player -> getMapX(), player -> getMapY()) == true) {
        m_target[1] = aggro_base + aggro_avatar;
    }
    // Add creatures if criteria is met
    for(int i = 0; i < v_creature.size(); ++i) {
        if(v_creature[i] != emitter
        and engine -> game -> diplomacy.getStance(a_uid[emitter] -> AI -> getFaction(), a_uid[v_creature[i]] -> AI -> getFaction()) == diplomacy
        and c_helper::calculateDistance(a_uid[emitter] -> getMapX(), a_uid[emitter] -> getMapY(), a_uid[v_creature[i]] -> getMapX(), a_uid[v_creature[i]] ->getMapY()) <= 16
        and engine -> game -> map -> los(a_uid[emitter] -> getMapX(), a_uid[emitter] -> getMapY(), a_uid[v_creature[i]] -> getMapX(), a_uid[v_creature[i]] ->getMapY()) == true) {
            m_target[v_creature[i]] = aggro_base;
        }
    }
    std::set<std::pair<int, int>, s_comp> set_target(m_target.begin(), m_target.end());
    for(auto const &pair: set_target) {
		return pair.first;
	}
    return 0;
}