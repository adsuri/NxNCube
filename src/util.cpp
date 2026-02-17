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

bool util::grab_input(std::vector<std::string> *output) {
  std::string input;
  std::cout << "$ ";

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

std::string util::format_time(double val) {
  std::string hours_str = "";
  std::string minutes_str = "";
  std::string seconds_str = "";
  int hours = 0;
  int minutes = 0;

  if (val > 3600) {
    hours = static_cast<int>(val / 3600);

    val -= hours * 3600.0;
    hours_str += std::to_string(hours);
  }

  if (val > 60) {
    minutes = static_cast<int>(val / 60);

    val -= minutes * 60.0;
    minutes_str += std::to_string(minutes);
  }

  // truncate to three places
  val = static_cast<double>(static_cast<int>(val * 1000.0)) / 1000.0;
  std::string temp_seconds_str = std::to_string(val);
  if (val < 10) {
    for (int i = 0; i < 5; ++i) {
      seconds_str += temp_seconds_str[i];
    }
  } else {
    for (int i = 0; i < 6; ++i) {
      seconds_str += temp_seconds_str[i];
    }
  }

  std::string result = "";
  if (hours_str != "") {
    result += hours_str;
    result += ":";
    if (minutes < 10) {
      result += "0";
      result += minutes_str;
    } else {
      result += minutes_str;
    }
    result += ":";
    if (val < 10) {
      result += "0";
      result += seconds_str;
    } else {
      result += seconds_str;
    }
  } else if (minutes_str != "") {
    result += minutes_str;
    result += ":";
    if (val < 10) {
      result += "0";
      result += seconds_str;
    } else {
      result += seconds_str;
    }
  } else {
    result += seconds_str;
  }
  return result;
}