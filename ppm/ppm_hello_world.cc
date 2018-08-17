/*
This is the ppm example from Shirley, verbatim. It produces a small example ppm
with green in the top-left, yellow in the top-right, red in the bottom-right,
and blue in the bottom-left, with a smooth gradient between the colors.

Usage:

  $ ./ppm_hello_world > test.ppm
  $ display test.ppm

*/

#include <iostream>
#include "third_party/eigen3/Eigen/Core"

int main() {
  int nx = 200;
  int ny = 100;
  // P3: colors are in ascii. Use P6 for binary, P2/P5 for grayscale.
  // nx ny: number of columns and rows
  // 255: max value of the range to be represented
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";
  // Rows are written from top to bottom
  for (int j = ny - 1; j >= 0; --j) {
    // Columns are left-to-right.
    for (int i = 0; i < nx; ++i) {
      // The color of the pixel is based on its position in the graphic.
      Eigen::Vector3f rgb = 
          Eigen::Vector3f(float(i) / float(nx), float(j) / float(ny), 0.2f);
      Eigen::Vector3i irgb = (rgb * 255.99).cast<int>();
      std::cout << irgb[0] << " " << irgb[1] << " " << irgb[2] << "\n";
    }
  }
}