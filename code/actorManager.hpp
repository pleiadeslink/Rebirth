#ifndef c_actorManager_hpp
#define c_actorManager_hpp

class c_actor;

class c_actorManager {

    private:
        c_actor* player = 0;
        c_actor* a_uid[32766];
        std::vector<int> v_map;
        std::vector<int> v_active;
        std::vector<int> v_locations;
        std::vector<int> v_inventory;
        unsigned int icounter = 1;

    public:
        c_actorManager();
        ~c_actorManager();
        void savePlayer();
        void loadPlayer();

        /// @brief Save those actors that are not in the inventory.
        /// @param zip A pointer to the TCODZip save file.
        void saveMapActors(TCODZip* zip);
        
        void saveInventoryActors(TCODZip* zip);
        void loadActors(TCODZip* zip);
        void clear();
        void timeUpdate();
        c_actor* getPlayer() { return player; }
        c_actor* getActor(const int& uid);
        const int& createActor(const std::string& id, const int& mapX, const int& mapY);
        void deleteActor(const int& uid);

        /// @brief Returns a list of all currently active actors (those that are inside the active radius).
        /// @return A vector with the uid of all active actors.
        std::vector<int> getActiveActors() { return v_active; }

        /// @brief Returns all active actors that are on a visible tile.
        /// @return A vector with the uid of all visible actors.
        std::vector<int> getVisibleActors();

        std::vector<int> getLocations() { return v_locations; }
        const bool& actorExists(const int& uid);
        void addToMap(const int& uid);
        void addToInventory(const int& uid);
        const bool& removeFromMap(const int& uid);
        const bool& removeFromActive(const int& uid);
        const bool& removeFromLocations(const int& uid);
        const bool& removeFromInventory(const int& uid);
        //void updateInventory();
};

#endif