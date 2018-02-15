#include "metropolis.hpp"

#include <cmath>

double neighbor_sum(Lattice const&lattice, Index const &idx) {
  double sum = 0.0;

  for (int dir = 0; dir < 4; ++dir) {
    for (int sign : {+1, -1}) {
      // Copy the index.
      auto idx_neighbor = idx;

      // Perform a shift into the given direction.
      idx_neighbor[dir] += sign;

      // Sum this lattice site to the intermediate result.
      sum += lattice[idx_neighbor];
    }
  }

  return sum;
}

double get_delta_S(Lattice const &lattice,
                   Index const &idx,
                   int const phi_new,
                   double const mu) {
  // The action difference consists of the local and non-local part. For the
  // local part we just need to compute the local part.
  auto const local_old = 0.5 * (8 + pow(mu, 2)) * std::pow(lattice[idx], 2);
  auto const local_new = 0.5 * (8 + pow(mu, 2)) * std::pow(phi_new, 2);

  // For the non-local part we need to sum up the eight connections to the
  // nearest neighbors. The change in energy comes from this site's bonds to
  // the neighbors and all the neighbor's bonds to the current site. Therefore
  // we _do not_ need to have the factor 1/2 in there.
  auto const sum = neighbor_sum(lattice, idx);
  auto const nonlocal_old = - lattice[idx] * sum;
  auto const nonlocal_new = - phi_new * sum;

  return local_new - local_old + nonlocal_new - nonlocal_old;
}
