#ifndef c_engine_hpp
#define c_engine_hpp

class c_engine {
    private:
        std::vector<std::string> v_messageLog;
        std::string command;
        std::vector<std::string> commandHistory;
        int commandIndex;
        bool commandPrompt;
        bool f_quit;
        
	public:
        c_screen screen;
        c_interface interface;
        c_assetManager assetManager;
        c_game* game;
        
        //c_keyboard keyboard;
        
        c_engine();
        ~c_engine();
        void start();
        int input();
        sf::Vector2i getMouse() { return sf::Mouse::getPosition(*screen.getWindow()); }
        void quit();
		void message(std::string message);
        static void runScript(const std::string& path);
        static void runScript(const std::string& path, const structEventData& data);
        std::string getCommand() { return command; }
};

#endif