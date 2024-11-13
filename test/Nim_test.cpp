#include "../src/Algorithm.h"

int main() {
    // Test data
    constexpr size_t numPiles = 3;
    constexpr std::array<int, numPiles> testPiles1 = {3, 4, 5};
    constexpr std::array<int, numPiles> testPiles2 = {1, 5, 4};

    // Compile-time tests using static_assert
    static_assert(calculateXorSum(testPiles1) == 2, "Test failed: calculateXorSum for testPiles1");
    static_assert(calculateXorSum(testPiles2) == 0, "Test failed: calculateXorSum for testPiles2");

    static_assert(canWinNim(testPiles1) == true, "Test failed: canWinNim for testPiles1");
    static_assert(canWinNim(testPiles2) == false, "Test failed: canWinNim for testPiles2");

    // Compile-time modification test using constexpr
    constexpr std::array<int, numPiles> testPiles3 = [] {
        std::array<int, numPiles> piles = {3, 4, 5};
        Nim_makeOptimalMove(piles);
        return piles;
    }();

    // Validate the result of Nim_makeOptimalMove
    static_assert(testPiles3[0] == 1 && testPiles3[1] == 4 && testPiles3[2] == 5,
                  "Test failed: Nim_makeOptimalMove for testPiles3");


    // If we reach here, all compile-time tests passed
    std::cout << "All compile-time tests passed.\n";
    return 0;
}
