#include <array>
#include <catch2/catch.hpp>
#include <libnnue/nnue.hpp>

TEST_CASE("XOR - 1") {
    // Create tests
    const std::pair<std::array<int, 2>, int> tests[] = {
        {{0, 0}, 0},
        {{0, 1}, 1},
        {{1, 0}, 1},
        {{1, 1}, 0},
    };

    // Create network
    libnnue::Weights<int, 2, 2> weights1({1, 2, 1, 2});
    libnnue::Weights<int, 2, 1> weights2({-2, 1});

    // Run tests
    for (const auto &[input, expected] : tests) {
        const auto inputs = libnnue::Vector<int, 2>(input);
        const auto a = libnnue::multiply<int>(inputs, weights1).apply(libnnue::threshold<int, 2>);
        const auto b = libnnue::multiply<int>(a, weights2).apply(libnnue::threshold<int, 1>);
        REQUIRE(b[0] == expected);
    }
}

TEST_CASE("XOR - 2") {
    // Create tests
    const std::pair<std::array<float, 2>, float> tests[] = {
        {{0.0f, 0.0f}, 0.0f},
        {{0.0f, 1.0f}, 1.0f},
        {{1.0f, 0.0f}, 1.0f},
        {{1.0f, 1.0f}, 0.0f},
    };

    // Create network
    libnnue::Weights<float, 2, 2> weights1({20.0f, -20.0f, 20.0f, -20.0f});
    libnnue::Weights<float, 2, 1> weights2({20.0f, 20.0f});
    libnnue::Vector<float, 2> bias1({-10.0f, 30.0f});
    libnnue::Vector<float, 1> bias2({-30.0f});

    // Run tests
    for (const auto &[input, expected] : tests) {
        const auto inputs = libnnue::Vector<float, 2>(input);
        const auto a = libnnue::multiply<float>(inputs, weights1).add(bias1).apply(libnnue::sigmoid<float>);
        const auto b = libnnue::multiply<float>(a, weights2).add(bias2).apply(libnnue::sigmoid<float>);
        const float diff = std::abs(b[0] - expected);
        REQUIRE(diff <= 0.001f);
    }
}
