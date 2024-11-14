#ifndef Algorithm_H
#define Algorithm_H

#include <array>
#include <cstddef> 
#include <format>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <optional>
#include <iomanip>


/**
 * Breadth-First Search (BFS) algorithm specification.
 * 
 * Purpose:
 * Breadth-First Search (BFS) is an algorithm for traversing or searching a graph or tree.
 * This `bfs` template function performs a BFS traversal on a graph represented by a 
 * fixed-size adjacency matrix (`std::array`), starting from a specified node, and records
 * the order of node visits.
 * 
 * Parameters:
 * - graph: The adjacency matrix representing the graph, of type `std::array<std::array<int, N>, N>`,
 *          where `graph[i]` contains all neighbors of node `i`. Any non-existent neighbor is represented by `-1`.
 * - startNode: The starting node for the BFS traversal.
 * - result: An array to store the order of visited nodes, of type `std::array<int, N>`.
 * 
 * Preconditions:
 * - The `graph` adjacency matrix is represented as a `std::array` and has a known, fixed number of nodes, `N`.
 * - The `startNode` is a valid node index, within the range `[0, N-1]`.
 * - The `result` array is prepared to store the order of visited nodes as integers.
 * 
 * Postconditions:
 * - The `result` array contains the nodes in the order they were visited according to BFS.
 * - All nodes reachable from `startNode` are visited once and only once.
 * - Unvisited entries in the `result` array will retain their initial values, as only reachable nodes are populated.
 * 
 * Complexity:
 * - Time Complexity: O(V + E), where `V` is the number of nodes and `E` is the number of edges.
 * - Space Complexity: O(V), requiring both a `visited` array and a fixed-size `queue` array to record node visit statuses.
 */
template<size_t N>
constexpr void bfs(const std::array<std::array<int, N>, N>& graph, int startNode, std::array<int, N>& result) {
    std::array<bool, N> visited = {false};
    std::array<int, N> queue = {0}; // Fixed-size queue array
    size_t front = 0;
    size_t back = 0;
    size_t result_index = 0;

    // Initialize the BFS
    queue[back++] = startNode; // Enqueue start node
    visited[startNode] = true;

    // Perform BFS
    while (front < back) {
        int node = queue[front++]; // Dequeue front element
        result[result_index++] = node;

        for (int neighbor : graph[node]) {
            if (neighbor != -1 && !visited[neighbor]) {
                queue[back++] = neighbor; // Enqueue neighbor
                visited[neighbor] = true;
            }
        }
    }
}

/**
 * Depth-First Search (DFS) algorithm specification.
 * 
 * Purpose:
 * Depth-First Search (DFS) is an algorithm for traversing or searching a graph or tree.
 * This `dfs` template function performs a DFS traversal on a graph represented by a
 * fixed-size adjacency matrix (`std::array`), starting from a specified node, and records
 * the order of node visits.
 * 
 * Parameters:
 * - graph: The adjacency matrix representing the graph, of type `std::array<std::array<int, N>, N>`,
 *          where `graph[i]` contains all neighbors of node `i`. Any non-existent neighbor is represented by `-1`.
 * - startNode: The starting node for the DFS traversal.
 * - result: An array to store the order of visited nodes, of type `std::array<int, N>`.
 * 
 * Preconditions:
 * - The `graph` adjacency matrix is represented as a `std::array` and has a known, fixed number of nodes, `N`.
 * - The `startNode` is a valid node index, within the range `[0, N-1]`.
 * - The `result` array is prepared to store the order of visited nodes as integers.
 * 
 * Postconditions:
 * - The `result` array contains the nodes in the order they were visited according to DFS.
 * - All nodes reachable from `startNode` are visited once and only once.
 * - Unvisited entries in the `result` array will retain their initial values, as only reachable nodes are populated.
 * 
 * Complexity:
 * - Time Complexity: O(V + E), where `V` is the number of nodes and `E` is the number of edges.
 * - Space Complexity: O(V), requiring both a `visited` array and a fixed-size `stack` array to record node visit statuses.
 */
