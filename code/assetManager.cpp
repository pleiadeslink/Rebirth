void c_assetManager::loadTiles() {
	structTileAsset asset;
	asset = clearTileAsset(asset);
	std::string line;
	std::string key;
	bool n = true;
	std::ifstream file("data/tile.dat");
    while(getline(file, line)) {
		if(line[0] == '[') {

			// Save previous dump and clear asset
			if(n == false) {
				v_tileAsset.push_back(asset);
				asset = clearTileAsset(asset);
			}

			// Get new id name
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
			asset.id = id;
		}

		key = "name: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.name = line;
		}

		key = "type: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			if(line == "floor") {
				asset.type = tileType::floor;
			} else if(line == "wall") {
				asset.type = tileType::wall;
			} else if(line == "obstacle") {
				asset.type = tileType::obstacle;
			} else if(line == "water") {
				asset.type = tileType::water;
			} else if(line == "deepWater") {
				asset.type = tileType::deepWater;
			} else if(line == "lava") {
				asset.type = tileType::lava;
			} else if(line == "world") {
				asset.type = tileType::world;
			}
		}

		key = "symbol: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			bool digit = 0;
			std::string n1 = "";
			std::string n2 = "";
			for(int i = 0; i < line.length(); ++i) {
				if(line[i] == 'x') {
					digit = 1;
				} else if(digit == 0) {
					n1 += line[i];
				} else {
					n2 += line[i];
				}
			}
 			asset.tx = atof(n1.c_str());
			asset.ty = atof(n2.c_str());
		}

		key = "color: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.color = color(line);
		}
		key = "colorbg: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.bgcolor = color(line);
		}
    }
    if(file.is_open()) {
        file.close();
	}
}

void c_assetManager::loadActors() {
	structActorAsset asset;
	asset = clearActorAsset(asset);
	std::string line;
	std::string key;
	bool n = true;
	std::ifstream file("data/actor.dat");
	int effectIndex = 0;
    while(getline(file, line)) {
		if(line[0] == '[') {

			// Save previous dump and clear asset
			if(n == false) {
				v_actorAsset.push_back(asset);
				asset = clearActorAsset(asset);
			}

			// Get new id name
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
			asset.id = id;
		}

		key = "type: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			if(line == "avatar") {
				asset.type = actorType::avatar;
			} else if(line == "creature") {
				asset.type = actorType::creature;
			} else if(line == "weapon") {
				asset.type = actorType::weapon;
			} else if(line == "armor") {
				asset.type = actorType::armor;
			} else if(line == "food") {
				asset.type = actorType::food;
			} else if(line == "potion") {
				asset.type = actorType::potion;
			} else if(line == "staircase") {
				asset.type = actorType::staircase;
			} else if(line == "door") {
				asset.type = actorType::door;
			} else if(line == "scroll") {
				asset.type = actorType::scroll;
			} else if(line == "container") {
				asset.type = actorType::container;
			} else if(line == "misc") {
				asset.type = actorType::misc;
			} else if(line == "location") {
				asset.type = actorType::location;
			}
		}

		key = "name: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.name = line;
		}
		
		key = "plural: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.plural = line;
		} else {
			std::string str = asset.name;
			str.append("s");
			asset.plural = str;		
		}

		key = "desc: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.description = line;
		}

		key = "texture: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.texture = "actor/";
			asset.texture.append(line);
		}

		key = "player_tex: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.playerTex = "actor/player/";
			asset.playerTex.append(line);
		}

		key = "TALL";
		if(line.find(key) != std::string::npos) {
			asset.tall = true;
		}

		key = "symbol: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			bool digit = 0;
			std::string n1 = "";
			std::string n2 = "";
			for(int i = 0; i < line.length(); ++i) {
				if(line[i] == 'x') {
					digit = 1;
				} else if(digit == 0) {
					n1 += line[i];
				} else {
					n2 += line[i];
				}
			}
 			asset.tx = atof(n1.c_str());
			asset.ty = atof(n2.c_str());
		}

		key = "color: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.color = color(line);
		}

		key = "mass: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.mass = std::stof(line.c_str());
		}

		key = "canMove: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.canMove = atof(line.c_str());
		}

		key = "canView: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.canView = atof(line.c_str());
		}

		key = "canGet: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.canGet = atof(line.c_str());
		}

		key = "direction: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			if(line == "up") {
				asset.direction = direction::up;
			} else if(line == "down") {
				asset.direction = direction::down;
			}
		}

		key = "type_w: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			if(line == "one_handed") {
				asset.wType = weaponType::oneHanded;
			} else if(line == "two_handed") {
				asset.wType = weaponType::twoHanded;
			} else if(line == "ranged") {
				asset.wType = weaponType::ranged;
			}
		}

		key = "category_w: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			if(line == "sword") {
				asset.wCategory = weaponCategory::sword;
			} else if(line == "axe") {
				asset.wCategory = weaponCategory::axe;
			} else if(line == "bow") {
				asset.wCategory = weaponCategory::bow;
			}
		}

		key = "health: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.health = atof(line.c_str());
		}

		key = "damage: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			bool digit = 0;
			std::string n1 = "";
			std::string n2 = "";
			for(int i = 0; i < line.length(); ++i) {
				if(line[i] == '-') {
					digit = 1;
				} else if(digit == 0) {
					n1 += line[i];
				} else {
					n2 += line[i];
				}
			}
 			asset.minDamage = atof(n1.c_str());
			asset.maxDamage = atof(n2.c_str());
		}

		key = "speed: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.speed = atof(line.c_str());
		}

		key = "speed_a: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.attackSpeed = atof(line.c_str());
		}

		key = "accuracy: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.accuracy = atof(line.c_str());
		}

		key = "dodge: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.dodge = atof(line.c_str());
		}

		key = "parry: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.parry = atof(line.c_str());
		}

		key = "exp: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.exp = atof(line.c_str());
		}

		key = "protection: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.protection = atof(line.c_str());
		}

		key = "slot: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.slot = atof(line.c_str());
		}

		key = "penalty: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.penalty = atof(line.c_str());
		}

		key = "faction: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			if(line == "avatar") {
				asset.faction = faction::avatar;
			} else if(line == "animal") {
				asset.faction = faction::animal;
			}
		}
		
		key = "effect: ";
		if(line.find(key) != std::string::npos and effectIndex < 5) {
			line.erase(0, key.length());
			int a = 0;
			std::string a1 = "";
			std::string a2 = "";
			std::string a3 = "";
			for(int i = 0; i < line.length(); ++i) {
				if(line[i] == '|') {
					++a;
				} else if(a == 0) {
					a1 += line[i];
				} else if(a == 1)  {	
					a2 += line[i];
				} else if(a == 2){
					a3 += line[i];
				}
			}
			asset.effect[effectIndex].script = a1.c_str();
			asset.effect[effectIndex].value1 = atof(a2.c_str());
			asset.effect[effectIndex].string1 = a3.c_str();
			++effectIndex;
		}

		// Flags

		key = "NOSHADOW";
		if(line.find(key) != std::string::npos) {
			asset.f_noshadow = true;
		}

    }
    if(file.is_open()) {
        file.close();
	}
}

