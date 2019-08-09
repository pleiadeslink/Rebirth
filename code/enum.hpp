
namespace key {
    enum keys {
        none,
        a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
        num0, num1, num2, num3, num4, num5, num6, num7, num8, num9,
        f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,
        up,
        down,
        left,
        right,
        space,
        escape,
        lcontrol,
        tab,
        backspace,
        lclick,
        rclick,
        add,
        subtract,
        comma,
        period,
        enter
    };
}

namespace actorType {
    enum actorTypes {
        nothingness,
        avatar,
        creature,
        weapon,
        armor,
        food,
        potion,
        scroll,
        staircase,
        door,
        container,
        misc,
        trigger,
        location,
        tree
    };
}

namespace wildernessType {
    enum wildernessTypes {
        plains,
        forest,
        desert,
        beach_n,
        beach_s,
        beach_e,
        beach_w,
        beach_ne,
        beach_nw,
        beach_se,
        beach_sw
    };
}

namespace direction {
    enum directions {
        none,
        north,
        east,
        south,
        west,
        northeast,
        southeast,
        southwest,
        northwest,
        up,
        down,
        random
    };
}

namespace size {
    enum sizes {
        tiny,
        small,
        medium,
        big,
        huge
    };
}

namespace textAlign {
    enum textAligns {
        right,
        left,
        center,
        justify
    };
}

namespace imode {
    enum imodes {
        game,
        character,
        edit,
        selectCloseTarget,
        dialogue,
        gameOver
    };
}

namespace emode {
    enum emodes {
        tile,
        actor,
        script
    };
}

namespace charScreen {
    enum charScreens {
        inventory,
        abilities,
        condition,
        talents,
        quests,
        system
    };
}

namespace tileType {
    enum tileTypes {
        floor,
        wall,
        obstacle,
        water,
        deepWater,
        lava,
        world
    };
}

namespace mapType {
    enum mapTypes {
        cave,
        jungle,
        dungeon,
        hell
    };
}

namespace event {
    enum events {
        none, // 0
        walk, // 1
        attack, // 2
        damage, // 3
        death, // 4
        speak,
        eat,
        read,
        drink, // 5
        travel, // Only available in wilderness maps
        explore // Only available in world map
    };
}

namespace faction {
    enum factions {
        none,
        avatar,
        animal
    };
}

namespace buttonType {
    enum buttonTypes {
        tile,
        actor
    };
}

namespace shader {
    enum shaders {
        water
    };
}

namespace tile {
    enum tiles {
        thevoid,
		wallRock,
        floorGrass,
        floorGravel
    };
}

namespace genTile {
    enum genTiles {
        floor1,
        floor2,
        floor3,
        wall1,
        wall2,
        wall3,
        water,
        lava
    };
}

// ! Careful with altering this order, as literals are being used in walk.lua
namespace biome {
    enum biomes {
        grassland,
        location,
        mountain,
        temperateForest,
        taiga,
        jungle,
        desert,
        savanna,
        marsh,
        tundra,
        ocean
    };
}

namespace layer {
    enum layers {
        thebackest,
        background,
        tiles,
        fog,
        gamelog,
        healthbars
    };
}

namespace weaponType {
    enum weaponTypes {
        none,
        oneHanded,
        twoHanded,
        ranged
    };
}

namespace weaponCategory {
    enum weaponCategories {
        none,
        sword,
        axe,
        bow
    };
}

namespace bodySlot {
    enum bodySlot {
        head,
        torso,
        feet,
        hands,
        ring,
        mainHand,
        offHand
    };
}