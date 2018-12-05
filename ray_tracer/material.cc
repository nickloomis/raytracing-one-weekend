#include "ray_tracer/material.h"
#include "ray_tracer/math_util.h"

namespace {

// Returns the reflection direction of a ray with a given incident direction
// onto a surface with a given normal.
Eigen::Vector3d ReflectionDirection(const Eigen::Vector3d& incident,
                                    const Eigen::Vector3d& normal) {
  return incident - 2 * incident.dot(normal) * normal;
}

bool RayRefracts(const Eigen::Vector3d& incident_direction,
                 const Eigen::Vector3d& normal,
                 double ni_over_nt,
                 Eigen::Vector3d* refracted_direction) {
  Eigen::Vector3d incident_unit = incident_direction.normalized();
  double dt = incident_unit.dot(normal);
  double discriminant = 1 - ni_over_nt * ni_over_nt * (1 - dt * dt);
  if (discriminant > 0) {
    *refracted_direction = ni_over_nt * (incident_unit - normal * dt) -
        normal * sqrt(discriminant);
    return true;
  }
  return false;
}

// Returns the Schlick approximation of the probability of a Fresnel reflection. 
double Schlick(double cosine, double refractive_index) {
  // Reflection coefficient at zero degrees.
  double r0 = (1.0 - refractive_index) / (1 + refractive_index);
  // Power of reflection.
  double R0 = r0 * r0;
  // Taylor approximation for off-axis incidence angles.
  return R0 + (1 - R0) * pow((1 - cosine), 5);
}

double ClipToUnit(double v) {
  return v > 1.0 ? 1.0 : (v < 0.0 ? 0.0 : v);
}

}  // namespace

namespace trace {

Dielectric::Dielectric(double refractive_index)
    : refractive_index_(refractive_index) {}

bool Dielectric::Scatter(const Ray& ray_in,
                         const HitRecord& hit,
                         Eigen::Vector3d* attenuation,
                         Ray* ray_out) const {
  // Assume (for now) that there is no attenuation which occurs when a ray
  // scatters from a dielectric (eg, the index is always real-valued).
  *attenuation = Eigen::Vector3d::Ones();
  Eigen::Vector3d outward_normal;
  // Ratio of incident index over transmitted index
  double ni_over_nt;
  double cosine;
  // Determine whether the ray is inside or outside the physical object, and set
  // the refraction plane and indices. Note that the alternate refractive index
  // is alway 1, so that the objects can only refract to/from air.
  if (ray_in.direction().dot(hit.normal) > 0) {
    // Ray is inside the material.
    outward_normal = -hit.normal;
    ni_over_nt = refractive_index_;
    cosine = refractive_index_ * ray_in.direction().dot(hit.normal) /
        ray_in.direction().norm();
  } else {
    // Ray is outside the material.
    outward_normal = hit.normal;
    ni_over_nt = 1.0 / refractive_index_;
    cosine = -ray_in.direction().dot(hit.normal) / ray_in.direction().norm();
  }

  // Find out whether refraction could occur and the probability of a
  // reflection (eg, Fresnel reflection).
  Eigen::Vector3d refraction_direction;
  double reflection_probability;
  if (RayRefracts(ray_in.direction(), outward_normal, ni_over_nt,
                  &refraction_direction)) {
    reflection_probability = Schlick(cosine, refractive_index_);
  } else {
    reflection_probability = 1.0;
  }

  if (math_util::Random::Default()->Uniform() < reflection_probability) {
    // Reflection, by either Fresnel or TIR.
    Eigen::Vector3d reflection_direction =
      ReflectionDirection(ray_in.direction(), hit.normal);
    *ray_out = Ray(hit.point, reflection_direction);
    return true;
  }
  // Refraction.
  *ray_out = Ray(hit.point, refraction_direction);
  return true;
}  

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