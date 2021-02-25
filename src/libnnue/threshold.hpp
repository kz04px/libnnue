#ifndef LIBNNUE_THRESHOLD_HPP
#define LIBNNUE_THRESHOLD_HPP

namespace libnnue {

template <typename T, T thr>
[[nodiscard]] constexpr T threshold(const T x) {
    return x >= thr;
}

static_assert(threshold<int, 3>(2) == 0);
static_assert(threshold<int, 3>(3) == 1);
static_assert(threshold<int, 3>(4) == 1);

}  // namespace libnnue

#endif
