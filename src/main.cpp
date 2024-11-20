#include <iostream>

#include "gui.hpp"
#include "plots.hpp"
#include "recttube.hpp"

int main() {
  auto *tube = new RectangleTube(0.01, 0.01, 0.00000000000001, 0.0005, 0.0005);
  auto *field_observer = new FieldObserver(tube, {{0.05, 0.05}}, "E:\\dev\\lamp-of-god\\resources\\field.txt");
  std::ignore = field_observer;
  size_t frames_amount = 10;
  double delta_t = 0.016;
  for (size_t i = 0; i < frames_amount; i++) {
    std::cout << i * 1.0 / frames_amount << std::endl;
    tube->NewFrame(delta_t);
  }
}
