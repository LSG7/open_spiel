#ifndef OPEN_SPIEL_GAMES_SG_BASET_H_
#define OPEN_SPIEL_GAMES_SG_BASET_H_

/**
* @file baseT.h
* @brief 아무것도 구현 안되어있는 템플릿 용 
*
* @author SG Lee
* @date 8/30/2023
*/

// STD headers

// internal headers
#include "open_spiel/spiel.h"
#include "baseType.h"

namespace open_spiel {
namespace baseT {

class baseTGame : public Game {
 public:
  explicit baseTGame(const GameParameters& params);
  explicit baseTGame(const GameType& game_type, const GameParameters& game_parameters);
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

class baseTState : public State {

  /*****  모든 게임 공용 *****/
 public:
  baseTState(std::shared_ptr<const Game> game);
  baseTState(const baseTState&) = default;
  baseTState& operator=(const baseTState&) = default;
  std::string ActionToString(Player player, Action action_id) const override;
  Player CurrentPlayer() const override;
  bool IsTerminal() const override;
  std::vector<Action> LegalActions() const override;
  std::vector<double> Returns() const;

  std::string ToString() const override;
  std::unique_ptr<State> Clone() const override;
  std::string ObservationString(Player player) const override;

 protected:
  void DoApplyAction(Action move) override;

  virtual void init_map();
  virtual void init_unit();
  
  Map_coord map_size;
  Map_state map_state_now; 
  std::vector<Map_state> Map_history;
  int max_units; // max number of one player
  
 private:

 /********** 각 게임 별 전용 ***********/
  

};

} // baseT
} // open_spiel

#endif // OPEN_SPIEL_GAMES_SG_BASET_H_