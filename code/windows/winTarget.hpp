#ifndef c_winTarget_hpp
#define c_winTarget_hpp

class c_winTarget : public c_window
{
    private:
        int actor;

	public:
		c_winTarget() {}
        void init(const int& x, const int& y, const int& width, const int& height);
		const int& update(int key);
        void draw();
        void clear();
        void setActor(const int& uid);
};

#endif