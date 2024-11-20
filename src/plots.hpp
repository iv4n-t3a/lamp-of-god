#pragma once

#include <fstream>
#include <string>

#include "tube.hpp"
#include "math.hpp"

class FieldObserver final : public TubeObserver {
  public:
    FieldObserver(Tube* tube, std::vector<Vector<double>> positions, std::string file_path);
    void NewFrame(double delta_time) override;

  private:
    std::vector<Vector<double>> positions_;
    double time_ = 0;
    std::ofstream file_;
};
