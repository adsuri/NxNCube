#include "NxNCube.h"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

int main(int argc, char *argv[]) {
  std::string arg_error = "USAGE: ./game.exe LAYERS";

  if (!(argc == 2)) {
    std::cout << arg_error << std::endl;
  }

  if (!NxNCube::is_positive_int(argv[1])) {
    std::cout << arg_error << std::endl;
    return 1;
  }

  if (std::stoi(argv[1]) == 0) {
    std::cout << "LAYERS cannot be zero" << std::endl;
    std::cout << arg_error << std::endl;
    return 1;
  }

  int n = std::stoi(argv[1]);
  NxNCube cube(n);
  std::string input;

  while (true) {
    cube.clear_draw();
    std::cout << "Valid moves are: {'u', 'ui', 'u2', 'l', 'li', 'l2', 'f', 'fi', 'f2', 'r', 'ri', 'r2', 'b', 'bi', 'b2', 'd', 'di', 'd2'}" << std::endl;

    std::cout << "What move?: ";
    std::cin >> input;
    input = NxNCube::string_lower(input);

    if(input == "done") {return 1;}

    while (!NxNCube::valid_move(input)) {
      std::cout << "Invalid move, try again: ";
      std::cin >> input;
      input = NxNCube::string_lower(input);
    }
    std::string side = input;

    std::cout << "How many layers?: " ;
    std::cin >> input;

    while (!NxNCube::valid_move_layers(input, n)) {
      std::cout << "Invalid number of layers, try again: ";
      std::cin >> input;
      input = NxNCube::string_lower(input);
    }
    int layers = std::stoi(input);
    cube.move(side, layers);
  }
  // cube.play();
}