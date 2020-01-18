#ifndef c_diplomacy_hpp
#define c_diplomacy_hpp

/// @brief This actor component provides information about the diplomacy relations between actors
class c_diplomacy {
    private:
        /// @brief Stores a diplomacy stance for each faction (size should be equal to number of factions)
        int a_diplomacy[16][16];

    public:
        /// @brief Set all diplomacy relations to neutral by default
        c_diplomacy();

        /// @brief Returns the diplomacy stance between two factions
        /// @brief param emitterFaction The emitter's faction ID
        /// @brief param targetFaction The target's faction ID
        const int& getStance(const int& emitterFaction, const int& targetFaction);
};
#endif