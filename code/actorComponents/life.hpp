#ifndef c_life_hpp
#define c_life_hpp

class c_life {
    
    private:
        c_actor* father;
        int health; // *
        int maxHealth; // *

    public:
        c_life(c_actor* father);
        void init(); // Does nothing, // ! Delete
        const int& getHealth() { return health; }
        const int& getMaxHealth() { return maxHealth; }
        void restoreHealth(const int& points);
        void damageHealth(const int& points);
        void setHealth(const int& value) { health = value; }
        const int& getViewRange() { return global::maxFOVRange; }
};

#endif
