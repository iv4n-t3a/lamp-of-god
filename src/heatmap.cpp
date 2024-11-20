#include "heatmap.hpp"

void HeatMap::Render() {
  for (int x = 0; x < size_.x; ++x) {
    for (int y = 0; y < size_.y; ++y) {
      DrawSquare(x, y);
    }
  }
}

void HeatMap::DrawSquare(int x, int y) {
  Vector<double> tube_pos = {scale_ * static_cast<double>(x),
                             scale_ * static_cast<double>(y)};

  Vector<double> field = tube_->GetElectricityField(tube_pos);

  std::ignore = field;
}
