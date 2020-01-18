c_winInfo::c_winInfo(const int& x, const int& y, const int& width, const int& height) {
	this -> x = x;
    this -> y = y;
    originalX = x;
    originalY = y;
	this -> width = width;
    this -> height = height;
}

void c_winInfo::draw(const bool& mainView) {

    // We only show it if there's anything selected
    if(engine -> interface.getSelectedTile() == 0 and engine -> interface.getSelectedActor() == 0 and engine -> interface.getSelectedAbility() == "") {
        return;
    }

    // First lets calculate the text strings that will be later printed
    std::string name;
    std::string desc;
    int iconX = 0;
    int iconY = 0;
    sf::Color symcolor;
    std::string commands;

    // * Selected actor
    if(engine -> interface.getSelectedActor()) {
        c_actor* p_actor = engine -> game -> actorManager.getActor(engine -> interface.getSelectedActor());
        if(p_actor != 0 and engine -> game -> actorManager.actorExists(p_actor -> getUid())) {

            // Set icon
            iconX = p_actor -> getTileX();
            iconY = p_actor -> getTileY();
            symcolor = p_actor -> getColor();

            // Set name
            name = p_actor -> getName();
            
            // Set description
            desc.append("Type: ");
            switch(p_actor -> getType()) {  
                case actorType::creature: {
                    desc.append("creature");
                    break;
                }
                case actorType::weapon: {
                    desc.append("weapon");
                    break;
                }
                case actorType::armor: {
                    desc.append("armor");
                    break;
                }
                case actorType::food: {
                    desc.append("food");
                    break;
                }
                case actorType::potion: {
                    desc.append("potion");
                    break;
                }
                case actorType::scroll: {
                    desc.append("scroll");
                    break;
                }
                case actorType::staircase: {
                    desc.append("staircase");
                    break;
                }
                case actorType::door: {
                    desc.append("door");
                    break;
                }
                case actorType::tree: {
                    desc.append("tree");
                    break;
                }
                case actorType::misc: {
                    desc.append("misc");
                    break;
                }
            }
            if(p_actor -> weapon) {
                desc.append("/nWeapon type: ");
                switch(p_actor -> weapon -> getType()) {
                    case weaponType::oneHanded: {
                        desc.append("one-handed");
                        break;
                    }
                    case weaponType::twoHanded: {
                        desc.append("two-handed");
                        break;
                    }
                    case weaponType::ranged: {
                        desc.append("ranged");
                        break;
                    }
                }
                desc.append("/nCategory: ");
                switch(p_actor -> weapon -> getCategory()) {
                    case weaponCategory::sword: {
                        desc.append("sword");
                        break;
                    }
                    case weaponCategory::axe: {
                        desc.append("axe");
                        break;
                    }
                    case weaponCategory::bow: {
                        desc.append("bow");
                        break;
                    }
                }
                desc.append("/nDamage: ");
                desc.append(std::to_string(p_actor -> weapon -> getMinDamage()));
                desc.append(" - ");
                desc.append(std::to_string(p_actor -> weapon -> getMinDamage()));
                desc.append("/nSpeed: ");
                desc.append(std::to_string(p_actor -> weapon -> getSpeed()));
            }
            //desc.append("/nMass: ");
            //desc.append(std::to_string(p_actor -> body -> getMass()));
            desc.append("/n/n");
            desc.append(c_helper::justify(p_actor -> getDescription(), 39));

            // Set commands
            if(p_actor -> consumable) {
                commands.append("[C]onsume, ");
            }
            if(p_actor -> weapon) {
                if(engine -> game -> actorManager.getPlayer() -> player -> getEquippedItem(bodySlot::mainHand) == p_actor -> getUid()) {
                    commands.append("[R]emove, ");
                } else {
                    commands.append("[E]quip, ");
                }
            } else if(p_actor -> armor) {
                if(engine -> game -> actorManager.getPlayer() -> player -> getEquippedItem(p_actor -> armor -> getSlot()) == p_actor -> getUid()) {
                    commands.append("[R]emove, ");
                } else {
                    commands.append("[E]quip, ");
                }
            }
            if(!p_actor -> life) {
                commands.append("[D]rop");
            }
        }


    // * Selected tile
    } else if(engine -> interface.getSelectedTile()) {
        c_tile* tile = engine -> interface.getSelectedTile();

        // Set icon
        //iconX = ability -> getTileX();
        //iconY = ability -> getTileY();

        // Set name
        name = tile -> getName();
        
        // Set description
        desc.append(c_helper::justify(tile -> getDesc(), 39));
        
        // Set commands
        commands = "[C]ast, [K]ey";


    // * Selected ability
    } else if(engine -> interface.getSelectedAbility() != "") {
        s_abilityAsset* ability = engine -> assetManager.getAbilityAsset(engine -> interface.getSelectedAbility());

        // Set icon
        //iconX = ability -> getTileX();
        //iconY = ability -> getTileY();

        // Set name
        name = ability -> name;
        
        // Set description
        desc.append(c_helper::justify(ability -> description, 39));
        
        // Set commands
        commands = "[C]ast, [K]ey";
      
    }

    // We don't draw if it just changed screen to avoid flash
    if(f_prevMain != mainView) {
        f_prevMain = mainView;
        return;
    }

    // If main view, We set the height according to the content
    int th = height;
    if(mainView == true) {
        std::vector<std::string> lines = c_helper::splitter("/n", desc);
        th =  6 + lines.size();
    }

    // Regular view? Update coords following cursor
    if(mainView == true) {
        x = engine -> getMouse().x / 16 + 3;
        y = engine -> getMouse().y / 16;
        if(x > 43) {
            x = engine -> getMouse().x / 16 - 3 - width;
        } else {
            engine -> getMouse().x / 16 + 3;
        }
        if(x + width > 63) {
            x = 66 - width;
        }
        if(y + th > 39) {
            y = 39 - th;
        }
    } else {
        x = originalX;
        y = originalY;
    }    

    // Draw backgound
    if(mainView) {
        engine -> screen.drawBox(x * 16, y * 16, width * 16, th * 16, sf::Color::Black);
    }

    // Draw context indicator
    engine -> screen.drawTexture("detailsTitle", (x + 1) * 16, (y + 2) * 16);
    drawTitle("Details", 1);

    // Draw icon
    engine -> screen.drawTile(iconX, iconY, (x + 20) * 16 - 8, (y + 2) * 16 + 2, symcolor, 2);

    // Draw name
    engine -> screen.drawText(name, (x + 2) * 16 - 8, (y + 2) * 16 + 6, sf::Color::White);

    // Draw desc
    engine -> screen.drawText(desc, (x + 2) * 16 - 8, (y + 4) * 16 + 8, color("lighter grey"), textAlign::justify, 39);

    // Draw commands
    if(!mainView) {
        drawTitle(commands, th - 2);
    }
		
    // Lastly, draw frame
    if(mainView == true) {
        int oldHeight = height;
        height = th;
        drawFrame();
        height = oldHeight;
    } else {
        drawFrame();
    }
}