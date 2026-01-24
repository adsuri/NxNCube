#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

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