void c_assetManager::loadAbilities() {
	s_abilityAsset asset;
	asset = clearAbilityAsset(asset);
	std::string line;
	std::string key;
	bool n = true;
	std::ifstream file("data/ability.dat");
    while(getline(file, line)) {
		if(line[0] == '[') {

			// Save previous dump and clear asset
			if(n == false) {
				v_abilityAsset.push_back(asset);
				asset = clearAbilityAsset(asset);
			}

			// Get new id name
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
			asset.id = id;
		}

		key = "name: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.name = line;
		}

		key = "desc: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.description = line;
		}

		key = "duration: ";
		if(line.find(key) != std::string::npos) {
			line.erase(0, key.length());
			asset.duration = atof(line.c_str());
		}
    }
    if(file.is_open()) {
        file.close();
	}
}

structTileAsset c_assetManager::clearTileAsset(structTileAsset asset) {
    asset.id = "default";
    asset.name = "default";
    asset.type = tileType::floor;
	asset.tx = 0;
	asset.ty = 0;
	return asset;
}

structActorAsset c_assetManager::clearActorAsset(structActorAsset asset) {
	asset.id = "default";
	asset.type = 0;
	asset.name = "Default";
	asset.plural = "defaults";
	asset.description = "Default description";
	asset.texture = "";
	asset.playerTex = "";
	asset.tall = false;
	asset.tx = 1;
	asset.ty = 0;
	asset.color = sf::Color::White;
	asset.mass = 0;
	asset.canMove = true;
	asset.canView = true;
	asset.canGet = true;
	asset.direction = 0;
	asset.wType = 0;
	asset.wCategory = 0;
	asset.health= 1;
	asset.minDamage = 1;
	asset.maxDamage = 1;
	asset.speed = 1;
	asset.attackSpeed = 1;
	asset.accuracy = 0;
	asset.dodge = 0;
	asset.parry = 0;
	asset.exp = 0;
	asset.protection = 0;
	asset.slot = 0;
	asset.faction = 0;
	asset.effect[0].script = "";
	asset.effect[0].value1 = 0;
	asset.effect[0].string1 = "";
	asset.effect[1].script = "";
	asset.effect[1].value1 = 0;
	asset.effect[1].string1 = "";
	asset.effect[2].script = "";
	asset.effect[2].value1 = 0;
	asset.effect[2].string1 = "";
	asset.effect[3].script = "";
	asset.effect[3].value1 = 0;
	asset.effect[3].string1 = "";
	asset.f_noshadow = false;
	return asset;
}

