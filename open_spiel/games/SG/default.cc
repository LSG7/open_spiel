#include "open_spiel/games/SG/default.h"
#include "open_spiel/spiel_utils.h"

namespace open_spiel {
namespace default {
namespace {

// Facts about the game.
// spiel.h 참고
const GameType kGameType{
    /*short_name=*/"default",
    /*long_name=*/"default",
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
  return std::shared_ptr<const Game>(new defaultGame(params));
}

REGISTER_SPIEL_GAME(kGameType, Factory);

RegisterSingleTensorObserver single_tensor(kGameType.short_name);

} //namespace

// GAME !!!!!!!!!!!
defaultGame::defaultGame(const GameParameters& params)
    : Game(kGameType, params) {

      // 배틀쉽에 따르면 여기서 게임에 필요한 것들 설정한다.
}

std::vector<int> defaultGame::InformationStateTensorShape() const
{
  //TODO
  return {0};
}

int defaultGame::MaxChanceOutcomes() const
{
  //TODO
  return 0;
}

int defaultGame::MaxGameLength() const
{
  //TODO
  return 0;
}

double defaultGame::MaxUtility() const
{
  //TODO
  return 0.0;
}

double defaultGame::MinUtility() const
{
  //TODO
  return 0.0;
}

std::unique_ptr<State> defaultGame::NewInitialState() const
{
  //TODO
   return std::unique_ptr<State>(new defaultState(shared_from_this()));
}

int defaultGame::NumDistinctActions() const
{
  //TODO
  return 0;
}

std::vector<int> defaultGame::ObservationTensorShape() const
{
  //TODO
  return {0};
}

 int defaultGame::NumPlayers() const
 {
  //TODO
  return 2;
 }

 absl::optional<double> defaultGame::UtilitySum() const
 {
  //TODO
  return 0.0;

 }

/* GAME END */

/* STATE START */

defaultState::defaultState(std::shared_ptr<const Game> game) : State(game)
{

}

std::string defaultState::ActionToString(Player player, Action action_id) const
{
  return std::string("temp");
}

Player defaultState::CurrentPlayer() const
{
  //TODO
  return Player{0};
}

bool defaultState::IsTerminal() const
{
  //TODO
  return 0;
}

std::vector<Action> defaultState::LegalActions() const
{
  //TODO
  return {0};
}

std::vector<double> defaultState::Returns() const
{
  //TODO
  return {0.0};
}

std::string defaultState::ToString() const
{
  //TODO
  return std::string("temp");
}

std::unique_ptr<State> defaultState::Clone() const
{
  //TODO
  return nullptr;
}

void defaultState::DoApplyAction(Action action_id)
{
  //TODO
}


} // default
} // open_spiel