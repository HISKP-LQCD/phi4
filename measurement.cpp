#include "measurement.hpp"

#include <cmath>

std::vector<double> measure_corr(Lattice const &lattice) {
  auto const size_L = lattice.size_L();
  auto const size_T = lattice.size_T();
  auto const volume = std::pow(size_L, 3);

  std::vector<double> corr(size_T, 0.0);

  // Iterate through the whole volume.
  for (int z = 0; z < size_L; ++z) {
    for (int y = 0; y < size_L; ++y) {
      for (int x = 0; x < size_L; ++x) {
        for (int t = 0; t < size_L; ++t) {
          for (int t = 0; t < size_T; ++t) {
            for (int diff = 0; diff < size_T; ++diff) {
              auto const product =
                  lattice(x, y, z, t) * lattice(x, y, z, t + diff);
              corr[diff] += product;
            }
          }
        }
      }
    }
  }

  return corr;
}
