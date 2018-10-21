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
        period
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
        trigger
    };
}

namespace direction {
    enum directions {
        none,
        north,
        northeast,
        east,
        southeast,
        south,
        southwest,
        west,
        northwest,
        up,
        down
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
        dialogue
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
        skills,
        talents,
        questlog
    };
}

namespace tileType {
    enum tileTypes {
        floor,
        wall,
        obstacle,
        water,
        deepWater,
        lava
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
        talk,
        eat,
        read,
        drink // 5
    };
}

namespace faction {
    enum factions {
        none,
        avatar,
        animal
    };
}

namespace screen {
    enum screens {
        game,
        worldmap
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

namespace tileScript {
    enum tileScripts {
        none,
        travelNorth,
        travelSouth,
        travelEast,
        travelWest,
        travelUp,
        travelDown
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