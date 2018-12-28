#ifndef RAY_TRACER_EIGEN_RGB_IMAGE_WRAPPER_H_
#define RAY_TRACER_EIGEN_RGB_IMAGE_WRAPPER_H_

#include "third_party/eigen3/Eigen/Core"

namespace image_util {

class EigenRgbImageWrapper {
 public:
  EigenRgbImageWrapper(int nx, int ny);

  inline int nx() const { return nx_; }
  inline int ny() const { return ny_; }

  // Access the (x, y) pixel in the image.
  Eigen::Vector3d& operator()(int x, int y);
  const Eigen::Vector3d& operator()(int x, int y) const;

 private:
  EigenRgbImageWrapper() = delete;

  const int nx_;
  const int ny_;
  std::vector<Eigen::Vector3d> pixel_data_;
};

}  // namespace image_util

#endif  // RAY_TRACER_EIGEN_RGB_IMAGE_WRAPPER_H_