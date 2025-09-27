#include "NxNCube.h"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

bool isPositiveInt(std::string str) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (!std::isdigit(str[i])) {
      std::cout << str[i] << " is not a digit character" << std::endl;
      return false;
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  std::string arg_error = "USAGE: ./game.exe LAYERS";
  if (!(argc == 2)) {
    std::cout << arg_error << std::endl;
  }
  if (!isPositiveInt(argv[1])) {
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
  cube.draw();
}