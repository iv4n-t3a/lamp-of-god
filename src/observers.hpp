#pragma once

#include <string>
#include <vector>

#include "tube.hpp"

class PotentialObserver : public TubeObserver {
 public:
  explicit PotentialObserver(Tube* tube, const std::string& file_path,
                             const std::pair<int, int>& resolution, std::vector<delay_t> offsets);

  void NewFrame(delay_t delta_time) override;

 protected:
  const std::string& file_path_;
  delay_t time_passed_ = 0;
  std::vector<delay_t> offsets_;
  size_t offset_index_ = 0;
  int width_;
  int height_;
};
