class c_actor;

// GENERAL

typedef struct structEventData {
    structEventData():emitter(0),target(0),type("none"),mapX(0),mapY(0),value1(0),string1("") { }
    void setEmitter(const int& val) { emitter = val; }
    void setTarget(const int& val) { target = val; }
    void setType(std::string val) { type = val; }
    void setMapX(const int& val) { mapX = val; }
    void setMapY(const int& val) { mapY = val; }
    void setValue1(const int& val) { value1 = val; }
    void setString1(std::string str) { string1 = str; }
    int emitter;
    int target;
    std::string type;
    int mapX;
    int mapY;
    int value1;
    std::string string1;
};

typedef struct s_coordinates {
    int x;
    int y;
};

typedef struct s_map {
    double tile[MAPSIZE][MAPSIZE];
};

typedef struct structFOVMap {
    bool val[global::maxFOVRange][global::maxFOVRange];
};


// MAP

typedef struct s_worldTile {
    int biome; 
    int danger;
};


// ASSET

typedef struct structTextureAsset {
    std::string id;
    sf::Texture* data;
};

typedef struct s_effect {
    std::string script;
    int value1;
    std::string string1;
};

typedef struct structActorAsset {
    std::string id;
    int type;
    std::string name;
    std::string plural;
    std::string description;
    std::string texture;
    std::string playerTex;
    bool tall;
    int tx;
    int ty;
    sf::Color color;
    int mass;
    bool canMove;
    bool canView;
    bool canGet;
    int direction;
    int wType;
    int wCategory;
    int health;
    int minDamage;
    int maxDamage;
    int speed;
    int attack;
    int defense;
    int protection;
    int block;
    int parry;
    int exp;
    //int protection;
    int slot;
    int penalty;
    int faction;
    s_effect effect[4];
    bool f_noshadow;
};


// Used to random populate a room
typedef struct s_herdAsset {
    std::string id;
    std::string actor[15];
    int chance[15];
};

typedef struct s_abilityAsset {
    std::string id;
    std::string name;
    std::string description;
    int duration;
    int energy;
};

typedef struct structTileAsset {
    std::string id;
    std::string name;
    std::string desc;
    int type;
    int tx;
    int ty;
    sf::Color color;
    sf::Color bgcolor;
    sf::Color olcolor;
    int script;
};

typedef struct s_genTile {
    std::string tile;
    std::string actor;
    bool flag;
};

typedef struct structMapAsset {
    std::string name;
    int width;
    int height;
};

typedef struct s_gamelogMessage {
    std::string message;
    bool old;
};

typedef struct structVerbAsset {
    std::string id;
    std::string name;
    int duration;
};

typedef struct structEntryAsset {
    std::string text;
    std::string isActor;
};

typedef struct structTopicAsset {
    std::string name;
    std::vector<structEntryAsset> v_entry;
};

typedef struct s_invItem {
    int uid;
    int quantity;
    bool equipped;
};

typedef struct s_script {
    int uid;
    std::string command;
    bool autodelete;
};

/* /typedef struct s_gameMessage {
    std::string text;
    int type;
};*/