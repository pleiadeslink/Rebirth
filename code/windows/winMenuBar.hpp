#ifndef c_winMenuBar_hpp
#define c_winMenuBar_hpp

#define PDNAM 2
#define PDQUA 30
#define PDTYP 39
#define PDDAM 52
#define PDPRO 66
#define PDWGT 81

#define PDTIM 30
#define PDENE 50

class c_winMenuBar : public c_window
{
    private:
        std::string text;
        int actor;
        int quantity;
        std::string ability;
        bool selected;

	public:
		c_winMenuBar() { }
        void init(const int& x, const int& y, const int& width, const int& height);
		const int& update(int key, const bool& s); // Updates text and checks for player input
        void draw();
        void clear();
        void setActor(const int& uid, const int& q);
        void setAbility(std::string ab);
};

#endif