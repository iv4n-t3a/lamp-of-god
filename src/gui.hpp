#pragma once

#include "tube.hpp"

class Gui : TubeObserver {
 public:
  Gui(Tube* tube);
  void Run();

  void NewFrame() override;
  void RegisterElectron(Vector<double> pos) override;

 private:
};
