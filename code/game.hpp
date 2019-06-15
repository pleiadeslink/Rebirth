#ifndef c_game_hpp
#define c_game_hpp

class c_actor;
class c_map;

// ! World es creado a través de defines MAPSIZE

class c_game {
    private:
        s_worldTile** world;

    public:
        c_actorManager actorManager;
        c_gamelog gamelog;
        c_map* map = 0;
        
        c_game() { }
        ~c_game();
        const bool& newGame();
        const bool& saveGame();
        const bool& loadGame();
        void updateWorld(); // Updates world from map 0.0.0
        int getBiome(const int& x, const int& y); // Returns the biome of the selected location of the world map
        void update(const int& key);
        void turn(); // Runs turns till the player finishes his action
        static bool runScript(structEventData& data);
        static bool runEvent(structEventData& data);
        static bool runEffect(structEventData& data);
        s_worldTile getWorldTile(const int& x, const int& y);
};

#endif