#ifndef c_player_hpp
#define c_player_hpp

class c_player
{
	private:
        c_actor* father;
        int key;
        
	public:
        c_player(c_actor* father);
        bool channel(const int& key); // Follows human input
        void setKey(const int& key) { this -> key = key; }
};

#endif
