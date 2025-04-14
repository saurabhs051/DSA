/*
* A new alien language uses the English alphabet, but the order of letters is unknown. 
* You are given a list of words[] from the alien language’s dictionary, where the words are claimed to be sorted lexicographically according to their language’s rules.
* determine the correct order of letters in this alien language based on the given words.
* Topological Sort - BfS + Indegree
*/
class Solution {
  public:
    string findOrder(vector<string> &words) {
        if (!words.size())
            return "";
            
        // Get all available characters
        unordered_map<char, int> inDegree;
        for (auto& word : words)
        {
            for (auto ch : word)
                inDegree[ch] = 0;
        }
            
        // Create adjacency list
        // Let's create edges involving letters at same index between subsequent words 
        // (if letters are not same)
        unordered_map<char, vector<char>> adj;
        for (int cur = 0; cur < words.size() - 1; ++cur)
        {
            string& curWord = words[cur];
            string& nextWord = words[cur + 1];
            bool bFoundEdge = false;
            int j = 0;
            while (j < min(curWord.size(), nextWord.size()))
            {
                if (curWord[j] == nextWord[j]) // same letters, look at next letters
                    ++j;
                else    // the letters mismatched i.e. consider the letter of next word as greater than letter of current word
                {
                    // ---------------------Very important : don't add duplicate edges, otherwise wrong indegree -----------------------------------------
                    char u = curWord[j], v = nextWord[j];
                    if (find(adj[u].begin(), adj[u].end(), v) == adj[u].end())
                    {
                        adj[u].push_back(v);
                        ++inDegree[v];
                    }
                    /* Could have used unordered_set as well rather than vector, as shown below
                    if (adj[u].insert(v).second)
                        ++inDegree[v];
                    */
                    bFoundEdge = true;
                    break;
                }
            }
            // Not found edge - either exactly same words or same but cur word smaller, or same but next word smaller (wrong)
            if (!bFoundEdge && (curWord.size() > nextWord.size()))
                return ""; // Something is wrong, all same letters and next word has lesser size
        }
        
        // topological sort
        queue<char> q;
        // Insert all 0 indegree vertices
        for (auto entry : inDegree)
        {
            if (entry.second == 0)
                q.push(entry.first);
        }
        
        string answer;
        while (q.size())
        {
            char front = q.front(); q.pop();
            answer += front;
            for (auto& next : adj[front])
            {
                --inDegree[next];
                if (inDegree[next] == 0)
                    q.push(next);
            }
        }
        if (answer.size() == inDegree.size())
            return answer;
        // answer doesn't have all chars, thee was a cycle, couldn't topological sort
        return "";
    }
};
