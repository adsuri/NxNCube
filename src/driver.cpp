#include <iostream>
#include <string>

#include "NxNCube.hpp"
#include "util.hpp"

int main(int argc, char *argv[]) {
  const std::string arg_error = "USAGE: ./game.exe LAYERS [letters]";

  if (!(argc == 2 || argc == 3)) {
    std::cout << arg_error << std::endl;
    return 1;
  }

  if (!util::is_positive_int(argv[1])) {
    std::cout << arg_error << std::endl;
    return 1;
  }

  if (std::stoi(argv[1]) == 0) {
    std::cout << "LAYERS cannot be zero" << std::endl;
    std::cout << arg_error << std::endl;
    return 1;
  }

  bool blocks = true;
  if (argc == 2) {
    blocks = true;
  } else {
    if (std::string(argv[2]) == "letters") {
      blocks = false;
    } else {
      std::cout << arg_error << std::endl;
      return 1;
    }
  }

  const int n = std::stoi(argv[1]);
  NxNCube cube(n, blocks);

  cube.play();
}