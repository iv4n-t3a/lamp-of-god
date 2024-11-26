#include <iostream>

#include "phys.hpp"
#include "recttube.hpp"

const double kWidth = 0.002;
const double kHeight = 0.0001;
const double kField = 1e-100;
const double kCurent = kElementaryCharge * 10000;
const double kAnodeWidth = kWidth / 100;
const double kCatodeWidth = kHeight / 100;

const double kIterations = 100000;
const double kDeltaTime = 1 / kIterations;

int main() {
  RectangleTube tube(kWidth, kHeight, kCurent, kField, kAnodeWidth,
                     kCatodeWidth);

  for (size_t i = 0; i < kIterations; ++i) {
    tube.NewFrame(kDeltaTime);
    std::cout << tube.GetElectricityField({0, kHeight / 2}).SqrLen()
              << '\n';
  }
}
