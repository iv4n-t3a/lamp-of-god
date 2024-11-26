#include "observers.hpp"

#include <algorithm>
#include <fstream>

PotentialObserver::PotentialObserver(Tube* tube,
  const std::string& directory_path,
  const std::pair<int, int>& resolution,
  std::vector<delay_t> offsets)
    : TubeObserver(tube),
      directory_path_(directory_path),
      offsets_(offsets),
      width_(resolution.first),
      height_(resolution.second)
{
  std::sort(offsets_.begin(), offsets_.end());
}

void PotentialObserver::NewFrame(delay_t delta_time) {
  time_passed_ += delta_time;
  if (offset_index_ < std::size(offsets_) and time_passed_ >= offsets_[offset_index_]) {
    std::ofstream output_file(directory_path_ + '/' + std::to_string(time_passed_) + ".txt");
    std::vector<std::vector<Vector<potential_t>>> potentials;

    auto dimensions = tube_->GetDimensions();
    auto tube_width = dimensions.first;
    auto tube_height = dimensions.second;
    for (int i = 0; i < height_ - 1; i++) {
      potentials.push_back(std::vector<Vector<potential_t>>());
      for (int j = 0; j < width_ - 1; j++) {
        potentials.back().push_back(Vector(j * tube_width / (width_ - 1), i * tube_height / (height_ - 1)));
      }
      potentials.back().push_back(Vector(tube_width, i * tube_height / (height_ - 1)));
    }
    potentials.push_back(std::vector<Vector<potential_t>>());
    for (int j = 0; j < width_ - 1; j++) {
      potentials.back().push_back(Vector(j * tube_width / (width_ - 1), tube_height));
    }
    potentials.back().push_back(Vector(tube_width, tube_height));

    for (auto line : potentials) {
      for (auto value : line) {
        output_file << value.Len() << ' ';
      }
      output_file << '\n';
    }

    offset_index_++;
  }
}

