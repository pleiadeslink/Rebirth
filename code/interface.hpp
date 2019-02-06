#ifndef c_interface_hpp
#define c_interface_hpp

class c_tile;
class c_winMap;
class c_winGamelog;
class c_winSidebar;
class c_winCharacter;
class c_winInfo;
//class c_winMessage;

class c_interface {

    private:
        c_winGamelog* gamelog;
        c_winCharacter* character;
        c_winSidebar* sidebar;
        c_winMap* map;
        c_winInfo* info;
        int mode; // Game, character screen, etc.
        int emode; // Editor
        c_tile* sTile;
        int sActor;
        std::string sSkill;
        c_tile* destination;
        std::string targetText;
        std::string inputText;
        structTileAsset* editTile;
        structActorAsset* editActor;
        int editScript;
        int editRadius;
        bool pasteMode;
        int processInput(int key);

	public:
        c_interface();
        ~c_interface();
        void init();
        int update(int key);
        void draw();

        int getMode() { return mode; }
        void edit();
        void talk(const int& actor); // Opens a talk window in the interface with several dialogue options
        void selectTile(c_tile* tile) { sTile = tile; }
        void selectActor(const int& actor) { sActor = actor; }
        void selectSkill(std::string skill) { sSkill = skill; }
        void setTileDestination(c_tile* tile) { destination = tile; }
        void setEditTile(structTileAsset* tile) { editTile = tile; }
        void setEditActor(structActorAsset* actor) { editActor = actor; }
        void setEditScript(int script) { editScript = script; }
        void setMode(const int& value) { mode = value; }
        void setEmode(const int& value) { emode = value; }
        structTileAsset* getEditTile() { return editTile; }
        structActorAsset* getEditActor() { return editActor; }
        const int& getEditScript() { return editScript; }
        int selectCloseTarget(const int& prevMode, const std::string& targetText);
        //c_tile* selectTarget(const int& prevMode, const std::string& targetText);
        int getEmode() { return emode; }
        c_tile* getSelectedTile() { return sTile; }
        int getSelectedActor() { return sActor; }
        std::string getSelectedSkill() { return sSkill; }
        c_tile* getTileDestination() { return destination; }
        int getEditRadius() { return editRadius; }
        std::string getTargetText() { return targetText; }
};

#endif