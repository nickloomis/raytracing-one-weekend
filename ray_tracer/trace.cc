#include <iostream>

#include "ray_tracer/ray.h"
#include "third_party/eigen3/Eigen/Core"

namespace trace {

double HitSphere(const Eigen::Vector3d& center, double radius, const Ray& ray) {
  Eigen::Vector3d relative_center = ray.origin() - center;
  double a_coefficient = ray.direction().dot(ray.direction());
  double b_coefficient = 2.0 * relative_center.dot(ray.direction());
  double c_coefficient = relative_center.squaredNorm() - radius * radius;
  double discriminant = b_coefficient * b_coefficient - 
      4 * a_coefficient * c_coefficient;
  if (discriminant < 0) {
    return -1;  // sentinal for "the ray didn't hit", an infeasible distance.
  }
  return (-b_coefficient - sqrt(discriminant))/(2 * a_coefficient);
}

Eigen::Vector3d color(const Ray& ray) {
  Eigen::Vector3d sphere_center(0, 0, -1);
  double t = HitSphere(sphere_center, 0.5, ray);
  if (t > 0) {
    Eigen::Vector3d sphere_normal = 
      (ray.point_at_parameter(t) - sphere_center).normalized();
    // Remap the normal vector from [-1, 1] to [0, 1] for use as a color.
    Eigen::Vector3d unit_mapped = 0.5 * (sphere_normal +
     Eigen::Vector3d::Ones());
    return unit_mapped;
  }
  Eigen::Vector3d unit_direction = ray.direction().normalized();
  t = 0.5 * (unit_direction.y() + 1);
  // LERP between white and blue depending on the y component of the ray's
  // direction
  return (1 - t) * Eigen::Vector3d::Ones() + t * Eigen::Vector3d(0.5, 0.7, 1);
}

}  // namespace trace

int main() {
  int nx = 200;
  int ny = 100;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";
  Eigen::Vector3d lower_left_corner(-2, -1, -1);
  Eigen::Vector3d canvas_width(4, 0, 0);
  Eigen::Vector3d canvas_height(0, 2, 0);
  Eigen::Vector3d camera_origin(0, 0, 0);
  for (int j = ny - 1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      // (u, v) parameterizes the canvas and ranges from [0, 1] (ish).
      double u = (i + 0.5) / static_cast<double>(nx);
      double v = (j + 0.5) / static_cast<double>(ny);
      Eigen::Vector3d ray_direction = lower_left_corner - camera_origin + 
          u * canvas_width + v * canvas_height;
      trace::Ray ray(camera_origin, ray_direction);
      Eigen::Vector3d pixel_color = trace::color(ray);
            Eigen::Vector3i irgb = (pixel_color * 255.99).cast<int>();
      std::cout << irgb[0] << " " << irgb[1] << " " << irgb[2] << "\n";
    }
  }
  return 0;
}