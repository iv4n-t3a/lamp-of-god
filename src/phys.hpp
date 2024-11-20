#pragma once

#include "math.hpp"

const double kElementaryCharge = 1.6E-19;
const double kElectronMass = 9.1E-31;
const double kColoumbConstant = 8.99E9;

inline Vector<double> ElectricForce(Vector<double> el1, Vector<double> el2) {
  double val = kColoumbConstant * kElementaryCharge * kElementaryCharge /
               el1.SqrDist(el1);
  return (el1 - el2).Normalize() * val;
}

inline Vector<double> ElectricField(Vector<double> pos, Vector<double> elc) {
  double val = kColoumbConstant * kElementaryCharge / pos.SqrDist(elc);
  return (pos - elc).Normalize() * val;
}
