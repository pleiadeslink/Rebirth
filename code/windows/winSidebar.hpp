#ifndef c_winSidebar_hpp
#define c_winSidebar_hpp

#define MAXTARGET 35
#define MAXITEMTARGET 17

class c_winTarget;

class c_winSidebar : public c_window
{
	private:
		c_winButton** m_tileButtons;
		c_winButton** m_actorButtons;
		c_winTarget* m_target;
		int tileButtonWidth;
		int tileButtonHeight;
		int actorButtonWidth;
		int actorButtonHeight;
		int creatureCounter;
		int itemCounter;

	public:
		c_winSidebar(const int& x, const int& y, const int& width, const int&height);
		~c_winSidebar() { }
		void init();
		int update(int key, sf::Vector2i mousePos);
        void draw();
};

#endif