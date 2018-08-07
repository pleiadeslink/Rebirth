#ifndef c_gamelog_hpp
#define c_gamelog_hpp

class c_gamelog {

    private:
        std::vector<std::string> v_gamelog;
        std::string currentMessage;
        bool newMessage;

    public:  
        c_gamelog() { }
        void update();
        void message(std::string str);
        std::string getLastMessage(const int& position);
        void clear();
};

#endif