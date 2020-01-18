#ifndef c_actorManager_hpp
#define c_actorManager_hpp
class c_actor;

/// @brief This class manages the game actors (who would've guessed it?), keeping their IDs in several memory vectors while they are alive
class c_actorManager {

    private:
        c_actor* player = 0;
        c_actor* a_uid[32766];
        std::vector<int> v_map;
        std::vector<int> v_active;
        std::vector<int> v_creature;
        std::vector<int> v_locations;
        std::vector<int> v_inventory;
        unsigned int icounter = 1;

    public:
        /// @brief Variable initializations
        c_actorManager();

        /// @brief Deletes all actors
        ~c_actorManager();

        /// @brief Saves player into 'data/save/player.sav'
        void savePlayer();

        /// @brief Loads player's actor data from 'data/save/player.sav', then creates it in the stored position
        void loadPlayer();

        /// @brief Save in a text file (.act) those actors that are not in the inventory
        /// @param path A string of the .act path
        void storeMapActors(std::string path);

        /// @brief Save in a binary file those actors that are not in the inventory
        /// @param zip A pointer to the TCODZip save file
        void saveMapActors(TCODZip* zip);

        /// @brief Save those actors that are not in the inventory
        /// @param zip A pointer to the TCODZip save file        
        void saveInventoryActors(TCODZip* zip);

        /// @brief Creates all actors stored in a .act file (human-readable) 
        /// @param path A string of the .act file path
        void loadActorsFromText(std::string path);

        /// @brief Creates all actors stored in a TCODZip file
        /// @param zip A pointer to the TCODZip save file 
        void loadActorsFromBinary(TCODZip* zip);

        /// @brief Removes all actors from map and vectors, then deletes them
        void clear();

        /// @brief Updates all active actors that are within AI range; executed at every tick
        void timeUpdate();

        /// @brief Returns a pointer to the player's actor object
        c_actor* getPlayer() { return player; }

        /// @brief Returns a pointer to the actor
        /// @param uid The actor's UID
        c_actor* getActor(const int& uid);

        /// @brief Removes an actor from map and vectors, then deletes it
        /// @param id The actor's asset ID
        /// @param mapX The X coord of the destination tile
        /// @param mapY The X coord of the destination tile
        const int& createActor(const std::string& id, const int& mapX, const int& mapY);

        /// @brief Deletes an actor from map and vectors, finally the actor's object is also deleted
        /// @param uid The actor's unique ID
        void deleteActor(const int& uid);

        /// @brief Returns a list of all actors present in the map (meaning excluding those in the inventory)
        /// @return A vector composed of the actor's uid
        std::vector<int> getMapActors() { return v_map; }

        /// @brief Returns a list of all currently active actors (those that are inside the active radius)
        /// @return A vector composed of the actor's uid
        std::vector<int> getActiveActors() { return v_active; }

        /// @brief Returns all active actors that are located on top of a visible map tile
        /// @return A vector composed of the actor's uid
        std::vector<int> getVisibleActors();

        std::vector<int> getLocations() { return v_locations; }
        const bool& actorExists(const int& uid);
        void addToMap(const int& uid);
        void addToInventory(const int& uid);
        const bool& removeFromMap(const int& uid);
        const bool& removeFromActive(const int& uid);
        const bool& removeFromLocations(const int& uid);
        const bool& removeFromInventory(const int& uid);
        const bool& removeFromCreature(const int& uid);
        //void updateInventory();

        /// @brief Returns the most aggroed target
        /// @param emitter The emitter's UID
        /// @param diplomacy Diplomacy stance for the desired target
        /// @return The target's UID, 0 if nothing found
        const int& findTarget(const int& emitter, const int& diplomacy);
};

#endif