#include "sound.hpp"

SoundTrack::SoundTrack(double rate, double time)
    : rate_(rate), amplitudes_(time / rate) {}

SoundTrack::SoundTrack(std::string filepath) {}

void SoundTrack::Normalize() {}

void SoundTrack::WriteToFile(std::string path) {}

double SoundTrack::GetAmplitude(double time) {
  return amplitudes_[time / rate_];
}
void SoundTrack::SetAmplitude(double time, double amplitude) {
  amplitudes_[time / rate_] = amplitude;
}

void SoundTrack::ExtandTime(double new_time) {
  size_t new_size = new_time / rate_;
  if (new_size > amplitudes_.size()) {
    amplitudes_.resize(new_size);
  }
}
