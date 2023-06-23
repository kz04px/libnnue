#include <catch2/catch.hpp>
#include <libnnue/nnue.hpp>

TEST_CASE("Vector::pad") {
    REQUIRE(libnnue::Vector<int, 1>().pad<2>().size() == 2);
    REQUIRE(libnnue::Vector<int, 1>().pad<10>().size() == 10);
    REQUIRE(libnnue::Vector<int, 1>().pad<128>().size() == 128);

    REQUIRE(libnnue::Vector<int, 3>({1, 2, 3}).pad<4>() == libnnue::Vector<int, 4>({1, 2, 3, 0}));
    REQUIRE(libnnue::Vector<int, 3>({1, 2, 3}).pad<6>() == libnnue::Vector<int, 6>({1, 2, 3, 0, 0, 0}));
}
