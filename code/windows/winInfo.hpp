#ifndef c_winInfo_hpp
#define c_winInfo_hpp

class c_winInfo : public c_window
{
	public:
		c_winInfo(const int& x, const int& y, const int& width, const int&height);
		~c_winInfo() { }
        void draw();
};

#endif