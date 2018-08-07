#ifndef c_winMessage_hpp
#define c_winMessage_hpp

class c_winMessage
{
	private:
		int width;
		int height;

	public:
		c_winMessage(const int& width, const int& height);
		~c_winMessage();
        draw();
};

#endif