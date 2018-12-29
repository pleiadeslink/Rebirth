#ifndef c_winSidebar_hpp
#define c_winSidebar_hpp

class c_winSidebar : public c_window
{
	private:
		c_winButton** m_tileButtons;
		//c_winButton** m_tileButtons;
		int tileButtonWidth;
		int tileButtonHeight;

	public:
		c_winSidebar(const int& x, const int& y, const int& width, const int&height);
		~c_winSidebar() { }
		void init();
		int update(int key, sf::Vector2i mousePos);
        void draw();
};

#endif