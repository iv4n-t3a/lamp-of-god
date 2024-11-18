#pragma once

#include "math.hpp"
#include "tube.hpp"

struct Electron {
  Vector<double> position;
  Vector<double> speed;
};

class RectangleTube : public Tube {
 public:
  RectangleTube(double height, double width, double current, double anode_width,
                double catode_width);
  Vector<double> GetElectricityField(Vector<double> pos) override;
  bool IsInsideTube(Vector<double> pos) override;

  size_t CountElectrons() const { return electrons_.size(); }

 private:
  void NewFrameSetup(double delta_time) override;

  void SpawnNewElectrons(double delta_time);
  void RemoveFinishedElectrons(double delta_time);
  void AplyElectrycForce(double delta_time);

  void RemoveElectron(size_t idx);

  double height_;
  double width_;
  double current_;
  double field_;
  double anode_width_;
  double catode_width_;

  std::vector<Electron> electrons_;
};
