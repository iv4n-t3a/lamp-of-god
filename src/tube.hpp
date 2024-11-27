#pragma once

#include <ctime>
#include <vector>

#include "math.hpp"
#include "phys.hpp"

class TubeObserver;

class Tube {
 public:
  Tube(temp_t temp, dist_t width, dist_t height)
      : temp_(temp), width_(width), height_(height) {}

  void AddObserver(TubeObserver* obs);
  void NewFrame(delay_t delta_time);

  void SetCathodePotential(potential_t pot) { cathode_potential_ = pot; }
  void SetAnodePotential(potential_t pot) { anode_potential_ = pot; }
  void SetWarmerTemperature(temp_t temp) { temp_ = temp; }

  std::pair<dist_t, dist_t> GetDimensions() const {
    return std::make_pair(width_, height_);
  }

  virtual current_t GetCurrent() const = 0;
  virtual potential_t GetPotential(Vector<dist_t>) const = 0;
  virtual Vector<field_t> GetElectricityField(Vector<dist_t>) const = 0;

  virtual ~Tube() = default;

 protected:
  virtual void NewFrameSetup(delay_t delta_time) = 0;

  temp_t temp_;
  dist_t width_;
  dist_t height_;
  potential_t cathode_potential_ = 0;
  potential_t anode_potential_ = 0;

 private:
  std::vector<TubeObserver*> observers_;
};

class TubeObserver {
 public:
  TubeObserver(Tube* tube);
  virtual void NewFrame(delay_t delta_time) = 0;
  virtual ~TubeObserver() = default;

 protected:
  const Tube* tube_;
};
