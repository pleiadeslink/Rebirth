#ifndef c_winCharacter_hpp
#define c_winCharacter_hpp

class c_winCharacter : public c_window
{
	private:
		int screen;
		int inventoryPos;
		int abilitiesPos;
		int conditionPos;
		int skillsPos;
		int talentsPos;
		int questlogPos;
		std::vector<s_invItem> inventory;

	public:
		c_winCharacter(const int& x, const int& y, const int& width, const int&height);
		~c_winCharacter() { }
		int update(int key);
        void draw();
};

#endif