#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <vector>

#include "tube.hpp"
#include "widget.hpp"

class Gui {
 public:
  Gui(Tube* tube, int fps, Vector<int> winsize, std::string winname,
      double scale);
  ~Gui();

  void Run();

 private:
  int fps_;

  Tube* tube_;

  std::vector<Widget*> widgets_;
  sf::RenderWindow window_;
};
