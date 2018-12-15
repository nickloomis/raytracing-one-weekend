#ifndef RAY_TRACER_CAMERA_H_
#define RAY_TRACER_CAMERA_H_

#include "ray_tracer/ray.h"
#include "third_party/eigen3/Eigen/Core"

namespace trace {

class Camera {
 public:
  // look_from: camera's lens pupil location
  // look_at: point the camera is aimed towards
  // up: vector which points in the upward direction; the orthogonal projection
  //     of the up vector onto the camera plane is used if up is not in the
  //     camera plane
  // vertical_fov_deg: field of view in degrees in the "up" direction
  // aspect_ratio: horizontal FOV relative to the vertical FOV. A value of 1.5
  //      means that the horizontal is 1.5x larger than the vertical.
  // distance_to_image_plane: distance from the camera lens to the image plane
  //      (where the image rays are in focus); sometimes termed the "focus
  //      distance" of the lens (different than the optical term)
  // aperture_diameter: diameter of the camera lens pupil, in world units
  Camera(const Eigen::Vector3d& look_from, const Eigen::Vector3d& look_at,
    const Eigen::Vector3d& up, double vertical_fov_deg, double aspect_ratio,
    double distance_to_image_plane, double aperture_diameter);

  // Returns a ray originating from the camera and aimed towards the point (s,t)
  // in the camera's canvas. s corresponds to the canvas width and is in [0, 1];
  // t is the canvas height and is also [0, 1] range. The ray is randomly offset
  // so that it appears to originate from a disk with a diameter of
  // aperture_diameter.
  Ray GetRay(double s, double t);

 private:
  const Eigen::Vector3d camera_origin_;
  const double lens_radius_;
  Eigen::Vector3d lower_left_corner_;
  Eigen::Vector3d canvas_width_;
  Eigen::Vector3d canvas_height_;
  Eigen::Vector3d u_;
  Eigen::Vector3d v_;
};

}  // namespace trace

#endif  // RAY_TRACER_CAMERA_H_