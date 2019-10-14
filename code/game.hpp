#ifndef c_game_hpp
#define c_game_hpp

class c_actor;
class c_map;

class c_game {
    private:
        s_worldTile** world; // World map
        int time; // Global ingame timer

    public:
        c_actorManager actorManager;
        c_gamelog gamelog;
        c_map* map = 0;
        
        c_game() { }
        ~c_game();
        const bool& newGame();
        const bool& saveGame();
        const bool& loadGame();
        void loadMap(const int& x, const int& y, const int& z); // Tries to load from saved file, or static map, or generates it
        void saveMap(const bool& default = false); // Saves as default map if parameter is true
        void updateWorld(); // Updates world from map 0.0.0
        void populate(std::string herd); // Populates the map with the monster group specified
        int getBiome(const int& x, const int& y); // Returns the biome of the selected location of the world map
        void update(const int& key);
        void turn(); // Runs turns till the player finishes his action
        void message(std::string text); // Prints a message in the game console
        s_worldTile getWorldTile(const int& x, const int& y);
        static bool runScript(structEventData& data);
        static bool runEvent(structEventData& data);
        static bool runEffect(structEventData& data);
        
};

#endif