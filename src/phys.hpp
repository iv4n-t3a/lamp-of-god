#pragma once

#include "math.hpp"

using default_physical_t = long double;
using charge_t = default_physical_t;
using dist_t = default_physical_t;
using mass_t = default_physical_t;
using vel_t = default_physical_t;
using force_t = default_physical_t;
using field_t = default_physical_t;
using accel_t = default_physical_t;
using current_t = default_physical_t;
using delay_t = default_physical_t;

const charge_t kElementaryCharge = 1.6E-19;
const mass_t kElectronMass = 9.1E-31;
const force_t kColoumbConstant = 8.99E9;

inline Vector<force_t> ElectricForce(Vector<dist_t> el1, Vector<dist_t> el2) {
  force_t val = kColoumbConstant * kElementaryCharge * kElementaryCharge /
                el1.SqrDist(el1);
  return (el1 - el2).Normalized() * val;
}

inline Vector<field_t> ElectricField(Vector<dist_t> pos, Vector<dist_t> elc) {
  field_t val = kColoumbConstant * kElementaryCharge / pos.SqrDist(elc);
  return (pos - elc).Normalized() * val;
}
