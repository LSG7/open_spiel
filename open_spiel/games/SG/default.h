#ifndef OPEN_SPIEL_GAMES_KI_BO_GUNG_H_
#define OPEN_SPIEL_GAMES_KI_BO_GUNG_H_

/**
* @file default.h
* @brief 아무것도 구현 안되어있는 템플릿 용 

*
* @author SG Lee
* @date 8/30/2023
*/

// STD headers

// internal headers
#include "open_spiel/spiel.h"

namespace open_spiel {
namespace default {

class defaultState : public State {
 public:
  defaultState(std::shared_ptr<const Game> game);
  defaultState(const defaultState&) = default;
  defaultState& operator=(const defaultState&) = default;
  std::string ActionToString(Player player, Action action_id) const override;
  Player CurrentPlayer() const override;
  bool IsTerminal() const override;
  std::vector<Action> LegalActions() const override;
  std::vector<double> Returns() const;

  std::string ToString() const override;
  std::unique_ptr<State> Clone() const override;

 protected:
  void DoApplyAction(Action move) override;

 private:

};


class defaultGame : public Game {
 public:
  explicit defaultGame(const GameParameters& params);
  std::vector<int> InformationStateTensorShape() const override;
  int MaxChanceOutcomes() const override;
  int MaxGameLength() const override;
  double MaxUtility() const override;
  double MinUtility() const override;
  std::unique_ptr<State> NewInitialState() const override;
  int NumDistinctActions() const override;
  std::vector<int> ObservationTensorShape() const override;
  int NumPlayers() const override;
  absl::optional<double> UtilitySum() const override;
};

} // default
} // open_spiel

#endif // OPEN_SPIEL_GAMES_KI_BO_GUNG_H_