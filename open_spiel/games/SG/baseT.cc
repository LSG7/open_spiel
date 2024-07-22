#include <cmath>
#include <omp.h>
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
      return msn.current_player;
    }

    UnitActionState baseTState::CurrentUAS() const
    {
      return msn.current_uas;
    }

    int baseTState::CurrentUniqueUnitId() const
    {
      return msn.current_unique_unit_id;
    }

    int baseTState::CurrentUnitId() const
    {
      return msn.current_player_unit_id;
    }
    PlayerActionState baseTState::CurrentPAS() const
    {
      return current_pas;
    }

    void baseTState::SetNextUAS()
    {
      switch (game_uak)
      {
      case UA_Kind_1step:
        SetNextUAS_1step();
        break;
      case UA_Kind_2step:
        SetNextUAS_2step();
        break;
      }
    }

    void baseTState::SetNextUAS_1step()
    {
      return;
    }

    void baseTState::SetNextUAS_2step()
    {
      switch (msn.current_uas)
      {
      case UA_Act_0:
        msn.current_uas = UA_attk;
        break;
      case UA_attk:
        msn.current_uas = UA_Act_0;
        break;
      case UA_None:
        break;
      }
    }
    void baseTState::SetNextPAS()
    {
      switch (current_pas)
      {
      case PA_Obs:
        current_pas = PA_Think;
        break;
      case PA_Think:
        current_pas = PA_Action;
        break;
      case PA_Action:
        current_pas = PA_Obs;
        break;
      case PA_None:
        break;
      }
    }
    void baseTState::SetNextPlayer()
    {
      msn.current_player++;

      if (msn.current_player == num_players_)
        msn.current_player = 0;
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

    MapCoord baseTState::id_to_crd(Action a)
    {
      MapCoord r;
      int xy = (map_size.x * map_size.y);
      r.z = a / xy;
      r.y = (a % xy) / map_size.x;
      r.x = (a % xy) % map_size.x;

      return r;
    }

    Action baseTState::crd_to_id(MapCoord crd)
    {
      int a = 0;
      a += crd.z * (map_size.x * map_size.y);
      a += crd.y * map_size.x;
      a += crd.x;

      return a;
    }

    void baseTState::set_next_unit_to_action()
    {
      switch (unit_selection_order)
      {
      case USO_ALL_P_RAND:
        set_next_unit_to_action_rand_all_p();
        break;
      case USO_PER_P_RAND:
        set_next_unit_to_action_rand_per_p();
        break;
      default:
        return;
      }

      return;
    }

    void baseTState::set_next_unit_to_action_rand_all_p()
    {
      if (turn_unit_all_p_v.size() == 0)
      {
        for (int i = 0; i < unique_unit_id_count + 1; i++)
        {
          if (get_unit_by_uniqueId(i).is_alive)
          { // unique_unit_id 에서 unit 객체에 접근할 방법 만들어야함
            turn_unit_all_p_v.push_back(i);
          }
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(turn_unit_all_p_v.begin(), turn_unit_all_p_v.end(), gen);
      }

      msn.current_unique_unit_id = turn_unit_all_p_v.back();
      turn_unit_all_p_v.pop_back();
      msn.current_player = get_unit_by_uniqueId(msn.current_unique_unit_id).player;
      msn.current_player_unit_id = get_unit_by_uniqueId(msn.current_unique_unit_id).unit_id;

      return;
    }

    void baseTState::set_next_unit_to_action_rand_per_p()
    {
      int p = CurrentPlayer();
      if (turn_unit_per_p_v[p].size() == 0)
      {
        #pragma omp parallel
        #pragma omp for
        for (int i = 0; i < max_units; i++)
        {
          if (msn.units_v[p][i].is_alive)
          {
            turn_unit_per_p_v[p].push_back(msn.units_v[p][i].unique_unit_id);
          }
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(turn_unit_per_p_v[p].begin(), turn_unit_per_p_v[p].end(), gen);
      }
      msn.current_unique_unit_id = turn_unit_per_p_v[p].back();
      turn_unit_per_p_v[p].pop_back();
      msn.current_player = get_unit_by_uniqueId(msn.current_unique_unit_id).player;
      msn.current_player_unit_id = get_unit_by_uniqueId(msn.current_unique_unit_id).unit_id;

      return;
    }

    Unit &baseTState::get_unit_by_uniqueId(int unique_id)
    {
      int player_id = unique_id_to_player_id_v[unique_id].player_id;
      int unit_id = unique_id_to_player_id_v[unique_id].player_unit_id;

      return msn.units_v[player_id][unit_id];
    }

    void baseTState::DoApplyAction(Action action_id)
    {
      // apply_action call this

      // STATE CHANGE WORK
    }

    void baseTState::init_map()
    {
      // TODO
    }

    void baseTState::init_unit()
    {
      // TODO
    }

    void baseTState::init_server()
    {
      ipc_server = std::make_unique<SocketServer>(7777);
      ipc_server->start();
    }

    void baseTState::init_first(int max_u, int piece_tn, int last_mn, int supply_n,
                                int land_channel_d, UnitSelectionOrder uso, MapCoord ms, UnitActionKind uak)
    {
      init_server();

      land_info_channel_depth = land_channel_d;
      max_units = max_u;
      piece_type_n = piece_tn;
      last_move_len = last_mn;
      unit_selection_order = uso;
      ground_type_num = sizeof(GroundType) - 1;
      game_uak = uak;

      // 1. 맵 사이즈 결정
      map_size.x = ms.x;
      map_size.y = ms.y;
      map_size.z = ms.z;

      // 플레이어 수 만큼 아이디 카운트용 벡터에 0으로 채운다.
      unit_id_count.assign(num_players_, UNone);
      // 게임에서 유일한 아이디를 유닛에 배정
      unique_unit_id_count = -1;

      // 플레이서 수 만큼 현상태의 유닛 벡터에 빈 유닛벡터 채운다.
      std::vector<Unit> empty_units_v;
      msn.units_v.assign(num_players_, empty_units_v);

      // 플레이어 수 만큼 턴 남은 유닛 셋 채운다.
      switch (unit_selection_order)
      {
      case USO_ALL_P_RAND:
      {
      }
      break;
      case USO_PER_P_RAND:
      {
        std::vector<int8_t> empty_id_v;
        turn_unit_per_p_v.assign(num_players_, empty_id_v);
        msn.current_player = 0;
      }
      break;
      }

      // P0 부터 시작

      msn.current_uas = UA_Act_0;
      current_pas = PA_Obs;

      init_cells();
      init_obs();
      cells_to_obs();

      // 보금품 남은 수
      supply_v.assign(num_players_, supply_n);

      // P_UnitId empty_id = {-1,-1,-1};
      // unique_id_to_player_id_v.assign(max_units*num_players_, empty_id);

      init_map();
      init_unit();
    }

    // player p 가 바라보는 셀의 정보에 따른 스트링
    std::string baseTState::get_cell_observation_string(MapState s, MapCoord crd, int p) const
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

      if (s.cells_v[crd.z][crd.y][crd.x].being_observed_by[p]) // p 에 의해 관찰되는 중
      {
        if (s.cells_v[crd.z][crd.y][crd.x].occupying_player != PNone) // 차지된 셀이면
        {
          cell_observed += std::to_string(s.cells_v[crd.z][crd.y][crd.x].occupying_player);
          cell_observed += std::to_string(s.cells_v[crd.z][crd.y][crd.x].occupying_unit_id);
        }
      }
      else // 관찰 안되는 중
      {
        cell_observed += "?";
      }

      // 빈자리 채우기
      if (max_units < 10) // GPI = 3문자
      {
        cell_observed.insert(cell_observed.cend(), (3 - cell_observed.length()), ' ');
      }
      else if (max_units < 100)
      {
        cell_observed.insert(cell_observed.cend(), (4 - cell_observed.length()), ' ');
      }

      return cell_observed;
    }

    std::string baseTState::ObservationString(Player player) const
    {
      std::string board_string = "BoardString of P" + std::to_string(player) + "\n";
      std::string cell_string = "";

      // 1. print ground if not occupied
      // 2. print unit if occupied
      for (int z = 0; z < map_size.z; z++)
      {
        for (int y = 0; y < map_size.y; y++)
        {
          for (int x = 0; x < map_size.x; x++)
          {
            cell_string = get_cell_observation_string(msn, {z, y, x}, player);
            if (msn.cells_v[z][y][x].occupying_unique_unit_id == msn.current_unique_unit_id)
            {
              board_string += "\033[31m" + cell_string + "\033[0m";
            }
            else
            {
              board_string += cell_string;
            }
          } // x
          board_string += "\n";
        } // y
        board_string += "\n";
      } // z

      return board_string;
    }

    int baseTState::distance_between(MapCoord crd_0, MapCoord crd_1)
    {
      int x = crd_0.x - crd_1.x;
      if (x < 0)
        x = x * -1;

      int y = crd_0.y - crd_1.y;
      if (y < 0)
        y = y * -1;

      int z = crd_0.z - crd_1.z;
      if (z < 0)
        z = z * -1;

      return x+y+z;
    }

    // 데미지 계산 및 적용 
    int baseTState::attack(Unit& target_unit, Unit& src_unit)
    {
      target_unit.hp -= target_unit.hp - src_unit.power;

      return 0;
    }

    int baseTState::action_select_tile(int pn, int unit_id, MapCoord tg_crd, bool is_init)
    {
      if (tg_crd.z < 0 || tg_crd.y < 0 || tg_crd.x < 0 ||
          tg_crd.z >= map_size.z || tg_crd.y >= map_size.y || tg_crd.x >= map_size.x)
      {
        get_set_error("tg_crd is out of boundary.", true);
        return -1;
      }
      Unit &mine = msn.units_v[pn][unit_id];
      if (msn.cells_v[tg_crd.z][tg_crd.y][tg_crd.x].occupying_player == PNone)
      { // 비어있음
        if (msn.cells_v[tg_crd.z][tg_crd.y][tg_crd.x].ground_type != GT_CannotEnter)
        { // 이동가능한 곳

          if (!is_init)
          {
            // 1. 현재 유닛이 떠난다. 위치한 셀 정보 수정. 차지한 플레이어 유닛 없음으로
            // msn.cells_v[mine.crd.z][mine.crd.y][mine.crd.x].occupying_player = PNone;
            // msn.cells_v[mine.crd.z][mine.crd.y][mine.crd.x].occupying_unit_id = UNone;
            /// msn.cells_v[mine.crd.z][mine.crd.y][mine.crd.x].occupying_unique_unit_id = UNone;
            set_cell_and_obs({0, 1, 1, 1, 0}, {GT_None, PNone, UNone, UNone, {}}, 
            {mine.crd.z, mine.crd.y, mine.crd.x}, -1, -1, {true, pn, unit_id, ObsRefDown});
            // 2. 현재 유닛이 위치한 셀 기준 주위 셀 obs ref_count 수정
            //scout(pn, unit_id, ObsRefDown);
          }

          // 3. 유닛을 타겟 지점으로 이동시킨다.
          mine.crd = tg_crd;
          // msn.cells_v[mine.crd.z][mine.crd.y][mine.crd.x].occupying_player = mine.player;
          /// msn.cells_v[mine.crd.z][mine.crd.y][mine.crd.x].occupying_unit_id = mine.unit_id;
          // msn.cells_v[mine.crd.z][mine.crd.y][mine.crd.x].occupying_unique_unit_id = mine.unique_unit_id;
          set_cell_and_obs({0, 1, 1, 1, 0}, {GT_None, mine.player, mine.unit_id, mine.unique_unit_id, {}},
                            {mine.crd.z, mine.crd.y, mine.crd.x}, -1, -1, {true, pn, unit_id, ObsRefUp});
          // 4. 이동한지점에서 주위 맵 관찰한다.
          //scout(pn, unit_id, ObsRefUp);
          // 5. 유닛 obs 를 현재 위치 셀과 같게 한다. TODO : 스텔스 가진 유닛이면 다르게 구현해야 한다.
          mine.being_observed_by = msn.cells_v[mine.crd.z][mine.crd.y][mine.crd.x].being_observed_by;
        }
        else
        { // 이동 불가능한 지형. Model 이 이것을 선택하는 것을 마스크 했어야 했다. 이것이 불리면 안됨.
          get_set_error("GroundType is CannotEnter", true);
          return -1;
        }
      }
      else
      { // 누군가 차지 중
        if (msn.cells_v[tg_crd.z][tg_crd.y][tg_crd.x].occupying_player == pn)
        { // 자신이 차지 중
          if (mine.unit_id == msn.cells_v[tg_crd.z][tg_crd.y][tg_crd.x].occupying_unit_id)
          { // 현재 유닛이 있는 곳. 그 자리 유지하는 경우
            return 0;
          }
          else
          {
            // 자신이 차지 중 임을 경고로 알린다. Model 이 이것을 선택하는 것을 마스크 했어야 했다. 이것이 불리면 안됨.
            get_set_error("There is already an unit. Cannot move", true);
            return -1;
          }
        }
        else
        { // 적이 차지 중
          if (msn.cells_v[tg_crd.z][tg_crd.y][tg_crd.x].being_observed_by[pn])
          { // 내가 관찰 중인 곳
            int p_enemy = msn.cells_v[tg_crd.z][tg_crd.y][tg_crd.x].occupying_player;
            int uid_enemy = msn.cells_v[tg_crd.z][tg_crd.y][tg_crd.x].occupying_unit_id;

            if (msn.units_v[p_enemy][uid_enemy].being_observed_by[pn])
            { // 맵&적이 보이는 중
              // 공격한다.
              if (distance_between(tg_crd, mine.crd) > mine.atk_dstc) {
                // 공격거리 불가. 애초에 이 지점을 선택하는 상황이 있으면 안된다. 선택가능한 행동에서 제외되었어야 한다.
                get_set_error("This Action should not been selected", true);
                return -1;
              } else {
                int attck_ret = attack(msn.units_v[p_enemy][uid_enemy], msn.units_v[pn][unit_id]);
              }
            }
            else
           {  // 맵은 보이고 적은 안보이는 중. 스텔스 기능 가진 유닛. 나중에 구현
              // TODO. 나중에 언젠가 구현. 이동하다가 바로 앞에서 적을 발견하는 기능 구현 해야 한다.
              // 지금은 이곳에 들어오는 경우가 존재하면 안된다. 
              get_set_error("This log should not have been visible.", true);
              return -1;
            }
          }
          else
          { // 내가 관찰 아닌 곳. 적이 있는데 맵이 안보이고 적도 안보이는 상황.
            // 맵에 안보이는 곳. 이동 명령 내리면 이동하다가 바로 앞에서 적을 발견하는 기능 구현 해야 한다.
            // 시야보다 이동거리가 더 긴 경우에 이곳에서 실행되게 된다. 지금은 그런 유닛이 없다.
            get_set_error("This log should not have been visible.", true);
            return -1;
          }
        }
      }

      // 2. 맵 관찰지역을 수정한다.
      //    2-1. pn 의 관찰 중 지역만 다 지우고
      //    2-2. pn 유닛들 돌면서 새롭게 관찰지역 만든다.

      return 0;
    }

    std::string baseTState::get_set_error(std::string log, bool is_save)
    {
      static std::string last_log;
      if (is_save)
      {
        last_log = log;
      }
      else
      {
        return last_log;
      }
    }

    int baseTState::is_watched_by_others(Player player, std::vector<int8_t> &being_observed_by)
    {
      int count = 0;

      for (int i = 0; i < being_observed_by.size(); i++)
      {
        if (i == player)
        {
          continue;
        }

        if (being_observed_by[i] > 0)
        {
          count++;
        }
      }
      return count;
    }

    // cell obs check function
    void baseTState::scout(int pn, int unit_id, ObsRefCount o_r_c) // ref_ count should be -1 or 1
    {
      // 1. 주변 셀 observed marking
      Unit &u = msn.units_v[pn][unit_id];

      // 1. pn 주변 vw_dstc 만큼 셀들을 관찰한다.
      // 타겟 셀 z,y 좌표와 unit의 z,y 좌표의 차이만큼 x 를 덜 간다.
      // 대각선 하면 안된다. 거리차이 많이 난다.
      // z + y + x = u.vw_dstc
      #pragma omp parallel
      #pragma omp for
      for (int z = -u.vw_dstc; z <= u.vw_dstc; z++)
      {
        for (int y = -(u.vw_dstc - std::abs(z)); y <= (u.vw_dstc - std::abs(z)); y++)
        {
          for (int x = -(u.vw_dstc - std::abs(z) - std::abs(y)); x <= (u.vw_dstc - std::abs(z) - std::abs(y)); x++)
          {
            //printf("thread num %d \n", omp_get_thread_num());
            int tg_z = u.crd.z + z;
            int tg_y = u.crd.y + y;
            int tg_x = u.crd.x + x;

            // 범위 검사
            if (tg_z >= 0 && tg_z < map_size.z && tg_y >= 0 && tg_y < map_size.y && tg_x >= 0 && tg_x < map_size.x)
            {
              // 해당 셀 Obs Ref count 수정
              // msn.cells_v[tg_z][tg_y][tg_x].being_observed_by[pn] += o_r_c;
              set_cell_and_obs({0, 0, 0, 0, 1}, {GT_None, 0, 0, 0, {}}, {tg_z, tg_y, tg_x}, pn, o_r_c, {false,-1,-1,ObsRefNone});

              // 그 셀에 유닛이 존재한다면 셀과 같은 obs 값 대입
              if (msn.cells_v[tg_z][tg_y][tg_x].occupying_player != PNone)
              {
                msn.units_v[msn.cells_v[tg_z][tg_y][tg_x].occupying_player][msn.cells_v[tg_z][tg_y][tg_x].occupying_unit_id].being_observed_by = msn.cells_v[tg_z][tg_y][tg_x].being_observed_by;
              }
            }
          }
        }
      }
    }

    // Spiel 에 구현되있는 ObservationTensor 함수들이 비효율적이다. 매번 vector 생성하는것.
    void baseTState::ObservationTensorBaseT(Player player)
    {
      // std::fill(obs_v.begin(), obs_v.end(), 0);
      int index = 0;

      // 지형정보
    }

    void baseTState::deploy_unit(int player_id, bool is_alive, int shift_dstc, int atk_dstc,
                                 int vw_dstc, float hp, float power, UnitClass unit_class,
                                 MapCoord crd, std::string name)
    {
      std::vector<int8_t> empty_v(num_players_, 0);
      msn.units_v[player_id].push_back({player_id, is_alive, ++unit_id_count[player_id], ++unique_unit_id_count,
                                        shift_dstc, atk_dstc, vw_dstc, hp, power, unit_class, crd, empty_v, name});
      unique_id_to_player_id_v.push_back({unique_unit_id_count, player_id, unit_id_count[player_id]});
      action_select_tile(player_id, unit_id_count[player_id], crd, true);
    }

    // msn.cell_v 의 정보를 obs_per_p_v 로 옮겨야함
    void baseTState::ObservationTensor(Player player,
                                       absl::Span<float> values) const
    {
      // DeepNash.md
      // 0. 지리정보 채우기. channel = land_info_channel_depth

      // 1. Private Info. c = piece_type_n

      // 2. Op Public Info. c = piece_type_n

      // 3. My Public Info. c = piece_type_n

      // 4. last move. c = last_move_len

      // 5. draw ratio
    }

    void baseTState::set_cell_and_obs(struct Cell_set_flags flags, struct Cell cell, struct MapCoord crd, int player_n, int8_t ref_c, struct scout_info sc_info)
    {
      if (flags.is_gtype)
      {
        msn.cells_v[crd.z][crd.y][crd.x].ground_type = cell.ground_type;
      }
      if (flags.is_op)
      {
        msn.cells_v[crd.z][crd.y][crd.x].occupying_player = cell.occupying_player;
      }
      if (flags.is_oui)
      {
        msn.cells_v[crd.z][crd.y][crd.x].occupying_unit_id = cell.occupying_unit_id;
      }
      if (flags.is_ouui)
      {
        msn.cells_v[crd.z][crd.y][crd.x].occupying_unique_unit_id = cell.occupying_unique_unit_id;
      }
      if (flags.is_bob)
      {
        if (player_n != -1)
        {
          msn.cells_v[crd.z][crd.y][crd.x].being_observed_by[player_n] = ref_c;
        }
        else
        {
          msn.cells_v[crd.z][crd.y][crd.x].being_observed_by = cell.being_observed_by;
        }
      }

      if (sc_info.do_scout)
        scout(sc_info.p, sc_info.unit_id, sc_info.o_r_c);

      #pragma omp parallel
      #pragma omp for
      for (int p = 0; p < num_players_; p++) {
        set_obs_onehot_vector(obs_per_p_v[p][crd.z][crd.y][crd.x], msn.cells_v[crd.z][crd.y][crd.x], p);
      }

      // send
    }

    void baseTState::init_obs()
    {
      // obs 채널 깊이. network_input.md
      // 지형 + (병종수 * 3(OP public,P private, P public)) + move +  무승부까지남은수 + 나에게보이는유닛들남은체력
      obs_total_channel_depth = land_info_channel_depth + (piece_type_n * 3) + last_move_len + 1 + 1;

      std::vector<int8_t> channel_vector(obs_total_channel_depth, 0); //(c,1,1) vector
      std::vector<std::vector<int8_t>> x_vector(map_size.x, channel_vector);
      std::vector<std::vector<std::vector<int8_t>>> yx_vector(map_size.y, x_vector);
      std::vector<std::vector<std::vector<std::vector<int8_t>>>> zyx_vector(map_size.z, yx_vector);

      obs_per_p_v.assign(num_players_, zyx_vector);
    }

    void baseTState::set_obs_onehot_vector(std::vector<int8_t> &now_obs_v, Cell &now_cell, int p)
    {
      // 주어진 셀의 정보를 obs vector 로 옮긴다.
      now_obs_v.assign(now_obs_v.size(), 0); // 초기화
      int last_index = 0;

      // 지형정보 3 채널
      now_obs_v[now_cell.ground_type] = 1; // one-hot encoding
      last_index += ground_type_num;

      // player's own unit info
      if (now_cell.occupying_player == p &&
          is_watched_by_others(p, now_cell.being_observed_by) == 0)
      {
        now_obs_v[last_index + msn.units_v[p][now_cell.occupying_unit_id].unit_class] = 1;
      }
      last_index += sizeof(UnitClass) - 1;

      // Op player's public info
      if (now_cell.occupying_player != p &&
          now_cell.occupying_player != PNone &&
          now_cell.being_observed_by[p] > 0)
      {
        now_obs_v[last_index + msn.units_v[p][now_cell.occupying_unit_id].unit_class] = 1;
      }
      last_index += sizeof(UnitClass) - 1;

      // player's public info
      if (now_cell.occupying_player == p &&
          is_watched_by_others(p, now_cell.being_observed_by) != 0)
      {
        now_obs_v[last_index + msn.units_v[p][now_cell.occupying_unit_id].unit_class] = 1;
      }
      last_index += sizeof(UnitClass) - 1;
    }
    // 이거 존나 복잡하다.
    void baseTState::cells_to_obs()
    {
      // map cell 을 순회하며 obs 에 데이터 넣는다.
      // cell(1x1) 하나가 obs(1xc) 벡터 하나로 바뀐다.
      // cells_v[z][y][x] -> obs_per_p_v[p][z][y][x] = vector<int8>
      for (int z = 0; z < map_size.z; z++)
      {
        for (int y = 0; y < map_size.y; y++)
        {
          for (int x = 0; x < map_size.x; x++)
          {
            for (int p = 0; p < num_players_; p++)
            {
              // 플레이어별로 vector<int8_t> 벡터 하나 만들어야 한다.
              set_obs_onehot_vector(obs_per_p_v[p][z][y][x], msn.cells_v[z][y][x], p);
            }
          }
        }
      }
    }

    void baseTState::init_cells()
    {
      std::vector<int8_t> obp(num_players_, 0);
      Cell normal_ground = {GT_Normal, PNone, UNone, UNone, obp};
      std::vector<Cell> col_1d(map_size.x, normal_ground);
      std::vector<std::vector<Cell>> row_col_2d(map_size.y, col_1d);
      std::vector<std::vector<std::vector<Cell>>> z_row_col_3d(map_size.z, row_col_2d);
      msn.cells_v = z_row_col_3d;
    }
  } // baseT
} // open_spiel