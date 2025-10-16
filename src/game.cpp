#include "NxNCube.h"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

// void clear_console() {
//   std::cout << "\033[H\033[2J0" << std::endl;
// }

// void clear_draw(const NxNCube &c) {
//   NxNCube::clear_console();
//   c.draw();
// }

// bool is_positive_int(std::string str) {
//   for (size_t i = 0; i < str.size(); ++i) {
//     if (!std::isdigit(str[i])) {
//       return false;
//     }
//   }
//   return true;
// }

// bool str_in_vector(const std::vector<std::string> &str, std::string value) {
//   for (size_t i = 0; i < str.size(); ++i) {
//     if (str[i] == value) {
//       return true;
//     }
//   }
//   return false;
// }

// std::string string_lower(std::string str) {
//   std::transform(str.begin(), str.end(), str.begin(),
//     [](unsigned char c){return std::tolower(c);});
//   return str;
// }

bool valid_move(std::string input) {
  std::vector<std::string> valid_moves = {"u", "ui", "u2",
                                          "l", "li", "l2",
                                          "f", "fi", "f2",
                                          "r", "ri", "r2",
                                          "b", "bi", "b2",
                                          "d", "di", "d2"};
  input = NxNCube::string_lower(input);

  if (NxNCube::str_in_vector(valid_moves, input)) {
    return true;
  }

  return false;
}

bool valid_move_layers(std::string input, int n) {
  input = NxNCube::string_lower(input);
  if (!NxNCube::is_positive_int(input)) {
    return false;
  }

  if (std::stoi(input) == 0) {
    return false;
  }

  if (std::stoi(input) > n) {
    return false;
  }

  return true;
}


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

    while (!valid_move(input)) {
      std::cout << "Invalid move, try again: ";
      std::cin >> input;
      input = NxNCube::string_lower(input);
    }
    std::string side = input;

    std::cout << "How many layers?: " ;
    std::cin >> input;

    while (!valid_move_layers(input, n)) {
      std::cout << "Invalid number of layers, try again: ";
      std::cin >> input;
      input = NxNCube::string_lower(input);
    }
    int layers = std::stoi(input);
    cube.move(side, layers);
  }
  // cube.play();
}