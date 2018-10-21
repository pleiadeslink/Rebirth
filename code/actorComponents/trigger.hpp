#ifndef c_trigger_hpp
#define c_trigger_hpp

class c_actor;

class c_trigger
{
	private:
		c_actor* father;
        std::string command;
        bool autodelete;
    
	public:
		c_trigger(c_actor* father);
		~c_trigger() { }
		void set(std::string command, const bool& autodelete);
		void activate();
};

#endif