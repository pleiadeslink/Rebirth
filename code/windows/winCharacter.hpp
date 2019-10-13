#ifndef c_winCharacter_hpp
#define c_winCharacter_hpp

class c_winMenuBar;

#define MAXMENUBAR 17

class c_winCharacter : public c_window
{
	private:
		std::vector<s_invItem>* v_item;
		std::vector<std::string>* v_ability;
		c_winMenuBar* a_menuBar;
		int screen;
		int itemPos;
		int abilityPos;
		int conditionPos;
		int talentPos;
		int questPos;
		int systemPos;

	public:
		c_winCharacter(const int& x, const int& y, const int& width, const int& height);
		~c_winCharacter() {}
		void init();
		int update(int key);
        void draw();
};

#endif