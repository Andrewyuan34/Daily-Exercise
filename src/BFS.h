#ifndef Algorithm_H
#define Algorithm_H


#include <array>
#include <cstddef> 

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
#endif
