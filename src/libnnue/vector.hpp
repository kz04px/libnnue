#ifndef LIBNNUE_VECTOR_HPP
#define LIBNNUE_VECTOR_HPP

#include <array>
#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <limits>

namespace libnnue {

template <typename T, std::size_t A>
class Vector {
   public:
    static_assert(A > 0, "Size must be > 0");

    using size_type = std::size_t;

    constexpr Vector() : m_data{} {
    }

    constexpr Vector(const std::array<T, A> &d) : m_data{d} {
    }

    void load_file(std::ifstream &fs) {
        for (std::size_t i = 0; i < A; ++i) {
            if (fs.eof()) {
                throw "asd";
            }
            fs.read(reinterpret_cast<char *>(&m_data[i]), sizeof(T));
        }
    }

    [[nodiscard]] constexpr auto data() noexcept {
        return m_data.data();
    }

    [[nodiscard]] constexpr auto data() const noexcept {
        return m_data.data();
    }

    [[nodiscard]] constexpr size_type size() const noexcept {
        return A;
    }

    [[nodiscard]] constexpr auto max() const noexcept {
        T val = std::numeric_limits<T>::lowest();
        for (const auto n : m_data) {
            val = std::max(val, n);
        }
        return val;
    }

    [[nodiscard]] constexpr auto min() const noexcept {
        T val = std::numeric_limits<T>::max();
        for (const auto n : m_data) {
            val = std::min(val, n);
        }
        return val;
    }

    constexpr auto apply(const std::function<T(T)> &func) noexcept {
        for (size_type i = 0; i < A; ++i) {
            m_data[i] = func(m_data[i]);
        }
        return *this;
    }

    template <typename R>
    constexpr inline auto add(const Vector<R, A> &rhs) noexcept {
        for (size_type i = 0; i < A; ++i) {
            m_data[i] = m_data[i] + rhs[i];
        }
        return *this;
    }

    template <typename R>
    constexpr auto sub(const Vector<R, A> &rhs) noexcept {
        for (size_type i = 0; i < A; ++i) {
            m_data[i] = m_data[i] - rhs[i];
        }
        return *this;
    }

    template <typename F>
    constexpr auto mul(const F &n) noexcept {
        for (size_type i = 0; i < A; ++i) {
            m_data[i] = m_data[i] * n;
        }
        return *this;
    }

    template <typename F>
    constexpr auto div(const F &n) noexcept {
        for (size_type i = 0; i < A; ++i) {
            m_data[i] = m_data[i] / n;
        }
        return *this;
    }

    constexpr auto rshift(const std::size_t n) noexcept {
        for (size_type i = 0; i < A; ++i) {
            m_data[i] = m_data[i] >> n;
        }
        return *this;
    }

    constexpr auto lshift(const std::size_t n) noexcept {
        for (size_type i = 0; i < A; ++i) {
            m_data[i] = m_data[i] << n;
        }
        return *this;
    }

    [[nodiscard]] constexpr auto &at(const size_type idx) {
        return m_data.at(idx);
    }

    [[nodiscard]] constexpr const auto &at(const size_type idx) const {
        return m_data.at(idx);
    }

    [[nodiscard]] constexpr auto &operator[](const std::size_t idx) noexcept {
        return m_data[idx];
    }

    [[nodiscard]] constexpr const auto &operator[](const std::size_t idx) const noexcept {
        return m_data[idx];
    }

    [[nodiscard]] constexpr bool operator==(const Vector<T, A> &rhs) const noexcept {
        bool equal = true;
        for (size_type i = 0; i < A; ++i) {
            equal &= m_data[i] == rhs.m_data[i];
        }
        return equal;
    }

    [[nodiscard]] constexpr bool operator!=(const Vector<T, A> &rhs) const noexcept {
        return !(*this == rhs);
    }

    [[nodiscard]] auto begin() noexcept {
        return m_data.begin();
    }

    [[nodiscard]] auto end() noexcept {
        return m_data.end();
    }

    [[nodiscard]] const auto begin() const noexcept {
        return m_data.begin();
    }

    [[nodiscard]] const auto end() const noexcept {
        return m_data.end();
    }

    template <std::size_t S>
    [[nodiscard]] auto pad() const noexcept -> Vector<T, S> {
        static_assert(S > A, "Vector padded size must be larger than original size");

        Vector<T, S> out;
        std::memcpy(out.data(), m_data.data(), A * sizeof(T));
        std::memset(&out[A], static_cast<T>(0), S - A);
        return out;
    }

   private:
    std::array<T, A> m_data;
};

// operator==
static_assert(Vector<int, 3>({1, 2, 3}) == Vector<int, 3>({1, 2, 3}), "operator== failed");
// operator!=
static_assert(Vector<int, 3>({1, 2, 3}) != Vector<int, 3>({5, 7, 9}), "operator!= failed");
// add()
static_assert(Vector<int, 3>({1, 2, 3}).add(Vector<int, 3>({4, 5, 6})) == Vector<int, 3>({5, 7, 9}), "add() failed");
// sub()
static_assert(Vector<int, 3>({1, 2, 3}).sub(Vector<int, 3>({4, 5, 6})) == Vector<int, 3>({-3, -3, -3}), "sub() failed");
// mul()
static_assert(Vector<int, 3>({1, 2, 3}).mul(2) == Vector<int, 3>({2, 4, 6}), "mul() failed");
// div()
static_assert(Vector<int, 3>({2, 4, 6}).div(2) == Vector<int, 3>({1, 2, 3}), "div() failed");
// rshift
static_assert(Vector<int, 3>({0, 8, 256}).rshift(1) == Vector<int, 3>({0, 4, 128}), "rshift() failed");
// lshift
static_assert(Vector<int, 3>({0, 8, 256}).lshift(1) == Vector<int, 3>({0, 16, 512}), "lshift() failed");

}  // namespace libnnue

#endif
