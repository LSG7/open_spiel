#include "open_spiel/games/SG/ki_bo_gung.h"
#include "open_spiel/spiel_utils.h"


namespace open_spiel {
namespace kbg {
namespace {
using namespace baseT;
// Facts about the game.
// spiel.h 참고
const GameType kGameType{
    /*short_name=*/"kbg",
    /*long_name=*/"Ki Bo Gung",
    GameType::Dynamics::kSequential,
    GameType::ChanceMode::kDeterministic,
    GameType::Information::kImperfectInformation,
    GameType::Utility::kZeroSum,
    /* 종료시 보상 반환 */ GameType::RewardModel::kTerminal, 
    /*max_num_players=*/2,
    /*min_num_players=*/2,
    /*provides_information_state_string=*/true,
    /*provides_information_state_tensor=*/true,
    /*provides_observation_string=*/true,
    /*provides_observation_tensor=*/true,
    /*parameter_specification=*/{}  // no parameters 비어있는 파람 
};

std::shared_ptr<const Game> Factory(const GameParameters& params) {
  return std::shared_ptr<const Game>(new kbgGame(params));
}

REGISTER_SPIEL_GAME(kGameType, Factory);

RegisterSingleTensorObserver single_tensor(kGameType.short_name);

} //namespace

// GAME !!!!!!!!!!!
kbgGame::kbgGame(const GameParameters& params) : baseTGame(kGameType, params) 
{

      // 배틀쉽에 따르면 여기서 게임에 필요한 것들 설정한다.
}

kbgState::kbgState(std::shared_ptr<const Game> game) : baseTState(game)
{
  // 맵을 생성하고
  init_map();
  // 말을 생성하고 배치하고 
  init_unit();
}

/**
 * @brief 맵을 생성한다. 타일을 깔아야 한다.
*/
void kbgState::init_map()
{
  /* 10X10 맵에서 가운데에 1X4 호수가 있다.  */

  // 1. 맵 사이즈 결정 
  map_size.x = 10;
  map_size.y = 10;
  map_size.z = 1;

  // 2. 맵 만들기. 3차원 이므로 1차원부터 만들어서 삽입해야 한다. 
  // [z][row][col]
  Cell normal_ground = {GT_Normal, false, 0};
  std::vector<Cell> col_1d(map_size.x, normal_ground);
  std::vector<std::vector<Cell>> row_col_2d(map_size.y, col_1d);
  std::vector<std::vector<std::vector<Cell>>> z_row_col_3d(map_size.z, row_col_2d);
  Map_state.map_cells_v = z_row_col_3d;

  // 호수 만들기 
  Cell water_ground = {GT_CannotEnter, false, 0};
  map_state_now.map_cells_v[0][4][3] = water_ground;
  map_state_now.map_cells_v[0][4][4] = water_ground;
  map_state_now.map_cells_v[0][4][5] = water_ground;
  map_state_now.map_cells_v[0][4][6] = water_ground;
}

/**
* @brief 말을 생성하고 배치한다.
*/
void kbgState::init_unit()
{
  // kind ki:0 bo:1 gung:2
  int unit_id = 0;
  Map_coord unit_coord = {0,0,0};
  Map_coord unit_drction = {0,0,0};

  // 기병. 기종 0, 이거 2, 공거 2, 체 1, 공 1
  Unit ki(true, -1, 0, 2, 2, 1, 1, unit_coord, unit_drction, "ki");
  // 보병. 기종 1, 이거 1, 공거 1, 체 2, 공 1
  Unit bo(true, -1, 1, 1, 1, 2, 1, unit_coord, unit_drction, "bo");
  // 궁병. 기종 2, 이거 1, 공거 2, 체 1, 공 1 
  Unit gung(true, -1, 2, 1, 2, 1, 1, unit_coord, unit_drction, "gung");

   
  map_units.player0_units_v.push_back(ki);
  map_units.player0_units_v.push_back(bo);
  map_units.player0_units_v.push_back(bo);
  map_units.player0_units_v.push_back(gung);

  map_units.player1_units_v.push_back(ki);
  map_units.player1_units_v.push_back(bo);
  map_units.player1_units_v.push_back(bo);
  map_units.player1_units_v.push_back(gung);

  // unique id set
  for (int i = 0; i < map_units.player0_units_v.size(); i++) {
    map_units.player0_units_v[i].unit_id = unit_id;
    unit_id++;
  }

  // 아군과 적 유닛 아이디 구부
  unit_id += 1000;

  for (int i = 0; i < map_units.player1_units_v.size(); i++) {
    map_units.player1_units_v[i].unit_id = unit_id;
    unit_id++;
  }

}

} // kbg
} // open_spiel