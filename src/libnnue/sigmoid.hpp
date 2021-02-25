#ifndef LIBNNUE_SIGMOID_HPP
#define LIBNNUE_SIGMOID_HPP

#include <cmath>

namespace libnnue {

template <typename T>
[[nodiscard]] constexpr T sigmoid(const T x) {
    return 1.0f / (1.0f + std::exp(-x));
}

}  // namespace libnnue

#endif
