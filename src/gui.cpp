#include "gui.hpp"

#include <tuple>

#include "tube.hpp"

Gui::Gui(Tube* tube) : TubeObserver(tube) {}

void Gui::NewFrame() {}
void Gui::RegisterElectron(Vector<double> pos) { std::ignore = pos; }

void Gui::Run() {}
