#include "lattice.hpp"

int fastmod(int const x, int const n) {
  if (x > 0) {
    if (x < n) {
      return x;
    } else {
      return x - n;
    }
  } else {
    return x + n;
  }
}
