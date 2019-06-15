#ifndef c_helper_hpp
#define c_helper_hpp

class c_helper {

	public:
		static void test() { std::cout << "test" << std::endl; }
		static std::vector<std::string> split(const std::string& s, char delimiter);
		static int random(const int& min, const int& max);
		static std::vector<std::string> splitter(std::string in_pattern, std::string& content); // Splits a string in lines by '\n'
		static std::string justify(std::string string, const size_t size);
		static void gameMessage(const std::string& text, const bool& unique = false);
		static void toggleFullScreen(); // Changes between window and fullscreen mode
		static void talk(const int& actor);

		// * Sound

		static void playAmbience(std::string track); // Plays a big audio file


		// * Map

		static void showMapInfo();
		static void loadMap(const int& x, const int& y, const int& z);
		static void saveMap(const bool& default = false); // Saves as default map if parameter is true
		static void changeMap(const int& x, const int& y, const int& z, int startX = 0, int startY = 0);
		static void worldMap(const int& mapX, const int& mapY);
		static const bool& isLocation(const int& x, const int& y); // Returns true if it finds a location actor in the tile
		static const bool& isWorldMap();
		static void resetMap();
		static void createMapScript(std::string command, const bool& autodelete);
		static const int& calculateDistance(const int& x1, const int& y1, const int& x2, const int& y2);
		static const int& getMapSeed();
		static const int& getMapWidth();
		static const int& getMapHeight();
		static const int& getMapX();
		static const int& getMapY();
		static const int& getMapZ();
		static const bool& findTileByName(const int& x, const int& y, std::string name); // Returns true if the tile in location has the same name as parameter
		static const int& genClear(const int& value);
		static const bool& genDigRoom(const int& x0, const int& y0, const int& width, const int& height, const int& direction, const bool& digStartingTile = false);
		static const bool& genDungeon(const int& value);
		static const bool& genCave();
		static const bool& genWild(const int& type);
		static const bool& genWorld();
		static const int& setGenFloor1(std::string value);
		static const int& setGenFloor2(std::string value);
		static const int& setGenFloor3(std::string value);
		static const int& setGenWall1(std::string value);
		static const int& setGenWall2(std::string value);
		static const int& setGenWall3(std::string value);
		static void setAmbience(std::string track);
		static const int& build();
		static void forgetMap();
		static void updateWorld(); // Updates world map from map 0.0.0 stored locally
		static int getBiome(const int& x, const int& y); // Returns the biome of the selected location of the world map
		static void genAddCellularPatch(std::string tile, const int& size); // Adds a patch of the specified tile using a cellular automata generated pattern
		static void genPlantTrees(std::string tree, const int& size, const bool& dead); // Plants trees randomly on grass tiles (if dead is true, there is a small chance every round of a dead tree being plant in a dirt tile if found
		static void genPlaceActorSomewhere(std::string actor, const int& quantity); // Places actor in a free random position	
		

		// * Actor

		static const int& findActorByName(const int& x, const int&y, std::string name);
		static const bool& isObstacle(const int& x, const int& y);
		static const int& getCreatureFromTile(const int& x, const int& y);
		static const bool& actorTypeInTile(std::string type, const int& x, const int& y);
		static const int& getFirstActorInTile(const int& emitter, const int& x, const int& y);
		static void teleportActor(const int& actor, const int& x, const int& y, const bool& recalculateFOV = true);
		static const int& createActor(std::string id, const int& x, const int& y);
		static const int& tryToTalk(const int& x, const int& y);
		static void startAction(const structEventData& eventData);
		static const int& findEnemy(const int& actor);
		static const bool& isEnemy(const int& emitter, const int& target);
		static void showActorPosition(const int& actor); // Shows actor's coordinates in the game console
		static void showPlayerPosition(); // Shows player's coordinates in the game console
		static const int& getDirectionToActor(const int& emitter, const int& target);

		static std::string getActorId(const int& actor); // Returns the actor's id
		static std::string getName(const int& actor); // Returns the actor's name
		static std::string getPlayerName(); // Returns the actor's name
		static const int& getPlayer(); // Returns the player actor uid
		static const bool& isPlayer(const int& actor); // Check if the actor is the player
		static const int& getActorMapX(const int& actor); // Returns the actor's map Y
		static const int& getActorMapY(const int& actor); // Returns the actor's map X
		static const int& getConstitution(); // Returns avatar's constitution
		static const int& getAgility(); // Returns avatar's agility
		static const int& getSpirit(); // Returns avatar's spirit
		static const int& getLuck(); // Returns avatar's luck
		static const int& getHealth(const int& actor); // Returns the actor's health
		static const int& getMaxHealth(const int& actor); // Returns the actor's max health
		static const int& getMinDamage(const int& actor);
		static const int& getMaxDamage(const int& actor);
		static const int& getAccuracy(const int& actor);
		static const int& getDodge(const int& actor);
		static const int& getViewRange(const int& actor); // Returns the actor's view range

		static void setConstitution(const int& value); // Returns avatar's constitution
		static void setAgility(const int& value); // Returns avatar's agility
		static void setSpirit(const int& value); // Returns avatar's spirit
		static void setLuck(const int& value); // Returns avatar's luck
		static void setAttributes(const int& maxHealth, const int& minDamage, const int& maxDamage, const int& speed, const int& attackSpeed, const int& accuracy, const int& dodge, const int& parry);
		static void calculateAttributes();

		//static const int& getMinMeleeDamage(const int& actor);
		//static const int& getMaxMeleeDamage(const int& actor);
		//static const int& getMeleeDamage(const int& actor); // How much damage does the actor deal?
		static void restoreHealth(const int& actor, const int& points); // Restore 
		static void damage(const int& actor, const int& value);
		static void kill(const int& actor);
		static void openCloseDoor(const int& emitter, const int& door);
		static const bool& getItemFromFloor(const int& target);
		static const bool& dropItemFromInventory(const int& target);
		static void consume(const int& emitter, const int& target);
		static const int& findStaircase(const int& x, const int& y); // Returns direction if found
		static const bool& equipItem(const int& emitter, const int& item);
		static const bool& removeItem(const int& emitter, const int& item);
		static void give(std::string item);
		static void toggleGodMode();
		static const bool& isPlayerGod();
		static const bool& learn(std::string id); // Teaches the player a ability
};

#endif