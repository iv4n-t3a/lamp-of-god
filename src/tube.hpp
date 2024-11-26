#pragma once

#include <ctime>
#include <vector>

#include "math.hpp"
#include "phys.hpp"

class TubeObserver;

class Tube {
 public:
  void AddObserver(TubeObserver* obs);
  void NewFrame(delay_t delta_time);

  virtual Vector<field_t> GetElectricityField(Vector<dist_t>) = 0;
  virtual Vector<potential_t> GetPotential(Vector<dist_t>) = 0;

  virtual bool IsInsideTube(Vector<dist_t>) = 0;
  virtual ~Tube() = default;

 protected:
  virtual void NewFrameSetup(delay_t delta_time) = 0;

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
