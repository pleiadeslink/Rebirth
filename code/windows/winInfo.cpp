c_winInfo::c_winInfo(const int& x, const int& y, const int& width, const int& height) {
	this -> x = x;
	this -> y = y;
	this -> width = width;
	this -> height = height;
}

void c_winInfo::draw() {

    c_actor* p_actor = engine -> game -> actorManager.getActor(engine -> interface.getSelectedActor());
    if(p_actor != 0 and engine -> game -> actorManager.actorExists(p_actor -> getUid())) {

        // Backgound
        engine -> screen.drawTexture("detailsTitle", (x + 1) * 16, (y + 2) * 16);

        // Icon
        engine -> screen.drawTile(p_actor -> getTileX(), p_actor -> getTileY(), (x + 20) * 16, (y + 4) * 16 + 8, p_actor -> getColor(), 1);

        // Name
        engine -> screen.drawText(p_actor -> getName(), (x + 2) * 16, (y + 2) * 16 + 6, sf::Color::White);
        
        // Description
        std::string desc;
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
            case actorType::misc: {
                desc.append("misc");
                break;
            }
        }
        if(p_actor -> weapon) {
            desc.append("\nWeapon type: ");
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
            desc.append("\nCategory: ");
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
            desc.append("\nDamage: ");
            desc.append(std::to_string(p_actor -> weapon -> getMinDamage()));
            desc.append(" - ");
            desc.append(std::to_string(p_actor -> weapon -> getMinDamage()));
            desc.append("\nSpeed: ");
            desc.append(std::to_string(p_actor -> weapon -> getSpeed()));
        }
        desc.append("\nMass: ");
        desc.append(std::to_string(p_actor -> body -> getMass()));
        desc.append("\n\n");
        desc.append(c_helper::justify(p_actor -> getDescription(), 37));
        engine -> screen.drawText(desc, (x + 2) * 16, (y + 4) * 16 + 8, color("lighter grey"), textAlign::justify, 36);
        drawTitle("[U]se, [D]rop", height - 2);
    }
		
    drawTitle("Details", 1);
    drawFrame();	
}