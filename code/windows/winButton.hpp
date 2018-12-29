#ifndef c_winButton_hpp
#define c_winButton_hpp

class c_winButton
{
	private:
		int x;
		int y;
		int width;
		int height;
		int type;
		std::string id;
		bool selected;

	public:
		c_winButton();
		void init(const int& x, const int& y, const int& width, const int& height, const int& type);
		int update(int key, sf::Vector2i mousePos);
        void draw();
        void setId(std::string id) { this -> id = id; }
};

#endif