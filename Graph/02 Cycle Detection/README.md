# Cycle Detection: Directed vs Undirected

| Graph Type         | DFS | BFS | Comments |
|--------------------|-----|-----|----------|
| **Directed Graph (Common, Easy)** <br><br> Prefer BFS <br> | - Node should not be in **current path** (i.e., in current **Recursion Stack**). | - **Topological Sort** (Kahn's algorithm): Cycle exists if we couldn't visit all nodes. | <img width="365" alt="image" src="https://github.com/user-attachments/assets/6c518526-1e10-4abd-92eb-c41e62307df0" /> |
| **Undirected Graph** <br><br> Prefer DFS <br>  | - In DFS traversal, a **visited node shouldn't be seen again** (as long as it's not the **immediate parent**). <br><br> - Hence, pass Parent as well in parameter <br>| - In BFS traversal, a **visited node shouldn't be seen again** (as long as it's not the **immediate parent**). <br><br>   - Hence, put `{Node, Parent}` in the queue. <br> | <img width="503" alt="image" src="https://github.com/user-attachments/assets/719769df-8099-4b80-9cd9-f6c406ee4bbb" />|
