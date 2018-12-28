#include "ray_tracer/ppm_writer.h"

#include <iostream>

#include "third_party/eigen3/Eigen/Core"
#include "ray_tracer/image_util.h"

namespace image_util {

void PpmWriter::Write(const EigenRgbImageWrapper& image) const {
  std::cout << "P3\n" << image.nx() << " " << image.ny() << "\n255\n";
  // NB: PPMs are stored in top-to-bottom order, similar to a matrix. This is
  // the opposite as what an (x,y) coordinate system would use. Thus, the
  // y-indices are written out in opposite order.
  for (int j = image.ny() - 1; j >= 0; --j) {
    for (int i = 0; i < image.nx(); ++i) {
      Eigen::Vector3d srgb_pixel_color = LinearRgbToSrgb(image(i, j));
      Eigen::Vector3i irgb = (srgb_pixel_color * 255.99).cast<int>();
      std::cout << irgb[0] << " " << irgb[1] << " " << irgb[2] << "\n";
    }
  }
}

}  // namespace image_util