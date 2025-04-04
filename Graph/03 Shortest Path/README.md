### BFS Intuition
1. Minimum/shortest asked
    - Shortest path
    - Minimum distance
    - Minimum time
2. Spreading behaviour seen
    - Flood fill
    - Spreading infection
3. Not Backtracking
    - Rat ALL PATHS in maze
    - Rat VALID PATHS in maze, etc.
---
### BFS for Shortest path Variations
1. Unweighted (Unit weight) graphs / grids     : Standard BFS (normal or multi-source or Level order BFS)
2. Weighted graphs (Positive weight)           : Dijksta BFS (BFS with Min Heap)
3. Weighted graphs (Negative weights)          : Bellmon Ford


**💡 Example Problems:**
- Flood fill
- Shortest path in a maze
- Knight's minimum moves on a chessboard
- Word ladder

---
### 1. 📶 Standard BFS 
When no specific value is asked, just need to do some operation / traversal
**🧱 Pattern:**
```cpp
queue<int> q;
// Push starting node into the queue
q.push(src);
// Traverse
while (!q.empty()) {
    auto curNode = q.front(); q.pop();
    // process current cell and enqueue neighbors if valid and mark neighbours as visited
}
```

**💡 Example Problems:**
- Flood fill (single source)

---

### 2. 📶 Level-Order BFS (Processing by Levels)

**Use:** **Level-wise BFS**  
**Why:** When distance, time or number of steps progresses level-by-level (e.g., 1 second per layer), use BFS that processes all nodes at a level in one go.

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
- Calculating *time* to spread/infect/cover areas
- Grouping nodes by *depth*
- Knight's minimum *moves* on a chessboard
- Shortest *Path size* in Binary Matrix

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
- Flood fill (multi source)

---

## 🧠 Quick Reference Table

| Problem Type                                                  | Recommended BFS Variant     |
|---------------------------------------------------------------|-----------------------------|
| Just traverse / fill / spread                                 | Standard BFS                |
| Shortest path / Minimum steps / Time/steps tracked per level  | Level-Order BFS             |
| Simultaneous spread from multiple sources                     | Multi-Source BFS            |
| Shortest path - Weighted Graph                                | Dijkstra BFS (Min Heap      |
| Shortst path - Negative Weights                               | Bellmon Ford                |

---
