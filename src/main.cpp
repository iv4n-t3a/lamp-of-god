#include <iostream>

#include "phys.hpp"
#include "recttube.hpp"

const dist_t kWidth = 0.002;
const dist_t kHeight = 0.0001;
const dist_t kAnodeWidth = kWidth / 100;
const dist_t kCatodeWidth = kHeight / 100;
const current_t kCurrent = kElementaryCharge * 10000;
const field_t kField = 1e-100;

const double kIterations = 100000;
const double kDeltaTime = 1 / kIterations;

int main() {
  RectangleTube tube(kWidth, kHeight, kAnodeWidth, kCatodeWidth, kCurrent,
                     kField);

  for (size_t i = 0; i < kIterations; ++i) {
    tube.NewFrame(kDeltaTime);
    std::cout << tube.GetElectricityField({0, kHeight / 2}).SqrLen() << '\n';
  }
}
