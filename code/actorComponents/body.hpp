#ifndef c_body_hpp
#define c_body_hpp

class c_actor;

class c_body
{
	private:
		c_actor* father;
        bool canMove;
        bool canView;
        bool canPickup;
        int weight;
    
	public:
		c_body(c_actor* father, const bool& canMove, const bool& canView, const bool& canPickup, const int& weight);
		const bool& getCanMove() { return canMove; }
		const bool& getCanView() { return canView; }
		const bool& getCanPickup() { return canPickup; }
		const int& getMass() { return weight; }
		void setCanMove(const bool& value) { canMove = value; }
		void setCanView(const bool& value) { canView = value; }
};

#endif
