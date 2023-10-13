#include <iostream>

#include "open_spiel/spiel.h"
#include "open_spiel/spiel_utils.h"
#include "open_spiel/tests/basic_tests.h"

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

  std::cerr << "Printing observation p0..." << std::endl;
  std::string p0_observation = state->ObservationString(0);

  std::cout << p0_observation ;

  return 0;
}