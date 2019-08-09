
#ifndef c_winDeath_hpp
#define c_winDeath_hpp

class c_winDeath : public c_window {
	
	public:
		c_winDeath(const int& x, const int& y, const int& width, const int& height);
		~c_winDeath () { }
        void draw();
};

#endif