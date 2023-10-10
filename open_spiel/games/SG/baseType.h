#ifndef OPEN_SPIEL_GAMES_SG_BASETYPE_H_
#define OPEN_SPIEL_GAMES_SG_BASETYPE_H_

#include "open_spiel/spiel.h"

namespace open_spiel {
namespace baseT {

enum GroundType {GT_Normal = 0, GT_CannotEnter = 1, };

struct Map_coord {
    //z:floor y:row x:col
    int z; int y; int x;
};
struct Cell {
    GroundType ground_type;
    bool is_occupied;
    int occupying_unit_id;
    Map_coord coord_player0;
    Map_coord coord_player1;
};

struct Unit {
    bool is_alive;
    int unit_id;
    int unit_kind;
    int shift_distance;
    int atk_range;
    float hp;
    float power;
    Map_coord coord;        // 현재 위치한 셀 
    Map_coord direction;    // coord 주위 4방향 셀  가르킨다.
    std::string name;
};

struct Map_units {
    std::vector<Unit> p0_units_v;
    std::vector<Unit> p1_units_v;
};

struct Map_state {
    Map_units units;
    std::vector<std::vector<std::vector<Cell>>> cells_v;
};

} // baseT
} // open_spiel



#endif // OPEN_SPIEL_GAMES_SG_BASETYPE_H_