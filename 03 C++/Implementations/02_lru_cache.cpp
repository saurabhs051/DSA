#include <unordered_map> // For std::unordered_map
#include <utility>       // For std::pair
#include <stdexcept>     // For potential exceptions (though not used here)
#include <iostream>      // For potential debugging (optional)

// Represents a node in the doubly linked list
// Stores the key to allow easy removal from the hash map during eviction
struct Node {
    int key;         // The key associated with this cache entry
    Node *prev;
    Node *next;

    // Constructor
    explicit Node(int k) : key(k), prev(nullptr), next(nullptr) {}	// Explicit constructor when constructor with only one parameter

    // Default destructor is sufficient as the List class manages deletion
    ~Node() = default;	// Important, don't delete *prev and *next, it'll lead to recursive deleting on connected nodes, which are not owned by me. Let List take care of deleting nodes

    // Make Node non-copyable and non-movable to prevent accidental pointer issues
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
    Node(Node&&) = delete;
    Node& operator=(Node&&) = delete;
};

// Manages the doubly linked list for LRU order (LRU at head, MRU at tail)
class List {
private:
    Node* head = nullptr; // Least Recently Used (LRU)
    Node* tail = nullptr; // Most Recently Used (MRU)

public:
    // Constructor
    List() = default;

    // Destructor: Cleans up all nodes remaining in the list
    ~List() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr; // Reset pointers
    }

    // Make List non-copyable and non-movable as it manages raw pointers
    List(const List&) = delete;
    List& operator=(const List&) = delete;
    List(List&&) = delete;
    List& operator=(List&&) = delete;

    // Checks if the list is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // Adds a node to the tail (MRU position)
    void addNodeToTail(Node* node) {
        if (!node) return; // Should not happen with current usage, but safe check

        // Ensure node is detached before adding
        node->prev = nullptr;
        node->next = nullptr;

        if (!tail) {
            // List was empty
            head = tail = node;
        } else {
            // Add to the end
            tail->next = node;
            node->prev = tail;
            tail = node; // Update tail
        }
    }

    // Removes a node from the list.
    // Resets the node's pointers *before* optional deletion.
    void removeNode(Node* node, bool deleteNode = true) {
        if (!node) return;

        // Update previous node's next pointer
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            // Node was the head, update head
            head = node->next;
        }

        // Update next node's previous pointer
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            // Node was the tail, update tail
            tail = node->prev;
        }

        // Reset the removed node's pointers to detach it completely
        node->prev = nullptr;	// Important, later we'll be using removeNode in combination with addNode to promote a node, it's important to clear its prev and next
        node->next = nullptr;

        // Delete the node's memory if requested
        if (deleteNode) {
            delete node;
        }
    }

    // Removes the LRU node (head) and returns its key.
    // Returns -1 if the list is empty (as a convention).
    int removeLRU() {
        if (isEmpty()) {
             return -1; // Indicate failure or empty list
        }

        Node* nodeToRemove = head;
        int key = nodeToRemove->key;
        removeNode(nodeToRemove, true); // Remove and delete the head node
        return key;
    }

    // Moves an existing node to the tail (MRU position).
    void promoteNodeToTail(Node* node) {
        if (!node || node == tail) {
            // Node is null or already the most recently used
            return;
        }

        // Detach node from its current position (without deleting)
        // Note: removeNode now correctly resets internal pointers
        removeNode(node, false);

        // Add it back to the tail
        addNodeToTail(node);
    }
};

// LRUCache implementation
class LRUCache {
private:
    int capacity;
    // Use map's size for current count instead of a separate counter
    std::unordered_map<int, std::pair<int, Node*>> cacheMap; // {key -> {value, node_ptr}}
    List usageList; // Doubly linked list for LRU order

public:
    // Constructor
    explicit LRUCache(int cap) : capacity(cap > 0 ? cap : 0) {
        // Initialize with non-negative capacity
    }

    // Get the value associated with a key, return -1 if not found.
    // Promotes the accessed key to MRU.
    int get(int key) {
        if (capacity == 0) return -1; // Handle zero capacity case

        auto it = cacheMap.find(key);
        if (it == cacheMap.end()) {
            // Key not found
            return -1;
        }

        // Key found:
        // 1. Promote the node to the MRU position (tail of the list)
        usageList.promoteNodeToTail(it->second.second); // Pass the Node*

        // 2. Return the value
        return it->second.first;
    }

    // Put a key-value pair into the cache.
    // If key exists, update value and promote to MRU.
    // If key doesn't exist, add it. If capacity is exceeded, evict LRU.
    void put(int key, int value) {
        if (capacity == 0) return; // Cannot put anything if capacity is 0

        auto it = cacheMap.find(key);

        if (it != cacheMap.end()) {
            // Key already exists:
            // 1. Update value in the map
            it->second.first = value;
            // 2. Promote the node to MRU position
            usageList.promoteNodeToTail(it->second.second);
        } else {
            // Key does not exist: Insert new key-value pair

            // Check if capacity is reached BEFORE inserting
            if (cacheMap.size() >= capacity) {
                // Evict the LRU item (head of the list)
                int keyToRemove = usageList.removeLRU();
                if (keyToRemove != -1) { // Check if list was not empty
                    cacheMap.erase(keyToRemove); // Remove from map
                }
            }

            // Only proceed to add if capacity allows (might be 0 initially or after eviction)
             if (cacheMap.size() < capacity) {
                // 1. Create the new node
                Node* newNode = new Node(key); // Node stores the key
                // 2. Add the new node to the MRU position (tail)
                usageList.addNodeToTail(newNode);
                // 3. Add entry to the map (use emplace for potential efficiency)
                cacheMap.emplace(key, std::make_pair(value, newNode));
            }
        }
    }

    // Default destructor is sufficient because member destructors (`cacheMap`, `usageList`)
    // will be called automatically, cleaning up map entries and allocated Nodes.
    ~LRUCache() = default;

    // Make LRUCache non-copyable and non-movable
    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(const LRUCache&) = delete;
    LRUCache(LRUCache&&) = delete;
    LRUCache& operator=(LRUCache&&) = delete;

};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
