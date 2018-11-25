#ifndef RAY_TRACER_SPHERE_H_
#define RAY_TRACER_SPHERE_H_

#include <memory>

#include "ray_tracer/hitable.h"
#include "ray_tracer/ray.h"
#include "third_party/eigen3/Eigen/Core"

namespace trace {

class Material;

class Sphere : public Hitable {
 public:
  Sphere(const Eigen::Vector3d& center, double radius,
         std::shared_ptr<Material> material);

  bool Hit(const Ray& ray, double tmin, double tmax, HitRecord* hit) const
   override;

 private:
  const Eigen::Vector3d center_;
  const double radius_;
  std::shared_ptr<Material> material_;
};

}  // namespace trace

#endif  // RAY_TRACER_SPHERE_H_