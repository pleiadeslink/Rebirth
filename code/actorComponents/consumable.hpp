#ifndef c_consumable_hpp
#define c_consumable_hpp

class c_actor;

class c_consumable
{
	private:
		c_actor* father;
		//int action;
        s_effect effect[4];
    
	public:
		//c_consumable(c_actor* father, const int& action, s_effect effect0, s_effect effect1, s_effect effect2, s_effect effect3);
		c_consumable(c_actor* father, s_effect effect0, s_effect effect1, s_effect effect2, s_effect effect3);
		~c_consumable() { }
		void consume(const int& consumer);
		//const int& getAction() { return action; }
};

#endif