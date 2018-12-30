#include <iostream>
#include <limits>
#include <memory>
#include <random>

#include "gflags/gflags.h"
#include "ppm/eigen_rgb_image_wrapper.h"
#include "ppm/ppm_writer.h"
#include "ray_tracer/camera.h"
#include "ray_tracer/hitable.h"
#include "ray_tracer/hitable_list.h"
#include "ray_tracer/material.h"
#include "ray_tracer/math_util.h"
#include "ray_tracer/memory_util.h"
#include "ray_tracer/ray.h"
#include "ray_tracer/sphere.h"
#include "third_party/eigen3/Eigen/Core"

DEFINE_int32(nx, 200, "Number of x-direction pixels");
DEFINE_int32(ny, 100, "Number of y-direction pixels");
DEFINE_int32(samples, 100, "Samples per pixel");
DEFINE_double(aperture_diameter, 0.1, "Camera aperture in world units");

namespace trace {

Eigen::Vector3d color(const Ray& ray, const Hitable& scene, int depth) {
  const int kMaxDepth = 50;
  double t_max = std::numeric_limits<double>::infinity();
  double t_min = std::numeric_limits<double>::epsilon() * 1000;  // to avoid numerical errors
  HitRecord hit;
  Ray scattered_ray;
  Eigen::Vector3d attenuation;
  if (scene.Hit(ray, t_min, t_max, &hit)) {
    if (depth < kMaxDepth &&
        hit.material->Scatter(ray, hit, &attenuation, &scattered_ray)) {
      return attenuation.cwiseProduct(color(scattered_ray, scene, depth + 1));
    }
    return Eigen::Vector3d::Zero();
  }
  Eigen::Vector3d unit_direction = ray.direction().normalized();
  double t = 0.5 * (unit_direction.y() + 1);
  // LERP between white and blue depending on the y component of the ray's
  // direction
  return (1 - t) * Eigen::Vector3d::Ones() + t * Eigen::Vector3d(0.5, 0.7, 1);
}

void TraceSphereScene(int nx, int ny, int samples_per_pixel) {
  Eigen::Vector3d look_from(-2, 2, 1);
  Eigen::Vector3d look_at(0, 0, -1);
  Eigen::Vector3d camera_up(0, 1, 0);
  double vertical_fov_deg = 90;
  double aspect_ratio = double(nx) / double(ny);
  double image_distance = (look_from - look_at).norm();
  double aperture_diameter = FLAGS_aperture_diameter;
  Camera camera(look_from, look_at, camera_up, vertical_fov_deg, aspect_ratio, image_distance, aperture_diameter);

  // TODO(nloomis): function to build the scene
  HitableList scene;
  scene.Add(make_unique<Sphere>(Eigen::Vector3d(0, 0, -1),
      0.5, std::make_shared<Lambertian>(Eigen::Vector3d(0.8, 0.3, 0.3))));
  scene.Add(make_unique<Sphere>(Eigen::Vector3d(0, -100.5, -1),
      100, std::make_shared<Lambertian>(Eigen::Vector3d(0.8, 0.8, 0))));
  scene.Add(make_unique<Sphere>(Eigen::Vector3d(1, 0, -1), 0.5,
      std::make_shared<Metal>(Eigen::Vector3d(0.8, 0.6, 0.2), 0.3)));
  scene.Add(make_unique<Sphere>(Eigen::Vector3d(-1, 0, -1), 0.5,
      std::make_shared<Dielectric>(1.5)));
  scene.Add(make_unique<Sphere>(Eigen::Vector3d(-1, 0, -1), -0.45,
    std::make_shared<Dielectric>(1.5)));

  std::default_random_engine generator;
  std::uniform_real_distribution<double> uniform(0.0, 1.0);

  image_util::EigenRgbImageWrapper image(nx, ny);

  // collapse(2) causes the par-for to be over both j and i.
  #pragma omp parallel for schedule(dynamic) collapse(2)
  for (int j = 0; j < ny; ++j) {
    for (int i = 0; i < nx; ++i) {
      Eigen::Vector3d summed_color = Eigen::Vector3d::Zero();
      for (int s = 0; s < samples_per_pixel; ++s) {
        // (u, v) parameterizes the canvas and ranges from [0, 1] (ish).
        double u = (i + uniform(generator)) / nx;
        double v = (j + uniform(generator)) / ny;
        Ray ray = camera.GetRay(u, v);
        summed_color += color(ray, scene, 0);
      }
      Eigen::Vector3d pixel_color = summed_color / samples_per_pixel;
      image(i, j) = pixel_color;
    }
  }

  // TODO(nloomis): TraceFoo should return an image. Writing it out should be
  // done elsewhere.
  image_util::PpmWriter writer;
  writer.Write(image);
}

}  // namespace trace

int main() {
  trace::TraceSphereScene(FLAGS_nx, FLAGS_ny, FLAGS_samples);
  return 0;
}