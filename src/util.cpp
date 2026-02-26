/*
 * Copyright (C) 2026 Aditya Suri
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "util.hpp"

bool util::is_positive_int(const std::string &str) {
  if (str == "") { return false; }

  for (size_t i = 0; i < str.size(); ++i) {
    if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
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

bool util::grab_input(std::vector<std::string> *output) {
  std::string input;
  std::cout << "$ ";

  if (!std::getline(std::cin, input)) { return false; }
  // input = util::string_lower(input);

  std::istringstream is(input);

  std::string current_str;
  output->clear();
  while (is >> current_str) {
    output->push_back(current_str);
  }

  return true;
}

std::string util::format_time(double val) {
  int hours = 0;
  int minutes = 0;

  std::ostringstream os;

  hours = static_cast<int>(val / 3600);
  val -= hours * 3600;

  minutes = static_cast<int>(val / 60);
  val -= minutes * 60;
  
  // truncate to three places
  val = static_cast<int>(val * 1000) / 1000.0;

  os << std::fixed << std::setprecision(3);
  if (hours > 0) {
    os << hours
       << ":" << std::setw(2) << std::setfill('0') << minutes
       << ":" << std::setw(6) << std::setfill('0') << val;
  } else if (minutes > 0) {
    os << minutes
       << ":" << std::setw(6) << std::setfill('0') << val;
  } else {
    os << val;
  }
  return os.str();
}