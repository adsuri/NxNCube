#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>

#include "util.hpp"

bool util::is_positive_int(const std::string &str) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (!std::isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

bool util::str_in_vector(const std::vector<std::string> &vec, const std::string &value) {
  return std::find(vec.begin(), vec.end(), value) != vec.end();
}

std::string util::string_lower(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(),
    [](unsigned char c){ return std::tolower(c); });
  return str;
}

bool util::grab_input(const std::string &prompt, std::vector<std::string> *output) {
  std::string input;
  std::cout << prompt;

  if (!std::getline(std::cin, input)) { return false; }
  input = util::string_lower(input);

  std::istringstream is(input);

  std::string current_str;
  output->clear();
  while (is >> current_str) {
    output->push_back(current_str);
  }

  if (output->size() == 0) {
    output->push_back("EMPTYINPUT"); // handle weird empty vector errors
  }

  return true;
}