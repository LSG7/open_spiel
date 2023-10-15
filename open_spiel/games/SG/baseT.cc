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
    }

    // player p 가 바라보는 셀의 정보에 따른 스트링
    std::string baseTState::get_cell_observation_string(MapState s, MapCoord crd, PlayerN p)
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

    void baseTState::set_unit(PlayerN pn, UnitClass cs, Unit base_unit, MapCoord crd, UnitDirection drc)
    {
      base_unit.unit_class = cs;
      base_unit.player = pn;
      base_unit.coord = crd;
      base_unit.direction = drc;

      base_unit.unit_id = unit_id_count[pn]++;
      map_state_now.units_v[pn].push_back(base_unit);

      map_state_now.cells_v[crd.z][crd.y][crd.x].occupying_player = pn;
      map_state_now.cells_v[crd.z][crd.y][crd.x].occupying_unit_id = base_unit.unit_id;
    }

  } // baseT
} // open_spiel