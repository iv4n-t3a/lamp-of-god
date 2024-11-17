#pragma once

#include <ctime>
#include <vector>

#include "math.hpp"

class TubeObserver;

class Tube {
 public:
  void AddObserver(TubeObserver* obs) { observers_.push_back(obs); }

  virtual void NewFrame(double time_delta) = 0;
  virtual bool IsInsideTube(Vector<double>) = 0;
  virtual ~Tube() = default;

 protected:
  std::vector<TubeObserver*> observers_;
};

class TubeObserver {
 public:
  TubeObserver(Tube* tube) : tube_(tube) { tube->AddObserver(this); }
  virtual void NewFrame() = 0;
  virtual void RegisterElectron(Vector<double>) = 0;
  virtual ~TubeObserver() = default;

 protected:
  Tube* tube_;
};
