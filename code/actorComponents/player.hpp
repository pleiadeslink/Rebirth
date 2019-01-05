#ifndef c_player_hpp
#define c_player_hpp

class c_player
{
	private:
        c_actor* father;
        int key;
        bool god;
        std::vector<s_invItem> inventory;
        int equipment[7];
        int carried;
        
	public:
        c_player(c_actor* father);
        bool channel(const int& key, const bool& worldMap); // Follows human input
        void setKey(const int& key) { this -> key = key; }
        const bool& toggleGodMode() { if(god == true) god = false; else god = true; return god; }
        const bool& isGod() { return god; }

        const bool& addToInventory(const int& uid, const int& quantity = 1); // Returns true if the item already existed
        std::vector<s_invItem> getInventory() { return inventory; }
        const bool& deleteFromInventory(const int& item); // Returns true if it was the last item of its type that existed
        const int& getEquippedItem(const int& slot) { return equipment[slot]; }
        const bool& equipItem(const int& item); // Returns false if the item is not in inventory
        const bool& removeItem(const int& slot); // Returns false if the item is not in inventory
        const bool& isInInventory(const int& item); // Check if the item is in the inventory
        const int& getInventorySize() { return inventory.size(); }
};

#endif
