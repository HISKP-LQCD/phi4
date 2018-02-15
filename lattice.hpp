#pragma once

#include <vector>
#include <array>

/**
  Fast modulo function that just wraps once.
  */
int fastmod(int const x, int const n);

using Index = std::array<int, 4>;

/**
  Data structure that holds a spin lattice.
  */
class Lattice {
public:
  using Data = double;

  Lattice(int const size_L, int const size_T)
      : size_L_(size_L),
        size_T_(size_T),
        data_(size_L * size_L * size_L * size_T, 0.0) {}

  Data &operator()(int const x, int const y, int const z, int const t) {
    auto const x2 = fastmod(x, size_L_);
    auto const y2 = fastmod(y, size_L_);
    auto const z2 = fastmod(z, size_L_);
    auto const t2 = fastmod(t, size_T_);

    return data_[((x2 * size_L_ + y2) * size_L_ + z2) * size_T_ + t2];
  }

  Data const &
  operator()(int const x, int const y, int const z, int const t) const {
    auto const x2 = fastmod(x, size_L_);
    auto const y2 = fastmod(y, size_L_);
    auto const z2 = fastmod(z, size_L_);
    auto const t2 = fastmod(t, size_T_);

    return data_[((x2 * size_L_ + y2) * size_L_ + z2) * size_T_ + t2];
  }

  Data &operator[](Index const& idx) {
      return (*this)(idx[0], idx[1], idx[2], idx[3]);
  }

  Data const &operator[](Index const& idx) const {
      return (*this)(idx[0], idx[1], idx[2], idx[3]);
  }

  int size_L() const { return size_L_; }
  int size_T() const { return size_T_; }

private:
  int size_L_;
  int size_T_;
  std::vector<Data> data_;
};
