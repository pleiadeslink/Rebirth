#ifndef c_assetManager_hpp
#define c_assetManager_hpp

struct structActorAsset;
struct structMapAsset;
struct structTileAsset;
struct structTextureAsset;
struct structVerbAsset;

class c_assetManager {
	private:
        sf::Font font;
        sf::Texture tileset;
        std::vector<structTextureAsset> v_textureAsset;
        std::vector<structActorAsset> v_actorAsset;
        structMapAsset a_mapAsset[127][127][63];
        std::vector<structTileAsset> v_tileAsset;
        std::vector<structVerbAsset> v_verbAsset;
        //std::vector<structTopicAsset> v_topicAsset;
        int indexTile;
        int indexActor;
        void loadActors();
        structActorAsset clearActorAsset(structActorAsset asset);
        structMapAsset clearMapAsset(structMapAsset asset);
	
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
};

#endif