template<size_t N>
constexpr void dfs(const std::array<std::array<int, N>, N>& graph, int startNode, std::array<int, N>& result) {
    std::array<bool, N> visited = {false};
    std::array<int, N> stack = {0}; // Fixed-size stack array
    size_t top = 0;
    size_t result_index = 0;

    // Initialize DFS
    stack[top++] = startNode; // Push start node onto the stack
    visited[startNode] = true;

    // Perform DFS
    while (top > 0) {
        int node = stack[--top]; // Pop the top element from the stack
        result[result_index++] = node;

        // Traverse neighbors in reverse order to maintain order consistency with BFS
        for (int i = N - 1; i >= 0; --i) {
            int neighbor = graph[node][i];
            if (neighbor != -1 && !visited[neighbor]) {
                stack[top++] = neighbor; // Push neighbor onto the stack
                visited[neighbor] = true;
            }
        }
    }
}

template<size_t N>
constexpr int calculateXorSum(const std::array<int, N>& piles) {
    if (N == 0) throw std::invalid_argument("Error: The array of piles cannot be empty.");
    
    int xorSum = 0;
    for (int pile : piles) {
        if (pile < 0) throw std::invalid_argument("Error: Pile cannot contain a negative number.");
        xorSum ^= pile;
    }
    return xorSum;
}

template<size_t N>
constexpr bool canWinNim(const std::array<int, N>& piles) {
    return calculateXorSum(piles) != 0;
}

/**
 * Nim Game Optimal Move algorithm specification.
 * 
 * This function identifies the optimal move by adjusting one of the piles so that the 
 * XOR sum becomes zero. It modifies the original array `piles` to reflect the move.
 * 
 * @tparam N The size of the array.
 * @param piles An array of integers representing the number of stones in each pile.
 * 
 * @complexity Time Complexity: O(N), where N is the number of piles.
 * @complexity Space Complexity: O(1).
 */
template<size_t N>
constexpr void Nim_makeOptimalMove(std::array<int, N>& piles) {
    int xorSum = calculateXorSum(piles);

    // Traverse all piles to find a move that makes the XOR sum zero
    for (size_t i = 0; i < N; ++i) {
        int targetPile = piles[i] ^ xorSum;
        if (targetPile < piles[i]) {
            piles[i] = targetPile; // Update the pile after taking stones
            return;
        }
    }
}

/**
 * Simple Moving Average (SMA) algorithm specification.
 * 
 * Purpose:
 * The Simple Moving Average (SMA) is a statistical tool used in financial markets 
 * to smooth out short-term fluctuations and highlight longer-term trends in time series data.
 * This function computes the SMA for a given set of stock prices using a fixed window size.
 * 
 * Parameters:
 * - prices: A vector of doubles representing the historical prices.
 * - window: An integer representing the size of the moving average window.
 * - result: A vector of doubles to store the computed moving averages.
 * 
 * Preconditions:
 * - The `prices` vector is non-empty and contains historical stock prices.
 * - The `window` parameter is a positive integer.
 * - The `result` vector is prepared to store the computed moving averages.
 * 
 * Postconditions:
 * - The `result` vector contains the SMA values computed over the specified window size.
 * - If the window size is larger than the number of data points, the `result` vector remains empty.
 * - The `result` vector only includes averages for complete windows (i.e., the calculation starts only when enough data is available).
 * 
 * Complexity:
 * - Time Complexity: O(N), where `N` is the number of prices in the input vector.
 * - Space Complexity: O(M), where `M` is the number of computed moving averages.
 */
std::optional<std::vector<double>> computeSMA(const std::vector<double>& prices, int window) {
    // Check for invalid inputs
    if (prices.empty() || window <= 0 || window > static_cast<int>(prices.size())) return std::nullopt;
    std::vector<double> result;
    double sum = 0.0;

    // Pre-compute the first SMA
    for (int i = 0; i < window; ++i) {
        sum += prices[i];
    }
    result.push_back(sum / window);

    // Move the window and update the SMA
    for (size_t i = window; i < prices.size(); ++i) {
        sum += prices[i] - prices[i - window];
        result.push_back(sum / window);
    }

    return result;
}


#endif
