#ifndef c_weapon_hpp
#define c_weapon_hpp

class c_actor;

class c_weapon
{
	private:
		c_actor* father;
        int type;
		int category;
        int minDamage;
        int maxDamage;
        int speed;
    
	public:
		c_weapon(c_actor* father, const int& type, const int& category, const int& minDamage, const int& maxDamage, const int& speed);
		~c_weapon() { }
		const int& getType() { return type; }
		const int& getCategory() { return category; }
		const int& getMinDamage() { return minDamage; }
		const int& getMaxDamage() { return maxDamage; }
		const int& getSpeed() { return speed; }
};

#endif