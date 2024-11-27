#include "diode.hpp"

#include <cassert>
#include <cmath>
#include <random>

#include "math.hpp"
#include "phys.hpp"

Diode::Diode(dist_t width, dist_t height, dist_t cathode_area, temp_t temp,
             potential_t cathode_potential, Conductor conductor,
             dist_t potential_grid_gap, physical_t electrons_per_charge)
    : Tube(temp, width, height, cathode_potential),
      cathode_area_(cathode_area),
      cond_(conductor),
      potential_grid_gap_(potential_grid_gap),
      electrons_per_charge_(electrons_per_charge) {
  size_t grid_width = width_ / potential_grid_gap_;
  size_t grid_height = height_ / potential_grid_gap_;

  potential_grid_ =
      std::vector(grid_height, std::vector<potential_t>(grid_width));

  for (size_t i = 0; i < grid_height; i++) {
    potential_grid_[i][0] = cathode_potential_;
  }

  SolvePoisson<potential_t>(
      potential_grid_,
      std::vector(grid_height, std::vector<bool>(grid_width, false)));
}

potential_t Diode::GetPotential(Vector<dist_t> pos) const {
  size_t grid_x = (pos.x + potential_grid_gap_ / 2) / potential_grid_gap_;
  size_t grid_y = (pos.y + potential_grid_gap_ / 2) / potential_grid_gap_;

  if (grid_y >= potential_grid_.size() or
      grid_x >= potential_grid_[grid_y].size()) {
    return 0;
  }
  return potential_grid_[grid_y][grid_x];
}
Vector<field_t> Diode::GetElectricityField(Vector<dist_t> pos) const {
  Vector<dist_t> delta_x = {potential_grid_gap_, 0};
  Vector<dist_t> delta_y = {0, potential_grid_gap_};

  field_t field_x =
      (GetPotential(pos) - GetPotential(pos + delta_x)) / potential_grid_gap_;
  field_t field_y =
      (GetPotential(pos) - GetPotential(pos + delta_y)) / potential_grid_gap_;

  return {field_x, field_y};
}

void Diode::NewFrameSetup(delay_t delta_time) {
  SpawnNewCharges(delta_time);
  ApplyElectricForce(delta_time);
  RemoveFinishedCharges(delta_time);
}

void Diode::SpawnNewCharges(delay_t delta_time) {
  static std::mt19937 gen;
  static std::uniform_real_distribution<> dis_y(0, height_);

  new_charges_ += CalcNewCharge(temp_, cond_, delta_time, cathode_area_) /
                  kElementaryCharge / electrons_per_charge_;

  double new_charges_int_part = std::floor(new_charges_);
  new_charges_ -= new_charges_int_part;

  for (size_t i = 0; i < new_charges_int_part; ++i) {
    dist_t x = 0;
    dist_t y = dis_y(gen);
    Vector<dist_t> position = {x, y};
    Vector<vel_t> velocity = {0, 0};
    charges_.emplace_back(position, velocity);
  }
}

void Diode::RemoveFinishedCharges(delay_t delta_time) {
  current_t removed = 0;

  for (size_t i = 0; i < CountCharges(); ++i) {
    if (not IsInsideTube(i)) {
      RemoveCharge(i);
      if (IsOnAnode(i)) {
        removed += 1;
      }
    }
  }

  current_ = removed * electrons_per_charge_ * kElementaryCharge / delta_time;
}

void Diode::ApplyElectricForce(delay_t delta_time) {
  for (size_t i = 0; i < CountCharges(); ++i) {
    ApplyElectricForceToCharge(delta_time, i);
  }
}

void Diode::ApplyElectricForceToCharge(delay_t delta_time, size_t idx) {
  const physical_t kCharge = electrons_per_charge_ * kElementaryCharge;
  const physical_t kMass = electrons_per_charge_ * kElectronMass;

  auto pos = charges_[idx].position;
  auto vel = charges_[idx].velocity;
  Vector<force_t> force = GetElectricityField(pos) * kCharge;
  Vector<accel_t> accel = force / kMass;
  charges_[idx].velocity += accel * delta_time;
  charges_[idx].position +=
      vel * delta_time + accel * delta_time * delta_time / 2;
}

bool Diode::IsInsideTube(size_t idx) const {
  return IsInsideTube(charges_[idx].position);
}
bool Diode::IsInsideTube(Vector<dist_t> pos) const {
  return pos.x >= 0 and pos.x <= width_ and pos.y >= 0 and pos.y <= height_ and
         not std::isnan(pos.x) and not std::isnan(pos.y);
}
bool Diode::IsOnAnode(size_t idx) const {
  auto pos = charges_[idx].position;
  return pos.x >= width_ and pos.y >= 0 and pos.y <= height_;
}
void Diode::RemoveCharge(size_t idx) {
  charges_[idx] = charges_.back();
  charges_.pop_back();
}
