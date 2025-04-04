## 🚦 Weighted Graphs (Positive Weights)

### 🧠 Dijkstra's Algorithm using BFS with Min Heap (Priority Queue)

This approach is a classic solution to find the shortest path in a weighted graph with **non-negative** edge weights.

- It works like BFS but uses a **Min Heap** (or priority queue) to always explore the node with the shortest current distance.
- **Time complexity:**

|Graph Representation	|Priority Queue	|Time Complexity|
|--------|-------|----------|
|Adjacency List	|Binary Heap	|O((V + E) log V)|
|Adjacency Matrix	|Array (Naive)	|O(V²)|

#### 📌 Use Cases
- GPS navigation
- Network routing
- Pathfinding in games (when all weights are positive)

---

### 🧪 C++-Style Pseudocode

```cpp
struct Edge {
    int to;
    int weight;
};

using Graph = vector<vector<Edge>>;

vector<int> dijkstra(const Graph& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;

    // Min heap: {distance, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
    minHeap.push({0, start});

    while (!minHeap.empty()) {
        auto [currDist, u] = minHeap.top();
        minHeap.pop();

        // Skip if we've already found a better path
        if (currDist > dist[u]) continue;

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                minHeap.push({dist[v], v});
            }
        }
    }

    return dist;
}
