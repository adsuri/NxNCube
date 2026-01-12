#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cassert>

#include "NxNCube.hpp"
#include "util/util.hpp"

NxNCube::NxNCube(int layers)
 : n(layers),
   m_top(layers, std::vector<std::string>(layers, NxNCube::WHITE)),
   m_left(layers, std::vector<std::string>(layers, NxNCube::ORANGE)),
   m_front(layers, std::vector<std::string>(layers, NxNCube::GREEN)),
   m_right(layers, std::vector<std::string>(layers, NxNCube::RED)),
   m_back(layers, std::vector<std::string>(layers, NxNCube::BLUE)),
   m_bottom(layers, std::vector<std::string>(layers, NxNCube::YELLOW)) {}

void NxNCube::rotate_cw(std::vector<std::vector<std::string>> &face) {
  std::vector<std::vector<std::string>> temp(this->n, std::vector<std::string>(this->n, ""));

  for (size_t r = 0; r < this->n; ++r) {
    for (size_t c = 0; c < this->n; ++c) {
      temp[c][this->n - 1 - r] = face[r][c];
    }
  }
  face = temp;
}

void NxNCube::rotate_ccw(std::vector<std::vector<std::string>> &face) {
  std::vector<std::vector<std::string>> temp(this->n, std::vector<std::string>(this->n, ""));

  for (size_t r = 0; r < this->n; ++r) {
    for (size_t c = 0; c < this->n; ++c) {
      temp[this->n - 1 - c][r] = face[r][c];
    }
  }
  face = temp;
}

void NxNCube::rotate_half_turn(std::vector<std::vector<std::string>> &face) {
  std::vector<std::vector<std::string>> temp(this->n, std::vector<std::string>(this->n, ""));

  for (size_t r = 0; r < this->n; ++r) {
    for (size_t c = 0; c < this->n; ++c) {
      temp[this->n - 1 - r][this->n - 1 - c] = face[r][c];
    }
  }
  face = temp;
}

bool NxNCube::is_valid_move(const std::string &input) const {
  return util::str_in_vector(NxNCube::VALID_MOVES, input);
}

bool NxNCube::is_valid_depth(const std::string &input) const {
  if (!util::is_positive_int(input)) {
    return false;
  }

  if (std::stoi(input) == 0) {
    return false;
  }

  if (std::stoi(input) > this->n) {
    return false;
  }

  return true;
}

