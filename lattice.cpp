#include "lattice.hpp"

#include <cassert>

int fastmod(int const x, int const n) {
  assert(0 < x + n);
  assert(x - n < n);

  if (x >= 0) {
    if (x < n) {
      return x;
    } else {
      return x - n;
    }
  } else {
    return x + n;
  }
}
