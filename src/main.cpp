#include <iostream>

#include "diode.hpp"
#include "observers.hpp"
#include "phys.hpp"

const dist_t kWidth = 0.03;
const dist_t kHeight = 0.01;
const dist_t kCathodeArea = 0.01 * 0.01;
const current_t kVoltage = -10;
const temp_t kTemp = 2200;

const delay_t kIterations = 100;
const delay_t kDeltaTime = 1e-7;

const physical_t kElectronPerCharge = 100000;

const size_t kCatodeSegments = 1000;
const dist_t kPotentialGridGap = kHeight / kCatodeSegments;

const double kHeatmapScale = 10000;

const std::pair<size_t, size_t> kHeatmapResolution = {kWidth * kHeatmapScale,
                                                      kHeight* kHeatmapScale};

int main() {
  std::cout << "Solving Poisson..." << std::endl;

  Diode tube(kWidth, kHeight, kCathodeArea, kTemp, kVoltage, kTungsten, kPotentialGridGap,
             kElectronPerCharge);

  std::cout << "OK" << std::endl;

  AveragePotentialObserver average_potential_observer(&tube, "/home/ivan/codes/lamp-of-god/data/file.txt",
                                                      kHeatmapResolution);

  std::cout << "Running simulation..." << std::endl;

  for (size_t i = 0; i < kIterations; ++i) {
    tube.NewFrame(kDeltaTime);
    std::cout << tube.GetCurrent() << std::endl;
  }

  std::cout << "OK" << std::endl;
}