s_abilityAsset c_assetManager::clearAbilityAsset(s_abilityAsset asset) {
	asset.id = "default";
	asset.name = "Default";
	asset.duration = 1;
	return asset;
}

void c_assetManager::load() {

	indexTile = 0;
	indexActor = 0;
	if(!font.loadFromFile("data/font/ibm.ttf")) {
		throw std::invalid_argument( "The font file could not be found! :/" );
	}
	tileset.loadFromFile("data/texture/terminal.png");
	loadTiles();
	loadActors();
	loadAbilities();
}

sf::Texture* c_assetManager::getTextureAsset(const std::string& id) {
	// Look for texture in vector
	if(v_textureAsset.size() != 0) // Check is there are some
		for(unsigned int i = 0; i < v_textureAsset.size(); ++i)
			if(v_textureAsset[i].id == id)
				return v_textureAsset[i].data;

	// It doesn't exist, load it
	sf::Texture* data = new sf::Texture();
	data -> loadFromFile("data/texture/" + id + ".png");

	// Set attributes
	data -> setSmooth(true);
	if(id == "s_abilityAssetwater")
		data -> setRepeated(true);

	// Console message
	std::ostringstream s;
	s << "Loading /texture/" << id << ".png...";
	engine -> message(s.str());
	
	// Now add it to the asset manager
	structTextureAsset newTexture;
	newTexture.id = id;
	newTexture.data = data;
	v_textureAsset.push_back(newTexture);
	
	return newTexture.data;
}

structVerbAsset* c_assetManager::getVerbAsset(const std::string& id) {
    int max = v_verbAsset.size();
	if(max != 0) { 
		for(int i = 0; i < max; ++i) {
			if(v_verbAsset[i].id == id) {
				return &v_verbAsset[i];
            }
        }
    }
    // Not found, default returned
	return &v_verbAsset[0]; 
}

structMapAsset* c_assetManager::getMapAsset(const int& x, const int& y, const int& z) {
	return &a_mapAsset[x][y][z]; 
}

structTileAsset* c_assetManager::getTileAsset(const std::string& id) {
    int max = v_tileAsset.size();
	if(max != 0) { 
		for(int i = 0; i < max; ++i) {
			if(v_tileAsset[i].id == id) {
				return &v_tileAsset[i];
            }
        }
    }
    // Not found, default returned
	return &v_tileAsset[0]; 
}

std::vector<std::string> c_assetManager::getTileIdList() {
	std::vector<std::string> list;
	int max = v_tileAsset.size();
	if(max != 0) { 
		for(int i = 0; i < max; ++i) {
			list.push_back(v_tileAsset[i].id);
        }
    }
	return list;
}

structActorAsset* c_assetManager::getActorAsset(const std::string& id) {
    int max = v_actorAsset.size();
	if(max != 0) { 
		for(int i = 0; i < max; ++i) {
			if(v_actorAsset[i].id == id) {
				return &v_actorAsset[i];
            }
        }
    }
    // Not found, default returned
	return &v_actorAsset[0]; 
}

std::vector<std::string> c_assetManager::getActorIdList() {
	std::vector<std::string> list;
	int max = v_actorAsset.size();
	if(max != 0) { 
		for(int i = 0; i < max; ++i) {
			list.push_back(v_actorAsset[i].id);
        }
    }
	return list;
}

s_abilityAsset* c_assetManager::getAbilityAsset(const std::string& id) {
    int max = v_abilityAsset.size();
	if(max != 0) { 
		for(int i = 0; i < max; ++i) {
			if(v_abilityAsset[i].id == id) {
				return &v_abilityAsset[i];
            }
        }
    }
    // Not found, default returned
	return &v_abilityAsset[0]; 
}