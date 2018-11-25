#ifndef RAY_TRACER_RAY_H_
#define RAY_TRACER_RAY_H_

#include "third_party/eigen3/Eigen/Core"

namespace trace {

class Ray {
 public:
  Ray() {}

  // The direction vector does NOT need to have unit length.
  Ray(const Eigen::Vector3d& origin, const Eigen::Vector3d& direction)
      : origin_(origin), direction_(direction) {}

  inline const Eigen::Vector3d& origin() const {
    return origin_;
  }

  inline const Eigen::Vector3d& direction() const {
    return direction_;
  }

  // Returns the point which is "t" multiples of the ray direction away from the
  // ray origin. If direction is unit-length, t is equal to the distance along
  // the ray.
  inline Eigen::Vector3d point_at_parameter(double t) const {
    return origin_ + t * direction_;
  }

 private:
  Eigen::Vector3d origin_;
  Eigen::Vector3d direction_;
};

}  // namespace trace

#endif  // RAY_TRACER_RAY_H_