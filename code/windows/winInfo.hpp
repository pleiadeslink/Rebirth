#ifndef c_winInfo_hpp
#define c_winInfo_hpp

class c_winInfo : public c_window {
	
	private:
		int originalX;
		int originalY;
		bool f_prevMain; // Informs if previous window was main or not

	public:
		c_winInfo(const int& x, const int& y, const int& width, const int& height);
		~c_winInfo() { }
        void draw(const bool& mainView);
};

#endif