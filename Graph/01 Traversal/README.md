# Graph Traversal Notes

## 1. Traversal Methods

### 1.1 Depth-First Search (DFS)
- **Uses recursion with a visited vector**  
- **Steps:**
  1. **Base case**: If the node is already visited, return.
  2. **Visit node**:
     - Mark as visited.
     - Add to the result.
     - Recursively visit its neighbors.

### 1.2 Breadth-First Search (BFS)
- **Uses a queue with a visited vector**  
- **Steps:**
  1. **Result Management**:
     - Add to the result when popping from the queue.
  2. **Visited Vector**:
     - Update when inserting a node into the queue.
     - Ensure the node is not visited before traversing its neighbors.
---

## 2. Consideraions for different graph types
1. Disconnected / Disjoint graph : Traverse from each node as source
2. Directed graph : Traverse from each node as source (handles Forked graph case)
3. Undirected connected graph : Only traverse from any 1 source, will be able to visit all 
