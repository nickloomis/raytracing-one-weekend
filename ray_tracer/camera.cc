#include "ray_tracer/camera.h"

namespace trace {

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