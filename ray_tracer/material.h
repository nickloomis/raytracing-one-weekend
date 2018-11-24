#ifndef RAY_TRACER_MATERIAL_H_
#define RAY_TRACER_MATERIAL_H_

#include "ray_tracer/hitable.h"
#include "ray_tracer/ray.h"
#include "third_party/eigen3/Eigen/Core"

namespace trace {

class Material {
 public:
  // Returns true if the ray is scattered or false if it is absorbed. The
  // attenuation vector gives the transmittance of each color; a value of 1
  // indicates 100% transmittance.
  virtual bool Scatter(const Ray& ray_in, const HitRecord& hit,
                       Eigen::Vector3d* attenuation, Ray* ray_out) const = 0;
};

class Lambertian : public Material {
 public:
  Lambertian(const Eigen::Vector3d& albedo);

  bool Scatter(const Ray& ray_in,
               const HitRecord& hit,
               Eigen::Vector3d* attenuation,
               Ray* ray_out) const override;

 private:
  const Eigen::Vector3d albedo_;
};

class Metal : public Material {

};

}  // namespace trace

#endif  // RAY_TRACER_MATERIAL_H_