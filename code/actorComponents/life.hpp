#ifndef c_life_hpp
#define c_life_hpp

class c_life {
    
    private:
        c_actor* father;
        int constitution;
        int agility;
        int intelligence;
        int health; // *
        int energy; // *
        int frequency;
        int carried;
        std::vector<s_invItem> inventory;
        int equipment[7];

    public:
        c_life(c_actor* father);
        void init();

        const int& getConstitution() { return constitution; }
        const int& getAgility() { return agility; }
        const int& getIntelligence() { return intelligence; }

        const int& getHealth() { return health; }
        const int& getMaxHealth();
        void restoreHealth(const int& points);
        void damageHealth(const int& points);
        void setHealth(const int& value) { health = value; }

        const int& getEnergy() { return energy; }
        const int& getMaxEnergy();
        void consumeEnergy(const int& points);
        void setEnergy(const int& value) { energy = value; }

        const int& getMaxHitDamage();
        const int& getMinHitDamage();
        const int& getHitDamage();

        const int& getFrequency() { return frequency; }
        void changeFrequency(const int& points);
        const int& getViewRange() { return global::maxFOVRange; }

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
