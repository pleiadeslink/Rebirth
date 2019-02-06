#ifndef c_winTalk_hpp
#define c_winTalk_hpp

class c_winTalk : public c_window
{
	private:
		int pos;

	public:
		c_winTalk(const int& x, const int& y, const int& width, const int& height);
		~c_winTalk() { }
		//void init();
		int update(int key);
        void draw();
};

#endif