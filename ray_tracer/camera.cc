#include "ray_tracer/camera.h"

#include "ray_tracer/math_util.h"

namespace trace {

Camera::Camera(double vertical_fov_deg, double aspect_ratio) {
  // Total vertical field of view
  double vertical_fov_rad = math_util::DegToRad(vertical_fov_deg);
  // Half-height of the FOV in tan-angle space
  double half_height = tan(0.5 * vertical_fov_rad);
  double half_width = half_height * aspect_ratio;
  lower_left_corner_ = Eigen::Vector3d(-half_width, -half_height, -1);
  canvas_width_ = Eigen::Vector3d(2 * half_width, 0, 0);
  canvas_height_ = Eigen::Vector3d(0, 2 * half_height, 0);
  camera_origin_ = Eigen::Vector3d::Zero();
}

Camera::Camera(const Eigen::Vector3d& lower_left_corner,
   const Eigen::Vector3d& canvas_width,
   const Eigen::Vector3d& canvas_height,
   const Eigen::Vector3d& camera_origin)
   : lower_left_corner_(lower_left_corner),
     canvas_width_(canvas_width),
     canvas_height_(canvas_height),
     camera_origin_(camera_origin) {
}

Ray Camera::GetRay(double u, double v) {
  Eigen::Vector3d ray_direction = lower_left_corner_ - camera_origin_ + 
      u * canvas_width_ + v * canvas_height_;
  return Ray(camera_origin_, ray_direction);
}

}  // namespace trace