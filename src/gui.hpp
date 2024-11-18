#pragma once

#include "tube.hpp"

class Gui : TubeObserver {
 public:
  Gui(Tube* tube);
  void Run();

  void NewFrame(double delta_time) override;

 private:
};
