#ifndef c_life_hpp
#define c_life_hpp

/// @brief This actor component grants life stats used for combat, kill rewards, etc.
class c_life {
    
    private:
        c_actor* father;
        int health; // *
        int maxHealth;
        int minDamage;
        int maxDamage;
        int speed;
        int attack;
        int defense;
        int protection;
        int block;
        int parry;

        /// @brief Experience points rewarded when killed
        int exp;

        /// @brief Items drop when actor is killed
        s_loot loot[5];

    public:
        c_life(c_actor* father, const int& maxHealth, const int& minDamage, const int& maxDamage, const int& speed, const int& attack, const int& defense, const int& protection, const int& block, const int& parry, const int& exp, const s_loot& loot0, const s_loot& loot1, const s_loot& loot2, const s_loot& loot3, const s_loot& loot4);      
        void set(const int& maxHealth, const int& minDamage, const int& maxDamage, const int& speed, const int& attack, const int& defense, const int& protection, const int& block, const int& parry);
        void restoreHealth(const int& points);
        void damageHealth(const int& points); 
        void setHealth(const int& health) { this -> health = health; }

        /// @brief Drops loot in father's position
        void dropLoot();
        const int& getHealth() { return health; }
        const int& getMaxHealth() { return maxHealth; }
        const int& getMinDamage() { return minDamage; }
        const int& getMaxDamage() { return maxDamage; }
        const int& getSpeed() { return speed; }
        const int& getAttack() { return attack; }
        const int& getDefense() { return defense; }
        const int& getProtection() { return protection; }
        const int& getBlock() { return block; }
        const int& getParry() { return parry; }
        const int& getExp() { return exp; }
        const int& getViewRange() { return global::maxFOVRange; }
};

#endif
