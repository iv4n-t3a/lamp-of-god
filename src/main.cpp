#include <iostream>

#include "diode.hpp"
#include "phys.hpp"

const dist_t kWidth = 0.03;
const dist_t kHeight = 0.01;
const dist_t kAnodeWidth = kWidth / 100;
const dist_t kCatodeWidth = kHeight / 100;
const current_t kVoltage = 100;
const temp_t kTemp = 2200;

const delay_t kIterations = 10000;
const delay_t kDeltaTime = 1e-7;

const physical_t kElectronPerCharge = 10000;

const size_t kCatodeSegments = 1000;
const dist_t kPotentialGridGap = kHeight / kCatodeSegments;

int main() {
  std::cout << CurrentDensity(kTemp, kTungsten) << std::endl;

  Diode tube(kWidth, kHeight, kAnodeWidth, kCatodeWidth, kTemp, kVoltage,
             kTungsten, kPotentialGridGap, kElectronPerCharge);

  for (size_t i = 0; i < kIterations; ++i) {
    tube.NewFrame(kDeltaTime);
    std::cout << tube.GetPotential({0, kHeight / 2}).x << ' '
              << tube.GetPotential({0, kHeight / 2}).y << ' '
              << tube.CountCharges() << '\n';
  }
}
