#ifndef c_map_hpp
#define c_map_hpp
struct structMapAsset;
struct structFOVMap;

/// @brief A 2D matrix composed of map tiles representing a physical space structure
class c_map : public TCODMap {
    private:
        /// @brief This vector array stores tha map tiles 
        std::vector<std::vector<c_tile*>> matrix;

        /// @brief This array is used during map generation
        s_genTile** genMatrix;

        /// @brief [SAVED] Map name
        std::string name;

        /// @brief [SAVED] X world coordinate
        int x;

        /// @brief [SAVED] T world coordinate
        int y;

        /// @brief [SAVED] Z world coordinate
        int z;

        /// @brief [SAVED] Map width
        int width;
        
        /// @brief [SAVED] Map height
        int height;

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

        /// @brief Saves the map data into the specified TCODZip file (used when storing and saving)
        /// @param zip A pointer to the TCODZip file
        void save(TCODZip* zip);

        /// @brief Loads map data from a saved TCODZip file (binary)
        /// @param zip A pointer to the TCODZip file
        void load(TCODZip* zip);

        /// @brief Parse map terrain data from a txt file
        /// @param path A string of the map file path
        void parse(std::string path);

        /// @brief Resets tile matrix to default values and the coordinates given in parameters
        /// @param x X coordinate
        /// @param y Y coordinate
        /// @param z Z coordinate
        void wipe(const int& x, const int& y, const int& z);

        /// @brief Calculates a path between two given points
        /// @return A pointer to the path - WARNING! The path must be deleted after being used
        TCODPath* path(const int& x0, const int& y0, const int& x1, const int& y1);

        /// @brief Returns the tile in opposite direction of the target's position
        /// @param x1 The emitter X coordinate
        /// @param y1 The emitter Y coordinate
        /// @param tx The target X coordinate
        /// @param ty The target Y coordinate
        /// @return A pointer to the destination tile
        c_tile* runaway(const int& x1, const int& y1, const int& tx, const int& ty);

        /// @brief Adds a s_script object to the map's script vector
        /// @param script The s_script object to be saved
        void addScript(s_script script);

        /// @brief Informs if the current map is the world map or not
        /// @return Returns true if the current map is the world map
        const bool& isWorldMap();

        /// @brief Creates the tile matrix
        void createMatrix();

        /// @brief Creates the generator tile matrix
        void createGenMatrix();
        void fill(const s_tileAsset* asset);
        void flood(const s_tileAsset* asset, const int& x, const int& y);
        void floodAux(const s_tileAsset* asset, const int& x, const int& y);
        void genClear(std::string tile);
        const bool& genDigRoom(const int& x0, const int& y0, const int& rwidth, const int& rheight, const int& direction, const bool& digStartingTile);
        void genCleanCorridors();
        const bool& genDungeon(const int& rooms = 10); // Generates a dungeon map
        const bool& genCave(); // Generates a cave map
        const bool& genWild(const int& type); // Generates wilderness areas
        const bool& genWorld(); // Generates world map
        const bool& genIsFloor(const int& x, const int& y);
        const bool& genIsWall(const int& x, const int& y);

        /// @brief Adds a random border with a specified terrain
        /// @param tile Tile ID
        /// @param direction Determines where the border will be made
        /// @param minWidth Minimum border width
        /// @param maxWidth Maximum border width    
        void genAddBorder(std::string tile, const int& direction, const int& minWidth, const int& maxWidth);
        
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

        /// @brief Teleports an actor to a new tile
        /// @param actor The actor UID
        /// @param x X map coordinate
        /// @param x Y map coordinate
        /// @param recalculateFOV If true, map FOV is recalculated using the new position
        void teleportActor(const int& actor, const int& mapX, const int& mapY, const bool& recalculateFOV = true);

        const bool& addActorToTile(const int& actor, const int& x, const int& y);
        const bool& removeActorFromTile(const int& actor, const int& x, const int& y);
        std::vector<int> countActorsAround(const int& x, const int& y); // Returns a list with the uids of all actors around the tile
        //const int& getActorInRange(const int& x, const int& y, const int& type = 0); // Returns uid of actor in 1 tile distance, if many, it makes you choose using directional keys
        const int& getActorFromTile(const int& x, const int& y, const int& type = 0); // Returns uid of first actor of type, if no type first actor
            
        // FOV
        std::vector<int> fov(const int& x, const int& y, const int& viewRange, const bool& isPlayer);
        const structFOVMap& computeFOV(const int& x, const int& y, const int& viewRange);

        /// @brief Set all map tiles to unexplored
        void forget();

        /// @brief Calculates line of sight using Bresenham’s Line Generation Algorithm
        /// @param x1 The source X coordinate
        /// @param y1 The source Y coordinate
        /// @param x2 The destiny X coordinate
        /// @param y2 The destiny Y coordinate
        /// @return Returns false if any tile blocks view
        const bool& los(int x1, int y1, const int& x2, const int& y2);

		/// @brief Checks the ID of a tile
        /// @param x X map coordinate
        /// @param x Y map coordinate
		/// @param name Tile ID
		/// @return Returns true if the tile is found at position
		const bool& findTileByName(const int& x, const int& y, std::string name);        

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

        // Set
        void setX(const int& x) { this -> x = x; }
        void setY(const int& y) { this -> y = y; }
        void setZ(const int& z) { this -> z = z; }
};

#endif