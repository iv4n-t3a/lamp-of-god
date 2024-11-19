#include "gui.hpp"

const double kFps = 30;
const Vector<int> kWinSize = {360, 640};
const std::string kWinName = "Lamp Of God";

int main() {
  // TODO: implement
  Gui gui(nullptr, kFps, kWinSize, kWinName);
  gui.Run();
}
