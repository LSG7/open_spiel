#include "open_spiel/games/SG/ki_bo_gung.h"
#include "open_spiel/spiel_utils.h"

namespace open_spiel {
namespace kbg {
namespace {

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
kbgGame::kbgGame(const GameParameters& params)
    : Game(kGameType, params) {

      // 배틀쉽에 따르면 여기서 게임에 필요한 것들 설정한다.
}

kbgState::kbgState(std::shared_ptr<const Game> game) : State(game)
{

}

kbgState::init_field()
{
  
}

} // kbg
} // open_spiel