#ifndef LIBNNUE_ACCUMULATOR_HPP
#define LIBNNUE_ACCUMULATOR_HPP

#include <array>
#include <vector>
#include "vector.hpp"
#include "weights.hpp"

namespace libnnue {

template <typename bias_type,
          typename weight_type,
          typename output_type,
          std::size_t in,
          std::size_t out,
          output_type activation(output_type)>
class AccumulatorShared {
   public:
    constexpr AccumulatorShared(const Vector<bias_type, out> *bias, const Weights<weight_type, in, out> *weights)
        : m_bias{bias}, m_weights{weights}, m_first{}, m_second{}, m_first_post{}, m_second_post{}, m_flipped{} {
    }

    [[nodiscard]] const auto get() const noexcept {
        Vector<output_type, 2 * out> output;

        for (std::size_t j = 0; j < out; ++j) {
            output[j + out * m_flipped] = m_first_post[j];
        }

        for (std::size_t j = 0; j < out; ++j) {
            output[j + out * !m_flipped] = m_second_post[j];
        }

        return output;
    }

    void clear_first() noexcept {
        for (std::size_t j = 0; j < out; ++j) {
            m_first[j] = m_bias->at(j);
            m_first_post[j] = activation(m_first[j]);
        }
    }

    void clear_second() noexcept {
        for (std::size_t j = 0; j < out; ++j) {
            m_second[j] = m_bias->at(j);
            m_second_post[j] = activation(m_second[j]);
        }
    }

    void clear() noexcept {
        for (std::size_t j = 0; j < out; ++j) {
            m_first[j] = m_bias->at(j);
            m_second[j] = m_bias->at(j);
            m_first_post[j] = activation(m_first[j]);
            m_second_post[j] = activation(m_second[j]);
        }
        m_flipped = false;
    }

    void update_first(const std::size_t idx, const bool value) {
        for (std::size_t j = 0; j < out; ++j) {
            const auto widx = m_weights->index(idx, j);
            m_first[j] -= !value * (*m_weights)[widx];
            m_first[j] += value * (*m_weights)[widx];
        }

        for (std::size_t j = 0; j < out; ++j) {
            m_first_post[j] = activation(m_first[j]);
        }
    }

    void update_second(const std::size_t idx, const bool value) {
        for (std::size_t j = 0; j < out; ++j) {
            const auto widx = m_weights->index(idx, j);
            m_second[j] -= !value * (*m_weights)[widx];
            m_second[j] += value * (*m_weights)[widx];
        }

        for (std::size_t j = 0; j < out; ++j) {
            m_second_post[j] = activation(m_second[j]);
        }
    }

    void flip() noexcept {
        m_flipped = !m_flipped;
    }

    void flip(const bool flipped) noexcept {
        m_flipped = flipped;
    }

   private:
    const Vector<bias_type, out> *m_bias;
    const Weights<weight_type, in, out> *m_weights;
    Vector<output_type, out> m_first;
    Vector<output_type, out> m_second;
    Vector<output_type, out> m_first_post;
    Vector<output_type, out> m_second_post;
    bool m_flipped;
};

template <typename bias_type,
          typename weight_type,
          typename output_type,
          std::size_t in,
          std::size_t out,
          output_type activation(output_type)>
class AccumulatorUnshared {
   public:
    constexpr AccumulatorUnshared(const Vector<bias_type, out> *bias_first,
                                  const Weights<weight_type, in, out> *weights_first,
                                  const Vector<bias_type, out> *bias_second,
                                  const Weights<weight_type, in, out> *weights_second)
        : m_bias_first{bias_first},
          m_weights_first{weights_first},
          m_bias_second{bias_second},
          m_weights_second{weights_second},
          m_first{},
          m_second{},
          m_first_post{},
          m_second_post{},
          m_flipped{} {
    }

    [[nodiscard]] const auto get() const noexcept {
        Vector<output_type, 2 * out> output;

        for (std::size_t j = 0; j < out; ++j) {
            output[j + out * m_flipped] = m_first_post[j];
        }

        for (std::size_t j = 0; j < out; ++j) {
            output[j + out * !m_flipped] = m_second_post[j];
        }

        return output;
    }

    void clear_first() noexcept {
        for (std::size_t j = 0; j < out; ++j) {
            m_first[j] = m_bias_first->at(j);
            m_first_post[j] = activation(m_first[j]);
        }
    }

    void clear_second() noexcept {
        for (std::size_t j = 0; j < out; ++j) {
            m_second[j] = m_bias_second->at(j);
            m_second_post[j] = activation(m_second[j]);
        }
    }

    void clear() noexcept {
        for (std::size_t j = 0; j < out; ++j) {
            m_first[j] = m_bias_first->at(j);
            m_second[j] = m_bias_second->at(j);
            m_first_post[j] = activation(m_first[j]);
            m_second_post[j] = activation(m_second[j]);
        }
        m_flipped = false;
    }

    void update_first(const std::size_t idx, const bool value) {
        for (std::size_t j = 0; j < out; ++j) {
            const auto widx = m_weights_first->index(idx, j);
            m_first[j] -= !value * (*m_weights_first)[widx];
            m_first[j] += value * (*m_weights_first)[widx];
        }

        for (std::size_t j = 0; j < out; ++j) {
            m_first_post[j] = activation(m_first[j]);
        }
    }

    void update_second(const std::size_t idx, const bool value) {
        for (std::size_t j = 0; j < out; ++j) {
            const auto widx = m_weights_second->index(idx, j);
            m_second[j] -= !value * (*m_weights_second)[widx];
            m_second[j] += value * (*m_weights_second)[widx];
        }

        for (std::size_t j = 0; j < out; ++j) {
            m_second_post[j] = activation(m_second[j]);
        }
    }

    void flip() noexcept {
        m_flipped = !m_flipped;
    }

    void flip(const bool flipped) noexcept {
        m_flipped = flipped;
    }

   private:
    const Vector<bias_type, out> *m_bias_first;
    const Weights<weight_type, in, out> *m_weights_first;
    const Vector<bias_type, out> *m_bias_second;
    const Weights<weight_type, in, out> *m_weights_second;
    Vector<output_type, out> m_first;
    Vector<output_type, out> m_second;
    Vector<output_type, out> m_first_post;
    Vector<output_type, out> m_second_post;
    bool m_flipped;
};

}  // namespace libnnue

#endif
