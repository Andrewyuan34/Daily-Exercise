#include <cassert>
#include <cmath>    // For std::abs
#include "../src/Algorithm.h"  // Ensure this file defines computeSMA

// Macro to compare floating point numbers with a given precision
#define FLOAT_EQ(x, y, epsilon) (std::abs((x) - (y)) < (epsilon))

// Function to test the computeSMA implementation
void testComputeSMA() {
    // Test Case 1: Normal scenario with valid input
    {
        std::vector<double> prices = {100, 102, 104, 103, 101, 98, 97, 99, 100, 102, 105};
        int window = 3;
        auto result = computeSMA(prices, window);
        assert(result.has_value() && "Test 1 failed: Expected result, but got nullopt.");

        // Expected output based on a window of size 3
        std::vector<double> expected = {102.0, 103.0, 102.67, 100.67, 98.67, 98.0, 98.67, 100.33, 102.33};

        // Check if the computed SMA matches the expected values
        for (size_t i = 0; i < result->size(); ++i) {
            assert(FLOAT_EQ(result->at(i), expected[i], 0.01) && "Test 1 failed: SMA value mismatch.");
        }
        std::cout << "Test 1 passed." << std::endl;
    }

    // Test Case 2: Window size larger than the number of data points
    {
        std::vector<double> prices = {100, 102, 104};
        int window = 5;
        auto result = computeSMA(prices, window);
        assert(!result.has_value() && "Test 2 failed: Expected nullopt for window size larger than prices size.");
        std::cout << "Test 2 passed." << std::endl;
    }

    // Test Case 3: Window size is zero
    {
        std::vector<double> prices = {100, 102, 104};
        int window = 0;
        auto result = computeSMA(prices, window);
        assert(!result.has_value() && "Test 3 failed: Expected nullopt for zero window size.");
        std::cout << "Test 3 passed." << std::endl;
    }

    // Test Case 4: Negative window size
    {
        std::vector<double> prices = {100, 102, 104};
        int window = -3;
        auto result = computeSMA(prices, window);
        assert(!result.has_value() && "Test 4 failed: Expected nullopt for negative window size.");
        std::cout << "Test 4 passed." << std::endl;
    }

    // Test Case 5: Empty prices vector
    {
        std::vector<double> prices = {};
        int window = 3;
        auto result = computeSMA(prices, window);
        assert(!result.has_value() && "Test 5 failed: Expected nullopt for empty prices vector.");
        std::cout << "Test 5 passed." << std::endl;
    }

    // Test Case 6: Window size of 1, result should match the original prices
    {
        std::vector<double> prices = {100, 102, 104};
        int window = 1;
        auto result = computeSMA(prices, window);
        assert(result.has_value() && "Test 6 failed: Expected result, but got nullopt.");

        // The SMA with a window of 1 should match the original prices
        std::vector<double> expected = {100.0, 102.0, 104.0};
        for (size_t i = 0; i < result->size(); ++i) {
            assert(FLOAT_EQ(result->at(i), expected[i], 0.01) && "Test 6 failed: SMA value mismatch.");
        }
        std::cout << "Test 6 passed." << std::endl;
    }
}

int main() {
    // Run all test cases
    testComputeSMA();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
