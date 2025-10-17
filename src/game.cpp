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
  
  cube.play();
}