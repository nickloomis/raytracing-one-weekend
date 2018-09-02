#ifndef RAY_TRACER_HITABLE_H_
#define RAY_TRACER_HITABLE_H_

#include "ray_tracer/ray.h"
#include "third_party/eigen3/Eigen/Core"

namespace trace {

struct HitRecord {
  double t;
  Eigen::Vector3d point;
  Eigen::Vector3d normal;
};

// Defines an abstract object which can be hit by a ray.
class Hitable {
 public:
  // Returns true and fills in the hit if the ray hits the surface with a t
  // between tmin and tmax.
  virtual bool Hit(const Ray& ray, double t_min, double t_max, HitRecord* hit)
   const = 0;
};

}  // namespace trace

#endif  // RAY_TRACER_HITABLE_H_