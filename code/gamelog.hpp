#ifndef c_gamelog_hpp
#define c_gamelog_hpp

typedef struct s_message {
    std::string str; // Regular string 
    std::string cstr; // Color-coded string
};

class c_gamelog {

    private:
        std::vector<s_message> v_gamelog;
        s_message currentMessage;
        bool newMessage;
        int x;
		int y;
		int width;
		int height;
		int scroll;
		std::string text;
        s_message getLastMessage(const int& position);

    public:  
        c_gamelog();
        void update();
        void message(std::string str);
        void clear();
        void draw();
};

#endif