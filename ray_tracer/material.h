#ifndef RAY_TRACER_MATERIAL_H_
#define RAY_TRACER_MATERIAL_H_

#include <memory>

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

class Dielectric : public Material {
 public:
  Dielectric(double refractive_index);

  bool Scatter(const Ray& ray_in,
               const HitRecord& hit,
               Eigen::Vector3d* attenuation,
               Ray* ray_out) const override;
 private:
  const double refractive_index_;
};

class Lambertian : public Material {
 public:
  Lambertian(const Eigen::Vector3d& albedo);

  // Returns a new Lambertian material with a randomly chosen color.
  static std::shared_ptr<Lambertian> CreateRandom();

  bool Scatter(const Ray& ray_in,
               const HitRecord& hit,
               Eigen::Vector3d* attenuation,
               Ray* ray_out) const override;

 private:
  const Eigen::Vector3d albedo_;
};

class Metal : public Material {
 public:
  // "fuzziness" is a measure of microfacet randomness modelled by the metallic
  // material. A fuzziness of 0 is a perfect mirror which follows the underlying
  // shape, while a fuzziness of 1 gives an approximately diffuse orientation of
  // the microfacets. Fuzziness of (0, 1) is allowed.
  Metal(const Eigen::Vector3d& albedo, double fuzziness);

  // Returns a new Metal material with a randomly chosen color and fuzziness.
  static std::shared_ptr<Metal> CreateRandom();

  bool Scatter(const Ray& ray_in,
               const HitRecord& hit,
               Eigen::Vector3d* attenuation,
               Ray* ray_out) const override;

 private:
  const Eigen::Vector3d albedo_;
  const double fuzziness_;
};

}  // namespace trace

#endif  // RAY_TRACER_MATERIAL_H_