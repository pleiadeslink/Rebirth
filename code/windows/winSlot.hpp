#ifndef c_winSlot_hpp
#define c_winSlot_hpp

class c_winSlot : public c_window
{
	private:
		int item;
		int itemQuantity;
		bool itemEquipped;

	public:
		c_winSlot(const int& x, const int& y, const int& width, const int&height);
		int update(int key);
        void draw();
        void drawOverlay();
        void clear();
        void setItem(const int& uid, const int& quantity, const bool& equipped);
};

#endif