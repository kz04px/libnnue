#ifndef LIBNNUE_IDENTITY_HPP
#define LIBNNUE_IDENTITY_HPP

namespace libnnue {

template <typename T>
[[nodiscard]] constexpr T identity(const T x) {
    return x;
}

}  // namespace libnnue

#endif
