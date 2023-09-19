#ifndef OPEN_SPIEL_GAMES_SG_BASETYPE_H_
#define OPEN_SPIEL_GAMES_SG_BASETYPE_H_

#include "open_spiel/spiel.h"

namespace open_spiel {
namespace baseT {

enum GroundType {Normal = 0, };

class cell {
    GroundType ground_type;
    bool is_occupied;
    int unit_id;
}



#endif // OPEN_SPIEL_GAMES_SG_BASETYPE_H_