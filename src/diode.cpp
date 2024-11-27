#include "diode.hpp"

#include <cassert>
#include <cmath>
#include <random>
#include <tuple>

#include "math.hpp"
#include "phys.hpp"

Diode::Diode(dist_t width, dist_t height, dist_t cathode_width,
             dist_t anode_width, temp_t temp, voltage_t voltage,
             Conductor conductor, dist_t potential_grid_gap,
             physical_t electrons_per_charge)
    : Tube(temp, width, height),
      cathode_width_(cathode_width),
      anode_width_(anode_width),
      cathode_potential_(voltage),
      cond_(conductor),
      potential_grid_gap_(potential_grid_gap),
      electrons_per_charge_(electrons_per_charge) {}

Vector<field_t> Diode::GetPotential(Vector<dist_t> pos) const {
  // TODO implement with poison
  std::ignore = pos;
  return {0, 0};
}

void Diode::NewFrameSetup(delay_t delta_time) {
  SpawnNewCharges(delta_time);
  ApplyElectricForce(delta_time);
  RemoveFinishedCharges(delta_time);
}

void Diode::SpawnNewCharges(delay_t delta_time) {
  static std::mt19937 gen;
  static std::uniform_real_distribution<> dis_x(0, cathode_width_);
  static std::uniform_real_distribution<> dis_y(0, height_);

  static physical_t new_charges = 0;

  new_charges +=
      CalcNewCharge(temp_, cond_, delta_time, cathode_width_ * height_) /
      kElementaryCharge / electrons_per_charge_;

  for (size_t i = 0; i < new_charges; ++i) {
    dist_t x = dis_x(gen);
    dist_t y = dis_y(gen);
    Vector<dist_t> position = {x, y};
    Vector<vel_t> velocity = {0, 0};
    charges_.emplace_back(position, velocity);
  }
}

void Diode::RemoveFinishedCharges(delay_t delta_time) {
  std::ignore = delta_time;

  for (size_t i = 0; i < CountCharges(); ++i) {
    if (not IsInsideTube(i)) {
      RemoveCharge(i);
    }
  }
}

void Diode::ApplyElectricForce(delay_t delta_time) {
  for (size_t i = 0; i < CountCharges(); ++i) {
    ApplyElectricForceToCharge(delta_time, i);
  }
  for (size_t i = 0; i < CountCharges(); ++i) {
    charges_[i].position += charges_[i].velocity * delta_time;
  }
}

void Diode::ApplyElectricForceToCharge(delay_t delta_time, size_t idx) {
  std::ignore = delta_time;

  const physical_t kCharge = electrons_per_charge_ * kElementaryCharge;
  const physical_t kChargeMass = electrons_per_charge_ * kElectronMass;

  Vector<dist_t> pos = charges_[idx].position;
  Vector<work_t> energy = GetPotential(pos) * kCharge;
  Vector<vel_t> velocity_sqr = energy * 2 / kChargeMass;
  charges_[idx].velocity =
      velocity_sqr.Normalized() * pow(velocity_sqr.SqrLen(), 1. / 2);
}

bool Diode::IsInsideTube(size_t idx) {
  auto pos = charges_[idx].position;
  return pos.x >= 0 and pos.x <= width_ and pos.y >= 0 and pos.y <= height_ and
         not std::isnan(pos.x) and not std::isnan(pos.y);
}

void Diode::RemoveCharge(size_t idx) {
  charges_[idx] = charges_.back();
  charges_.pop_back();
}
