#pragma once

#include <cmath>

#include "math.hpp"

using physical_t = long double;

using charge_t = physical_t;
using dist_t = physical_t;
using mass_t = physical_t;
using vel_t = physical_t;
using force_t = physical_t;
using field_t = physical_t;
using accel_t = physical_t;
using current_t = physical_t;
using delay_t = physical_t;
using potential_t = physical_t;
using voltage_t = physical_t;
using temp_t = physical_t;
using work_t = physical_t;
using power_t = physical_t;

struct Conductor {
  physical_t work_function;
  physical_t richardson_constant;
};

const mass_t kElectronMass = 9.1E-31;
const charge_t kElementaryCharge = 1.6E-19;
const physical_t kColoumbConstant = 8.99E9;
const physical_t kBoltzmanConstant = 1.38E-23;
const physical_t kVacuumPermutivity = 8.85E-12;

const Conductor kWolfram = {4.5 * kElementaryCharge, 60E4};

inline Vector<force_t> ElectricForce(Vector<dist_t> el1, Vector<dist_t> el2) {
  force_t val = kColoumbConstant * kElementaryCharge * kElementaryCharge /
                el1.SqrDist(el1);
  return (el1 - el2).Normalized() * val;
}

inline Vector<field_t> ElectricField(Vector<dist_t> pos, Vector<dist_t> elc) {
  field_t val = kColoumbConstant * kElementaryCharge / pos.SqrDist(elc);
  return (pos - elc).Normalized() * val;
}

inline current_t CurrentDensity(temp_t temp, Conductor cond) {
  return cond.richardson_constant * temp * temp *
         std::pow(kElementaryCharge,
                  -cond.work_function / (kBoltzmanConstant * temp));
}

inline charge_t CountNewCharge(temp_t temp, Conductor cond, delay_t time,
                               dist_t area) {
  return CurrentDensity(temp, cond) * area * time;
}

inline Vector<potential_t> CountPotential(
    Vector<dist_t> charge_position, Vector<dist_t> target_position,
    charge_t charge, physical_t permutivity = kVacuumPermutivity) {
  Vector<dist_t> radius_vector = target_position - charge_position;
  return radius_vector * kColoumbConstant * charge / permutivity /
         radius_vector.SqrLen();
}

inline Vector<potential_t> CountElectronsPotential(Vector<vel_t> velocity) {
  return velocity * velocity.SqrLen() * kElectronMass / 2 / kElementaryCharge;
}
