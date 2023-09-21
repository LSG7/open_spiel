#ifndef OPEN_SPIEL_GAMES_SG_BASETYPE_H_
#define OPEN_SPIEL_GAMES_SG_BASETYPE_H_

#include "open_spiel/spiel.h"

namespace open_spiel {
namespace baseT {

enum GroundType {Normal = 0, CannotEnter = 1, };

struct Map_size {
    int x; int y; int z;
};
struct Cell {
    GroundType ground_type;
    bool is_occupied;
    int occupied_unit_id;
};

struct Piece {
    bool is_alive;
    int unit_id;
    int shift_distance;
    float hp;
};

struct Map_pieces {
    std::vector<Piece> allies_pieces_v;
    std::vector<Piece> enemy_pieces_v;
};

struct Map_state {
    Map_pieces map_pieces;
    std::vector<std::vector<std::vector<Cell>>> map_cells_v;
};

} // baseT
} // open_spiel



#endif // OPEN_SPIEL_GAMES_SG_BASETYPE_H_