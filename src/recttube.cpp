#include "recttube.hpp"

#include <random>

#include "math.hpp"
#include "phys.hpp"

RectangleTube::RectangleTube(double height, double width, double current,
                             double anode_width, double catode_width)
    : height_(height),
      width_(width),
      current_(current),
      anode_width_(anode_width),
      catode_width_(catode_width) {}

Vector<double> RectangleTube::GetElectricityField(Vector<double> pos) {
  Vector<double> field = {field_, 0};

  for (Electron elc : electrons_) {
    field += ElectricField(pos, elc.position);
  }

  return field;
}

bool RectangleTube::IsInsideTube(Vector<double> pos) {
  return pos.x < width_ and pos.x >= 0 and pos.y < height_ and pos.y >= 0;
}

void RectangleTube::NewFrameSetup(double delta_time) {
  RemoveFinishedElectrons(delta_time);
  SpawnNewElectrons(delta_time);
  AplyElectrycForce(delta_time);
}

void RectangleTube::SpawnNewElectrons(double delta_time) {
  static std::mt19937 gen;
  static std::uniform_real_distribution<> dis_x(0, anode_width_);
  static std::uniform_real_distribution<> dis_y(0, height_);

  const size_t kNewElectrons = current_ * delta_time / kElementaryCharge;

  for (size_t i = 0; i < kNewElectrons; ++i) {
    double x = dis_x(gen);
    double y = dis_y(gen);
    Vector<double> position = {x, y};
    Vector<double> speed = {0, 0};
    electrons_.emplace_back(position, speed);
  }
}

void RectangleTube::RemoveFinishedElectrons(double delta_time) {
  for (size_t i = 0; i < CountElectrons(); ++i) {
    if (electrons_[i].position.x >= width_ - catode_width_) {
      RemoveElectron(i);
    }
  }
}

void RectangleTube::AplyElectrycForce(double delta_time) {
  static std::vector<Vector<double>> forces;

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
    Vector<double> acceleration = forces[i] / kElectronMass;
    electrons_[i].speed += acceleration * delta_time;
    electrons_[i].position += electrons_[i].speed * delta_time +
                              acceleration * delta_time * delta_time / 2;

    if (IsInsideTube(electrons_[i].position)) {
      RemoveElectron(i);
    }
  }
}

void RectangleTube::RemoveElectron(size_t idx) {
  electrons_[idx] = electrons_.back();
  electrons_.pop_back();
}
