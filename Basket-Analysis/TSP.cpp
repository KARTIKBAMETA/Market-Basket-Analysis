/*
Solved using branch and bounds algorithm

The undirected weighted graph is given by the adjacency matrix. Find the shortest cycle that visits each vertex one time.
 
The first line of input gives number N (N ≤ 20)   — the number of vertices of the graph. The next N
lines contain N non-negative integers each and define an adjacency matrix. 
The number 0 means that there is no edge. Any other number defines the weight of the edge.
You should output one line containing the minimum total length of the cycle or the number -1, if the cycle doesn't exist.
 */

#include <iostream>
#include <vector>
#include <cstdint>
#include <utility>

using Node = std::vector<std::pair<int32_t, int>>;
using Graph = std::vector<Node>;
int32_t bound = 2'147'483'647;
int vertices = 0;
Graph graph;

void FillGraph(Graph& graph, int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            int32_t tmp;
            std::cin >> tmp;
            if (tmp != 0)
                graph[i].push_back({tmp, j});
        }
    }
}

int32_t TSP(int position, int32_t TotalPath, std::vector<bool>& visited, int cities) {
    if (TotalPath > bound)
        return bound;
    if (0 == position && cities != 0) {
        if (cities < vertices - 1)
            return bound;
        else if (TotalPath < bound)
            return bound = TotalPath;
        else
            return bound;
    }
    if (0 != position) {
        visited[position] = true;
        ++cities;
    }

    for (int i = 0; i < graph[position].size(); i++) {
        if (visited[ graph[position][i].second ] == false) {
            TSP (graph[position][i].second,
                 TotalPath + graph[position][i].first,
                 visited, cities);
        }
    }
    visited[position] = false;
    return bound;
}

int main() {
    std::cin >> vertices;
    std::vector<bool> visited (vertices, false);
    Node tmp;

    for (int i = 0; i < vertices; i++)
        graph.push_back(tmp);

    FillGraph(graph, vertices);

    if (vertices == 0) {
        std::cout << -1;
        return 0;
    }
    else if (vertices == 1) {
        std::cout << 0;
        return 0;
    }

    int32_t answer = TSP(0, 0, visited, 0);
    if (answer == 2'147'483'647)
        std::cout << -1;
    else
        std::cout << answer;
}
