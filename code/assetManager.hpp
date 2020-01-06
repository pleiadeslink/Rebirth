#ifndef c_assetManager_hpp
#define c_assetManager_hpp

/// @brief This class loads in memory all game assets and provides pointers to them upon request
class c_assetManager {

	private:

        sf::Font font;
        sf::Texture tileset;
        std::vector<s_textureAsset> v_textureAsset;
        std::vector<s_actorAsset> v_actorAsset;
        std::vector<s_abilityAsset> v_abilityAsset;
        std::vector<s_mapAsset> v_mapAsset;
        std::vector<s_tileAsset> v_tileAsset;
        std::vector<s_verbAsset> v_verbAsset;
        std::vector<s_herdAsset> v_herdAsset;
        std::vector<s_groupAsset> v_groupAsset;
        
        /// @brief This variable is used to keep track of the active tile in Edit Mode
        int indexTile;

        /// @brief This variable is used to keep track of the active tile in Edit Mode
        int indexActor;

        /// @brief Imports the map assets from the .dat file and loads them into memory
        void loadMaps();

        /// @brief Imports the tile assets from the .dat file and loads them into memory
        void loadTiles();

        /// @brief Imports the actors assets from the .dat file and loads them into memory
        void loadActors();

        /// @brief Imports the ability assets from the .dat file and loads them into memory
        void loadAbilities();

        /// @brief Imports the herd assets from the .dat file and loads them into memory
        void loadHerds();

        /// @brief Imports the actor group assets from the .dat file and loads them into memory
        void loadGroups();

        // Don't remove the asset from parameter as it creates a weird memory bug:

        /// @brief Returns the tile default asset
        /// @return A tile default asset object
        s_tileAsset clearTileAsset(s_tileAsset asset);

        /// @brief Returns the actor default asset
        /// @return A actor default asset object
        s_actorAsset clearActorAsset(s_actorAsset asset);

        /// @brief Returns the ability default asset
        /// @return A ability default asset object
        s_abilityAsset clearAbilityAsset(s_abilityAsset asset);

        /// @brief Returns the map default asset
        /// @return A map default asset object
        s_mapAsset clearMapAsset(s_mapAsset asset);

        /// @brief Returns the herd default asset
        /// @return A herd default asset object
        s_herdAsset clearHerdAsset(s_herdAsset asset);

        /// @brief Returns the actor group default asset
        /// @return An actor group default asset object
        s_groupAsset clearGroupAsset(s_groupAsset asset);

    public:

        /// @brief Loads in memory all game assets
        void load();

        /// @brief Returns a pointer to the system font
        /// @return A pointer to the sf::Font file
        sf::Font* getFont() { return &font; }

        /// @brief Returns a pointer to the tileset, from which ASCII symbols are produced
        /// @return A pointer to the sf::Texture file
        sf::Texture* getTileset() { return &tileset; }

        /// @brief Returns a pointer to a PNG texture; if the texture is not in memory yet, it loads it on the fly
        /// @param id A string of the texture ID
        /// @return A pointer to the sf::Texture file
        sf::Texture* getTextureAsset(const std::string& id);

        /// @brief Returns a pointer to the map asset
        /// @param id A string of the map ID
        /// @return A pointer to the s_mapAsset object
        s_mapAsset* getMapAsset(const std::string& id);

        s_tileAsset* getTileAsset(const std::string& id);
        std::vector<std::string> getTileIdList();
        s_actorAsset* getActorAsset(const std::string& id);
        std::vector<std::string> getActorIdList();
        s_verbAsset* getVerbAsset(const std::string& id);
        s_abilityAsset* getAbilityAsset(const std::string& id);
        s_herdAsset* getHerdAsset(const std::string& id);

        /// @brief Returns a random actor's ID from an actor group
        /// @param id A string of the actor group ID
        /// @return A string of the actor's ID
        std::string c_assetManager::getRandomActorFromGroup(const std::string& id);
};
#endif