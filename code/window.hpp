#ifndef c_window_hpp
#define c_window_hpp

//class c_label;
//class c_button;
//class c_slot;
//class c_item;

class c_window
{
    protected:
    	std::string id;
    	int x;
    	int y;
    	int width;
    	int height;
        //std::vector<std::shared_ptr<c_winItem>> v_item;
	    //std::vector<c_label*> v_label;
	    //std::vector<c_button*> v_button;
	    //std::vector<c_slot*> v_slot;
        void drawFrame();
        void drawHBar(const int& hpos);
        void drawVLine(const int& x, const int& y, const int& size);
        void drawTitle(const std::string text, const int& hpos);

    public:
        c_window() {}
        c_window(const std::string& id, const int& x, const int& y, const int& width, const int&height);
        void update();
        void draw();
        static void drawFrame(const int& x, const int& y, const int& width, const int& height);
        void addLabel(const int& x, const int& y, const std::string text);
        int getX() { return x; }
        int getY() { return y; }
};

#endif