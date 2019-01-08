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
        int attackSpeed;
        int accuracy;
        int dodge;
        int parry;
        int exp;

    public:
        c_life(c_actor* father, const int& maxHealth, const int& minDamage, const int& maxDamage, const int& speed, const int& attackSpeed, const int& accuracy, const int& dodge, const int& parry, const int& exp);      
        void set(const int& maxHealth, const int& minDamage, const int& maxDamage, const int& speed, const int& attackSpeed, const int& accuracy, const int& dodge, const int& parry);
        void restoreHealth(const int& points);
        void damageHealth(const int& points); 

        const int& getHealth() { return health; }
        const int& getMaxHealth() { return maxHealth; }
        const int& getMinDamage() { return minDamage; }
        const int& getMaxDamage() { return maxDamage; }
        const int& getSpeed() { return speed; }
        const int& getAttackSpeed() { return attackSpeed; }
        const int& getAccuracy() { return accuracy; }
        const int& getDodge() { return dodge; }
        const int& getParry() { return parry; }
        const int& getExp() { return exp; }

        void setHealth(const int& value) { health = value; }
        void setMaxHealth(const int& value) { maxHealth = value; }
        void setMinDamage(const int& value) { minDamage = value; }
        void setMaxDamage(const int& value) { maxDamage = value; }
        void setSpeed(const int& value) { speed = value; }
        void setAttackSpeed(const int& value) { attackSpeed = value; }
        void setAccuracy(const int& value) { accuracy = value; }
        void setDodge(const int& value) { dodge = value; }
        void setParry(const int& value) { parry = value; }

        const int& getViewRange() { return global::maxFOVRange; }
};

#endif
