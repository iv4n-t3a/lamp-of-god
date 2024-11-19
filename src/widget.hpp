#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "math.hpp"

class Widget {
 public:
  Widget(sf::RenderWindow* win, Vector<int> position, Vector<int> size)
      : position_(position), size_(size), win_(win) {}

  void UpdatePosition(Vector<int> position) { position_ = position; }
  void UpdateSize(Vector<int> size) { size_ = size; }

  virtual void Render() = 0;
  virtual ~Widget() = default;

 protected:
  sf::RenderWindow* win_;
  Vector<int> position_;
  Vector<int> size_;
};
