#include "diode.hpp"

#include <cassert>
#include <random>
#include <tuple>

#include "math.hpp"
#include "phys.hpp"

Diode::Diode(dist_t width, dist_t height, dist_t catode_width,
             dist_t anode_width, temp_t start_temp, voltage_t voltage,
             Conductor condcutor, dist_t potential_grid_gap,
             size_t electrons_per_charge)
    : Tube(start_temp, width, height),
      catode_width_(catode_width),
      anode_width_(anode_width),
      catode_potential_(voltage),
      cond_(condcutor),
      potential_grid_gap_(potential_grid_gap),
      electrons_per_charge_(electrons_per_charge) {}

Vector<field_t> Diode::GetElectricityField(Vector<dist_t> pos) const {
  size_t segments = height_ / potential_grid_gap_;
  voltage_t segment_potential = catode_potential_ / segments;

  double x = catode_width_ / 2;

  std::ignore = segment_potential;
  for (double y = 0; y < height_; y += potential_grid_gap_) {
    std::ignore = x;
  }

  std::ignore = pos;
  return {0, 0};
}

Vector<field_t> Diode::GetPotential(Vector<dist_t> pos) const {
  std::ignore = pos;
  return {0, 0};
}

void Diode::NewFrameSetup(delay_t delta_time) {
  RemoveFinishedCharges(delta_time);
  SpawnNewCharges(delta_time);
  AplyElectrycForce(delta_time);
}

void Diode::SpawnNewCharges(delay_t delta_time) {
  static std::mt19937 gen;
  static std::uniform_real_distribution<> dis_x(0, catode_width_);
  static std::uniform_real_distribution<> dis_y(0, height_);

  const size_t kNewCharges =
      CountNewCharge(temp_, cond_, delta_time, anode_width_ * height_) /
      kElementaryCharge / electrons_per_charge_;

  for (size_t i = 0; i < kNewCharges; ++i) {
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
    if (charges_[i].position.x >= width_ - anode_width_) {
      RemoveCharge(i);
    }
  }
}

void Diode::AplyElectrycForce(delay_t delta_time) {
  for (size_t i = 0; i < CountCharges(); ++i) {
    const mass_t kChargeMass = electrons_per_charge_ * kElectronMass;
    Vector<force_t> force = GetElectricityField(charges_[i].position) *
                            electrons_per_charge_ * kElementaryCharge;
    Vector<accel_t> acceleration = force / kChargeMass;

    charges_[i].speed += acceleration * delta_time;
    charges_[i].position += charges_[i].speed * delta_time +
                            acceleration * delta_time * delta_time / 2;
  }
}

void Diode::RemoveCharge(size_t idx) {
  charges_[idx] = charges_.back();
  charges_.pop_back();
}
