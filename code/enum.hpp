/// @brief Keyboard keys
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

/// @brief Actor categories
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

/// @brief Actor flags
namespace flag {
    enum flags {
        noshadow,
        passive
    };
}

/// @brief Actor factions, used by AI to establish enemies/allies
namespace faction {
    enum factions {
        avatar,
        animal,
        citizen
    };
}

/// @brief Diplomacy stances
namespace diplomacy {
    enum diplomacies {
        hostile,
        neutral,
        friendly
    };
}

/// @brief 8 cardinal directions + up/down + random
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

/// @brief Size categories
namespace size {
    enum sizes {
        tiny,
        small,
        medium,
        big,
        huge
    };
}

/// @brief Text alignment
namespace textAlign {
    enum textAligns {
        right,
        left,
        center,
        justify
    };
}

/// @brief Interface modes
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

/// @brief Interface edit modes
namespace emode {
    enum emodes {
        tile,
        actor,
        script
    };
}

/// @brief Screens for the main character menu
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

/// @brief Tile categories used in c_tile
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

/// @brief Button types by the interface's winButton element
namespace buttonType {
    enum buttonTypes {
        tile,
        actor
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

/// @brief Biome types for world map
///
/// Careful with altering this order, as literals are being used in walk.lua
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

/// @brief Weapon types used by the actor's c_weapon component
namespace weaponType {
    enum weaponTypes {
        none,
        oneHanded,
        twoHanded,
        ranged
    };
}

/// @brief Weapon categories used by the actor's c_weapon component
namespace weaponCategory {
    enum weaponCategories {
        none,
        sword,
        axe,
        bow
    };
}

/// @brief Weapon categories used by the actor's c_armor component
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