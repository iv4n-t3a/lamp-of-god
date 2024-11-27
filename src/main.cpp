#include <iostream>

#include "diode.hpp"
#include "phys.hpp"

const dist_t kWidth = 0.03;
const dist_t kHeight = 0.01;
const dist_t kAnodeWidth = kWidth / 100;
const dist_t kCatodeWidth = kHeight / 100;
const current_t kVoltage = 9;
const temp_t kTemp = 1000;

const delay_t kIterations = 100000;
const delay_t kDeltaTime = 1 / kIterations;

const size_t kElectronPerCharge = 10;

const size_t kCatodeSegments = 1000;
const dist_t kPotentialGridGap = kHeight / kCatodeSegments;

int main() {
  Diode tube(kWidth, kHeight, kAnodeWidth, kCatodeWidth, kTemp, kVoltage,
             kWolfram, kPotentialGridGap, kElectronPerCharge);

  for (size_t i = 0; i < kIterations; ++i) {
    tube.NewFrame(kDeltaTime);
    std::cout << tube.GetElectricityField({0, kHeight / 2}).SqrLen() << '\n';
  }
}
