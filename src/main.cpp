#include <iostream>

#include "diode.hpp"
#include "phys.hpp"

const dist_t kWidth = 0.03;
const dist_t kHeight = 0.01;
const dist_t kCathodeArea = 0.01 * 0.01;
const current_t kVoltage = 100;
const temp_t kTemp = 2200;

const delay_t kIterations = 10000;
const delay_t kDeltaTime = 1e-7;

const physical_t kElectronPerCharge = 100000;

const size_t kCatodeSegments = 1000;
const dist_t kPotentialGridGap = kHeight / kCatodeSegments;

int main() {
  std::cout << "Solving Poisson..." << std::endl;

  Diode tube(kWidth, kHeight, kCathodeArea, kTemp, kTungsten, kPotentialGridGap,
             kElectronPerCharge);

  tube.SetCathodePotential(kVoltage);

  std::cout << "OK" << std::endl;

  std::cout << "Running simulation..." << std::endl;

  for (size_t i = 0; i < kIterations; ++i) {
    tube.NewFrame(kDeltaTime);
  }

  std::cout << "OK" << std::endl;
}
