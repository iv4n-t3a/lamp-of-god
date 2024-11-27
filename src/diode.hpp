#pragma once

#include "math.hpp"
#include "phys.hpp"
#include "tube.hpp"

struct Charge {
  Vector<dist_t> position;
  Vector<vel_t> velocity;
};

class Diode : public Tube {
 public:
  Diode(dist_t width, dist_t height, dist_t cathode_width, dist_t anode_width,
        temp_t temp, voltage_t voltage, Conductor conductor,
        dist_t potential_grid_gap, physical_t electrons_per_charge);

  Vector<potential_t> GetPotential(Vector<dist_t> pos) const override;

  size_t CountCharges() const { return charges_.size(); }

 protected:
  void NewFrameSetup(delay_t delta_time) override;

  void SpawnNewCharges(delay_t delta_time);
  void RemoveFinishedCharges(delay_t delta_time);
  void ApplyElectricForce(delay_t delta_time);

  void ApplyElectricForceToCharge(delay_t delta_time, size_t idx);

  bool IsInsideTube(size_t idx);
  void RemoveCharge(size_t idx);

  double new_charges = 0;
  dist_t cathode_width_;
  dist_t anode_width_;
  potential_t cathode_potential_;
  Conductor cond_;

  dist_t potential_grid_gap_;
  physical_t electrons_per_charge_ = 1;

  std::vector<Charge> charges_;
};
