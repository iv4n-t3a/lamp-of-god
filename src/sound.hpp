#pragma once

#include <string>
#include <vector>

class SoundTrack {
 public:
  SoundTrack(double rate, double time);
  SoundTrack(std::string filepath);
  SoundTrack(const SoundTrack&) = default;
  void WriteToFile(std::string path);

  void Normalize();
  double GetAmplitude(double time);
  void SetAmplitude(double time, double amplitude);

  void ExtandTime(double new_time);

 private:
  double rate_;
  std::vector<double> amplitudes_;
};
