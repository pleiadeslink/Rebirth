#ifndef c_winMap_hpp
#define c_winMap_hpp

class c_winMap
{
	private:
		int x;
		int y;
		int xOffset;
		int yOffset;
		int tileWidth;
		int tileHeight;

	public:
		c_winMap(const int& x, const int& y, const int& tileWidth, const int& tileHeight);
		int update(int key, const int& mapX0, const int& mapY0, sf::Vector2i mousePos);
        void draw(const int& mapX0, const int& mapY0);
};

#endif