#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>

namespace util {

bool is_positive_int(const std::string &str);

bool str_in_vector(const std::vector<std::string> &str, std::string value);

std::string string_lower(std::string str);

}

#endif