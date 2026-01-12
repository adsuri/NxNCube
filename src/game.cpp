#include <iostream>
#include <string>
#include <cctype>

#include "NxNCube.hpp"
#include "util/util.hpp"

int main(int argc, char *argv[]) {
  const std::string ARG_ERROR = "USAGE: ./game.exe LAYERS";

  if (!(argc == 2)) {
    std::cout << ARG_ERROR << std::endl;
    return 1;
  }

  if (!util::is_positive_int(argv[1])) {
    std::cout << ARG_ERROR << std::endl;
    return 1;
  }

  if (std::stoi(argv[1]) == 0) {
    std::cout << "LAYERS cannot be zero" << std::endl;
    std::cout << ARG_ERROR << std::endl;
    return 1;
  }

  int n = std::stoi(argv[1]);
  NxNCube cube(n);

  cube.play();
}