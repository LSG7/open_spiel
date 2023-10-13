#include "open_spiel/games/SG/baseT.h"
#include "open_spiel/spiel_utils.h"

namespace open_spiel {
namespace baseT {
namespace {

// Facts about the game.
// spiel.h 참고
const GameType kGameType{
    /*short_name=*/"baseT",
    /*long_name=*/"baseT",
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
  return std::shared_ptr<const Game>(new baseTGame(params));
}

REGISTER_SPIEL_GAME(kGameType, Factory);

RegisterSingleTensorObserver single_tensor(kGameType.short_name);

} //namespace

// GAME !!!!!!!!!!!
baseTGame::baseTGame(const GameParameters& params)
    : Game(kGameType, params) {

      // 배틀쉽에 따르면 여기서 게임에 필요한 것들 설정한다.
}

baseTGame::baseTGame(const GameType& game_type, const GameParameters& game_parameters)
: Game(game_type, game_parameters)
{

}

baseTGame::~baseTGame()
{

}

std::vector<int> baseTGame::InformationStateTensorShape() const
{
  //TODO
  return {0};
}

int baseTGame::MaxChanceOutcomes() const
{
  //TODO
  return 0;
}

int baseTGame::MaxGameLength() const
{
  //TODO
  return 0;
}

double baseTGame::MaxUtility() const
{
  //TODO
  return 0.0;
}

double baseTGame::MinUtility() const
{
  //TODO
  return 0.0;
}

std::unique_ptr<State> baseTGame::NewInitialState() const
{
  //TODO
   return std::unique_ptr<State>(new baseTState(shared_from_this()));
}

int baseTGame::NumDistinctActions() const
{
  //TODO
  return 0;
}

std::vector<int> baseTGame::ObservationTensorShape() const
{
  //TODO
  return {0};
}

 int baseTGame::NumPlayers() const
 {
  //TODO
  return 2;
 }

 absl::optional<double> baseTGame::UtilitySum() const
 {
  //TODO
  return 0.0;

 }

/* GAME END */

/* STATE START */

baseTState::baseTState(std::shared_ptr<const Game> game) : State(game)
{

}

baseTState::~baseTState()
{
  
}

std::string baseTState::ActionToString(Player player, Action action_id) const
{
  return std::string("temp");
}

Player baseTState::CurrentPlayer() const
{
  //TODO
  return Player{0};
}

bool baseTState::IsTerminal() const
{
  //TODO
  return 0;
}

std::vector<Action> baseTState::LegalActions() const
{
  //TODO
  return {0};
}

std::vector<double> baseTState::Returns() const
{
  //TODO
  return {0.0};
}

std::string baseTState::ToString() const
{
  //TODO
  return std::string("temp");
}

std::unique_ptr<State> baseTState::Clone() const
{
  //TODO
  return nullptr;
}

void baseTState::DoApplyAction(Action action_id)
{
  //TODO
}

void baseTState::init_map()
{
  //TODO
}

void baseTState::init_unit()
{
  //TODO
}

void baseTState::init_first(int p_num)
{
  // 플레이어 수 만큼 아이디 카운트용 벡터에 0으로 채운다.
  unit_id_count.assign(p_num, 0);

  // 플레이서 수 만큼 현상태의 유닛 벡터에 빈 유닛벡터 채운다.
  std::vector<Unit> empty_units_v;
  map_state_now.units_v.assign(p_num, empty_units_v);
}

static std::string get_unit_id_string(PlayerN p, int int_unit_id, int max_us)
{
  std::string string_id;
  int string_id_length = 0;

  if (max_us < 10) {
    string_id_length = 2;
  } else if (max_us < 100) {
    string_id_length = 3;
  }

  string_id += std::to_string(p);

  string_id += std::to_string(int_unit_id);

  // 자리수 마추기 
  int diff_len = string_id_length - string_id.length();
  if (diff_len == 0) {
  } else if (diff_len == 1) {
    string_id += " ";
  } else if (diff_len == 2) {
    string_id += "  ";
  }

  return string_id;
}

static std::string get_ground_string(GroundType gt, int max_us)
{
  std::string g_string = "";

  switch (gt) {
    case GT_Normal:
      g_string += "_";
      break;
    case GT_CannotEnter:
      g_string += "X";
      break;
    default:
      g_string += "E";
  }

  if (max_us < 10) {
    g_string += " ";  // one space
  } else if (max_us < 100) {
    g_string += "  "; // two space
  }

  return g_string;
}

std::string baseTState::ObservationString(Player player) const
{
  std::cout << "ObservationString()" << std::endl;
  std::string board_string = "BoardString\n";

  // 1. print ground if not occupied
  // 2. print unit if occupied
  for (int z = 0; z < map_size.z; z++) {
    for (int y = 0; y < map_size.y; y++) {
      for (int x = 0; x < map_size.x; x++) {
        if (map_state_now.cells_v[z][y][x].is_occupied) {
          // player0,1 구분해서 그린다.
          board_string += get_unit_id_string(map_state_now.cells_v[z][y][x].occupying_player,
          map_state_now.cells_v[z][y][x].occupying_unit_id, max_units);
        } else {
          // 그라운드 종류에 따라 그린다. 
          board_string += get_ground_string(map_state_now.cells_v[z][y][x].ground_type, max_units);
        }
      }//x
      board_string += "\n";
    }//y
    board_string += "\n";
  }//z

  return board_string;
}

void baseTState::set_unit(PlayerN pn, UnitClass cs, Unit base_unit, MapCoord crd, UnitDirection drc)
{
  base_unit.unit_class = cs;
  base_unit.player = pn;
  base_unit.coord = crd;
  base_unit.direction = drc;

  base_unit.unit_id = unit_id_count[pn]++;
  map_state_now.units_v[pn].push_back(base_unit);
  
  map_state_now.cells_v[crd.z][crd.y][crd.x].is_occupied = true;
  map_state_now.cells_v[crd.z][crd.y][crd.x].occupying_player = pn;
  map_state_now.cells_v[crd.z][crd.y][crd.x].occupying_unit_id = base_unit.unit_id;

}

} // baseT
} // open_spiel