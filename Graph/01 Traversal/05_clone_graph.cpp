/*
* Given a reference of a node in a connected undirected graph. Return a deep copy (clone) of the graph.
* Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.
* class Node {
*    public int val;
*    public List<Node> neighbors;
*}
*/


/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
    unordered_map<Node*, Node*> clone;
public:
    Node* cloneGraph(Node* node) {
        // If null node passed
        if (!node)
            return nullptr;
        // Already cloned Node - Return to prevent cycle
        if (clone[node] != nullptr)
            return clone[node];
        
        // Clone doesn't exist - Create one
        Node* newNode = new Node(node->val);
        clone[node] = newNode;
		// Clone neighbours
        for (auto& neighbour : node->neighbors)
            newNode->neighbors.push_back(cloneGraph(neighbour));
        return newNode;
    }
};
