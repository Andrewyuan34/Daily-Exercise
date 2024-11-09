#include "../src/Algorithm.h"
#include <iostream>

// Compile-time DFS execution
constexpr auto test_dfs_compile_time() {
    std::array<int, 5> result = {0};
    std::array<std::array<int, 5>, 5> graph = {{
        {1, 2, -1, -1, -1},
        {0, 3, 4, -1, -1},   
        {0, 4, -1, -1, -1}, 
        {1, -1, -1, -1, -1}, 
        {1, 2, -1, -1, -1}  
    }};
    dfs(graph, 0, result);
    return result;
}

int main() {
    // Expected DFS traversal order for verification
    constexpr std::array<int, 5> expected_result = {0, 1, 3, 4, 2};

    constexpr auto result = test_dfs_compile_time();

    // Verify that the result matches the expected result at compile-time
    static_assert(result == expected_result, "DFS result does not match the expected result at compile-time!");

    return 0;
}

