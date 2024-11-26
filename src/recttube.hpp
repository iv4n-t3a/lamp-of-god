#pragma once

#include "math.hpp"
#include "phys.hpp"
#include "tube.hpp"

struct Electron {
  Vector<dist_t> position;
  Vector<vel_t> speed;
};

class RectangleTube : public Tube {
 public:
  RectangleTube(dist_t height, dist_t width, dist_t anode_width,
                dist_t catode_width, current_t current, field_t field);

  Vector<field_t> GetElectricityField(Vector<dist_t> pos) override;

  Vector<potential_t> GetPotential(Vector<dist_t> pos) override;

  virtual std::pair<dist_t, dist_t> GetDimensions() override;

  bool IsInsideTube(Vector<dist_t> pos) override;

  size_t CountElectrons() const { return electrons_.size(); }

  virtual ~RectangleTube() {}

 protected:
  void NewFrameSetup(delay_t delta_time) override;

  void SpawnNewElectrons(delay_t delta_time);
  void RemoveFinishedElectrons(delay_t delta_time);
  void AplyElectrycForce(delay_t delta_time);

  void RemoveElectron(size_t idx);

  dist_t height_;
  dist_t width_;
  dist_t anode_width_;
  dist_t catode_width_;
  current_t current_;
  field_t field_;

  std::vector<Electron> electrons_;
};
