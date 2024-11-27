#pragma once

#include <ctime>
#include <vector>

#include "math.hpp"
#include "phys.hpp"

class TubeObserver;

class Tube {
 public:
  Tube(temp_t start_temp, dist_t width, dist_t height);

  void AddObserver(TubeObserver* obs);
  void NewFrame(delay_t delta_time);

  void SetWarmerTemperature(temp_t temp);
  std::pair<dist_t, dist_t> GetDimensions() const;

  virtual Vector<field_t> GetElectricityField(Vector<dist_t>) const = 0;
  virtual Vector<potential_t> GetPotential(Vector<dist_t>) const = 0;

  virtual ~Tube() = default;

 protected:
  virtual void NewFrameSetup(delay_t delta_time) = 0;

  temp_t temp_;
  dist_t width_;
  dist_t height_;

 private:
  std::vector<TubeObserver*> observers_;
};

class TubeObserver {
 public:
  TubeObserver(Tube* tube);
  virtual void NewFrame(delay_t delta_time) = 0;
  virtual ~TubeObserver() = default;

 protected:
  Tube* tube_;
};
