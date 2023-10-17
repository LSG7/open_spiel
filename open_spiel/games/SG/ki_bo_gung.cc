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
    /*max_num_ps=*/2,
    /*min_num_ps=*/2,
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

kbgGame::~kbgGame()
{

}

kbgState::kbgState(std::shared_ptr<const Game> game) : baseTState(game)
{
  player_num = 2;
  
  //무조건 맨 처음에 불러줘야 함
  init_first(player_num);

  // 맵을 생성하고
  init_map();
  // 말을 생성하고 배치하고 
  init_unit();
}

kbgState::~kbgState()
{

}

std::unique_ptr<State> kbgGame::NewInitialState() const
{
  return std::unique_ptr<State>(new kbgState(shared_from_this()));
}


// 1번 구현 함수 
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

  // 비어있는 관찰자 벡터
  std::vector<bool> obp(player_num, false);

  // 2. 맵 만들기. 3차원 이므로 1차원부터 만들어서 삽입해야 한다. 
  // [z][row][col]
  Cell normal_ground = {GT_Normal, PNone, -1, obp};
  std::vector<Cell> col_1d(map_size.x, normal_ground);
  std::vector<std::vector<Cell>> row_col_2d(map_size.y, col_1d);
  std::vector<std::vector<std::vector<Cell>>> z_row_col_3d(map_size.z, row_col_2d);
  map_state_now.cells_v = z_row_col_3d;

  // 호수 만들기 
  Cell water_ground = {GT_CannotEnter, PNone, -1, obp};
  map_state_now.cells_v[0][4][3] = water_ground;
  map_state_now.cells_v[0][4][4] = water_ground;
  map_state_now.cells_v[0][4][5] = water_ground;
  map_state_now.cells_v[0][4][6] = water_ground;
}

// 2번 구현 함수  
/**
* @brief 말을 생성하고 배치한다.
*/
void kbgState::init_unit()
{
  max_units = 4;
  std::vector<bool> empty_v(player_num, false);
  // kind ki:0 bo:1 gung:2s

  // live. id -1, 이거 2, 공거 1, 시야 4, 체 1, 공 1, class 0, p 0, crd , drc, pb, name
  struct Unit ki = {true, -1, 2, 1, 4, 1, 1, CNone, PNone, {0,0,0}, D_None, empty_v, "ki"};
  // live. id -1, 이거 1, 공거 1, 시야 4, 체 2, 공 1
  struct Unit bo = {true, -1, 1, 1, 4, 2, 1, CNone, PNone, {0,0,0}, D_None, empty_v,"bo"};
  // live. id -1, 이거 1, 공거 2, 시야 4, 체 1, 공 1 
  struct Unit gung = {true, -1, 1, 2, 4, 1, 1, CNone, PNone, {0,0,0}, D_None, empty_v,"gung"};

  //P0 units
  map_state_now.units_v[P0].push_back({true, unit_id_count[P0]++, 2, 2, 1, 1, C0, P0, false, {0,8,5}, D_North, "ki"});
  action_mv(P0, unit_id_count-1, {0,8,5}, D_North);
  map_state_now.units_v[P0].push_back({true, unit_id_count[P0]++, 1, 1, 2, 1, C1, P0, false, {0,8,4}, D_North, "bo"});
  action_mv(P0, unit_id_count-1, {0,8,4}, D_North);
  map_state_now.units_v[P0].push_back({true, unit_id_count[P0]++, 1, 1, 2, 1, C1, P0, false, {0,8,3}, D_North, "bo"});
  action_mv(P0, unit_id_count-1, {0,8,3}, D_North);
  map_state_now.units_v[P0].push_back({true, unit_id_count[P0]++, 1, 1, 2, 1, C2, P0, false, {0,9,4}, D_North, "gu"});
  action_mv(P0, unit_id_count-1, {0,9,4}, D_North);

  //P1 units
  map_state_now.units_v[P1].push_back({true, unit_id_count[P1]++, 2, 2, 1, 1, C0, P1, false, {0,1,5}, D_South, "ki"});
  action_mv(P1, unit_id_count-1, {0,1,5}, D_South);
  map_state_now.units_v[P1].push_back({true, unit_id_count[P1]++, 1, 1, 2, 1, C1, P1, false, {0,1,4}, D_South, "bo"});
  action_mv(P1, unit_id_count-1, {0,1,4}, D_South);
  map_state_now.units_v[P1].push_back({true, unit_id_count[P1]++, 1, 1, 2, 1, C1, P1, false, {0,1,3}, D_South, "bo"});
  action_mv(P1, unit_id_count-1, {0,1,3}, D_South);
  map_state_now.units_v[P1].push_back({true, unit_id_count[P1]++, 1, 1, 2, 1, C2, P1, false, {0,0,4}, D_South, "gu"});
  action_mv(P1, unit_id_count-1, {0,0,4}, D_South);


}

} // kbg
} // open_spiel