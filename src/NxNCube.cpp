#include "NxNCube.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

NxNCube::NxNCube(int layers)
 : n(layers),
   top(layers, std::vector<std::string>(layers, NxNCube::WHITE)),
   left(layers, std::vector<std::string>(layers, NxNCube::ORANGE)),
   front(layers, std::vector<std::string>(layers, NxNCube::GREEN)),
   right(layers, std::vector<std::string>(layers, NxNCube::RED)),
   back(layers, std::vector<std::string>(layers, NxNCube::BLUE)),
   bottom(layers, std::vector<std::string>(layers, NxNCube::YELLOW)) {}

void NxNCube::rotate_cw(std::vector<std::vector<std::string>> &face) {
  std::vector<std::vector<std::string>> temp(this->n, std::vector<std::string>(this->n, ""));

  for (size_t r = 0; r < this->n; ++r) {
    for (size_t c = 0; c < this->n; ++c) {
      temp[c][this->n - 1 - r] = face[r][c];
    }
  }
  face = temp;
};

void NxNCube::rotate_ccw(std::vector<std::vector<std::string>> &face) {
  std::vector<std::vector<std::string>> temp(this->n, std::vector<std::string>(this->n, ""));

  for (size_t r = 0; r < this->n; ++r) {
    for (size_t c = 0; c < this->n; ++c) {
      temp[this->n - 1 - c][r] = face[r][c];
    }
  }
  face = temp;
};

void NxNCube::rotate_half_turn(std::vector<std::vector<std::string>> &face) {
  std::vector<std::vector<std::string>> temp(this->n, std::vector<std::string>(this->n, ""));

  for (size_t r = 0; r < this->n; ++r) {
    for (size_t c = 0; c < this->n; ++c) {
      temp[this->n - 1 - r][this->n - 1 - c] = face[r][c];
    }
  }
  face = temp;
};

bool NxNCube::str_in_vector(const std::vector<std::string> &str, std::string value) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == value) {
      return true;
    }
  }
  return false;
} // static

bool NxNCube::is_positive_int(const std::string &str) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (!std::isdigit(str[i])) {
      return false;
    }
  }
  return true;
} // static

std::string NxNCube::string_lower(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(),
    [](unsigned char c){return std::tolower(c);});
  return str;
} // static

bool NxNCube::is_valid_move(std::string input) {
  input = NxNCube::string_lower(input);

  return NxNCube::str_in_vector(NxNCube::VALID_MOVES, input);
} // static

bool NxNCube::is_valid_depth(std::string input, int n) {
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
} // static

