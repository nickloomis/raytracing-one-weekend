/*
This is the ppm example from Shirley, verbatim. It produces a small example ppm
with green in the top-left, yellow in the top-right, red in the bottom-right,
and blue in the bottom-left, with a smooth gradient between the colors.

Usage:

  $ ./ppm_hello_world > test.ppm
  $ display test.ppm

*/

#include <iostream>

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
      float r = float(i) / float(nx);
      float g = float(j) / float(ny);
      float b = 0.2;
      int ir = int(255.99 * r);
      int ig = int(255.99 * g);
      int ib = int(255.99 * b);
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}