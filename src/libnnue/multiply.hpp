#ifndef LIBNNUE_MULTIPLY_HPP
#define LIBNNUE_MULTIPLY_HPP

#include <cstdint>
#include "vector.hpp"
#include "weights.hpp"

namespace libnnue {

template <typename N, typename S, std::size_t A, typename T, std::size_t B>
[[nodiscard]] auto multiply(const Vector<S, A> &vector, const Weights<T, A, B> &weights) noexcept {
    Vector<N, B> result;
    for (std::size_t i = 0; i < A; ++i) {
        for (std::size_t j = 0; j < B; ++j) {
            result[j] += static_cast<N>(vector[i]) * static_cast<N>(weights.at(i * B + j));
        }
    }
    return result;
}

template <typename N, typename S, std::size_t A, typename T, std::size_t B>
[[nodiscard]] auto multiply2(const Vector<S, A> &vector, const Weights<T, A, B> &weights) noexcept {
    Vector<N, B> result;
    for (std::size_t j = 0; j < B; ++j) {
        for (std::size_t i = 0; i < A; ++i) {
            result[j] += static_cast<N>(vector[i]) * static_cast<N>(weights.at(j * A + i));
        }
    }
    return result;
}

}  // namespace libnnue

#endif
