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
        std::string script; // *
        bool interior; // *
        bool explored; // *
        bool visible; // *
        std::vector<int> v_actor;
        bool check;
        void drawTransitionMark(const int& x, const int& y);
        void drawShadow(const int& x, const int& y);
        void drawOverlay(const int& x, const int& y);
        
    public:
        c_tile();
        ~c_tile();
        void draw(const int& x, const int& y, const bool& playerIsInside);
        bool playerAction(); // Returns true if successful
        bool isObstacle();
        void updateObstacle();
        void explore();

        // Actor
        void addActor(const int& actor);
        const bool& removeActor(const int& actor);
        void removeActors();
        const bool& hasActor(const int& actor);
        const bool& hasActorType(std::string actType);
        const bool& hasAnyActor() { if(v_actor.size() > 0 ) return true; else return false; }
        std::vector<int> getActorList() { return v_actor; }
        const int& findStaircase(); // Returns direction if found
        
        const int& getX() { return x; }
        const int& getY() { return y; }
        const std::string& getId() { return id; }
        const std::string& getName() { return name; }
        const int& getType() { return type; }
        std::string getScript() { return script; }
        const bool& getInterior() { return interior; }
        const bool& getExplored() { return explored; }
        const bool& getVisible() { return visible; }
        const bool& getCheck() { return check; }

        void setCoords(const int& x, const int& y) { this -> x = x; this -> y = y; }
        void setAsset(const structTileAsset* asset);
        void wipe(const structTileAsset* asset);
        void setScript(std::string script) { this -> script = script; }
        void setInterior(const bool& interior) { this -> interior = interior; }
        void setVisible(const bool& visible) { this -> visible = visible; }
        void setCheck(const bool& check) { this -> check = check; }
};

#endif