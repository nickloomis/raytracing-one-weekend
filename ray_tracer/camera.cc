#include "ray_tracer/camera.h"

#include "ray_tracer/math_util.h"
#include "third_party/eigen3/Eigen/Geometry"

namespace trace {

Camera::Camera(const Eigen::Vector3d& look_from, const Eigen::Vector3d& look_at,
               const Eigen::Vector3d& up, double vertical_fov_deg,
               double aspect_ratio, double distance_to_image_plane) 
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
  u_ = up.cross(w).normalized();
  v_ = w.cross(u_);

  lower_left_corner_ = camera_origin_ - distance_to_image_plane * 
      (half_width * u_ + half_height * v_ + w);
  canvas_width_ = 2 * half_width * u_;
  canvas_height_ = 2 * half_height * v_;
}

Ray Camera::GetRay(double s, double t) {
  Eigen::Vector3d ray_position = camera_origin_;
  Eigen::Vector3d ray_direction = lower_left_corner_ - camera_origin_ + 
      s * canvas_width_ + t * canvas_height_;
  return Ray(ray_position, ray_direction);
}

}  // namespace trace