#include "ray_tracer/progress_bar.h"

#include <iostream>

namespace trace {

ProgressBar::ProgressBar(int width)
    : width_(width), current_work_units_(0), is_first_update_(true) {}

void ProgressBar::Start() {
  Update(0);
}

void ProgressBar::Update(double fraction_completed) {
  int new_work_units = static_cast<int>(width_ * fraction_completed);
  if (is_first_update_ | (new_work_units != current_work_units_)) {
    is_first_update_ = false;
    current_work_units_ = new_work_units;
    std::cout << "[";
    for (int i = 0; i < current_work_units_; ++i) {
      std::cout << "=";
    }
    for (int i = current_work_units_; i < width_; ++i) {
      std::cout << " ";
    }
    std::cout << "] " << 100 * fraction_completed << "%     \r";
    std::cout.flush();
  }
}

void ProgressBar::Finish() {
  Update(1);
  std::cout << "\n";
  std::cout.flush();
}

}  // namespace trace