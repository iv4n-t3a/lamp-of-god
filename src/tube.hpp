#pragma once

#include <ctime>
#include <vector>

#include "math.hpp"

class TubeObserver;

class Tube {
 public:
  void AddObserver(TubeObserver* obs);
  void NewFrame(double delta_time);

  virtual Vector<double> GetElectricityField(Vector<double>) = 0;
  virtual bool IsInsideTube(Vector<double>) = 0;
  virtual ~Tube() = default;

 protected:
  virtual void NewFrameSetup(double delta_time) = 0;

 private:
  std::vector<TubeObserver*> observers_;
};

class TubeObserver {
 public:
  TubeObserver(Tube* tube);
  virtual void NewFrame(double delta_time) = 0;
  virtual ~TubeObserver() = default;

 protected:
  Tube* tube_;
};
