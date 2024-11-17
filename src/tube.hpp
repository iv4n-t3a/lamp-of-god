#pragma once

#include <ctime>
#include <vector>

#include "math.hpp"

class Tube;

class TubeObserver {
 public:
  TubeObserver(Tube* tube) : tube_(tube) {}
  virtual void NewFrame() = 0;
  virtual void RegisterElectron(Vector<double>) = 0;
  virtual ~TubeObserver() = default;

 protected:
  Tube* tube_;
};

class Tube {
 public:
  void AddObserver(TubeObserver* obs) { observers_.push_back(obs); }

  virtual void NewFrame(double time_delta) = 0;
  virtual bool IsInsideTube(Vector<double>) = 0;
  virtual ~Tube() = default;

 protected:
  std::vector<TubeObserver*> observers_;
};
