#ifndef PPM_PPM_WRITER_H_
#define PPM_PPM_WRITER_H_

#include <string>

#include "ppm/eigen_rgb_image_wrapper.h"

namespace image_util {

class PpmWriter {
 public:
  // TODO(nloomis): include any options in a constructor

  // Writes a PPM image to a file with filename. The input image data is a
  // linear float map in the range [0, 1]. The output is gamma-corrected and
  // cast to [0, 255] integers. If the file cannot be opened for writing, the
  // function returns immediately.
  // The image is assumed to use right-hand coordinates,
  //
  // y max +--------------+
  //       ^              |
  //       |              |
  //       |              |
  // y min z------------->+
  //   x min              x max
  //
  // so that image(0, 0) is the lower-left corner, and larger y are toward the
  // top of the frame.
  void Write(const EigenRgbImageWrapper& image,
             const std::string& filename) const;

 private:
};

}  // namespace image_util

#endif  // PPM_PPM_WRITER_H_s