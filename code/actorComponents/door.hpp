#ifndef c_door_hpp
#define c_door_hpp
class c_actor;

/// @brief This actor component defines doors and allow them to be either opened or closed
class c_door {
	private:
		/// @brief A pointer to the actor's main object
		c_actor* father;
        
		/// @brief Doors can be either opened or closed
		bool open;
	public:
		c_door(c_actor* father);
		~c_door() { }

		/// @brief Changes door's state
		void toggleOpen();

		const bool& getOpen() { return open; }
		void setOpen(const bool& open) { this -> open = open; } 
};
#endif