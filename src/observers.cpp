#include "observers.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

PotentialObserver::PotentialObserver(Tube* tube,
                                     const std::string& directory_path,
                                     const std::pair<int, int>& resolution,
                                     std::vector<delay_t> offsets)
    : TubeObserver(tube),
      directory_path_(directory_path),
      offsets_(offsets),
      width_(resolution.first),
      height_(resolution.second) {
  std::sort(offsets_.begin(), offsets_.end());
}

void PotentialObserver::NewFrame(delay_t delta_time) {
  time_passed_ += delta_time;
  if (offset_index_ < std::size(offsets_) and
      time_passed_ >= offsets_[offset_index_]) {
    std::ofstream output_file(directory_path_ + '/' +
                              std::to_string(time_passed_) + ".txt");
    std::vector<std::vector<potential_t>> potentials;

    auto dimensions = tube_->GetDimensions();
    auto tube_width = dimensions.first;
    auto tube_height = dimensions.second;
    for (int i = 0; i < height_ - 1; i++) {
      potentials.push_back(std::vector<potential_t>());
      for (int j = 0; j < width_ - 1; j++) {
        potentials.back().push_back(tube_->GetPotential(
            {j * tube_width / (width_ - 1), i * tube_height / (height_ - 1)}));
      }
      potentials.back().push_back(
          tube_->GetPotential({tube_width, i * tube_height / (height_ - 1)}));
    }
    potentials.push_back(std::vector<potential_t>());
    for (int j = 0; j < width_ - 1; j++) {
      potentials.back().push_back(
          tube_->GetPotential({j * tube_width / (width_ - 1), tube_height}));
    }
    potentials.back().push_back(tube_->GetPotential({tube_width, tube_height}));

    for (auto line : potentials) {
      for (auto value : line) {
        output_file << value << ' ';
      }
      output_file << '\n';
    }

    offset_index_++;
  }
}

AveragePotentialObserver::AveragePotentialObserver(
    Tube* tube, const std::string& file_path,
    const std::pair<int, int>& resolution)
    : TubeObserver(tube),
      kFilePath(file_path),
      width_(resolution.first),
      height_(resolution.second) {
  for (int i = 0; i < height_; i++) {
    potentials_.push_back(std::vector<potential_t>());
    for (int j = 0; j < width_; j++) {
      potentials_.back().emplace_back(0);
    }
  }
}

void AveragePotentialObserver::NewFrame(delay_t delta_time) {
  std::ignore = delta_time;
  iterations_count_++;

  auto dimensions = tube_->GetDimensions();
  auto tube_width = dimensions.first;
  auto tube_height = dimensions.second;
  for (int i = 0; i < height_ - 1; i++) {
    for (int j = 0; j < width_ - 1; j++) {
      potentials_[i][j] += tube_->GetPotential(
          {j * tube_width / (width_ - 1), i * tube_height / (height_ - 1)});
    }
    potentials_[i].back() +=
        tube_->GetPotential({tube_width, i * tube_height / (height_ - 1)});
  }
  for (int j = 0; j < width_ - 1; j++) {
    potentials_.back()[j] +=
        tube_->GetPotential({j * tube_width / (width_ - 1), tube_height});
  }
  potentials_.back().back() += tube_->GetPotential({tube_width, tube_height});
}

AveragePotentialObserver::~AveragePotentialObserver() {
  std::cout << kFilePath << std::endl;
  std::ofstream output_file(kFilePath);
  // std::ofstream output_file("/home/ivan/codes/lamp-of-god/data/file.txt");
  for (size_t i = 0; i < potentials_.size(); i++) {
    for (size_t j = 0; j < potentials_[i].size(); j++) {
      output_file << potentials_[i][j] / iterations_count_ << ' ';
    }
    output_file << '\n';
  }
}
