#ifndef c_winSidebar_hpp
#define c_winSidebar_hpp

class c_winSidebar : public c_window
{
//	private:
//		c_winSlot* slot[9];

	public:
		c_winSidebar(const int& x, const int& y, const int& width, const int&height);
		~c_winSidebar() { }
		int update(int key);
        void draw();
};

#endif