#ifndef c_tile_hpp
#define c_tile_hpp

/// @brief This class represents the tiled floor sections that compose a map
class c_tile {
    private:

        /// @brief The horizontal map coordinate
        int x;

        /// @brief The vertical map coordinate
        int y;

        /// @brief The tile asset identifier
        std::string id; // *

        std::string name;
        std::string desc;
        int tileX;
        int tileY;
        sf::Color color;
        sf::Color bgcolor;
        sf::Color olcolor; // Seems this is not used anymore, delete it!
        int type;
        int script; // *
        bool interior; // *
        bool explored; // *
        bool visible;
        std::vector<int> v_actor;
        bool check;

        /// @brief Used to cycle between the present actor symbols when drawing the tile
        int frameIndex;

        /// @brief Used to cycle between the present actor symbols when drawing the tile
        int tickCounter;

        //void drawTransitionMark(const int& x, const int& y);
        void drawShadow(const int& x, const int& y);
        
    public:
        c_tile();
        ~c_tile();
        void draw(const int& x, const int& y, const bool& playerIsInside, const bool& fog);
        bool playerAction(c_actor* p_player); // Returns true if successful
        bool isObstacle();
        bool isLocation();
        void updateObstacle();
        void explore();

        /// @brief // Changes the symbol color to red as if it was stained by blood
        void stainBlood(); 

        // Actor
        void addActor(const int& actor);
        const bool& removeActor(const int& actor);
        void removeActors(const bool& savePlayer = false);
        const bool& hasActor(const int& actor);
        const bool& hasActorType(std::string actType);
        const bool& hasAnyActor() { if(v_actor.size() > 0 ) return true; else return false; }
        std::vector<int> getActorList() { return v_actor; }
        std::vector<int> getItems(); // Returns vector of actors  that can be picked up
        const int& findActorByName(std::string name);
        const int& findStaircase(); // Returns direction if found
        
        const int& getX() { return x; }
        const int& getY() { return y; }
        const std::string& getId() { return id; }
        const std::string& getName() { return name; }
        const std::string& getDesc() { return desc; }
        const int& getType() { return type; }
        const int& getScript() { return script; }
        const bool& getInterior() { return interior; }
        const bool& getExplored() { return explored; }
        const bool& getVisible() { return visible; }
        const bool& getCheck() { return check; }

        void setCoords(const int& x, const int& y) { this -> x = x; this -> y = y; }
        void setAsset(const s_tileAsset* asset);
        void wipe(const s_tileAsset* asset);
        void setScript(const int& script) { this -> script = script; }
        void setInterior(const bool& interior) { this -> interior = interior; }
        void setExplored(const bool& explored) { this -> explored = explored; }
        void setVisible(const bool& visible) { this -> visible = visible; }
        void setCheck(const bool& check) { this -> check = check; }
};

#endif