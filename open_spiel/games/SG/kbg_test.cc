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
    int action_state = s->CurrentUAS();
    int player_state = s->CurrentPAS();
    int next_unit = 0;

    next_unit = s->get_next_unit_to_action_rand(player, (player_state==PA_Action));

    std::cout << "Player:" << std::to_string(player);
    std::cout << " Unit:" << std::to_string(next_unit);
    std::cout << " PAState:" << std::to_string(player_state);
    std::cout << " UAState:" << std::to_string(action_state) << std::endl;

    std::string input;
    std::cin >> input;

    std::string p_observation;
    switch (player_state) {
      case PA_Obs :
        p_observation = s->ObservationString(player);
        std::cout << p_observation;
        // TODO : make obtensor

        s->SetNextPAS();
        break;
      case PA_Think :

        s->SetNextPAS();
        break;
      case PA_Action :

        s->SetNextPAS();
        s->SetNextUAS();
        break;
    }

    if (s->CurrentUAS() == UA_Move) // 이전 플레이어 차례 끝남 
      s->SetNextPlayer();
  }

  return 0;
}