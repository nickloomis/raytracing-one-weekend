#include "ppm/ppm_writer.h"

#include <iostream>
#include <fstream>

#include "ppm/image_util.h"
#include "third_party/eigen3/Eigen/Core"

namespace image_util {

void PpmWriter::Write(const EigenRgbImageWrapper& image,
                      const std::string& filename) const {
  std::fstream file;
  file.open(filename, std::ios::out);
  if (!file.is_open()) {
    std::cerr << "Error writing to file: " << filename;
    return;
  }

  // The magic string for binary RGB PPMs.
  const std::string kMagic = "P6";
  file << kMagic << "\n";

  // Image dimensions.
  file << image.nx() << " " << image.ny() << "\n";

  // The maximum value of any pixel; must be less than 65536. If the max value
  // is <=255, each pixel is expected to be one byte. Otherwise, two bytes are
  // used per sample.
  const int kMaxPixelValue = 255;
  file << kMaxPixelValue << "\n";

  // NB: PPMs are stored in top-to-bottom order, similar to a matrix. This is
  // the opposite as what an (x,y) coordinate system would use. Thus, the
  // y-indices are written out in opposite order.
  for (int j = image.ny() - 1; j >= 0; --j) {
    for (int i = 0; i < image.nx(); ++i) {
      Eigen::Vector3d srgb_pixel_color = LinearRgbToSrgb(image(i, j));
      Eigen::Matrix<char, 3, 1> irgb = (srgb_pixel_color * 255.99).cast<char>();
      file.write(irgb.data(), 3*sizeof(char));
    }
  }

  file.close();
}

}  // namespace image_util