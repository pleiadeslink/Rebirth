#ifndef c_AI_hpp
#define c_AI_hpp

class c_AI
{
	private:
        c_actor* father;
        
	public:
        c_AI(c_actor* father);
        bool think();
};

#endif
