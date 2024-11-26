#pragma once

#include "math.hpp"

const double kElementaryCharge = 1.6E-19;
const double kElectronMass = 9.1E-31;
const double kColoumbConstant = 8.99E9;

inline Vector<double> ElectricForce(Vector<double> el1, Vector<double> el2) {
  long double val = kColoumbConstant * kElementaryCharge * kElementaryCharge;
  val /= static_cast<long double>(el1.SqrDist(el1));
  return (el1 - el2).Normalized() * val;
}

inline Vector<double> ElectricField(Vector<double> pos, Vector<double> elc) {
  long double val = kColoumbConstant * kElementaryCharge;
  val /= static_cast<long double>(pos.SqrDist(elc));
  return (pos - elc).Normalized() * val;
}
