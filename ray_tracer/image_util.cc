#include "ray_tracer/image_util.h"

namespace image_util {

// https://en.wikipedia.org/wiki/SRGB#The_sRGB_transfer_function_(%22gamma%22)
static double kSrgbGamma = 2.4;
static double kSrgbInverseGamma = 1.0 / kSrgbGamma;
static double kSrgbA = 0.055;
static double kSrgbLinearLimit = 0.0031308;
static double kSrgbLinearRate = 12.92;

double LinearRgbToSrgb(double value) {
  return value <= kSrgbLinearLimit ?
      kSrgbLinearRate * value :
      (1 + kSrgbA) * pow(value, kSrgbInverseGamma) - kSrgbA;
}

Eigen::Vector3d LinearRgbToSrgb(const Eigen::Vector3d& linear_rgb) {
  return Eigen::Vector3d(LinearRgbToSrgb(linear_rgb[0]),
                         LinearRgbToSrgb(linear_rgb[1]),
                         LinearRgbToSrgb(linear_rgb[2]));
}

}  // namespace image_util