#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "tube.hpp"
#include "widget.hpp"

class HeatMap : public Widget {
 public:
  HeatMap(sf::RenderWindow* win, Vector<int> pos, Vector<int> size, Tube* tube,
          double scale)
      : Widget(win, pos, size), tube_(tube), scale_(scale) {}

  void Render() override;

 private:
  void DrawSquare(int x, int y);

  Tube* tube_;
  double scale_;
};
