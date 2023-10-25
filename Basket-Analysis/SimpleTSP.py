"""
The undirected weighted graph is given by the adjacency matrix. Find the shortest cycle that visits each vertex one time.

The first line of input gives number N (N ≤ 11)   — the number of vertices of the graph. The next N
lines contain N non-negative integers each and define an adjacency matrix. 
The number 0 means that there is no edge. Any other number defines the weight of the edge.

You should output one line containing the minimum total length of the cycle or the number -1, if the cycle doesn't exist.
"""
import math

cities = int(input())
distances = []
path = [[-2 for i in range(cities)] for j in range(1<<cities)]
all_visited = (1<<cities) - 1

# Taking n*n matrix input by user
for i in range(0, cities):
    distances.append([])
    
for i in range(0, cities):
    tmp = [int(x) for x in input().split()]
    for j in range(0, cities):
        if tmp[j] == 0 and i != j:
            distances[j].append(math.inf)
        else:
            distances[j].append(tmp[j])

# Function for "travelling salesman problem", computes the length of a cycle
def TSP(visited, position):
    if all_visited == visited:
        return distances[position][0]
    if path[visited][position] != -2:
        return path[visited][position]
    length = math.inf
    
    for CityIndex in range (0, cities):
        if visited&(1<<CityIndex) == 0:
            new_path = distances[position][CityIndex] + TSP(visited|(1<<CityIndex), CityIndex)
            length = min(new_path, length)
    path[visited][position] = length
    return length

# Check if there any cities
if cities != 0:
    Answer = TSP(1, 0)
else:
    Answer = math.inf
if (Answer == math.inf):
    print(-1)
else:
    print(Answer)
