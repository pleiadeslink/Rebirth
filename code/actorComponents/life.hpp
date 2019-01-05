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

        const int& getFrequency() { return frequency; }
        void changeFrequency(const int& points);
        const int& getViewRange() { return global::maxFOVRange; }
};

#endif
