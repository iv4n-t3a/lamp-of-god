#include "recttube.hpp"

#include <random>
#include <tuple>

#include "math.hpp"
#include "phys.hpp"

RectangleTube::RectangleTube(dist_t height, dist_t width, dist_t anode_width,
                             dist_t catode_width, current_t current,
                             field_t field)
    : height_(height),
      width_(width),
      anode_width_(anode_width),
      catode_width_(catode_width),
      current_(current),
      field_(field) {}

Vector<field_t> RectangleTube::GetElectricityField(Vector<dist_t> pos) {
  Vector<field_t> field = {field_, 0};

  for (Electron elc : electrons_) {
    field += ElectricField(pos, elc.position);
  }

  return field;
}

Vector<field_t> RectangleTube::GetPotential(Vector<dist_t> pos) {
  std::ignore = pos;
  return {0, 0};
}

bool RectangleTube::IsInsideTube(Vector<dist_t> pos) {
  return pos.x < width_ and pos.x >= 0 and pos.y < height_ and pos.y >= 0;
}

void RectangleTube::NewFrameSetup(delay_t delta_time) {
  RemoveFinishedElectrons(delta_time);
  SpawnNewElectrons(delta_time);
  AplyElectrycForce(delta_time);
}

void RectangleTube::SpawnNewElectrons(delay_t delta_time) {
  static std::mt19937 gen;
  static std::uniform_real_distribution<> dis_x(0, anode_width_);
  static std::uniform_real_distribution<> dis_y(0, height_);

  const size_t kNewElectrons = current_ * delta_time / kElementaryCharge;

  for (size_t i = 0; i < kNewElectrons; ++i) {
    dist_t x = dis_x(gen);
    dist_t y = dis_y(gen);
    Vector<dist_t> position = {x, y};
    Vector<vel_t> velocity = {0, 0};
    electrons_.emplace_back(position, velocity);
  }
}

void RectangleTube::RemoveFinishedElectrons(delay_t delta_time) {
  std::ignore = delta_time;

  for (size_t i = 0; i < CountElectrons(); ++i) {
    if (electrons_[i].position.x >= width_ - catode_width_) {
      RemoveElectron(i);
    }
  }
}

void RectangleTube::AplyElectrycForce(delay_t delta_time) {
  static std::vector<Vector<force_t>> forces;

  forces.resize(CountElectrons());

  for (auto& force : forces) {
    force.x = field_ * kElementaryCharge;
    force.y = 0;
  }

  for (size_t i = 0; i < CountElectrons(); ++i) {
    for (size_t j = 0; j < CountElectrons(); ++j) {
      forces[i] +=
          ElectricForce(electrons_[i].position, electrons_[j].position);
    }
  }

  for (size_t i = 0; i < CountElectrons(); ++i) {
    Vector<accel_t> acceleration = forces[i] / kElectronMass;
    electrons_[i].speed += acceleration * delta_time;
    electrons_[i].position += electrons_[i].speed * delta_time +
                              acceleration * delta_time * delta_time / 2;

    if (electrons_[i].position.y > height_) {
      electrons_[i].position.y = height_;
    } else if (electrons_[i].position.y < 0) {
      electrons_[i].position.y = 0;
    }
  }
}

void RectangleTube::RemoveElectron(size_t idx) {
  electrons_[idx] = electrons_.back();
  electrons_.pop_back();
}

std::pair<dist_t, dist_t> RectangleTube::GetDimensions() const {
  return std::make_pair(width_, height_);
}
