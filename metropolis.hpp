#pragma once

#include "lattice.hpp"

double neighbor_sum(Lattice const&lattice, Index const &idx);

double get_delta_S(Lattice const &lattice,
                   Index const &idx,
                   int const phi_new,
                   double const mu);
