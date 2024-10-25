#include "../src/BFS.h" 
#include <iostream>

//need more test

// Compile-time BFS execution
constexpr auto test_bfs_compile_time() {
    std::array<int, 5> result = {0};
    std::array<std::array<int, 5>, 5> graph = {{
        {1, 2, -1, -1, -1},
        {0, 3, 4, -1, -1},   
        {0, 4, -1, -1, -1}, 
        {1, -1, -1, -1, -1}, 
        {1, 2, -1, -1, -1}  
    }};
    bfs(graph, 0, result);
    return result;
}

int main() {
    // Expected BFS traversal order for verification
    constexpr std::array<int, 5> expected_result = {0, 1, 2, 3, 4};

    constexpr auto result = test_bfs_compile_time();

    // Verify that the result matches the expected result at compile-time
    static_assert(result == expected_result, "BFS result does not match the expected result at compile-time!");

    return 0;
}
