#ifndef LIBNNUE_COMBINE_HPP
#define LIBNNUE_COMBINE_HPP

#include "vector.hpp"

namespace libnnue {

template <typename T, std::size_t A, std::size_t B>
[[nodiscard]] constexpr auto combine(const Vector<T, A> &a, const Vector<T, B> &b) noexcept {
    Vector<T, A + B> result;

    for (std::size_t i = 0; i < A; ++i) {
        result[i] = a[i];
    }
    for (std::size_t i = 0; i < B; ++i) {
        result[i + A] = b[i];
    }

    return result;
}

template <typename T, std::size_t A, std::size_t B, std::size_t C>
[[nodiscard]] constexpr auto combine(const Vector<T, A> &a, const Vector<T, B> &b, const Vector<T, C> &c) noexcept {
    Vector<T, A + B + C> result;

    for (std::size_t i = 0; i < A; ++i) {
        result[i] = a[i];
    }
    for (std::size_t i = 0; i < B; ++i) {
        result[i + A] = b[i];
    }
    for (std::size_t i = 0; i < C; ++i) {
        result[i + A + B] = c[i];
    }

    return result;
}

static_assert(combine(Vector<int, 2>({1, 2}), Vector<int, 2>({3, 4})) == Vector<int, 4>({1, 2, 3, 4}));
static_assert(combine(Vector<int, 2>({1, 2}), Vector<int, 3>({3, 4, 5})) == Vector<int, 5>({1, 2, 3, 4, 5}));
static_assert(combine(Vector<int, 3>({1, 2, 3}), Vector<int, 2>({4, 5})) == Vector<int, 5>({1, 2, 3, 4, 5}));
static_assert(combine(Vector<int, 2>({1, 2}), Vector<int, 2>({3, 4}), Vector<int, 2>({5, 6})) ==
              Vector<int, 6>({1, 2, 3, 4, 5, 6}));

}  // namespace libnnue

#endif
