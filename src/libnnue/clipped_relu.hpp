#ifndef LIBNNUE_CLIPPED_RELU_HPP
#define LIBNNUE_CLIPPED_RELU_HPP

#include <algorithm>
#include <cassert>
#include <cmath>

namespace libnnue {

template <typename T, T M>
[[nodiscard]] constexpr T clipped_relu(const T x) {
    return std::max<T>(0, std::min<T>(M, x));
}

static_assert(clipped_relu<int, 3>(-2) == 0, "Clipped ReLu error");
static_assert(clipped_relu<int, 3>(-1) == 0, "Clipped ReLu error");
static_assert(clipped_relu<int, 3>(0) == 0, "Clipped ReLu error");
static_assert(clipped_relu<int, 3>(1) == 1, "Clipped ReLu error");
static_assert(clipped_relu<int, 3>(2) == 2, "Clipped ReLu error");
static_assert(clipped_relu<int, 3>(3) == 3, "Clipped ReLu error");
static_assert(clipped_relu<int, 3>(4) == 3, "Clipped ReLu error");
static_assert(clipped_relu<int, 3>(5) == 3, "Clipped ReLu error");

}  // namespace libnnue

#endif
