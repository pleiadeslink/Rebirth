#ifndef c_actorManager_hpp
#define c_actorManager_hpp

class c_actor;

class c_actorManager {

    private:
        c_actor* player = 0;
        c_actor* a_uid[32766];
        std::vector<int> v_active;
        std::vector<int> v_map;
        std::vector<int> v_locations;
        std::vector<int> v_inventory;
        unsigned int icounter = 1;

    public:
        c_actorManager();
        ~c_actorManager();
        void savePlayer();
        void loadPlayer();
        void saveMapActors(TCODZip* zip); // Saves actors which are not in the inventory
        void loadActors(TCODZip* zip);
        void clear();
        void timeUpdate();
        c_actor* getPlayer() { return player; }
        c_actor* getActor(const int& uid);
        const int& createActor(const std::string& id, const int& mapX, const int& mapY);
        void deleteActor(const int& uid);
        std::vector<int> getActiveActors() { return v_active; }
        std::vector<int> getLocations() { return v_locations; }
        const bool& actorExists(const int& uid);
        void actorGoesToInventory();
};

#endif