#ifndef c_player_hpp
#define c_player_hpp

class c_player
{
	private:
        c_actor* father;
        int key;
        bool god;
        
	public:
        c_player(c_actor* father);
        bool channel(const int& key, const bool& worldMap); // Follows human input
        void setKey(const int& key) { this -> key = key; }
        const bool& toggleGodMode() { if(god == true) god = false; else god = true; return god; }
        const bool& isGod() { return god; }
};

#endif
