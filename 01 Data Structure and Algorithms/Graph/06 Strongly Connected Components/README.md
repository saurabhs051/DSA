## SCC (Strongly connected component)
---
### Intro
- Group of nodes where - All nodes in an SCC are reachable from all nodes (i.e. A->B reachable, and B->A reachable, if in same SCC)
    - Think of it like a group of cities where there's a one-way road from every city to every other city — directly or indirectly. However if you go in another SCC, you won't be able to return back (1-way road, and no returning 1-way road)
- **This concept is only valid for Directed graphs**
- A directed graph can be divided into multiple SCCs
---
## Algorithms
1. Kosaraju's Algorithm
2. Tarjan's Algorithm
  
  
