# Graph Traversal: DFS vs BFS

| Graph Type         | DFS | BFS | Comments |
|--------------------|-----|-----|----------|
| **Directed Graph (Common, Easy)** | - Node should not be in **current path** (i.e., in current **Recursion Stack**). | - **Topological Sort** (Kahn's algorithm): Cycle exists if we couldn't visit all nodes. | ![Graph Example](image.png) |
| **Undirected Graph** | - In DFS traversal, a **visited node shouldn't be seen again** (as long as it's not the **immediate parent**). <br><br> - Hence, pass Parent as well in parameter <br>| - In BFS traversal, a **visited node shouldn't be seen again** (as long as it's not the **immediate parent**). <br><br>   - Hence, put `{Node, Parent}` in the queue. <br> | |
