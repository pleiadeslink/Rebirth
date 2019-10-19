#ifndef c_life_hpp
#define c_life_hpp

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
        int exp; // The exp the creature gives when dead

    public:
        c_life(c_actor* father, const int& maxHealth, const int& minDamage, const int& maxDamage, const int& speed, const int& attack, const int& defense, const int& protection, const int& block, const int& parry, const int& exp);      
        void set(const int& maxHealth, const int& minDamage, const int& maxDamage, const int& speed, const int& attack, const int& defense, const int& protection, const int& block, const int& parry);
        void restoreHealth(const int& points);
        void damageHealth(const int& points); 
        void setHealth(const int& health) { this -> health = health; }
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
