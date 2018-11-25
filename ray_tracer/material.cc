#include "ray_tracer/material.h"
#include "ray_tracer/math_util.h"

namespace {

// Returns the reflection direction of a ray with a given incident direction
// onto a surface with a given normal.
Eigen::Vector3d ReflectionDirection(const Eigen::Vector3d& incident,
  const Eigen::Vector3d& normal) {
  return incident - 2 * incident.dot(normal) * normal;
}

double ClipToUnit(double v) {
  return v > 1.0 ? 1.0 : (v < 0.0 ? 0.0 : v);
}

}  // namespace

namespace trace {

Lambertian::Lambertian(const Eigen::Vector3d& albedo) : albedo_(albedo) {}

bool Lambertian::Scatter(const Ray& ray_in, const HitRecord& hit,
                         Eigen::Vector3d* attenuation, Ray* ray_out) const {
  const Eigen::Vector3d target = hit.point + hit.normal +
      math_util::RandomOnUnitSphere();
  const Eigen::Vector3d direction = target - hit.point;
  *ray_out = Ray{hit.point, direction};
  *attenuation = albedo_;
  return true;
}

Metal::Metal(const Eigen::Vector3d& albedo, double fuzziness) 
    : albedo_(albedo),
      fuzziness_(ClipToUnit(fuzziness)) {}

bool Metal::Scatter(const Ray& ray_in, const HitRecord& hit,
  Eigen::Vector3d* attenuation, Ray* ray_out) const {
  const Eigen::Vector3d reflection_direction =
      ReflectionDirection(ray_in.direction(), hit.normal);
  const Eigen::Vector3d direction = reflection_direction + fuzziness_ *
      math_util::RandomOnUnitSphere();
  *ray_out = Ray{hit.point, direction};
  *attenuation = albedo_;
  return direction.dot(hit.normal) > 0;
}

}  // namespace trace