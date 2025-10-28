#include "NxNCube.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

int main(int argc, char *argv[]) {
  const std::string ARG_ERROR = "USAGE: ./game.exe LAYERS";

  if (!(argc == 2)) {
    std::cout << ARG_ERROR << std::endl;
    return 1;
  }

  if (!NxNCube::IS_POSITIVE_INT(argv[1])) {
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