void NxNCube::draw() const {
  // top face
  std::string filler((2*this->n), ' ');
  for (int i = 0; i < this->n; ++i) {
    std::cout << filler;
    for (int j = 0; j < this->n; ++j) {
      std::cout << m_top[i][j] << " ";
    }
    std::cout << std::endl;
  }

  // main "belt" of faces
  for (int i = 0; i < this->n; ++i) {
    for (int j = 0; j < this->n; ++j) {
      std::cout << m_left[i][j] << " ";
    }
    for (int j = 0; j < this->n; ++j) {
      std::cout << m_front[i][j] << " ";
    }
    for (int j = 0; j < this->n; ++j) {
      std::cout << m_right[i][j] << " ";
    }
    for (int j = 0; j < this->n; ++j) {
      std::cout << m_back[i][j] << " ";
    }
    std::cout << std::endl;
  }
  
  // bottom face
  for (int i = 0; i < this->n; ++i) {
    std::cout << filler;
    for (int j = 0; j < this->n; ++j) {
      std::cout << m_bottom[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << NxNCube::CLEAR_COLOR;
}

void NxNCube::clear_console() const {
  std::cout << "\033[H\033[2J0" << std::endl;
}

void NxNCube::clear_draw() const {
  this->clear_console();
  this->draw();
}

void NxNCube::move(const std::string &move, int depth) {
  if (!this->is_valid_move(move)) {
    throw std::runtime_error("Invalid move entered");
  }
  if (depth > this-> n) {
    throw std::runtime_error("Invalid depth entered");
  }

  if (move == "u") {
    this->rotate_cw(m_top);

    for (int layer = 0; layer < depth; ++layer) {
      std::vector<std::string> temp_left = m_left[layer];
      m_left[layer] = m_front[layer];
      m_front[layer] = m_right[layer];
      m_right[layer] = m_back[layer];
      m_back[layer] = temp_left;
    }

    if (depth == this->n) {
      this->rotate_ccw(m_bottom);
    }
  } else if (move == "ui") {
    this->rotate_ccw(m_top);

    for (int layer = 0; layer < depth; ++layer) {
      std::vector<std::string> temp_back = m_back[layer];

      m_back[layer] = m_right[layer];
      m_right[layer] = m_front[layer];
      m_front[layer] = m_left[layer];
      m_left[layer] = temp_back;
    }

    if (depth == this->n) {
      this->rotate_cw(m_bottom);
    }
  } else if (move == "u2") {
    this->rotate_half_turn(m_top);

    for (int layer = 0; layer < depth; ++layer) {
      std::vector<std::string> temp_left = m_left[layer];
      std::vector<std::string> temp_back = m_back[layer];

      m_left[layer] = m_right[layer];
      m_right[layer] = temp_left;
      m_back[layer] = m_front[layer];
      m_front[layer] = temp_back;
    }

    if (depth == this->n) {
      this->rotate_half_turn(m_bottom);
    }
  } else if (move == "d") {
    this->rotate_cw(m_bottom);

    for (int layer = this->n - 1; layer >= this->n - depth; --layer) {
      std::vector<std::string> temp = m_back[layer];

      m_back[layer] = m_right[layer];
      m_right[layer] = m_front[layer];
      m_front[layer] = m_left [layer];
      m_left[layer] = temp;
    }

    if (depth == this->n) {
      this->rotate_ccw(m_top);
    }
  } else if (move == "di") {
    this->rotate_ccw(m_bottom);

    for (int layer = this->n - 1; layer >= this->n - depth; --layer) {
      std::vector<std::string> temp = m_left[layer];

      m_left[layer] = m_front[layer];
      m_front[layer] = m_right[layer];
      m_right[layer] = m_back[layer];
      m_back[layer] = temp;
    }

    if (depth == this->n) {
      this->rotate_cw(m_top);
    }
  } else if (move == "d2") {
    this->rotate_half_turn(m_top);

    for (int layer = this->n - 1; layer >= this->n - depth; -- layer) {
      std::vector<std::string> temp_left = m_left[layer];
      std::vector<std::string> temp_back = m_back[layer];

      m_left[layer] = m_right[layer];
      m_right[layer] = temp_left;
      m_back[layer] = m_front[layer];
      m_front[layer] = temp_back;
    }

    if (depth == this->n) {
      this->rotate_half_turn(m_top);
    }
  } else if (move == "r") {
    this->rotate_cw(m_right);

    for (int layer = this->n - 1; layer >= this->n - depth; --layer) {
      for (int r = 0; r < this->n; ++r) {
        std::string temp = m_top[r][layer];

        m_top[r][layer] = m_front[r][layer];
        m_front[r][layer] = m_bottom[r][layer];
        m_bottom[r][layer] = m_back[this->n - 1 - r][this->n - 1 - layer];
        m_back[this->n - 1 - r][this->n - 1 - layer] = temp;
      }
    }

    if (depth == this->n) {
      this->rotate_ccw(m_left);
    }
  } else if (move == "ri") {

  } else if (move == "r2") {

  }

  else {
    std::cout << "You *really* shouldn't have gotten here" << std::endl;
    assert(false);
  }
}

void NxNCube::play() {
  std::string input;

  while (true) {
    this->clear_draw();
    std::cout << "Valid moves are: {'u', 'ui', 'u2', 'l', 'li', 'l2', 'f', 'fi', 'f2', 'r', 'ri', 'r2', 'b', 'bi', 'b2', 'd', 'di', 'd2'}" << std::endl;

    std::cout << "What move?: ";
    std::cin >> input;
    input = util::string_lower(input);

    if (input == "done") { return; }

    while (!this->is_valid_move(input)) {
      std::cout << "Invalid move, try again: ";
      std::cin >> input;
      input = util::string_lower(input);
      if (input == "done") { return; }
    }
    std::string side = input;

    std::cout << "How many layers?: " ;
    std::cin >> input;
    input = util::string_lower(input);

    if(input == "done") { return; }

    while (!this->is_valid_depth(input)) {
      std::cout << "Invalid number of layers, try again: ";
      std::cin >> input;
      input = util::string_lower(input);

      if(input == "done") { return; }
    }
    int layers = std::stoi(input);

    this->move(side, layers);
  }
}