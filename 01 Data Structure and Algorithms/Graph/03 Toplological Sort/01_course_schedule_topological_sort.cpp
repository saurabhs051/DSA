/*
* There are N courses, labeled from 0 to N-1. prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
* Return the ordering of courses you should take to finish all courses. If it is impossible to finish all courses, return an empty array.
* Topological Sort - BfS + Indegree
*/
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> courses;  // Result
      
        // Create adjacency list
        // Calculate and store indegree : How many inward dependencies a nose have
        unordered_map<int, vector<int>> adj;
        vector<int> indegree(numCourses, 0);
        for (auto& pre : prerequisites)
        {
            adj[pre[1]].push_back(pre[0]);
            ++indegree[pre[0]];  // 
        }

        // All the nodes with indegree 0 (no dependencies) can be executed, add to queue
        queue<int> q;
        for (int course = 0; course < numCourses; ++course)
        {
            if (indegree[course] == 0)
                q.push(course);
        }

        // Whenever a task is executed, reduce indegree of all its dependent children, if indegree of a child becomes 0, it is ready for execution - add to queue
        while (q.size())
        {
            int course = q.front();
            q.pop();
            courses.push_back(course);
            for (auto& nextCourse : adj[course])
            {
                --indegree[nextCourse];
                if (indegree[nextCourse] == 0)
                    q.push(nextCourse);
            }
        }

        // If all the tasks could be executed, nice!! Else there is a cycle
        if (courses.size() == numCourses)
            return courses;
        return {}; // Not possible
    }
};
