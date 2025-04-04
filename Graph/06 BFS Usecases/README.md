## 🔍 BFS Intuition Guide

Use these guidelines to choose the right BFS approach based on the problem type:

---

### 1. 🛣️ Minimum Time / Distance / Shortest Path

**Use:** Standard **Breadth-First Search (BFS)**  
**Why:** BFS explores nodes in the order of their distance from the source, ensuring the shortest path in **unweighted** graphs or grids.

**💡 Example Problems:**
- Shortest path in a maze
- Knight's minimum moves on a chessboard
- Word ladder

---

### 2. 📶 Level-Order BFS (Processing by Levels)

**Use:** **Level-wise BFS**  
**Why:** When time or number of steps progresses level-by-level (e.g., 1 second per layer), use BFS that processes all nodes at a level in one go.

**🧱 Pattern:**
```cpp
int level = 0;
while (!q.empty()) {
    int size = q.size();
    while (size--) {
        auto node = q.front(); q.pop();
        // process node
    }
    level++;
}
```

**💡 Example Problems:**
- Binary Tree Level Order Traversal
- Calculating time to spread/infect/cover areas
- Grouping nodes by depth

---

### 3. 🔥 Multi-Source BFS

**Use:** BFS starting from **multiple sources simultaneously**  
**Why:** When events (like infection, fire, flood, signal) spread from multiple starting points at the same time.

**🧱 Pattern:**
```cpp
queue<pair<int, int>> q;
// Push all starting points into the queue
for (auto& src : sources) {
    q.push(src);
}

while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();
    // process current cell and enqueue neighbors
}
```

**💡 Example Problems:**
- Rotting Oranges
- Fire spreading in a forest
- Distance from the nearest 1 in a binary matrix
- Signal propagation in a network

---

## 🧠 Quick Reference Table

| Problem Type                              | Recommended BFS Variant    |
|-------------------------------------------|-----------------------------|
| Shortest path / Minimum steps             | Standard BFS                |
| Time/steps tracked per level              | Level-Order BFS             |
| Simultaneous spread from multiple sources | Multi-Source BFS            |

---

### ✨ Tip:
All of these are based on the same BFS foundation — choose the variant based on **how** the problem evolves over time or space.
