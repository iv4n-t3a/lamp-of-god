#include "gui.hpp"
#include "plots.hpp"
#include "recttube.hpp"

int main() {
  auto *tube = new RectangleTube(0.1, 0.1, 1, 0.05, 0.05);
  auto *field_observer = new FieldObserver(tube, {{0.05, 0.05}}, "E:\\dev\\lamp-of-god\\resources\\field.txt");
  std::ignore = field_observer;
  Gui gui(tube);
  gui.Run();
}
