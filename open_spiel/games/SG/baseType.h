#ifndef OPEN_SPIEL_GAMES_SG_BASETYPE_H_
#define OPEN_SPIEL_GAMES_SG_BASETYPE_H_

#include "open_spiel/spiel.h"

namespace open_spiel {
namespace baseT {

enum GroundType {GT_Normal = 0, GT_CannotEnter = 1, GT_None = -1, };
enum UnitDirection {D_North = 0, D_West = 1, D_South = 2, D_East = 3, D_None = -1,};
enum PlayerN {P0 = 0, P1 = 1, P2 = 2, PNone = -1,};
enum UnitClass {C0 = 9, C1,C2,C3,C4,C5,C6,C7,C8,C9, CNone = -1,};

struct MapCoord {
    //z:floor y:row x:col
    int z; int y; int x;
};
struct Cell {
    GroundType ground_type;
    bool is_occupied;
    PlayerN occupying_player;
    int occupying_unit_id;
};

struct Unit {
    bool is_alive;
    int unit_id;
    int shift_distance;
    int atk_range;
    float hp;
    float power;
    UnitClass unit_class;
    PlayerN player;
    MapCoord coord;        // 현재 위치한 셀 
    UnitDirection direction;    // coord 주위 4방향 셀  가르킨다.
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