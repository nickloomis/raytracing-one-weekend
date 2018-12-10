#include "ray_tracer/math_util.h"

#include <cmath>
#include <random>

namespace math_util {

Random* Random::Default() {
  if (!instance_){
    instance_ = new Random;
  }
  return instance_;
}

double Random::Uniform() {
  return uniform_(generator_);
}

Random::Random() {
  std::random_device random_device;
  generator_ = std::mt19937(random_device());
}

Random *Random::instance_ = nullptr;

// Implementation based on a loomsci blog post:
// https://loomsci.wordpress.com/2015/03/14/generating-random-directions/
Eigen::Vector3d RandomOnUnitSphere() {
    double azimuth = 2 * M_PI * Random::Default()->Uniform();
    double altitude = std::acos(2 * Random::Default()->Uniform() - 1);
    // convert polar to cartesian
    return Eigen::Vector3d(std::cos(azimuth) * std::cos(altitude),
      std::sin(azimuth) * std::cos(altitude), std::sin(altitude));
    // TODO(nloomis): unit tests!!!!
}

Eigen::Vector3d RandomInUnitDisk() {
  double theta = 2 * M_PI * Random::Default()->Uniform();
  double radius = sqrt(Random::Default()->Uniform());
  return Eigen::Vector3d(radius * std::cos(theta), radius * std::sin(theta), 0);
}

}  // namespace math_util
