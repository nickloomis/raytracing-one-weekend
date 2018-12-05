#include <iostream>
#include <limits>
#include <memory>
#include <random>

#include "ray_tracer/camera.h"
#include "ray_tracer/hitable.h"
#include "ray_tracer/hitable_list.h"
#include "ray_tracer/image_util.h"
#include "ray_tracer/material.h"
#include "ray_tracer/math_util.h"
#include "ray_tracer/memory_util.h"
#include "ray_tracer/ray.h"
#include "ray_tracer/sphere.h"
#include "third_party/eigen3/Eigen/Core"

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
  Eigen::Vector3d lower_left_corner(-2, -1, -1);
  Eigen::Vector3d canvas_width(4, 0, 0);
  Eigen::Vector3d canvas_height(0, 2, 0);
  Eigen::Vector3d camera_origin(0, 0, 0);
  Camera camera(lower_left_corner, canvas_width, canvas_height, camera_origin);

// TODO(nloomis): add make_shared<Material...> to spheres.
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

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  for (int j = ny - 1; j >= 0; --j) {
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
      Eigen::Vector3d srgb_pixel_color =
          image_util::LinearRgbToSrgb(pixel_color);
      Eigen::Vector3i irgb = (srgb_pixel_color * 255.99).cast<int>();
      std::cout << irgb[0] << " " << irgb[1] << " " << irgb[2] << "\n";
    }
  }
}

}  // namespace trace

int main() {
  int nx = 200;
  int ny = 100;
  int samples_per_pixel = 100;
  trace::TraceSphereScene(nx, ny, samples_per_pixel);
  return 0;
}