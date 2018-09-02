#ifndef RAY_TRACER_CAMERA_H_
#define RAY_TRACER_CAMERA_H_

#include "ray_tracer/ray.h"
#include "third_party/eigen3/Eigen/Core"

namespace trace {

class Camera {
 public:
  Camera(const Eigen::Vector3d& lower_left_corner,
         const Eigen::Vector3d& canvas_width,
         const Eigen::Vector3d& canvas_height,
         const Eigen::Vector3d& camera_origin);

  // Returns a ray originating from the camera and aimed towards the point (u,v)
  // in the camera's canvas. u corresponds to the canvas width and is in [0, 1];
  // v is the canvas height and is also [0, 1] range.
  Ray GetRay(double u, double v);

 private:
  const Eigen::Vector3d lower_left_corner_;
  const Eigen::Vector3d canvas_width_;
  const Eigen::Vector3d canvas_height_;
  const Eigen::Vector3d camera_origin_;
};

}  // namespace trace

#endif  // RAY_TRACER_CAMERA_H_