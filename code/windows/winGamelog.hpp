#ifndef c_winGamelog_hpp
#define c_winGamelog_hpp

class c_winGamelog
{
	private:
		int x;
		int y;
		int width;
		int height;
		int scroll;

	public:
		c_winGamelog(const int& x, const int& y, const int& width, const int& height);
        void draw();

};

#endif