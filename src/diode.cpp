#include "diode.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <random>
#include <tuple>

#include "math.hpp"
#include "phys.hpp"

Diode::Diode(dist_t width, dist_t height, dist_t catode_width,
             dist_t anode_width, temp_t start_temp, voltage_t voltage,
             Conductor condcutor, dist_t potential_grid_gap,
             physical_t electrons_per_charge)
    : Tube(start_temp, width, height),
      catode_width_(catode_width),
      anode_width_(anode_width),
      catode_potential_(voltage),
      cond_(condcutor),
      potential_grid_gap_(potential_grid_gap),
      electrons_per_charge_(electrons_per_charge) {}

Vector<field_t> Diode::GetElectricityField(Vector<dist_t> pos) const {
  std::ignore = pos;

  if (charges_.size() < 100) {
    return {0, 1};
  }

  return charges_[100].position;
}

Vector<field_t> Diode::GetPotential(Vector<dist_t> pos) const {
  std::ignore = pos;
  return {0, 0};
}

void Diode::NewFrameSetup(delay_t delta_time) {
  SpawnNewCharges(delta_time);
  AplyElectrycForce(delta_time);
  RemoveFinishedCharges(delta_time);
}

void Diode::SpawnNewCharges(delay_t delta_time) {
  static std::mt19937 gen;
  static std::uniform_real_distribution<> dis_x(0, catode_width_);
  static std::uniform_real_distribution<> dis_y(0, height_);

  const size_t kNewCharges =
      CountNewCharge(temp_, cond_, delta_time, catode_width_ * height_) /
      kElementaryCharge / electrons_per_charge_;

  std::cout << "-----" << std::endl;
  std::cout << (CountNewCharge(temp_, cond_, delta_time,
                               catode_width_ * height_))
            << std::endl;
  std::cout << (CountNewCharge(temp_, cond_, delta_time,
                               catode_width_ * height_) /
                kElementaryCharge / electrons_per_charge_)
            << std::endl;
  std::cout << (size_t)(CountNewCharge(temp_, cond_, delta_time,
                                       catode_width_ * height_) /
                        kElementaryCharge / electrons_per_charge_)
            << std::endl;
  std::cout << "+++++" << std::endl;

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
    if (not IsInsideTube(i)) {
      RemoveCharge(i);
    }
  }
}

void Diode::AplyElectrycForce(delay_t delta_time) {
  for (size_t i = 0; i < CountCharges(); ++i) {
    AplyElectrycForceToCharge(delta_time, i);
  }
  for (size_t i = 0; i < CountCharges(); ++i) {
    charges_[i].position += charges_[i].velocity * delta_time;
  }
}

void Diode::AplyElectrycForceToCharge(delay_t delta_time, size_t idx) {
  std::ignore = delta_time;

  const mass_t kChargeMass = electrons_per_charge_ * kElectronMass;
  const charge_t kCharge = electrons_per_charge_ * kElementaryCharge;

  size_t segments = height_ / potential_grid_gap_;
  voltage_t segment_potential_value = catode_potential_ / segments;

  Vector<potential_t> potential_delta =
      CountElectronsPotential(charges_[idx].velocity);

  dist_t x = 0;
  for (dist_t y = 0; y < height_; y += potential_grid_gap_) {
    auto pos = charges_[idx].position;
    Vector<potential_t> segment_potential =
        (pos - Vector<dist_t>({x, y})).Normalized() * segment_potential_value;
    potential_delta += CountPotential(pos, {x, y}, kCharge) - segment_potential;
  }

  Vector<work_t> energy_delta = potential_delta * kCharge;
  Vector<vel_t> velocity_delta_sqr = energy_delta * 2 / kChargeMass;
  Vector<vel_t> velocity_delta =
      velocity_delta_sqr / std::pow(velocity_delta_sqr.SqrLen(), 1. / 4);
  charges_[idx].velocity += velocity_delta;
}

bool Diode::IsInsideTube(size_t idx) {
  auto pos = charges_[idx].position;
  return pos.x >= 0 and pos.x <= width_ and pos.y >= 0 and pos.y <= height_ and
         not std::isnan(pos.x) and not std::isnan(pos.y);
}

void Diode::RemoveCharge(size_t idx) {
  if (idx == 100) {
    std::cout << "Deleting 100" << std::endl;
  }
  charges_[idx] = charges_.back();
  charges_.pop_back();
}
