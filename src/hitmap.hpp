#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "tube.hpp"
#include "widget.hpp"

class Hitmap : public Widget {
 public:
  Hitmap(sf::RenderWindow* win, Vector<int> pos, Vector<int> size, Tube* tube)
      : Widget(win, pos, size), tube_(tube) {}

  void Render() override;

 private:
  Tube* tube_;
};
