#include <fstream>
#include <iostream>

#include "diode.hpp"
#include "observers.hpp"
#include "phys.hpp"

const dist_t kWidth = 0.023;
const dist_t kHeight = 0.03;
const dist_t kCathodeArea = 0.0004;
const current_t kVoltage = 10;
const temp_t kTemp = 2200;

const delay_t kIterations = 10;
const delay_t kDeltaTime = 1e-7;

const physical_t kElectronPerCharge = 100000;

const size_t kCathodeSegments = 100;
const dist_t kPotentialGridGap = kHeight / kCathodeSegments;

const double kHeatmapScale = 10000;

const std::pair<size_t, size_t> kHeatmapResolution = {kWidth * kHeatmapScale,
                                                      kHeight* kHeatmapScale};

const double kCVCMinVoltage = 0.0002;
const double kCVCMaxVoltage = 0.5;
const double kCVCStep = 0.05;
const size_t kCVCIterations = 10;

void BuildCVC(std::string path, voltage_t min, voltage_t max, voltage_t step,
              size_t iterations) {
  std::ofstream file(path);

  for (voltage_t volt = min; volt <= max; volt += step) {
    Diode tube(kWidth, kHeight, kCathodeArea, kTemp, volt, kTungsten,
               kPotentialGridGap, kElectronPerCharge);

    for (size_t i = 0; i < iterations; ++i) {
      tube.NewFrame(kDeltaTime);
    }

    file << volt << ' ' << tube.GetCurrent() << '\n';
  }
}

int main() {
  std::cout << "Solving Poisson..." << std::endl;

  Diode tube(kWidth, kHeight, kCathodeArea, kTemp, kVoltage, kTungsten,
             kPotentialGridGap, kElectronPerCharge);

  std::cout << "OK" << std::endl;

  AveragePotentialObserver(&tube, ".", kHeatmapResolution);

  std::cout << "Running simulation..." << std::endl;

  for (size_t i = 0; i < kIterations; ++i) {
    tube.NewFrame(kDeltaTime);
  }

  std::cout << "OK" << std::endl;

  std::cout << "Building current–voltage characteristic..." << std::endl;

  BuildCVC("data", kCVCMinVoltage, kCVCMaxVoltage, kCVCStep, kCVCIterations);

  std::cout << "OK" << std::endl;
}
