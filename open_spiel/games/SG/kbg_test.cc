#include <iostream>

#include "open_spiel/spiel.h"
#include "open_spiel/spiel_utils.h"
#include "open_spiel/tests/basic_tests.h"
#include "open_spiel/games/SG/ki_bo_gung.h"

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
  int next_unit = s->get_next_unit_to_action_rand();

  // obs - think - actino loop
  while (1) {
    int player = s->CurrentPlayer();
    int action_state = s->CurrentUAS();
    int player_state = s->CurrentPAS();
    std::cout << "Player:" << std::to_string(player);
    std::cout << " PAState:" << std::to_string(player_state);
    std::cout << " UAState:" << std::to_string(action_state) << std::endl;

    std::string input;
    std::cin >> input;

    switch (player_state) {
      case PA_Obs :

        break;
      case PA_Think :

        break;
      case PA_Action :

        break;
    }
  }

  std::cerr << "Printing observation p0..." << std::endl;
  std::string p0_observation = state->ObservationString(0);
  std::cout << p0_observation ;

  std::cerr << "Printing observation p1..." << std::endl;
  std::string p1_observation = state->ObservationString(1);
  std::cout << p1_observation ;



  return 0;
}