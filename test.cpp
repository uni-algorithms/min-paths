#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "paths.hpp"

TEST_CASE("test provided") {
    graph g = {{0, {1, 2, 4}},
               {1, {5}},
               {2, {3}},
               {3, {6}},
               {4, {3}},
               {5, {6}},
               {6, {}}};

    auto ps = min_paths(g, 0, 6);

    REQUIRE(ps.first == 3);
    REQUIRE(ps.second == 3);
}

TEST_CASE("circular graph") {
    graph g = {{0, {1, 5}},
               {1, {0, 2}},
               {2, {1, 3}},
               {3, {2, 4}},
               {4, {3, 5}},
               {5, {4, 0}}};

    auto ps = min_paths(g, 0, 3);

    REQUIRE(ps.first == 3);
    REQUIRE(ps.second == 2);
}

TEST_CASE("from_stream should work") {
    graph expected = {{0, {1, 2, 4}},
                      {1, {5}},
                      {2, {3}},
                      {3, {6}},
                      {4, {3}},
                      {5, {6}},
                      {6, {}}};

    stringstream in("0 1\n"
                    "0 2\n"
                    "2 3\n"
                    "0 4\n"
                    "4 3\n"
                    "1 5\n"
                    "5 6\n"
                    "3 6");

    graph actual;
    from_stream(actual, in, 7, 8);
    REQUIRE(actual == expected);
}