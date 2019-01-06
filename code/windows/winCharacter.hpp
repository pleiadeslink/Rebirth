#ifndef c_winCharacter_hpp
#define c_winCharacter_hpp

class c_winCharacter : public c_window
{
	private:
		int screen;
		int inventoryPos;
		int skillsPos;
		int conditionPos;
		int talentsPos;
		int questsPos;
		int systemPos;
		std::vector<s_invItem>* inventory;
		std::vector<std::string>* v_skills;

	public:
		c_winCharacter(const int& x, const int& y, const int& width, const int&height);
		~c_winCharacter() { }
		int update(int key);
        void draw();
};

#endif