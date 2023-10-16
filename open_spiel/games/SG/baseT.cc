#include "open_spiel/games/SG/baseT.h"
#include "open_spiel/spiel_utils.h"

namespace open_spiel
{
  namespace baseT
  {
    namespace
    {

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
          /*parameter_specification=*/{} // no parameters 비어있는 파람
      };

      std::shared_ptr<const Game> Factory(const GameParameters &params)
      {
        return std::shared_ptr<const Game>(new baseTGame(params));
      }

      REGISTER_SPIEL_GAME(kGameType, Factory);

      RegisterSingleTensorObserver single_tensor(kGameType.short_name);

    } // namespace

    // GAME !!!!!!!!!!!
    baseTGame::baseTGame(const GameParameters &params)
        : Game(kGameType, params)
    {

      // 배틀쉽에 따르면 여기서 게임에 필요한 것들 설정한다.
    }

    baseTGame::baseTGame(const GameType &game_type, const GameParameters &game_parameters)
        : Game(game_type, game_parameters)
    {
    }

    baseTGame::~baseTGame()
    {
    }

    std::vector<int> baseTGame::InformationStateTensorShape() const
    {
      // TODO
      return {0};
    }

    int baseTGame::MaxChanceOutcomes() const
    {
      // TODO
      return 0;
    }

    int baseTGame::MaxGameLength() const
    {
      // TODO
      return 0;
    }

    double baseTGame::MaxUtility() const
    {
      // TODO
      return 0.0;
    }

    double baseTGame::MinUtility() const
    {
      // TODO
      return 0.0;
    }

    std::unique_ptr<State> baseTGame::NewInitialState() const
    {
      // TODO
      return std::unique_ptr<State>(new baseTState(shared_from_this()));
    }

    int baseTGame::NumDistinctActions() const
    {
      // TODO
      return 0;
    }

    std::vector<int> baseTGame::ObservationTensorShape() const
    {
      // TODO
      return {0};
    }

    int baseTGame::NumPlayers() const
    {
      // TODO
      return 2;
    }

    absl::optional<double> baseTGame::UtilitySum() const
    {
      // TODO
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
      // TODO
      return Player{0};
    }

    bool baseTState::IsTerminal() const
    {
      // TODO
      return 0;
    }

    std::vector<Action> baseTState::LegalActions() const
    {
      // TODO
      return {0};
    }

    std::vector<double> baseTState::Returns() const
    {
      // TODO
      return {0.0};
    }

    std::string baseTState::ToString() const
    {
      // TODO
      return std::string("temp");
    }

    std::unique_ptr<State> baseTState::Clone() const
    {
      // TODO
      return nullptr;
    }

    void baseTState::DoApplyAction(Action action_id)
    {
      // TODO
    }

    void baseTState::init_map()
    {
      // TODO
    }

    void baseTState::init_unit()
    {
      // TODO
    }

    void baseTState::init_first(int p_num)
    {
      // 플레이어 수 만큼 아이디 카운트용 벡터에 0으로 채운다.
      unit_id_count.assign(p_num, 0);

      // 플레이서 수 만큼 현상태의 유닛 벡터에 빈 유닛벡터 채운다.
      std::vector<Unit> empty_units_v;
      map_state_now.units_v.assign(p_num, empty_units_v);

      // 재계산 해야 하는 셀 초기화
      std::vector<P_Cell> empty_pcell_v;
      need_recalc_v.assign(p_num, empty_pcell_v);
    }

    // player p 가 바라보는 셀의 정보에 따른 스트링
    std::string baseTState::get_cell_observation_string(MapState s, MapCoord crd, PlayerN p) const
    {
      std::string cell_observed = "";

      // 땅 속성을 그린다.
      switch (s.cells_v[crd.z][crd.y][crd.x].ground_type)
      {
      case GT_Normal:
        cell_observed += "_";
        break;
      case GT_CannotEnter:
        cell_observed += "X";
        break;
      default:
        cell_observed += "E";
      }

      if (s.cells_v[crd.z][crd.y][crd.x].being_observed_by[p])  // p 에 의해 관찰되는 중
      {
        if (s.cells_v[crd.z][crd.y][crd.x].occupying_player != -1) // 차지된 셀이면
        {
          cell_observed += std::to_string(s.cells_v[crd.z][crd.y][crd.x].occupying_player);
          cell_observed += std::to_string(s.cells_v[crd.z][crd.y][crd.x].occupying_unit_id);
        }
      } 
      else  // 관찰 안되는 중
      {
        cell_observed += "?";
      }

      // 빈자리 채우기
      if (max_units < 10)   //GPI = 3문자
      {
        cell_observed.insert(cell_observed.cend(), (3 - cell_observed.length()), ' ');
      } else if (max_units < 100)
      {
        cell_observed.insert(cell_observed.cend(), (4 - cell_observed.length()), ' ');
      }


      return cell_observed;
    }


