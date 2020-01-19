#ifndef c_game_hpp
#define c_game_hpp

class c_actor;
class c_map;

class c_game {
    private:
        s_worldTile** world; // World map
        int time; // Global ingame timer
        std::vector<s_coordinates> connectedTiles; // Used to store the tiles connected to a target tile when populating with herds

    public:
        c_actorManager actorManager;
        c_diplomacy diplomacy;
        c_gamelog gamelog;
        c_map* map = 0;
        
        c_game() { }
        ~c_game();

        /// @brief Creates a new game, loads the world map and teleports the player
        /// @return Returns true if successful
        const bool& newGame();

        const bool& saveGame();
        const bool& loadGame();

        /// @brief Ends game by showing the gameover screen, then closing the program 
		void endGame();

        /// @brief Unloads current map and loads a local map
        /// @param x X coordinate
        /// @param y Y coordinate
        /// @param z Z coordinate
        /// @return Returns true if successful
        const bool& changeMap(const int& x, const int& y, const int& z);

        /// @brief Loads a map from a saved file, a static map  or generates it
        /// @param x X coordinate
        /// @param y Y coordinate
        /// @param z Z coordinate
        void loadMap(const int& x, const int& y, const int& z);

        /// @brief Saves the map in a .TCODZip file
        void saveMap();

        /// @brief Stores the map in a human-readable file
        void storeMap();

        /// @brief Updates world map from local map 0.0.0
        void updateWorld();

        /// @brief Populates the map with a herd
        /// @param herd A string of the herd's id
        void populate(std::string herd);
        
        /// @brief Aux flood function used in populate() exclusively
        /// @param x X coordinate
        /// @param y Y coordinate
        void flood(const int& x, const int& y);

        /// @brief Returns the biome of the selected location of the world map
        /// @param x X coordinate
        /// @param y Y coordinate
        int getBiome(const int& x, const int& y);
        
        void update(const int& key);

        /// @brief Runs turns till the avatar finishes his action
        void turn();

        /// @brief Prints a message in the game console 
        void message(std::string text);

        s_worldTile getWorldTile(const int& x, const int& y);
        static bool runScript(structEventData& data);
        static bool runEvent(structEventData& data);
        static bool runEffect(structEventData& data);

        /// @brief Returns true when current map is worldmap (50, 0, 0)
        /// @return True if current map is worldmap
        const bool& isWorldMap();
};

#endif