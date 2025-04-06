
# ✈️ `findCheapestPrice` Solutions — What Works and What Doesn't

This guide explores different implementations of the `findCheapestPrice` problem using BFS with a `k` stop constraint. It explains which variations fail, why they fail, and presents a working version with commentary.

---

## ❌ Can't Do This – Version 0

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // ❌ Uses global price[] and updates it in-place.
        // This fails for k-stop constraints as it may prematurely update prices globally.

        if (src == dst) return 0;
        unordered_map<int, vector<pair<int, int>>> adj;
        for (auto& flight : flights)
            adj[flight[0]].push_back({flight[1], flight[2]});

        vector<int> price(n, INT_MAX);
        price[src] = 0;

        queue<int> q;
        q.push(src);

        while (q.size()) {
            int size = q.size();
            while (size--) {
                int node = q.front(); q.pop();
                for (auto& next : adj[node]) {
                    if (price[next.first] > price[node] + next.second) {
                        price[next.first] = price[node] + next.second;
                        q.push(next.first);
                    }
                }
            }
            --k;
            if (k < 0) break;
        }

        return (price[dst] == INT_MAX) ? -1 : price[dst];
    }
};
```

🛑 **Problem:** This uses a **global price array**, which gets incorrectly updated by other paths, breaking the stop limit condition.

---

## ❌ Can't Do This – Version 1

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // ❌ Doesn't track visited or check if cost to node is less than existing.

        if (src == dst) return 0;
        unordered_map<int, vector<pair<int, int>>> adj;
        for (auto& flight : flights)
            adj[flight[0]].push_back({flight[1], flight[2]});

        vector<int> price(n, INT_MAX);
        price[src] = 0;

        queue<pair<int, int>> q;  // {node, cost}
        q.push({src, 0});
        int minPath = INT_MAX;

        while (q.size()) {
            int size = q.size();
            while (size--) {
                auto node = q.front(); q.pop();
                for (auto& next : adj[node.first]) {
                    if (next.first == dst)
                        minPath = min(minPath, node.second + next.second);
                    else
                        q.push({next.first, node.second + next.second});
                }
            }
            --k;
            if (k < 0) break;
        }

        return (minPath == INT_MAX) ? -1 : minPath;
    }
};
```

🛑 **Problem:** No cost comparison before enqueueing — inefficient and can lead to revisiting worse paths.

---

## ❌ Can't Do This – Version 2

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // ❌ Doesn't process all paths before stopping, may skip better ones in last iteration.

        if (src == dst) return 0;
        unordered_map<int, vector<pair<int, int>>> adj;
        for (auto& flight : flights)
            adj[flight[0]].push_back({flight[1], flight[2]});

        vector<int> price(n, INT_MAX);
        price[src] = 0;

        queue<pair<int, int>> q;
        q.push({src, 0});
        int minPath = INT_MAX;

        while (q.size()) {
            int size = q.size();
            while (size--) {
                auto node = q.front(); q.pop();

                if (node.first == dst) {
                    minPath = min(minPath, node.second);
                    continue;
                }

                for (auto& next : adj[node.first]) {
                    if (price[next.first] > node.second + next.second) {
                        price[next.first] = node.second + next.second;
                        q.push({next.first, node.second + next.second});
                    }
                }
            }

            --k;
            if (k < 0) break;
        }

        return (minPath == INT_MAX) ? -1 : minPath;
    }
};
```

🛑 **Problem:** May reach `dst` in final level but not process it, due to `continue` and `k < 0` break. Might miss cheaper or correct solutions.

---

## ✅ This Works – Final Version

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // ✅ Correct approach using BFS with cost tracking and stop-level processing.

        if (src == dst) return 0;

        unordered_map<int, vector<pair<int, int>>> adj;
        for (auto& flight : flights)
            adj[flight[0]].emplace_back(flight[1], flight[2]);

        vector<int> price(n, INT_MAX);
        price[src] = 0;

        queue<pair<int, int>> q;  // {node, cost_so_far}
        q.push({src, 0});
        int minPath = INT_MAX;

        while (!q.empty()) {
            int size = q.size();
            vector<int> tempPrice = price; // 🔑 Track prices for this level only

            while (size--) {
                auto [node, cost] = q.front(); q.pop();

                for (auto& [neigh, fare] : adj[node]) {
                    if (cost + fare < tempPrice[neigh]) {
                        tempPrice[neigh] = cost + fare;
                        q.push({neigh, cost + fare});
                    }
                }
            }

            price = tempPrice;
            --k;
            if (k < 0) break;
        }

        return (price[dst] == INT_MAX) ? -1 : price[dst];
    }
};
```

✅ **Why it works:**

- Maintains a **temporary cost array per level** to avoid polluting global state.
- Only pushes neighbors if the **new path is cheaper** than any seen before.
- Stops exactly after `k+1` layers (k stops = k+1 nodes visited).

---

## 📌 Notes

- 🧠 Think of this as a **level-based BFS**, where each level means 1 additional stop.
- ✅ Updating `price[]` only after the level finishes ensures proper path independence.
- ❗️Avoid reusing global cost updates across BFS levels — this is the **most common mistake**.

---

Let me know if you'd like visual flow diagrams or complexity breakdowns!
