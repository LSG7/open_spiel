#include <iostream>

#include "open_spiel/spiel.h"
#include "open_spiel/spiel_utils.h"
#include "open_spiel/tests/basic_tests.h"
#include "open_spiel/games/SG/ki_bo_gung.h"

using namespace open_spiel::baseT;

int main(int argc, char** argv)
{
  std::cerr << "Loading game..\n" << std::endl;
  std::shared_ptr<const open_spiel::Game> game = open_spiel::LoadGame("kbg");

  if (!game) {
    std::cerr << "problem with loading game, exiting..." << std::endl;
    return -1;
  }

  std::cerr << "Starting new state..." << std::endl;
  std::unique_ptr<open_spiel::State> state = game->NewInitialState();

  open_spiel::kbg::kbgState* s = (open_spiel::kbg::kbgState*) state.release();
  

  // obs - think - actino loop
  while (1) {
    int player = s->CurrentPlayer();
    int unit_state = s->CurrentUAS();
    int next_unit = 0;

    next_unit = s->get_next_unit_to_action(player, false);

    std::cout << "Player:" << std::to_string(player);
    std::cout << " Unit:" << std::to_string(next_unit);
    std::cout << " UAState:" << std::to_string(unit_state) << std::endl;

    // PA_Obs
    std::cout << "Player observing" << std::endl;
    std::string p_observation = s->ObservationString(player);
    std::cout << p_observation;
    // TODO : make obtensor
    s->SetNextPAS();

    // PA_Think
    std::cout << "Player thinking" << std::endl;
    // TODO : inference network
    s->SetNextPAS();

    // PA_Action
    std::cout << "Player acting" << std::endl;
    // TODO : action_apply(p,a);
    s->SetNextPAS();

    s->SetNextUAS();
    if (s->CurrentUAS() == UA_Move) { // 플레이어 차례 끝남 
      s->get_next_unit_to_action(player, true); // 현재 플레이어 유닛 빼낸다.
      //s->SetNextPlayer();
      std::cout << "Unit changed" << std::endl;
    }

    std::cout << "move to Next State. input any char to next : ";
    std::string input;
    std::cin >> input;
  }

  return 0;
}