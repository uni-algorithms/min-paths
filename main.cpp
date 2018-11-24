#include <cassert>
#include "paths.hpp"

auto main() -> int {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    assert(input);
    assert(output);

    auto ps = min_paths(input);
    output << ps.first << " " << ps.second;

    input.close();
    output.close();
    return 0;
}