#ifndef RAY_TRACER_IMAGE_UTIL_H_
#define RAY_TRACER_IMAGE_UTIL_H_

#include "third_party/eigen3/Eigen/Core"

namespace image_util {

double LinearRgbToSrgb(double value);

Eigen::Vector3d LinearRgbToSrgb(const Eigen::Vector3d& linear_rgb);

}  // namespace image_util

#endif  // RAY_TRACER_IMAGE_UTIL_H_