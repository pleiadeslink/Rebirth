#ifndef c_tile_hpp
#define c_tile_hpp

class c_tile {
    private:
        int x;
        int y;
        std::string id; // *
        std::string name;
        int tileX;
        int tileY;
        sf::Color color;
        sf::Color bgcolor;
        sf::Color olcolor;
        int type;
        int script; // *
        bool interior; // *
        bool explored; // *
        bool visible;
        std::vector<int> v_actor;
        bool check;
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
        static void drawOverlay(const int& x, const int& y, const int& type, sf::Color color, const int& scale = 1);

        // Actor
        void addActor(const int& actor);
        const bool& removeActor(const int& actor);
        void removeActors(const bool& savePlayer = false);
        const bool& hasActor(const int& actor);
        const bool& hasActorType(std::string actType);
        const bool& hasAnyActor() { if(v_actor.size() > 0 ) return true; else return false; }
        std::vector<int> getActorList() { return v_actor; }
        const int& findActor(std::string type);
        const int& findStaircase(); // Returns direction if found
        
        const int& getX() { return x; }
        const int& getY() { return y; }
        const std::string& getId() { return id; }
        const std::string& getName() { return name; }
        const int& getType() { return type; }
        const int& getScript() { return script; }
        const bool& getInterior() { return interior; }
        const bool& getExplored() { return explored; }
        const bool& getVisible() { return visible; }
        const bool& getCheck() { return check; }

        void setCoords(const int& x, const int& y) { this -> x = x; this -> y = y; }
        void setAsset(const structTileAsset* asset);
        void wipe(const structTileAsset* asset);
        void setScript(const int& script) { this -> script = script; }
        void setInterior(const bool& interior) { this -> interior = interior; }
        void setExplored(const bool& explored) { this -> explored = explored; }
        void setVisible(const bool& visible) { this -> visible = visible; }
        void setCheck(const bool& check) { this -> check = check; }
};

#endif