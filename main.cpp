#include "metropolis.hpp"
#include "measurement.hpp"

#include <fstream>
#include <iostream>
#include <random>

int main() {
  // This is a fixed number for the sake of this program. Not very nice, but
  // easier to program for now.
  double const mu = 1.0;

  double const size_L = 16;
  double const size_T = 32;

  int const update_n = 100;
  double const update_sd = 2.0;

  Lattice lattice(size_L, size_T);

  std::default_random_engine engine;
  std::uniform_int_distribution<int> dist_L(0, size_L - 1);
  std::uniform_int_distribution<int> dist_T(0, size_T - 1);
  std::uniform_real_distribution<double> dist_accept(0, 1);
  std::normal_distribution<double> dist_phi(0, update_sd);

  std::ofstream ofs_corr("corr.txt");
  ofs_corr << "\"size_L\"\t\"size_T\"\t\"mu\"\t\"update\"\t\"t\"\t\"corr\"\n";

  // Full sweep loop.
  for (int n = 0; n < update_n; ++n) {
    std::cout << "Update " << n << " of " << update_n << std::endl;

    // Single site update loop.
    for (int nn = 0; nn < size_L * size_L * size_L * size_T; ++nn) {
      // Pick a random position.
      Index idx;
      for (int i = 0; i < 3; ++i) {
        idx[i] = dist_L(engine);
      }
      idx[3] = dist_T(engine);

      double const phi_new = dist_phi(engine);

      auto const delta_S = get_delta_S(lattice, idx, phi_new, mu);

      if (delta_S < 0 || exp(-delta_S) > dist_accept(engine)) {
        lattice[idx] = phi_new;
      }
    }

    auto const &corr = measure_corr(lattice);

    for (int t = 0; t < corr.size(); ++t) {
      ofs_corr << size_L << "\t" << size_T << "\t" << mu << "\t" << n << "\t"
               << t << "\t" << corr[t] << "\n";
    }
  }
}
