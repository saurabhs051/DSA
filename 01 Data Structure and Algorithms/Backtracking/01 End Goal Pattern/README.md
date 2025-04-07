# End Goal Recursion Pattern

When implementing recursion, follow this structured approach:

1. **Positive / Answer / Goal Base Condition**  
   Define the condition that determines when the recursion should return a valid result.

2. **Stopping / Negative Conditions**  
   Identify conditions that should stop further recursion (e.g., out-of-bounds checks, invalid states).  
   These can often be added in an `if` condition before visiting the node.

3. **Visit Node & Explore Neighbors**  
   - **Mark the node as visited** to prevent cycles.  
   - **Recursively visit neighboring nodes.**  
   - **Unmark the node after traversal** if revisiting through another path is required.

### Example Flow:
```cpp
void recurse(Node* node) {
    if (isGoal(node))			// (1) Base condition
	{ result.push_back(path); return; }

    if (isInvalid(node) || isVisited(node)) return;  // (2) Stopping condition

    visit(node);  // (3) Visit node
    for (Node* neighbor : node->neighbors) {
        recurse(neighbor);  // Visit neighbors
    }
    unvisit(node);  // (3.1) Allow revisiting if needed
}

