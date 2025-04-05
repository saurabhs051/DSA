# 📘 Topological Sort

## 🔹 What is Topological Sort?

Topological Sort determines the **order of tasks** when there are **dependencies** between them.

---

## ✅ Key Points

- Determines the **order of tasks** given dependencies.
- Applicable **only for Directed Acyclic Graphs (DAGs)**.
- If not all nodes can be visited, a **cycle exists**.
- **Time Complexity** (BFS / Kahn's Algorithm): `O(V + E)`
- No need for a separate visited array — **indegree array** is sufficient.

---

## 🔁 Pseudocode (Kahn's Algorithm - BFS Based in C++)

```cpp
vector<int> topologicalSort(int V, vector<vector<int>>& adj) {
    // Calculate and store indegree : How many inward dependencies a nose have
    vector<int> indegree(V, 0); 
    for (int node = 0; node < V; ++node) {
        for (int dest : adj[node]) {
            indegree[dest]++;
        }
    }

    // All the nodes with indegree 0 (no dependencies) can be executed, add to queue
    queue<int> q;
    for (int i = 0; i < V; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    // Whenever a task is executed, reduce indegree of all its dependent children, if indegree of a child becomes 0, it is ready for execution - add to queue
    vector<int> result;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);
        for (int neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // If all the tasks could be executed, nice!! Else there is a cycle
    if (result.size() == V)
        return result; // Valid topological sort
    else
        return {}; // Cycle exists, topological sort not possible
}
