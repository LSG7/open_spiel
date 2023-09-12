#ifndef OPEN_SPIEL_GAMES_KI_BO_GUNG_H_
#define OPEN_SPIEL_GAMES_KI_BO_GUNG_H_

/**
* @file ki_bo_gung.h
* @brief [기병 보병 궁병] '3가지 병' 으로 '두 플레이어' 가 싸우는 'inperfect information' 'zero sum' 게임 이다.
* 보병은 (창+방패) 팔랑크스 보병
* 턴베이스, 턴당 [이동,행동], 기병-보병-궁병 순으로, 동일 말에서 적군과의 순서는 랜덤으로, 
*
* [데미지 공식]
* 기본으로 1 씩 데미지 주는 것으로 함.
* 공격 보너스 +1 : (보병 옆,뒤 <- 기병 돌격),
* 공격 패널티 -0.665 : (보병 <- 궁), (보병 전면 <- 기병 돌격)
* 반격 +1 : (보병 전면 <- 기병 돌격)
*
* [Policy Head]
* deepnash 에서는 3+1=4 개 인데 (deployment, piece-selection, piece-displacemnt, value)
* 기보궁 게임에서는 배치X, 선택X, 이동(행동)O, 가치O,
* 즉 이동, 가치 2개 헤드만 있으면 된다.
* 이동과 행동을 분리해야하나? deepnash 는 하나인데
*
* @author SG Lee
* @date 8/30/2023
*/

/* observation 
 [0] 지형 정보             row * col

*/

// STD headers

// internal headers
#include "open_spiel/spiel.h"

namespace open_spiel {
namespace kbg {

inline constexpr int kNumPlayers = 2;
inline constexpr int kNumRows = 10;
inline constexpr int kNumCols = 10;

//inline constexpr int kCellStates = TODO

inline constexpr int kFieldType = 3;  // 노멀, 숲, 장애물 
inline constexpr int kPieceType = 3;  // 기병, 보병, 궁수
inline constexpr int kNumCells = kNumRows * kNumCols;
inline constexpr int kCellStates = 1 + kNumPlayers;  // TODO 정해야함


// State of a cell.
enum class CellState {
  kEmpty,
  kNought,  // O
  kCross,   // X
};

class kbgState : public State {
 public:
  kbgState(std::shared_ptr<const Game> game);

  kbgState(const kbgState&) = default;
  kbgState& operator=(const kbgState&) = default;

  Player CurrentPlayer() const override {
    return IsTerminal() ? kTerminalPlayerId : current_player_;
  }
  std::string ActionToString(Player player, Action action_id) const override;
  std::string ToString() const override;
  bool IsTerminal() const override;
  std::vector<double> Returns() const override;
  std::string InformationStateString(Player player) const override;
  std::string ObservationString(Player player) const override;
  void ObservationTensor(Player player,
                         absl::Span<float> values) const override;
  std::unique_ptr<State> Clone() const override;
  void UndoAction(Player player, Action move) override;
  std::vector<Action> LegalActions() const override;
  CellState BoardAt(int cell) const { return board_[cell]; }
  CellState BoardAt(int row, int column) const {
    return board_[row * kNumCols + column];
  }
  Player outcome() const { return outcome_; }

  // Only used by Ultimate Tic-Tac-Toe.
  void SetCurrentPlayer(Player player) { current_player_ = player; }

 protected:
  std::array<CellState, kNumCells> board_;
  void DoApplyAction(Action move) override;

 private:
  bool HasLine(Player player) const;  // Does this player have a line?
  bool IsFull() const;                // Is the board full?
  Player current_player_ = 0;         // Player zero goes first
  Player outcome_ = kInvalidPlayer;
  int num_moves_ = 0;
};


class kbgGame : public Game {
 public:
  explicit kbgGame(const GameParameters& params);
  int NumDistinctActions() const override { return kNumCells; }
  std::unique_ptr<State> NewInitialState() const override {
    return std::unique_ptr<State>(new kbgState(shared_from_this()));
  }
  int NumPlayers() const override { return kNumPlayers; }
  double MinUtility() const override { return -1; }
  absl::optional<double> UtilitySum() const override { return 0; }
  double MaxUtility() const override { return 1; }
  std::vector<int> ObservationTensorShape() const override {
    return {kCellStates, kNumRows, kNumCols};
  }
  int MaxGameLength() const override { return kNumCells; }
  std::string ActionToString(Player player, Action action_id) const override;

  battlefield_width = 10;
  battlefield_heigt = 10;
};

} // kbg
} // open_spiel

#endif // OPEN_SPIEL_GAMES_KI_BO_GUNG_H_