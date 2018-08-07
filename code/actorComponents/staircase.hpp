#ifndef c_staircase_hpp
#define c_staircase_hpp

class c_actor;

class c_staircase
{
	private:
		c_actor* father;
        int direction;
    
	public:
		c_staircase(c_actor* father, const int& direction);
		~c_staircase() { }
		const int& getDirection() { return direction; }
};

#endif