    std::string baseTState::ObservationString(Player player) const
    {
      std::cout << "ObservationString() P:" << player << std::endl;
      std::string board_string = "BoardString\n";

      // 1. print ground if not occupied
      // 2. print unit if occupied
      for (int z = 0; z < map_size.z; z++)
      {
        for (int y = 0; y < map_size.y; y++)
        {
          for (int x = 0; x < map_size.x; x++)
          {
            board_string += get_cell_observation_string(map_state_now, {z,y,x}, P0);
          } // x
          board_string += "\n";
        } // y
        board_string += "\n";
      } // z

      return board_string;
    }

    int baseTState::action_mv(PlayerN pn, int unit_id, MapCoord tg_crd, UnitDirection tg_drc)
    {
      Unit& mine = map_state_now.units_v[pn][unit_id];
      if (map_state_now.cells_v[tg_crd.z][tg_crd.y][tg_crd.x].occupying_player == PNone) {//비어있음
        if (map_state_now.cells_v[tg_crd.z][tg_crd.y][tg_crd.x].ground_type != GT_CannotEnter) { // 이동가능한 곳 
          //이동시킨다.
          // 1. 현재 유닛이 위치한 셀 정보 수정 
          map_state_now.cells_v[mine.crd.z][mine.crd.y][mine.crd.x].occupying_player = PNone;
          map_state_now.cells_v[mine.crd.z][mine.crd.y][mine.crd.x].occupying_unit_id = -1;
          need_recalc_v[pn].push_back({pn, mine.crd});

        } else {  // 이동 불가능한 지형. Model 이 이것을 선택하는 것을 마스크 했어야 했다. 이것이 불리면 안됨. 
          get_set_error("GroundType is CannotEnter", true);
          return -1;
        }
      } else {// 누군가 차지 중 
        if (map_state_now.cells_v[tg_crd.z][tg_crd.y][tg_crd.x].occupying_player == pn) {// 자신이 차지 중 
          // 자신이 차지 중 임을 경고로 알린다. Model 이 이것을 선택하는 것을 마스크 했어야 했다. 이것이 불리면 안됨. 
          get_set_error("There is already an unit. Cannot move", true);
          return -1;
        } else {  // 적이 차지 중 
          if (map_state_now.cells_v[tg_crd.z][tg_crd.y][tg_crd.x].being_observed_by[pn]) {// 내가 관찰 중인 곳
            PlayerN p_enemy = map_state_now.cells_v[tg_crd.z][tg_crd.y][tg_crd.x].occupying_player;
            int uid_enemy = map_state_now.cells_v[tg_crd.z][tg_crd.y][tg_crd.x].occupying_unit_id;
            if (map_state_now.units_v[p_enemy][uid_enemy].being_observed) { // 맵&적이 보이는 중  
              // 적이 있으니 이동 못 한다고 알려야 함. Model 이 이것을 선택하는 것을 마스크 했어야 했다. 이것이 불리면 안됨. 
              get_set_error("There is already an enemy. Cannot move", true);
              return -1;
            } else {  // 적이 안보이는 중. 스텔스 기능 가진 유닛. 나중에 구현  
              // TODO. 나중에 언젠가 구현. 이동하다가 바로 앞에서 적을 발견하는 기능 구현 해야 한다. 
            }

          } else {// 내가 관찰 아닌 곳. 적이 있는데 맵이 안보이고 적도 안보이는 상황.
            // 맵에 안보이는 곳. 이동 명령 내리면 이동하다가 바로 앞에서 적을 발견하는 기능 구현 해야 한다.
            // TODO
          }
        }
      }



      //2. 맵 관찰지역을 수정한다.
      //   2-1. pn 의 관찰 중 지역만 다 지우고 
      //   2-2. pn 유닛들 돌면서 새롭게 관찰지역 만든다.

      return 0;
    }

    std::string get_set_error(std::string log, bool is_save)
    {
      static std::string last_log;
      if (is_save) {
        last_log = log;
      } else {
        return last_log;
      }
    }

  } // baseT
} // open_spiel