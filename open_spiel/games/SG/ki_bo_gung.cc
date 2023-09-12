#include "open_spiel/games/SG/ki_bo_gung.h"


namespace open_spiel {
namespace  kbg {
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

// GAME !!!!!!!!!!!
kbgGame::kbgGame(const GameParameters& params)
    : Game(kGameType, params) {

      // 배틀쉽에 따르면 여기서 게임에 필요한 것들 설정한다.
}

std::string BattleshipGame::ActionToString(Player player,
                                           Action action_id) const {
  SPIEL_DCHECK_TRUE(player == Player{0} || player == Player{1});

  const absl::variant<CellAndDirection, Shot> action =
      DeserializeAction(action_id);

  if (absl::holds_alternative<Shot>(action)) {
    const Shot& shot = absl::get<Shot>(action);
    return absl::StrCat("Pl", player, ": shoot at (", shot.row, ", ", shot.col,
                        ")");
  } else {
    SPIEL_DCHECK_TRUE(absl::holds_alternative<CellAndDirection>(action));
    const CellAndDirection& cell_and_dir = absl::get<CellAndDirection>(action);
    absl::string_view direction_str;
    if (cell_and_dir.direction == CellAndDirection::Direction::Horizontal) {
      direction_str = "horizontally";
    } else {
      SPIEL_DCHECK_EQ(cell_and_dir.direction,
                      CellAndDirection::Direction::Vertical);
      direction_str = "vertically";
    }

    return absl::StrCat("Pl", player, ": place ship ", direction_str,
                        " with top-left corner in (",
                        cell_and_dir.TopLeftCorner().row, ", ",
                        cell_and_dir.TopLeftCorner().col, ")");
  }
}


} // namespace






} // kbg
} // open_spiel