#ifndef c_actor_hpp
#define c_actor_hpp

class c_action;
class c_AI;
class c_body;
class c_life;
class c_player;

/// @brief An object representing any type of entity in existence inside the game's universe; actors are composed of different components

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

        /// @brief The actor's unique ID
        int uid;

        /// @brief The actor's asset ID
        std::string id;

        /// @brief The actor's type
        int type;

        /// @brief The actor's name
        std::string name;

        /// @brief The plural version of the actor's name
        std::string plural;

        /// @brief The actor's description
        std::string description;

        /// @brief The actor's texture
        std::string texture;

        /// @brief The actor's X tileset coordinate (symbol) 
        int tileX;

        /// @brief The actor's Y tileset coordinate (symbol)
        int tileY;

        /// @brief The color that will be used to draw the actor's symbol on screen
        sf::Color color;

        /// @brief This variable keeps track of the target's UID
        int target;

        /// @brief X map coordinate
        int mapX;
        
        /// @brief X map coordinate
        int mapY;

        /// @brief This flag disables the sprite shadow
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
        
        /// @brief Assings uid and default values
        /// @param uid The actor's uid
        c_actor(const int& uid);

        /// @brief Deletes all the actor's components before dying
        ~c_actor();

        /// @brief Initialize the actor with the data provided in the asset
        /// @param asset A pointer to the actor's asset
        void init(s_actorAsset* asset);

        /// @brief Draws the character in the real coordinates provided
        /// @param x The real X coordinate
        /// @param y The real Y coordinate
        void draw(const int& x, int y);

        /// @brief Iterates through all time-update activated components; executed every time tick
        void timeUpdate();

        /// @brief Save required data in a TCODZip file
        /// @param zip A pointer to the TCODZip file
        void save(TCODZip* zip);

        /// @brief Load data from a TCODZip file
        /// @param zip A pointer to the TCODZip file
        void load(TCODZip* zip);

        bool playerAction(const bool& fromWalk, c_actor* p_player);

        /// @brief Checks if the actor can perform an ability; returns how long it takes
        /// @param abilityAsset A pointer to the s_abilityAsset file
        /// @return The ability duration or 0 if the actor cannot perform it
        const int& checkAbility(s_abilityAsset* abilityAsset); 

        /// @brief 
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
        const sf::Color& getColor() { return color; }
        const int& getTarget() { return target; }
        void setName(std::string name) { this -> name = name; }
        void setTile(const int& tileX, const int& tileY) { this -> tileX = tileX; this -> tileY = tileY; }
        void setMapX(const int& value) { mapX = value; }
        void setMapY(const int& value) { mapY = value; }
        void setTarget(const int& actor) { target = actor; }
};
#endif