#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <string>
#include <cctype>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <functional>
#include <cmath>
#include <memory>
#include <cstdio>
#include <stdio.h>
#include <queue>
#include <regex>
#include <filesystem>
#include <time.h>
#include <iso646.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ftext.hpp"
#include "libtcod.hpp"
#include "kaguya/kaguya.hpp"
#include "fastNoise.hpp"
#include "worldgen.hpp"

#define IN_RECTANGLE(x,y,w,h) ((unsigned)(x) < (unsigned)(w) && (unsigned)(y) < (unsigned)(h))
#define SQRDIST(x1,y1,x2,y2) (((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2)))
#define MAPSIZE 128
#define MAXITERATIONS 2000

#ifndef NDEBUG
#define DBG(x) printf x
#else
#define DBG(x)
#endif

namespace global {
	const bool debug = true;
	const int maxFOVRange = 36;
	const int maxLight = 255;
	const int lightMult = 16;
	const int tileSize = 16;
	const int maxRounds = 10000;
};

#include "enum.hpp"
#include "datatype.hpp"
#include "screen.hpp"
#include "sound.hpp"
#include "interface.hpp"
#include "window.hpp"
#include "windows/winButton.hpp"
#include "windows/winInfo.hpp"
#include "windows/winMap.hpp"
#include "windows/winTalk.hpp"
#include "windows/winCharacter.hpp"
#include "windows/winSidebar.hpp"
#include "windows/winDeath.hpp"
#include "windows/winTarget.hpp"
#include "windows/winMenuBar.hpp"
#include "fire.hpp"
#include "actorComponents/action.hpp"
#include "actorComponents/player.hpp"
#include "actorComponents/AI.hpp"
#include "actorComponents/body.hpp"
#include "actorComponents/door.hpp"
#include "actorComponents/staircase.hpp"
#include "actorComponents/life.hpp"
#include "actorComponents/consumable.hpp"
#include "actorComponents/weapon.hpp"
#include "actorComponents/armor.hpp"
#include "actor.hpp"
#include "assetManager.hpp"
#include "tile.hpp"
#include "actorManager.hpp"
#include "gamelog.hpp"
#include "map.hpp"
#include "mapGen.hpp"
#include "game.hpp"
#include "helper.hpp"
#include "engine.hpp"

TCODNoise noise1d(1);
TCODNoise noise2d(2);
WorldGenerator worldGen;
c_engine* engine;

std::map<std::string, sf::Color> m_color;
sf::Color color(std::string str) {
	return m_color[str];
}

int main(int argc, char *argv[]) {
    engine = new c_engine();
    engine -> start();
    delete engine;
	return EXIT_SUCCESS;
}

#include "ftext.cpp"
#include "fastNoise.cpp"
#include "worldgen.cpp"
#include "screen.cpp"
#include "sound.cpp"
#include "interface.cpp"
#include "window.cpp"
#include "windows/winButton.cpp"
#include "windows/winInfo.cpp"
#include "windows/winMap.cpp"
#include "windows/winTalk.cpp"
#include "windows/winCharacter.cpp"
#include "windows/winSidebar.cpp"
#include "windows/winDeath.cpp"
#include "windows/winTarget.cpp"
#include "windows/winMenuBar.cpp"
#include "fire.cpp"
#include "actorComponents/action.cpp"
#include "actorComponents/player.cpp"
#include "actorComponents/AI.cpp"
#include "actorComponents/body.cpp"
#include "actorComponents/door.cpp"
#include "actorComponents/staircase.cpp"
#include "actorComponents/life.cpp"
#include "actorComponents/consumable.cpp"
#include "actorComponents/weapon.cpp"
#include "actorComponents/armor.cpp"
#include "actor.cpp"
#include "assetManager.cpp"
#include "tile.cpp"
#include "actorManager.cpp"
#include "helper.cpp"
#include "gamelog.cpp"
#include "map.cpp"
#include "mapGen.cpp"
#include "game.cpp"
#include "engine.cpp"