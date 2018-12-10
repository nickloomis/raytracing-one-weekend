#include "ray_tracer/camera.h"

#include "ray_tracer/math_util.h"
#include "third_party/eigen3/Eigen/Geometry"

namespace trace {

Camera::Camera(const Eigen::Vector3d& look_from, const Eigen::Vector3d& look_at,
               const Eigen::Vector3d& up, double vertical_fov_deg,
               double aspect_ratio) 
    : camera_origin_(look_from) {
  // Total vertical field of view
  double vertical_fov_rad = math_util::DegToRad(vertical_fov_deg);
  // Half-height of the FOV in tan-angle space
  double half_height = tan(0.5 * vertical_fov_rad);
  double half_width = half_height * aspect_ratio;
  // w is the camera direction
  Eigen::Vector3d w = (look_from - look_at).normalized();
  // u and v are basis vectors in the plane orthgonal to the camera's direction.
  // they are orthogonal and unit length.
  Eigen::Vector3d u = up.cross(w).normalized();
  Eigen::Vector3d v = w.cross(u);

  lower_left_corner_ = camera_origin_ - half_width * u - half_height * v - w;
  canvas_width_ = 2 * half_width * u;
  canvas_height_ = 2 * half_height * v;
}

Ray Camera::GetRay(double u, double v) {
  Eigen::Vector3d ray_direction = lower_left_corner_ - camera_origin_ + 
      u * canvas_width_ + v * canvas_height_;
  return Ray(camera_origin_, ray_direction);
}

}  // namespace trace