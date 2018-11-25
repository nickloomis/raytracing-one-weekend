#include "ray_tracer/sphere.h"

namespace trace {

Sphere::Sphere(const Eigen::Vector3d& center, double radius,
               std::shared_ptr<Material> material)
  : center_(center), radius_(radius), material_(material) {}

bool Sphere::Hit(const Ray& ray, double tmin, double tmax, HitRecord* hit)
 const {
  Eigen::Vector3d relative_center = ray.origin() - center_;
  double a_coefficient = ray.direction().dot(ray.direction());
  double b_coefficient = 2.0 * relative_center.dot(ray.direction());
  double c_coefficient = relative_center.squaredNorm() - radius_ * radius_;
  double discriminant = b_coefficient * b_coefficient - 
      4 * a_coefficient * c_coefficient;
  if (discriminant < 0) {
    return false;
  }
  double root1 = (-b_coefficient - sqrt(discriminant)) / (2 * a_coefficient);
  if (root1 > tmin && root1 < tmax) {
    hit->t = root1;
    hit->point = ray.point_at_parameter(root1);
    hit->normal = (hit->point - center_) / radius_;
    hit->material = material_.get();
    return true;
  }
  double root2 = (-b_coefficient + sqrt(discriminant)) / (2 * a_coefficient);
  if (root2 > tmin && root2 < tmax) {
    hit->t = root2;
    hit->point = ray.point_at_parameter(root2);
    hit->normal = (hit->point - center_) / radius_;
    hit->material = material_.get();
    return true;
  }
  return false;
}

}  // namespace trace