#ifndef LIBNNUE_RELU_HPP
#define LIBNNUE_RELU_HPP

#include <cassert>
#include <cmath>

namespace libnnue {

template <typename T>
[[nodiscard]] constexpr T relu(const T x) {
    return std::max<T>(0, x);
}

static_assert(relu(-2) == 0);
static_assert(relu(-1) == 0);
static_assert(relu(0) == 0);
static_assert(relu(1) == 1);
static_assert(relu(2) == 2);

static_assert(relu(-2.0f) == 0.0f);
static_assert(relu(-1.0f) == 0.0f);
static_assert(relu(0.0f) == 0.0f);
static_assert(relu(1.0f) == 1.0f);
static_assert(relu(2.0f) == 2.0f);

}  // namespace libnnue

#endif
