#ifndef c_assetManager_hpp
#define c_assetManager_hpp

class c_assetManager {
	private:
        sf::Font font;
        sf::Texture tileset;
        std::vector<structTextureAsset> v_textureAsset;
        std::vector<structActorAsset> v_actorAsset;
        std::vector<s_abilityAsset> v_abilityAsset;
        structMapAsset a_mapAsset[127][127][63];
        std::vector<structTileAsset> v_tileAsset;
        std::vector<structVerbAsset> v_verbAsset;
        std::vector<s_herdAsset> v_herdAsset;
        //std::vector<structTopicAsset> v_topicAsset;
        int indexTile;
        int indexActor;
        void loadTiles();
        void loadActors();
        void loadAbilities();
        void loadHerds();
        structTileAsset clearTileAsset(structTileAsset asset);
        structActorAsset clearActorAsset(structActorAsset asset);
        s_abilityAsset clearAbilityAsset(s_abilityAsset asset);
        structMapAsset clearMapAsset(structMapAsset asset);
        s_herdAsset clearHerdAsset(s_herdAsset);
	
    public:
        void load();
        sf::Font* getFont() { return &font; }
        sf::Texture* getTileset() { return &tileset; }
        sf::Texture* getTextureAsset(const std::string& id);
        structMapAsset* getMapAsset(const int& x, const int& y, const int& z);
        structTileAsset* getTileAsset(const std::string& id);
        std::vector<std::string> getTileIdList();
        structActorAsset* getActorAsset(const std::string& id);
        std::vector<std::string> getActorIdList();
        structVerbAsset* getVerbAsset(const std::string& id);
        s_abilityAsset* getAbilityAsset(const std::string& id);
        s_herdAsset* getHerdAsset(const std::string& id);
};

#endif