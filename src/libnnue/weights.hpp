#ifndef LIBNNUE_WEIGHTS_HPP
#define LIBNNUE_WEIGHTS_HPP

#include <array>
#include <fstream>

namespace libnnue {

template <typename T, std::size_t in, std::size_t out>
class Weights {
   public:
    using size_type = std::size_t;

    constexpr Weights() : m_data{} {
    }

    constexpr Weights(const std::array<T, in * out> &d) : m_data{d} {
    }

    void load_file(std::ifstream &fs) {
        for (std::size_t i = 0; i < in * out; ++i) {
            if (fs.eof()) {
                throw "asd";
            }
            fs.read(reinterpret_cast<char *>(&m_data[i]), sizeof(T));
        }
    }

    [[nodiscard]] constexpr size_type size() const noexcept {
        return in * out;
    }

    [[nodiscard]] constexpr auto &at(const size_type i) {
        return m_data.at(i);
    }

    [[nodiscard]] constexpr const auto &at(const size_type i) const {
        return m_data.at(i);
    }

    [[nodiscard]] constexpr auto &at(const size_type i, const size_type j) {
        return m_data.at(index(i, j));
    }

    [[nodiscard]] constexpr const auto &at(const size_type i, const size_type j) const {
        return m_data.at(index(i, j));
    }

    [[nodiscard]] constexpr auto &operator[](const std::size_t idx) noexcept {
        return m_data[idx];
    }

    [[nodiscard]] constexpr const auto &operator[](const std::size_t idx) const noexcept {
        return m_data[idx];
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

    [[nodiscard]] constexpr size_type index(const size_type i, const size_type j) const noexcept {
        return i * out + j;
    }

   private:
    std::array<T, in * out> m_data;
};

static_assert(Weights<int, 2, 2>({1, 2, 3, 4}).at(0) == 1, "Weights::at() failure");
static_assert(Weights<int, 2, 2>({1, 2, 3, 4}).at(1) == 2, "Weights::at() failure");
static_assert(Weights<int, 2, 2>({1, 2, 3, 4}).at(2) == 3, "Weights::at() failure");
static_assert(Weights<int, 2, 2>({1, 2, 3, 4}).at(3) == 4, "Weights::at() failure");

static_assert(Weights<int, 2, 2>({1, 2, 3, 4}).at(0, 0) == 1, "Weights::at() failure");
static_assert(Weights<int, 2, 2>({1, 2, 3, 4}).at(0, 1) == 2, "Weights::at() failure");
static_assert(Weights<int, 2, 2>({1, 2, 3, 4}).at(1, 0) == 3, "Weights::at() failure");
static_assert(Weights<int, 2, 2>({1, 2, 3, 4}).at(1, 1) == 4, "Weights::at() failure");

}  // namespace libnnue

#endif
