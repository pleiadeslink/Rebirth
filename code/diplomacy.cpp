c_diplomacy::c_diplomacy() {
    for(int i = 0; i < 16; ++i) {
        for(int j = 0; j < 16; ++j) {
            a_diplomacy[i][j] = diplomacy::neutral;
        }
    }
    a_diplomacy[faction::avatar][faction::avatar] = diplomacy::friendly;
    a_diplomacy[faction::avatar][faction::animal] = diplomacy::hostile;
    a_diplomacy[faction::avatar][faction::citizen] = diplomacy::friendly;
    a_diplomacy[faction::animal][faction::avatar] = diplomacy::hostile;
    a_diplomacy[faction::animal][faction::animal] = diplomacy::friendly;
    a_diplomacy[faction::animal][faction::citizen] = diplomacy::hostile;
    a_diplomacy[faction::citizen][faction::avatar] = diplomacy::friendly;
    a_diplomacy[faction::citizen][faction::animal] = diplomacy::neutral;
    a_diplomacy[faction::citizen][faction::citizen] = diplomacy::friendly;
}

const int& c_diplomacy::getStance(const int& emitterFaction, const int& targetFaction) {
    return a_diplomacy[emitterFaction][targetFaction];
}