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
  virtual ~baseTGame();
  virtual std::vector<int> InformationStateTensorShape() const override;
  virtual int MaxChanceOutcomes() const override;
  virtual int MaxGameLength() const override;
  virtual double MaxUtility() const override;
  virtual double MinUtility() const override;
  virtual std::unique_ptr<State> NewInitialState() const override;
  virtual int NumDistinctActions() const override;
  virtual std::vector<int> ObservationTensorShape() const override;
  virtual int NumPlayers() const override;
  virtual absl::optional<double> UtilitySum() const override;
};

class baseTState : public State {

  /*****  모든 게임 공용 *****/
 public:
  baseTState(std::shared_ptr<const Game> game);
  baseTState(const baseTState&) = default;
  virtual ~baseTState();
  virtual baseTState& operator=(const baseTState&) = default;
  virtual std::string ActionToString(Player player, Action action_id) const override;
  virtual Player CurrentPlayer() const override;
  virtual bool IsTerminal() const override;
  virtual std::vector<Action> LegalActions() const override;
  virtual std::vector<double> Returns() const;
  virtual std::string ToString() const override;
  virtual std::unique_ptr<State> Clone() const override;
  virtual std::string ObservationString(Player player) const override;

 protected:
  virtual void DoApplyAction(Action move) override;
  virtual void set_unit(PlayerN pn, UnitClass cs, Unit base_unit, MapCoord crd, UnitDirection drc);

  virtual void init_first(int p_num);
  virtual void init_map();
  virtual void init_unit();
  
  MapCoord map_size;
  Map_state map_state_now; 
  std::vector<Map_state> Map_history;
  int max_units; // max number of one player
  int player_num = 0;
  std::vector<int> unit_id_count;
  
  
 private:

 /********** 각 게임 별 전용 ***********/
  

};

} // baseT
} // open_spiel

#endif // OPEN_SPIEL_GAMES_SG_BASET_H_