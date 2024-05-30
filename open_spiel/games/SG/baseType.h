#ifndef OPEN_SPIEL_GAMES_SG_BASETYPE_H_
#define OPEN_SPIEL_GAMES_SG_BASETYPE_H_

#include "open_spiel/spiel.h"

namespace open_spiel {
namespace baseT {

enum GroundType {GT_Normal = 0, GT_CannotEnter = 1, GT_None = -1, };
enum UnitDirection {D_North = 0, D_West = 1, D_South = 2, D_East = 3, D_None = -1,};
enum UnitClass {C0 = 0, C1,C2,C3,C4,C5,C6,C7,C8,C9, CNone = -1,};
enum ActionType {AMove = 0, AAttk, ANone = -1,};
enum ObsRefCount {ObsRefUp = 1, ObsRefDown = -1,};
enum PlayerActionState {PA_Obs = 0, PA_Think, PA_Action, PA_None = -1,};
enum UnitActionState {UA_Act_0 = 0, UA_attk=1, UA_None = -1,};
enum PlayerN {PNone = -1,};
enum UnitN {UNone = -1,};
enum UnitSelectionOrder {USO_ALL_P_RAND=0,USO_PER_P_RAND=1,USO_None=-1,};

struct MapCoord {
    //z:floor y:row x:col
    int z; int y; int x;
};

struct P_UnitId {
    int unique_id;
    int player_id;
    int player_unit_id;
};

struct P_Cell {
    int pn;
    MapCoord crd;
};

struct Cell {
    GroundType ground_type;
    int occupying_player;
    int8_t occupying_unit_id; 
    std::vector<int8_t> being_observed_by; // 이 셀을 관찰 중인 플레이어별 ref_count P0 : being_observed_by[0] 
};

class Unit {
public:
    bool is_alive;
    int unit_id;    // per player
    int unique_unit_id; // unique in game
    int shift_dstc;
    int atk_dstc;
    int vw_dstc;
    float hp;
    float power;
    UnitClass unit_class;
    int player;
    MapCoord crd;        // 현재 위치한 셀 
    std::vector<int8_t> being_observed_by; // Cell 의 being_observed_by 와 같다. 스텔스 기능 추가 전까지는 같아야 한다.
    std::string name;

    Unit(int player,bool is_alive,int unit_id,int unique_unit_id,int shift_dstc,int atk_dstc, int vw_dstc,float hp,float power,UnitClass unit_class,
    MapCoord crd, std::vector<int8_t> being_observed_by, std::string name)
    {
        this->is_alive = is_alive;
        this->unit_id = unit_id;
        this->unique_unit_id = unique_unit_id;
        this->shift_dstc = shift_dstc;
        this->atk_dstc = atk_dstc;
        this->vw_dstc = vw_dstc;
        this->hp = hp;
        this->power = power;
        this->unit_class = unit_class;
        this->player = player;
        this->crd = crd;        // 현재 위치한 셀 
        this->being_observed_by = being_observed_by;
        this->name = name;
    };

    virtual ~Unit(){};
};

struct MapState {
    std::vector<std::vector<Unit>> units_v; // P0:units_v[0]
    std::vector<std::vector<std::vector<Cell>>> cells_v;

    int current_player;
    int current_unique_unit_id;
    UnitActionState current_uas;
};

} // baseT
} // open_spiel



#endif // OPEN_SPIEL_GAMES_SG_BASETYPE_H_