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

// IMPORTANT !!!!!!!!!!!!!!!!!!!!
// bfloat_16 will be supported from c++23. Use GCC(>=13).
// GCC13 is still in test branch on May 2024.
// FP16 Macro
#ifdef __linux__
  #ifdef __clang__ // Ubuntu clang
    #define FP16 _Float16 // clang not support bfloat16 yet
  #elif __GNUC__ // Ubuntu gcc
    #if (__GNUC__ > 13) || (__GNUC__ == 13)
      #include <stdfloat> // UBUNTU gcc-13.
      #define FP16 std::bfloat16_t
    #endif
  #endif
#elif __APPLE__
  #ifdef __clang__ // Mac clang
    #define FP16 _Float16
  #elif __GNUC__ // Mac gcc
    #define FP16 _Float16
  #endif
#endif


#include "open_spiel/spiel.h"
#include "baseType.h"
#include "user_specified_type.h"
#include "socket_server.h"

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
  virtual void set_next_unit_to_action();
  void deploy_unit(int player_id,bool is_alive,int shift_dstc,int atk_dstc,
    int vw_dstc,float hp,float power,UnitClass unit_class,
    MapCoord crd, std::string name);
  
  UnitActionState CurrentUAS() const;
  PlayerActionState CurrentPAS() const;
  int CurrentUniqueUnitId() const;
  int CurrentUnitId() const;
  void SetNextUAS();
  void SetNextPAS();
  void SetNextPlayer();
  void ObservationTensorBaseT(Player player);

 protected:
  virtual void DoApplyAction(Action move) override;

  virtual int action_mv(int pn, int unit_id, MapCoord tg_crd, bool is_init);
  virtual void scout(int pn, int unit_id, ObsRefCount o_r_c);  // unit 주변 셀들을 관찰한다.
  virtual void init_first
  (int max_u, int piece_tn, int last_mn, int supply_n, int land_channel_d, UnitSelectionOrder uso, MapCoord ms);

  virtual std::string get_cell_observation_string(MapState state, MapCoord crd, int p) const;
  virtual std::string get_set_error(std::string log, bool is_save);
  virtual MapCoord id_to_crd(Action a);
  virtual Action crd_to_id(MapCoord crd);
  int ObservationTensorBaseT_Land(Player player, int last_index);
  virtual void set_next_unit_to_action_rand_all_p(); // 모든 플레이어의 유닛에서 다음행동 유닛 뽑기
  virtual void set_next_unit_to_action_rand_per_p(); // 특정 플레이어에게서 다음행동 유닛 랜덤뽑기
  Unit& get_unit_by_uniqueId(int unique_id);
  virtual void ObservationTensor(Player player, absl::Span<float> values) const;
  void set_cells_and_obs(struct Cell_set_flags flags, struct Cell cell, struct MapCoord crd,
                        int player_n, int8_t ref_c);
  
  void cells_to_obs();
  int is_watched_by_others(Player player, std::vector<int8_t>& being_observed_by);

  MapCoord map_size;
  MapState msn; //map state now
  std::vector<MapState> Map_history;
  int max_units; // max number of one player
  std::vector<int8_t> unit_id_count;  // per player count
  int unique_unit_id_count;
  std::vector<std::vector<int8_t>> turn_unit_per_p_v; // 플레이어 별 유닛 순서
  std::vector<int8_t> turn_unit_all_p_v; // 모든 플레이어의 유닛 순서
  PlayerActionState current_pas;
  UnitSelectionOrder unit_selection_order;
  int ground_type_num;

  // Observation info
  int land_info_channel_depth;
  int piece_type_n;
  std::vector<std::vector<std::vector<std::vector<std::vector<int8_t>>>>> obs_per_p_v; //z,y,x,c
  int obs_total_channel_depth;
  int last_move_len;
  std::vector<FP16> supply_v;
  std::vector<P_UnitId> unique_id_to_player_id_v;

  // ipc
   std::unique_ptr<SocketServer> ipc_server;
  
 private:
  void init_cells();
  void init_obs();
  virtual void init_map();
  virtual void init_unit();
  virtual void init_server();
 /********** 각 게임 별 전용 ***********/
  

};

} // baseT
} // open_spiel

#endif // OPEN_SPIEL_GAMES_SG_BASET_H_