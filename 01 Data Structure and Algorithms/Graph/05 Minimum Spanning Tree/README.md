## Spanning Tree
- A tree with V nodes and V-1 edges and all nodes reachable (connected)
## Minimum Spanning Tree
- The V-1 chosen edges are such that the total cost/weight is minimum.
- **MST is only defined for undirected graphs.**
## Algorithms
- Prim's Algo (Greedy, like Dijkstra)
    - Uses MinHeap : O((V + E)logV) = ~ElogV
- Krushkal's Algo (Uses Union-Find)
    - Sorts all edges : O(ElogE)
- Hence, Prim's se better if large number of edges (i.e. dense graphs), Krushkal is better if ow number of edges(i.e. sparse graph)
----

## 🥊 Prim's vs Kruskal's

| **Feature**               | **Prim's Algorithm**                                            | **Kruskal's Algorithm**                                       |
|---------------------------|------------------------------------------------------------------|----------------------------------------------------------------|
| **Approach**              | Grows MST from a single node, greedily picking min edge         | Sorts all edges and adds the smallest non-cycling edge         |
| **Data Structure**        | Min-heap / priority queue                                       | Union-Find (Disjoint Set Union)                                |
| **Best For**              | Dense graphs (many edges)                                       | Sparse graphs (fewer edges)                                    |
| **Time Complexity**       | O(E log V) (with heap), worst case: O(n² log n)                 | O(E log E), worst case: O(n² log n) on complete graph          |
| **Edge Selection**        | Picks edge from current tree to outside node                    | Picks the globally smallest edge that doesn’t form cycle       |
| **Edge Sorting Needed?**  | ❌ No                                                            | ✅ Yes                                                          |
| **Cycle Handling**        | Avoids it via visited[]                                         | Avoids it via Union-Find                                       |
| **Graph Representation**  | Adjacency list/matrix                                           | Edge list                                                      |

---

## 🧠 When to Use What?

### ✅ Use **Prim's** when:
- The graph is **dense** (many edges).
- You have an **adjacency matrix or list** ready.
- You're okay with using a **priority queue**.

### ✅ Use **Kruskal's** when:
- The graph is **sparse** (fewer edges).
- The graph is already in the form of an **edge list**.
- You can easily sort edges and use **Union-Find**.

---

## ⚡ TL;DR:
- **Dense graphs → Prim’s**  
- **Sparse graphs → Kruskal’s**  
- **Adjacency matrix/list → Prim’s is faster**  
- **Edge list → Kruskal’s is more natural**