void NxNCube::draw() const {
  // top face
  std::string filler((2*this->n), ' ');
  for (int i = 0; i < this->n; ++i) {
    std::cout << filler;
    for (int j = 0; j < this->n; ++j) {
      std::cout << this->top[i][j] << " ";
    }
    std::cout << std::endl;
  }

  // main "belt" of faces
  for (int i = 0; i < this->n; ++i) {
    for (int j = 0; j < this->n; ++j) {
      std::cout << this->left[i][j] << " ";
    }
    for (int j = 0; j < this->n; ++j) {
      std::cout << this->front[i][j] << " ";
    }
    for (int j = 0; j < this->n; ++j) {
      std::cout << this->right[i][j] << " ";
    }
    for (int j = 0; j < this->n; ++j) {
      std::cout << this->back[i][j] << " ";
    }
    std::cout << std::endl;
  }
  
  // bottom face
  for (int i = 0; i < this->n; ++i) {
    std::cout << filler;
    for (int j = 0; j < this->n; ++j) {
      std::cout << this->bottom[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << NxNCube::CLEAR_COLOR;
}

void NxNCube::CLEAR_CONSOLE() {
  std::cout << "\033[H\033[2J0" << std::endl;
} // static

void NxNCube::clear_draw() const {
  NxNCube::CLEAR_CONSOLE();
  this->draw();
}

void NxNCube::move(std::string move, int depth) {
  move = NxNCube::string_lower(move);

  if (!NxNCube::is_valid_move(move)) {
    throw InvalidMoveException("Invalid move entered");
  }
  if (depth > this-> n) {
    throw InvalidDepthException("Invalid depth entered");
  }

  if (move == "u") {
    this->rotate_cw(this->top);

    for (int layer = 0; layer < depth; ++layer) {
      std::vector<std::string> temp_left = this->left[layer];
      this->left[layer] = this->front[layer];
      this->front[layer] = this->right[layer];
      this->right[layer] = this->back[layer];
      this->back[layer] = temp_left;
    }

    if (depth == this->n) {
      this->rotate_ccw(this->bottom);
    }
  } else if (move == "ui") {
    this->rotate_ccw(this->top);

    for (int layer = 0; layer < depth; ++layer) {
      std::vector<std::string> temp_back = this->back[layer];

      this->back[layer] = this->right[layer];
      this->right[layer] = this->front[layer];
      this->front[layer] = this->left[layer];
      this->left[layer] = temp_back;
    }

    if (depth == this->n) {
      this->rotate_cw(this->bottom);
    }
  } else if (move == "u2") {
    this->rotate_half_turn(this->top);

    for (int layer = 0; layer < depth; ++layer) {
      std::vector<std::string> temp_left = this->left[layer];
      std::vector<std::string> temp_back = this->back[layer];

      this->left[layer] = this->right[layer];
      this->right[layer] = temp_left;
      this->back[layer] = this->front[layer];
      this->front[layer] = temp_back;
    }

    if (depth == this->n) {
      this->rotate_half_turn(this->bottom);
    }
  } else if (move == "d") {
    this->rotate_cw(this->bottom);

    for (int layer = this->n - 1; layer >= this->n - depth; --layer) {
      std::vector<std::string> temp = this->back[layer];

      this->back[layer] = this->right[layer];
      this->right[layer] = this->front[layer];
      this->front[layer] = this->left [layer];
      this->left[layer] = temp;
    }

    if (depth == this->n) {
      this->rotate_ccw(this->top);
    }
  } else if (move == "di") {
    this->rotate_ccw(this->bottom);

    for (int layer = this->n - 1; layer >= this->n - depth; --layer) {
      std::vector<std::string> temp = this->left[layer];

      this->left[layer] = this->front[layer];
      this->front[layer] = this->right[layer];
      this->right[layer] = this->back[layer];
      this->back[layer] = temp;
    }

    if (depth == this->n) {
      this->rotate_cw(this->top);
    }
  } else if (move == "d2") {
    this->rotate_half_turn(this->top);

    for (int layer = this->n - 1; layer >= this->n - depth; -- layer) {
      std::vector<std::string> temp_left = this->left[layer];
      std::vector<std::string> temp_back = this->back[layer];

      this->left[layer] = this->right[layer];
      this->right[layer] = temp_left;
      this->back[layer] = this->front[layer];
      this->front[layer] = temp_back;
    }

    if (depth == this->n) {
      this->rotate_half_turn(this->top);
    }
  } else if (move == "r") {
    this->rotate_cw(this->right);

    for (int layer = this->n - 1; layer >= this->n - depth; --layer) {
      for (int r = 0; r < this->n; ++r) {
        std::string temp = this->top[r][layer];

        this->top[r][layer] = this->front[r][layer];
        this->front[r][layer] = this->bottom[r][layer];
        this->bottom[r][layer] = this->back[this->n - 1 - r][this->n - 1 - layer];
        this->back[this->n - 1 - r][this->n - 1 - layer] = temp;
      }
    }

    if (depth == this->n) {
      this->rotate_ccw(this->left);
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
    input = NxNCube::string_lower(input);

    if (input == "done") {return;}

    while (!NxNCube::is_valid_move(input)) {
      std::cout << "Invalid move, try again: ";
      std::cin >> input;
      input = NxNCube::string_lower(input);
      if (input == "done") {return;}
    }
    std::string side = input;

    std::cout << "How many layers?: " ;
    std::cin >> input;

    if(input == "done") {return;}

    while (!NxNCube::is_valid_depth(input, this->n)) {
      std::cout << "Invalid number of layers, try again: ";
      std::cin >> input;
      input = NxNCube::string_lower(input);

      if(input == "done") {return;}
    }

    int layers = std::stoi(input);
    this->move(side, layers);
  }
}