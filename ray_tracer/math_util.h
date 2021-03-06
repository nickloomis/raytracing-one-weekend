#ifndef RAY_TRACER_MATH_UTIL_H_
#define RAY_TRACER_MATH_UTIL_H_

#include "third_party/eigen3/Eigen/Core"

namespace math_util {

// Singleton to manage a default RNG.
class Random {
 public:
  // Returns a pointer to the global Random instance.
  static Random* Default();

  // Returns a value in [0, 1).
  double Uniform();

 private:
  Random();
  static Random* instance_;
  std::mt19937 generator_;
  std::uniform_real_distribution<> uniform_{0.0, 1.0};
};

// Returns a point randomly distributed on the surface of a unit sphere.
Eigen::Vector3d RandomOnUnitSphere();

// Returns a point randomly distributed in a disk of unit radius in the
// (x, y) plane.
Eigen::Vector3d RandomInUnitDisk();

// Returns the product of Uniform() * Uniform().
double RandomProduct();

template <typename T>
T DegToRad(T angle_deg) { return M_PI * angle_deg / 180.0; }

}  // namespace math_util

#endif  // RAY_TRACER/MATH_UTIL_H_
