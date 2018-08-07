#ifndef c_game_hpp
#define c_game_hpp

class c_actor;
class c_map;

class c_game {

    public:
        c_actorManager actorManager;
        c_gamelog gamelog;
        c_map* map = 0;
        
        c_game() { }
        ~c_game();
        const bool& newGame();
        const bool& saveGame();
        const bool& loadGame();
        void saveMap(const bool& default = false);
        void loadMap(const int& x, const int& y, const int& z);
        void changeMap(const int& x, const int& y, const int& z, const int& playerX, const int& playerY);
        void resetMap();
        void update(const int& key);
        static bool runEvent(structEventData& data);
        static bool runEffect(structEventData& data);
};

#endif