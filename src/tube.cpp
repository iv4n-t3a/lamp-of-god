#include "tube.hpp"

TubeObserver::TubeObserver(Tube* tube) : tube_(tube) {
  tube->AddObserver(this);
}

void Tube::AddObserver(TubeObserver* obs) { observers_.push_back(obs); }

void Tube::NewFrame(double delta_time) {
  NewFrameSetup(delta_time);

  for (TubeObserver* obs : observers_) {
    obs->NewFrame(delta_time);
  }
}