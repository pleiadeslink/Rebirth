#ifndef c_map_hpp
#define c_map_hpp

struct structMapAsset;
struct structFOVMap;

class c_map : public TCODMap {
    private:
        c_tile** matrix; // *
        s_genTile** genMatrix;
        std::string name; // *
        int x; // *
        int y; // *
        int z; // *
        int width; // *
        int height; // *
        int oldXFOV;
        int oldYFOV;
        int selectedTileX;
        int selectedTileY;
        std::string ambience;
        int randomSeed;
        std::vector<s_script> v_script;

        // Generator
        std::string genFloor1;
        std::string genFloor2;
        std::string genFloor3;
        std::string genWall1;
        std::string genWall2;
        std::string genWall3;
        std::vector<s_coordinates> v_genWallStack;
        void updateWallStack();
        static s_map getCellularMap(const int& iterations, const int& birthLimit, const int& deathLimit, const int& chanceToStartAlive); // Returns a cellular automata generated map with 0s and 1s
        static s_map cellularIteration(s_map oldMap, const int& birthLimit, const int& deathLimit); // Conway's Game of Life rules
        static int countNeighbours(s_map map, const int& x, const int& y); // Used in cellular automata generation
        double getNoise(double nx, double ny, TCODNoise* noise); // Returns noise in specific location

        // 3D Stuff
        double dirX, dirY;
        double planeX, planeY;

    public:
        c_map();
        ~c_map();
        void init();
        void save(TCODZip* zip);
        void load(TCODZip* zip);
        void wipe(const int& x, const int& y, const int& z);
        TCODPath* path(const int& x0, const int& y0, const int& x1, const int& y1);
        c_tile* runaway(const int& x1, const int& y1, const int& tx, const int& ty);
        void addScript(s_script script);
        const bool& isWorldMap();

        // Public build
        void createMatrix();
        void createGenMatrix();
        void fill(const structTileAsset* asset);
        void flood(const structTileAsset* asset, const int& x, const int& y);
        void floodAux(const structTileAsset* asset, const int& x, const int& y);
        void genClear(const int& tile = 0);
        const bool& genDigRoom(const int& x0, const int& y0, const int& rwidth, const int& rheight, const int& direction, const bool& digStartingTile);
        void genCleanCorridors();
        const bool& genDungeon(const int& rooms = 10); // Generates a dungeon map
        const bool& genCave(); // Generates a cave map
        const bool& genWild(const int& type); // Generates wilderness areas
        const bool& genWorld(); // Generates world map
        const bool& genIsFloor(const int& x, const int& y);
        const bool& genIsWall(const int& x, const int& y);
        void setGenFloor1(std::string value) { genFloor1 = value; }
        void setGenFloor2(std::string value) { genFloor2 = value; }
        void setGenFloor3(std::string value) { genFloor3 = value; }
        void setGenWall1(std::string value) { genWall1 = value; }
        void setGenWall2(std::string value) { genWall2 = value; }
        void setGenWall3(std::string value) { genWall3 = value; }
        void setAmbience(std::string track) { ambience = track; }
        void genAddCellularPatch(std::string tile, const int& size); // Adds a patch of the specified tile using a cellular automata generated pattern
        void genPlantTrees(std::string tree, const int& size, const bool& dead); // Plants trees randomly on grass tiles (if dead is true, there is a small chance every round of a dead tree being plant in a dirt tile if found
        void genPlaceActorSomewhere(std::string actor, const int& quantity, std::string forbiddenTile = ""); // Places actor in a free random position
        void build();

        // Actor management
        const bool& addActorToTile(const int& actor, const int& x, const int& y);
        const bool& removeActorFromTile(const int& actor, const int& x, const int& y);
        std::vector<int> countActorsAround(const int& x, const int& y);

        // FOV
        std::vector<int> fov(const int& x, const int& y, const int& viewRange, const bool& isPlayer);
        const structFOVMap& computeFOV(const int& x, const int& y, const int& viewRange);
        void forget(); // Forgets FOV

        // Get
        c_tile* getTile(const int& x, const int& y);
        const std::string& getName() { return name; }
        const int& getX() { return x; }
        const int& getY() { return y; }
        const int& getZ() { return z; }
        const int& getWidth() { return width; }
        const int& getHeight() { return height; }
        std::string getAmbience() { return ambience; }
        const int& getRandomSeed() { return randomSeed; }
        std::vector<s_script> getScripts() { return v_script; }
};

#endif