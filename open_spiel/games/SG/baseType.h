#ifndef OPEN_SPIEL_GAMES_SG_BASETYPE_H_
#define OPEN_SPIEL_GAMES_SG_BASETYPE_H_

#include "open_spiel/spiel.h"

namespace open_spiel {
namespace baseT {

enum GroundType {GT_Normal = 0, GT_CannotEnter = 1, };

struct Map_coord {
    int x; int y; int z;
};
struct Cell {
    GroundType ground_type;
    bool is_occupied;
    int occupying_unit_id;
    Map_coord coord;
};

struct Unit {
    bool is_alive;
    int unit_id;
    int unit_kind;
    int shift_distance;
    int atk_range;
    float hp;
    float power;
    Map_coord coord;
    std::string name;
};

struct Map_units {
    std::vector<Unit> allies_units_v;
    std::vector<Unit> enemy_units_v;
};

struct Map_state {
    Map_units map_units;
    std::vector<std::vector<std::vector<Cell>>> map_cells_v;
};

} // baseT
} // open_spiel



#endif // OPEN_SPIEL_GAMES_SG_BASETYPE_H_