#include "NxNCube.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

NxNCube::NxNCube(int layers)
 : n(layers),
   top(layers, std::vector<std::string>(layers, NxNCube::white)),
   left(layers, std::vector<std::string>(layers, NxNCube::orange)),
   front(layers, std::vector<std::string>(layers, NxNCube::green)),
   right(layers, std::vector<std::string>(layers, NxNCube::red)),
   back(layers, std::vector<std::string>(layers, NxNCube::blue)),
   bottom(layers, std::vector<std::string>(layers, NxNCube::yellow)) {}

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

void NxNCube::printColors() {
  std::cout << NxNCube::white 
    << NxNCube::orange
    << NxNCube::green
    << NxNCube::red
    << NxNCube::blue
    << NxNCube::yellow
    << std::endl;
}

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
}

void NxNCube::move(std::string move, int depth) {
  if (move == "u") {
    this->rotate_cw(this->top);

    for (int layer = 0; layer < depth; ++layer) {
      std::vector<std::string> temp_left = this->left[layer];
      this->left[layer] = this->front[layer];
      this->front[layer] = this->right[layer];
      this->right[layer] = this->back[layer];
      this->back[layer] = temp_left;
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
  }
  
  else {
    std::cout << "You *really* shouldn't have gotten here" << std::endl;
    assert(false);
  }
}