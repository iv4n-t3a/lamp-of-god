#include "tube.hpp"

#include <utility>

#include "phys.hpp"

TubeObserver::TubeObserver(Tube* tube) : tube_(tube) {
  tube->AddObserver(this);
}

Tube::Tube(temp_t temp, dist_t width, dist_t height)
    : temp_(temp), width_(width), height_(height) {}

void Tube::SetWarmerTemperature(temp_t temp) { temp_ = temp; }

std::pair<dist_t, dist_t> Tube::GetDimensions() const {
  return std::make_pair(width_, height_);
}

void Tube::AddObserver(TubeObserver* obs) { observers_.push_back(obs); }

void Tube::NewFrame(delay_t delta_time) {
  NewFrameSetup(delta_time);

  for (TubeObserver* obs : observers_) {
    obs->NewFrame(delta_time);
  }
}
