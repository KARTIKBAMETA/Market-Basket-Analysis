// Given N points on the plane. You should to minimize the circular route through all points.

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <math.h>
#include <chrono>
#include <ctime>
#include <limits>
#include <random>

std::vector<int> path;
std::clock_t start;
int n;
double block = std::numeric_limits<double>::max();

struct point {
    int64_t x;
    int64_t y;
};
std::vector<point> storage;

void Print(std::vector<int>& res) {
    for (auto item: res) {
        std::cout << item << " ";
    }
}

double distance (point& a, point& b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

void FillStorage (std::vector<point>& storage) {
    for (int i = 0; i < n; i++) {
        int64_t x, y;
        std::cin >> x;
        std::cin >> y;
        storage[i] = point{x, y};
    }
}

void FillMatrix (std::vector< std::vector<double>>& distances) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            distances[i][j] = distance(storage[i], storage[j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            distances[i][j] = distances[j][i];
        }
    }
    for (int i = 0; i < n; i++) {
        distances[i][i] = block;
    }
}

void Near(std::vector< std::vector<double>>& v, std::vector<bool>& visited) {
    int index = 0;
    for (int i = 0; i < n - 1; i++) {
        double nearest = std::numeric_limits<double>::max();
        for (int j = 0; j < n; j++) {
            if ((v[index][j] < nearest) && (!visited[j + 1])) {
                nearest = v[index][j];
                path[i + 1] = j + 1;
            }
        }
        visited[path[i + 1]] = true;
        index = path[i + 1] - 1;
    }
    path[0] = 1;
    path[n] = 1;
}

void v2opt(std::vector< std::vector<double>>& distances) {
    for (int i = 1; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            double old = distances[path[i] - 1][path[i - 1] - 1] + distances[path[j] - 1][path[j + 1] - 1];
            double tmp = distances[path[i - 1] - 1][path[j] - 1] + distances[path[i] - 1][path[j + 1] - 1];
            if (old - tmp > 0) {
                std::reverse(path.begin() + i, path.begin() + j + 1);
            }
        }
    }
}

int main() {
    std::cin >> n;
    storage = std::vector<point> (n);
    path = std::vector<int> (n + 1);
    std::vector<bool> visited (n + 1, false);
    visited[0] = true;
    visited[1] = true;
    FillStorage(storage);
    
    std::vector< std::vector<double>> distances (n, std::vector<double>(n));
    FillMatrix(distances);
    Near(distances, visited);
    
    start = std::clock();
    v2opt(distances);
    double time = ((double)(std::clock() - start)*1000)/CLOCKS_PER_SEC;
    double count = 8000/time;
    
    if (count > 1000) {
        count = 500;
    }
    for (int i = 0; i < count; i ++) {
        v2opt(distances);
    }
    Print(path);
}
