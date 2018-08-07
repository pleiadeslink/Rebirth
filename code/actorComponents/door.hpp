#ifndef c_door_hpp
#define c_door_hpp

class c_actor;

class c_door
{
	private:
		c_actor* father;
        bool closed;
    
	public:
		c_door(c_actor* father);
		~c_door() { }
		void toggleOpen();
		const bool& isClosed() { return closed; }
};

#endif