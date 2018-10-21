#ifndef c_helper_hpp
#define c_helper_hpp

class c_helper {

	public:
		static void test() { std::cout << "test" << std::endl; }
		static std::vector<std::string> split(const std::string& s, char delimiter);
		static const int& random(const int& min, const int& max);
		static void gameMessage(const std::string& text);

		// Map
		static void changeMap(const int& direction, const int& mapX, const int& mapY);
		static void worldMap(const int& mapX, const int& mapY);
		static const int& calculateDistance(const int& x1, const int& y1, const int& x2, const int& y2);
		static const int& getMapSeed();
		static const int& getMapWidth();
		static const int& getMapHeight();
		static const int& getMapX();
		static const int& getMapY();
		static const int& genClear(const int& value);
		static const int& setGenFloor1(std::string value);
		static const int& setGenFloor2(std::string value);
		static const int& setGenFloor3(std::string value);
		static const int& setGenWall1(std::string value);
		static const int& setGenWall2(std::string value);
		static const int& setGenWall3(std::string value);
		static const int& build();
		static void saveMap();

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
		static const int& getDirectionToActor(const int& emitter, const int& target);

		static std::string getActorId(const int& actor); // Returns the actor's id
		static std::string getName(const int& actor); // Returns the actor's name
		static std::string getPlayerName(); // Returns the actor's name
		static const int& getPlayer(); // Returns the player actor uid
		static const bool& isPlayer(const int& actor); // Check if the actor is the player
		static const int& getActorMapX(const int& actor); // Returns the actor's map Y
		static const int& getActorMapY(const int& actor); // Returns the actor's map X
		static const int& getHealth(const int& actor); // Returns the actor's health
		static const int& getConstitution(const int& actor); // Returns the actor's constitution
		static const int& getMaxHealth(const int& actor); // Returns the actor's max health
		static const int& getViewRange(const int& actor); // Returns the actor's view range
		static const int& getMinMeleeDamage(const int& actor);
		static const int& getMaxMeleeDamage(const int& actor);
		static const int& getMeleeDamage(const int& actor); // How much damage does the actor deal?
		static void restoreHealth(const int& actor, const int& points); // Restore 
		
		static void damage(const int& actor, const int& value);
		static void kill(const int& actor);
		static void openCloseDoor(const int& emitter, const int& door);
		static const bool& getItemFromFloor(const int& emitter, const int& target);
		static void consume(const int& emitter, const int& target);
		static const int& findStaircase(const int& x, const int& y); // Returns direction if found
		static const bool& equipItem(const int& emitter, const int& item);
		static const bool& removeItem(const int& emitter, const int& item);
		static void give(std::string item);
};

#endif