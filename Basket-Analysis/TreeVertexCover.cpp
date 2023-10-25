/* Find minimum vertex cover for forest graph. */

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

struct Node {
    std::vector<int> neighbours;
};

std::pair<int, int> VertexCover(int root,
                                std::vector<Node>& tree,
                                std::vector<std::vector<int>>& pairs,
                                std::vector<bool>& parents) {
    if (parents[root] == true) {
        return std::make_pair (0, 0);
    }
    parents[root] = true;
    int NoRoot = 0, WithRoot = 0;
    
    for (int i = 0; i < tree[root].neighbours.size(); i++) {
        int child = tree[root].neighbours[i];
        std::pair<int, int> temp_res = VertexCover(child, tree, pairs, parents);
        pairs[child][0] = temp_res.first;
        pairs[child][1] = temp_res.second;
    }
    for (int i = 0; i < tree[root].neighbours.size(); i++) {
        int child = tree[root].neighbours[i];
        NoRoot += pairs[child][1];
        WithRoot += std::min(pairs[child][0], pairs[child][1]);
    }
    WithRoot++;
    return std::make_pair (NoRoot, WithRoot);
}

int main() {
    int vertices;
    std::cin >> vertices;
    std::vector<Node> nodes (vertices);
    std::vector<bool> parents (vertices, false);
    int result = 0;

    for (int i = 0; i < vertices; i++) {
        int degree;
        std::cin >> degree;
        std::vector<int> neighbours;
        for (int j = 0; j < degree; j++) {
            int edge;
            std::cin >> edge;
            neighbours.push_back(edge);
        }
        nodes[i].neighbours = neighbours;
    }

    for (int i = 0; i < vertices; i++) {
        std::pair<int, int> total;
        if (parents[i] == false) {
            std::vector<int> fill (2, 0);
            std::vector<std::vector<int>> DynamicPairs (vertices, fill);
            total = VertexCover(i, nodes, DynamicPairs, parents);
            result += std::min(total.first, total.second);
        }
    }
    std::cout << result;
}
