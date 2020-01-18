#ifndef c_body_hpp
#define c_body_hpp
class c_actor;

/// @brief This actor component provides a physical vessel inside the game world
class c_body
{
	private:
		/// @brief Pointer to the parent object
		c_actor* father;

		/// @brief If true, other actors can move to the same tile as the current actor
        bool canMove;

		/// @brief If true, other actors can see through the current actor
        bool canView;

		/// @brief If true, the actor can be picked up in the inventory
        bool canPickup;

		/// @brief Value representing the physical mass of the actor's body
        int weight;
    
	public:
		/// @brief The constructor initializes all component internal values
		/// @param father Pointer to the parent object
		/// @param canMove If true, other actors can move to the same tile as the current actor
		/// @param canView If true, other actors can see through the current actor
		/// @param canPickup If true, the actor can be picked up in the inventory
		/// @param weight Value representing the physical mass of the actor's body
		c_body(c_actor* father, const bool& canMove, const bool& canView, const bool& canPickup, const int& weight);
		
		const bool& getCanMove() { return canMove; }
		const bool& getCanView() { return canView; }
		const bool& getCanPickup() { return canPickup; }
		const int& getMass() { return weight; }
		void setCanMove(const bool& value) { canMove = value; }
		void setCanView(const bool& value) { canView = value; }
};

#endif
