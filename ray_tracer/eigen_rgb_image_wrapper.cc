#include "ray_tracer/eigen_rgb_image_wrapper.h"

namespace image_util {

EigenRgbImageWrapper::EigenRgbImageWrapper(int nx, int ny)
    : nx_(nx), ny_(ny) {
  pixel_data_.reserve(nx * ny);
  for (int i = 0; i < nx * ny; ++i) {
    pixel_data_[i] = Eigen::Vector3d::Zero();
  }
}

Eigen::Vector3d& EigenRgbImageWrapper::operator()(int x, int y) {
  // TODO(nloomis): assert if (x, y) out of range
  return pixel_data_[y * nx_ + x]; 
}

const Eigen::Vector3d& EigenRgbImageWrapper::operator()(int x, int y) const {
  // TODO(nloomis): assert if (x, y) out of range
  return pixel_data_[y * nx_ + x]; 
}

}  // namespace image_util