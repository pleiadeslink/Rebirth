#ifndef c_map_hpp
#define c_map_hpp

struct structMapAsset;
struct structFOVMap;

class c_map : public TCODMap {
    private:
        c_tile** matrix; // *
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
        int randomSeed;

        // 3D Stuff
        double dirX, dirY;
        double planeX, planeY;

        // Build
        void createMatrix();
        void fill(const structTileAsset* asset);

    public:
        c_map();
        ~c_map();
        void init();
        void save(TCODZip* zip);
        void load(TCODZip* zip);
        void wipe(const int& x, const int& y, const int& z);
        TCODPath* path(const int& x0, const int& y0, const int& x1, const int& y1);
        c_tile* runaway(const int& x1, const int& y1, const int& tx, const int& ty);

        // Public build
        void flood(const structTileAsset* asset, const int& x, const int& y);
        void floodAux(const structTileAsset* asset, const int& x, const int& y);

        // Actor management
        const bool& addActorToTile(const int& actor, const int& x, const int& y);
        const bool& removeActorFromTile(const int& actor, const int& x, const int& y);
        std::vector<int> countActorsAround(const int& x, const int& y);

        // FOV
        std::vector<int> fov(const int& x, const int& y, const int& viewRange, const bool& isPlayer);
        const structFOVMap& computeFOV(const int& x, const int& y, const int& viewRange);

        // Get
        c_tile* getTile(const int& x, const int& y);
        const std::string& getName() { return name; }
        const int& getX() { return x; }
        const int& getY() { return y; }
        const int& getZ() { return z; }
        const int& getWidth() { return width; }
        const int& getHeight() { return height; }
        const int& getRandomSeed() { return randomSeed; }
};

#endif