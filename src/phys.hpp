#pragma once

#include "math.hpp"

const double kElementaryCharge = 1.6E-19;
const double kColoumbConstant = 8.99E9;

double ElectricForce(Vector<double> el1, Vector<double> el2) {
  return kColoumbConstant * kElementaryCharge * kElementaryCharge /
         el1.SqrDist(el1);
}
