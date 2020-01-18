#ifndef c_AI_hpp
#define c_AI_hpp

/// @brief This actor component provides artificial intelligence to an actor
class c_AI {
    
    private:
        /// @brief A pointer to the actor's main object
        c_actor* father;

        /// @brief The faction the actor belongs to
        int faction;

        /// @brief Stores the target UID in memory
        int target;

    public:
        /// @brief Set all diplomacy relations to neutral by default
        c_AI(c_actor* father, const int& faction);

        /// @brief Launches a "think" event with the father as emitter
        const bool& think();

        const int& getFaction() { return faction; }
        const int& getTarget() { return target; }
        void setTarget(const int& uid) { target = uid; }
};
#endif