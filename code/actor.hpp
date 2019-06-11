#ifndef c_actor_hpp
#define c_actor_hpp

class c_action;
class c_AI;
class c_body;
class c_life;
class c_player;

class c_actor {

    private:
        int uid;
        std::string id;
        int type;
        std::string name;
        std::string plural;
        std::string description;
        std::string texture;
        bool tall;
        int tileX;
        int tileY;
        int faction;
        sf::Color color;
        int mapX;
        int mapY;
        int target; // not used 

        // Flags
        bool f_noshadow;
        
    public:
        // Components
        c_action* action; // The actor can perform actions
        c_player* player; // Allows human control
        c_AI* AI; // Adds artificial intelligence
        c_body* body; // Materializes the actor into a physical body
        c_life* life; // Adds life attributes
        c_door* door;
        c_consumable* consumable;
        c_staircase* staircase;
        c_weapon* weapon;
        c_armor* armor;
        
        c_actor(const int& uid);
        ~c_actor();
        void init(structActorAsset* asset);
        void draw(const int& x, int y);
        void timeUpdate();
        void save(TCODZip* zip);
        void load(TCODZip* zip);
        bool playerAction(const bool& fromWalk, c_actor* p_player);
        const int& checkSkill(s_skillAsset* skillAsset); // Checks if the actor can perform the skill, returns how long it takes (if 0, cannot perform)
        const bool& isGod() { if(player) return player -> isGod(); else return false; }

        const int& getUid() { return uid; }
        std::string getId() { return id; }
        const int& getType() { return type; }
        std::string getName() { return name; }
        std::string getPlural() { return plural; }
        std::string getDescription() { return description; }
        std::string getTexture() { return texture; }
        const int& getMapX() { return mapX; }
        const int& getMapY()  { return mapY; }
        const int& getTileX() { return tileX; }
        const int& getTileY() { return tileY; }
        const int& getFaction() { return faction; }
        const sf::Color& getColor() { return color; }
        const int& getTarget() { return target; }

        void setTile(const int& tileX, const int& tileY) { this -> tileX = tileX; this -> tileY = tileY; }
        void setMapX(const int& value) { mapX = value; }
        void setMapY(const int& value) { mapY = value; }
        void setTarget(const int& actor) { target = actor; }
};

#endif