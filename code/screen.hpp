#ifndef c_screen_hpp
#define c_screen_hpp

class c_screen {
    
    private:
        int xRes;
        int yRes;
        bool fullScreen;
        sf::RenderWindow window;
        sf::Shader shader_water;
    
	public:
        c_screen();
        ~c_screen();
        void clear();
        void display();
        void start(bool fullscreen = false);
        void screenshot();

        void drawTile(const int& charX, const int& charY, const int& x, const int& y, const sf::Color color, const int& scale = 1);
        void drawTexture(const std::string& id, const int& x, const int& y, const sf::Uint8& light = 255);
        void drawLine(const int& x1, const int& y1, const int& x2, const int& y2);
        void drawBox(const int& x, const int& y, const int& width, const int& height, const sf::Color color);
        const int& drawText(std::string str, int x, const int& y, const sf::Color color, const int& align = 0, const int& width = 20, const int& size = 16);

        const int& getXRes() {return xRes; }
        const int& getYRes() {return yRes; }
        sf::RenderWindow* getWindow() { return &window; }
        const bool& isFullScreen() { return fullScreen; }
};

#endif