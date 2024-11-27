#pragma once

#include "math.hpp"
#include "phys.hpp"
#include "tube.hpp"

struct Charge {
  Vector<dist_t> position;
  Vector<vel_t> speed;
};

class Diode : public Tube {
 public:
  Diode(dist_t width, dist_t height, dist_t catode_width, dist_t anode_width,
        temp_t temp, voltage_t voltage, Conductor condcutor,
        dist_t potential_grid_gap, size_t electrons_per_charge);

  Vector<field_t> GetElectricityField(Vector<dist_t> pos) const override;

  Vector<potential_t> GetPotential(Vector<dist_t> pos) const override;

  size_t CountCharges() const { return charges_.size(); }

 protected:
  void NewFrameSetup(delay_t delta_time) override;

  void SpawnNewCharges(delay_t delta_time);
  void RemoveFinishedCharges(delay_t delta_time);
  void AplyElectrycForce(delay_t delta_time);

  void RemoveCharge(size_t idx);

  dist_t catode_width_;
  dist_t anode_width_;
  potential_t catode_potential_;
  Conductor cond_;

  dist_t potential_grid_gap_;
  size_t electrons_per_charge_ = 1;

  std::vector<Charge> charges_;
};
