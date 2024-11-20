#include "plots.hpp"

#include <fstream>

FieldObserver::FieldObserver(Tube *tube, std::vector<Vector<double>> positions, std::string file_path)
    : TubeObserver(tube),
    positions_(positions),
    file_(file_path) {
    file_ << positions.size() << std::endl;
}

void FieldObserver::NewFrame(double delta_time) {
    time_ += delta_time;

    for (size_t i = 0; i < positions_.size(); i++) {
        auto field = tube_->GetElectricityField(positions_[i]);
        file_ << i << ' ' << time_ << ' ' << field.Len() << std::endl;
    }
}
