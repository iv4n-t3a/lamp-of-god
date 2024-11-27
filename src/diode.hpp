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
  Diode(dist_t width, dist_t height, dist_t cathode_area, temp_t temp,
        Conductor conductor, dist_t potential_grid_gap,
        physical_t electrons_per_charge);

  current_t GetCurrent() const override { return current_; }
  potential_t GetPotential(Vector<dist_t> pos) const override;
  Vector<field_t> GetElectricityField(Vector<dist_t> pos) const override;

  size_t CountCharges() const { return charges_.size(); }

 protected:
  void NewFrameSetup(delay_t delta_time) override;

  void SpawnNewCharges(delay_t delta_time);
  void RemoveFinishedCharges(delay_t delta_time);
  void ApplyElectricForce(delay_t delta_time);

  void ApplyElectricForceToCharge(delay_t delta_time, size_t idx);

  bool IsOnAnode(size_t idx) const;
  bool IsInsideTube(size_t idx) const;
  bool IsInsideTube(Vector<dist_t>) const;
  void RemoveCharge(size_t idx);

  dist_t cathode_area_;
  Conductor cond_;

  dist_t potential_grid_gap_;
  physical_t electrons_per_charge_ = 1;
  std::vector<std::vector<potential_t>> potential_grid_;

  current_t current_ = 0;
  physical_t new_charges_ = 0;
  std::vector<Charge> charges_;
};
