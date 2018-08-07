#ifndef c_armor_hpp
#define c_armor_hpp

class c_actor;

class c_armor
{
	private:
		c_actor* father;
        int protection;
        int slot;
        int penalty;
    
	public:
		c_armor(c_actor* father, const int& protection, const int& slot, const int& penalty);
		~c_armor() { }
		const int& getProtection() { return protection; }
		const int& getSlot() { return slot; }
		const int& getPenalty() { return penalty; }
};

#endif