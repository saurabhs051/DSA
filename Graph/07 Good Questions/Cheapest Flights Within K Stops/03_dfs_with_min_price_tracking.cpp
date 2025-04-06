class Solution {
    /*
    Problem:
    --------
    There are `n` cities connected by flights. Each flight has a starting city, a destination city, and a price.
    You are given the source city `src`, destination city `dst`, and an integer `k` representing the maximum number of stops.
    Find the cheapest price from `src` to `dst` with at most `k` stops. If no such route exists, return -1.

    Key Observations:
    -----------------
    1. We are looking for **minimum cost** ➝ Think BFS (Breadth-First Search).
    2. Flights have **positive weights** AND **bounded depth (k stops)**:
        - ❌ Dijkstra's algorithm with a global min-distance array and min-heap does NOT work here.
        - ✅ Standard **BFS** with **level order traversal** is ideal, as it respects the stop limit.
    3. Use a **global price array** only to prevent revisiting with worse costs (like a visited set), not for greedy updates.

    Approach:
    ---------
    - Construct adjacency list for the graph.
    - Use a queue to perform BFS.
    - Push nodes level-by-level, representing one extra stop.
    - Only allow pushing nodes if the new cost is cheaper than the previously known cost.
    - Stop traversal when `k` levels are done.
    */
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int stopsAllowed) {
        if (src == dst)
            return 0;

        // Build adjacency list: from -> list of (to, cost)
        unordered_map<int, vector<pair<int, int>>> adj;
        for (const auto& flight : flights)
            adj[flight[0]].emplace_back(flight[1], flight[2]);

        // Global cost array: holds cheapest known price to each city
        vector<int> price(n, INT_MAX);  // Not to be used for price[curNode] while calculating newCost, just use as condition (price[nextNode]) before inserting in queue
        price[src] = 0;

        // BFS queue: (currentNode, currentCost)
        queue<pair<int, int>> q;
        q.emplace(src, 0);

        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto [node, cost_till_now] = q.front();
                q.pop();

                for (const auto& [nextNode, nextCost] : adj[node]) {
                    int newCost = cost_till_now + nextCost;  // Don't use price[node] here, use passed cost from last iteration (i.e. cost_till_now)

                    // If cheaper than previously known price, enqueue
                    if (price[nextNode] > newCost) {
                        price[nextNode] = newCost;
                        q.emplace(nextNode, newCost);
                    }
                }
            }

            // Reduce stop
            --stopsAllowed;
            if (stopsAllowed < 0)
                break;
        }

        return price[dst] == INT_MAX ? -1 : price[dst];
    }
};
