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

void baseTState::init_field()
{
  //TODO
}



} // baseT
} // open_spiel