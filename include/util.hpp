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

#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>

namespace util {
  /**
   * @brief Checks if a `string` represents a positive integer
   * 
   * @param str `string` to check
   * @return `true` if `str` represents a positive integer, false otherwise
   * 
   */
  bool is_positive_int(const std::string &str);

  /**
   * @brief Checks if a `string` is in a `vector`
   * 
   * @param vec `vector` to look through
   * @param value `string` to look for
   * @return `true` if `value` is in `vec`, false otherwise
   * 
   */
  bool str_in_vector(const std::vector<std::string> &vec, const std::string &value);

  /**
   * @brief Creates a lowercase `string` from another `string`
   * 
   * @param str `string` to use
   * @return Copy of `str` in lowercase
   * 
   */
  std::string string_lower(std::string str);

  /**
   * @brief Prompts user for input, parsing it into a vector
   * 
   * Overwrites `*output`
   * 
   * Sets `*output` to {`"EMPTY_INPUT"`} if no input was given
   * 
   * @param output Address of vector to put inputs into
   * @return `true` if parsing was successful, `false` if EOF
   * 
   */
  bool grab_input(std::vector<std::string> *output);
}

#endif