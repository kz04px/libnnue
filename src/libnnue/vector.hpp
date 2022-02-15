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

    [[nodiscard]] constexpr auto apply(const std::function<T(T)> &func) const noexcept {
        Vector<T, A> result;
        for (size_type i = 0; i < A; ++i) {
            result[i] = func(m_data[i]);
        }
        return result;
    }

    template <typename R>
    [[nodiscard]] constexpr auto add(const Vector<R, A> &rhs) const noexcept {
        Vector<T, A> result;

        for (size_type i = 0; i < A; ++i) {
            result[i] = m_data[i] + rhs[i];
        }

        return result;
    }

    [[nodiscard]] constexpr auto sub(const Vector<T, A> &rhs) const noexcept {
        Vector<T, A> result;
        for (size_type i = 0; i < A; ++i) {
            result[i] = m_data[i] - rhs[i];
        }
        return result;
    }

    template <typename F>
    [[nodiscard]] constexpr auto mul(const F &n) const noexcept {
        Vector<T, A> result;
        for (size_type i = 0; i < A; ++i) {
            result[i] = m_data[i] * n;
        }
        return result;
    }

    template <typename F>
    [[nodiscard]] constexpr auto div(const F &n) const noexcept {
        Vector<T, A> result;
        for (size_type i = 0; i < A; ++i) {
            result[i] = m_data[i] / n;
        }
        return result;
    }

    [[nodiscard]] constexpr auto rshift(const std::size_t n) const noexcept {
        Vector<T, A> result;
        for (size_type i = 0; i < A; ++i) {
            result[i] = m_data[i] >> n;
        }
        return result;
    }

    [[nodiscard]] constexpr auto lshift(const std::size_t n) const noexcept {
        Vector<T, A> result;
        for (size_type i = 0; i < A; ++i) {
            result[i] = m_data[i] << n;
        }
        return result;
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

   private:
    std::array<T, A> m_data;
};

// operator==
static_assert(Vector<int, 3>({1, 2, 3}) == Vector<int, 3>({1, 2, 3}));
// operator!=
static_assert(Vector<int, 3>({1, 2, 3}) != Vector<int, 3>({5, 7, 9}));
// add()
static_assert(Vector<int, 3>({1, 2, 3}).add(Vector<int, 3>({4, 5, 6})) == Vector<int, 3>({5, 7, 9}));
// sub()
static_assert(Vector<int, 3>({1, 2, 3}).sub(Vector<int, 3>({4, 5, 6})) == Vector<int, 3>({-3, -3, -3}));
// mul()
static_assert(Vector<int, 3>({1, 2, 3}).mul(2) == Vector<int, 3>({2, 4, 6}));
// div()
static_assert(Vector<int, 3>({2, 4, 6}).div(2) == Vector<int, 3>({1, 2, 3}));
// rshift
static_assert(Vector<int, 3>({0, 8, 256}).rshift(1) == Vector<int, 3>({0, 4, 128}));
// lshift
static_assert(Vector<int, 3>({0, 8, 256}).lshift(1) == Vector<int, 3>({0, 16, 512}));

}  // namespace libnnue

#endif
