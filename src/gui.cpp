#include "gui.hpp"

#include "tube.hpp"

Gui::Gui(Tube* tube) : TubeObserver(tube) {}

void Gui::NewFrame(double delta_time) { std::ignore = delta_time; }

void Gui::Run() {}
