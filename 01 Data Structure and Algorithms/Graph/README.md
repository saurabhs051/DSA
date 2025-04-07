### Operations
---
1. **Traversal**
    1. BFS (Uses Queue) - O(V + E)
    2. DFS (Recursion - Stack) - O(V + E)
---
2. **Cycle Detection**
    1. Directed Graph
        1. BFS (Topological Sort - Should be able to visit all nodes i.e. everyone's indegree 0) - O(V+E)
        2. DFS (Node shouldn't be found again in recursion path) - O(V + E)
    2. Undirected Graph
        1. DFS (Any visited node shouldn't be seen again unless it is the immediate parent) - O(V+E)
        2. Disjoint Set (Do Union-Find : If parent of src == parent of destination, cycle exist) - O(E*V) -> O(E*1) if path compression used
---
3. **Topological Sort**
    1. Order of doing dependent Tasks (BFS + Indegree vector - Kahn's algorithm) - O(V+E)
    3. Only possible for DAG (Directed Acyclic Graph) - No need to have a visited vector to prevent cycle (indegree vector is enough)
---
4. **Connected Components**
    1. DFS : visit all nodes from each source - O(V + E)
    2. Union-Find : visit(Union-Find) all edges, connected components end up in same set
---
5. **Shortest Path**
    1. Unweighted Graph (Unit weight) : BFS (Standard, Multi-source, Level order) - O(V+E)
    2. Weighted Graph (Positive weight) : Dijkstra BFS (BFS with Min Heap) - O((V+E)logV)
    3. Weighted Graph (Negative weight) : Bellmon Ford
---
6. **Minimum Spanning Tree** (V-1 connecting edges comprising minimum weight)
    1. Krushkal's (Sort edges by weight and take V-1 minimum ones, as long as they are not making cycle(Union find - src, dest not having same parent))
    2. Prim's - Greedy
---
7. **Strongly Connected Components** (for directed graphs)
    1. Kosaraju's
    2. Tarjan's
---

---
# Summary
---
## Graph Algorithms Summary

| Topic                  | Algorithm       | Directed      | Undirected     | Both        |
|------------------------|----------------|---------------|----------------|-------------|
| Shortest Path          | Dijkstra        | ✅             | ✅              | ✅           |
| Shortest Path          | Bellman-Ford    | ✅             | ⚠️ (Adapted)    | ⚠️           |
| Shortest Path          | Floyd-Warshall  | ✅             | ⚠️              | ⚠️           |
| Minimum Spanning Tree  | Prim's          | ❌             | ✅              | ❌           |
| Minimum Spanning Tree  | Kruskal's       | ❌             | ✅              | ❌           |
| Strongly Connected Comp| Kosaraju's      | ✅             | ❌              | ❌           |
| Strongly Connected Comp| Tarjan's        | ✅             | ❌              | ❌           |
| Topological Sort       | Kahn's          | ✅ (DAG)       | ❌              | ❌           |
| Disjoint Sets / Union  | Union-Find      | ⚠️             | ✅              | ✅           |

- Summary :
    - Except MST and Disjoint-set(Connected components), all other concepts are applicable for Directed Graphs  

