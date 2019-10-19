#ifndef c_actor_hpp
#define c_actor_hpp

class c_action;
class c_AI;
class c_body;
class c_life;
class c_player;

/// @brief An object representing any type of entity in existence inside the game's universe

/// Attributes serialized:
///
/// - id
///
/// - mapX
///
/// - mapY
///
/// - name
///
/// > c_life
///
///   - has_life
///
///   - health
///
/// > c_door
///
///   - has_door
///
///   - open
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
        int target;

        /// @brief X map coordinate
        int mapX;
        
        /// @brief X map coordinate
        int mapY;

        // Flags
        bool f_noshadow;
        
    public:
        /// @brief A pointer to the action component
        c_action* action;

        /// @brief A pointer to the player component
        c_player* player;

        /// @brief A pointer to the artificial intelligence component
        c_AI* AI;

        /// @brief A pointer to the body component
        c_body* body;

        /// @brief A pointer to the life component
        c_life* life;

        /// @brief A pointer to the door component
        c_door* door;

        /// @brief A pointer to the consumable component
        c_consumable* consumable;

        /// @brief A pointer to the staircase component
        c_staircase* staircase;

        /// @brief A pointer to the weapon component
        c_weapon* weapon;

        /// @brief A pointer to the armor component
        c_armor* armor;
        
        c_actor(const int& uid);
        ~c_actor();
        void init(structActorAsset* asset);
        void draw(const int& x, int y);
        void timeUpdate();
        void save(TCODZip* zip);
        void load(TCODZip* zip);
        bool playerAction(const bool& fromWalk, c_actor* p_player);
        const int& checkAbility(s_abilityAsset* abilityAsset); // Checks if the actor can perform the ability, returns how long it takes (if 0, cannot perform)
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

        void setName(std::string name) { this -> name = name; }
        void setTile(const int& tileX, const int& tileY) { this -> tileX = tileX; this -> tileY = tileY; }
        void setMapX(const int& value) { mapX = value; }
        void setMapY(const int& value) { mapY = value; }
        void setTarget(const int& actor) { target = actor; }
};

#endif