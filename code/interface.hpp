#ifndef c_interface_hpp
#define c_interface_hpp

class c_tile;
class c_winMap;
class c_winGamelog;
class c_winSidebar;
class c_winCharacter;
class c_winInfo;
class c_winDeath;
//class c_winMessage;

/// @brief This object manages the interface windows; global input depends on the interface mode
class c_interface {

    private:

        /// @brief A pointer to the gamelog window
        c_winGamelog* gamelog;

        /// @brief A pointer to the character window
        c_winCharacter* character;

        /// @brief A pointer to the sidebar window
        c_winSidebar* sidebar;

        /// @brief A pointer to the map window
        c_winMap* map;

        /// @brief A pointer to the information window
        c_winInfo* info;

        /// @brief A pointer to the death window
        c_winDeath* death;

        /// @brief The interface mode affects what input is received and what windows are displayed
        int mode;

        /// @brief The editor interface mode, affects active editor element selection
        int emode; // Editor
        
        /// @brief X offset camera alignment value; allows to move the camera around
        int xOffset;
        
        /// @brief Y offset camera alignment value; allows to move the camera around
        int yOffset;
        
        bool f_help;
        c_tile* sTile;
        int sActor;
        std::string sAbility;
        c_tile* destination;
        std::string targetText;
        int targetType;
        std::string inputText;
        s_tileAsset* editTile;
        s_actorAsset* editActor;
        int editScript;
        int editRadius;
        bool pasteMode;
        int processInput(int key);

    public:

        /// @brief Set default values to variables
        c_interface();

        /// @brief Delete window objects before dying
        ~c_interface();

        /// @brief Creates the window objects using hardcoded values :/
        void init();

        /// @brief Reset selections, update windows and process input
        /// @param key The input key
        int update(int key);

        /// @brief Draw windows depending on the current interface mode
        void draw();

        /// @brief Draw mouse pointer
        void drawMouse();

        int getMode() { return mode; }
        void edit();
        void talk(const int& actor); // Opens a talk window in the interface with several dialogue options
        void selectTile(c_tile* tile) { sTile = tile; }
        void selectActor(const int& actor) { sActor = actor; }
        void selectAbility(std::string ability) { sAbility = ability; }
        void setTileDestination(c_tile* tile) { destination = tile; }
        void setEditTile(s_tileAsset* tile) { editTile = tile; }
        void setEditActor(s_actorAsset* actor) { editActor = actor; }
        void setEditScript(int script) { editScript = script; }
        void setMode(const int& value) { mode = value; }
        void setEmode(const int& value) { emode = value; }
        s_tileAsset* getEditTile() { return editTile; }
        s_actorAsset* getEditActor() { return editActor; }
        const int& getEditScript() { return editScript; }
        const int& selectCloseTarget(const int& prevMode, const std::string& targetText, const int& type = 0);
        void gameOver(); // Wait for enter key and deletes game
        //c_tile* selectTarget(const int& prevMode, const std::string& targetText);
        int getEmode() { return emode; }
        c_tile* getSelectedTile() { return sTile; }
        int getSelectedActor() { return sActor; }
        std::string getSelectedAbility() { return sAbility; }
        c_tile* getTileDestination() { return destination; }
        int getEditRadius() { return editRadius; }
        std::string getTargetText() { return targetText; }
        const bool& isHelpActivated() { return f_help; }
};

#endif