	/*
	* Problem : Given two words, beginWord and endWord, and a dictionary wordList,
  * return the number of words in the shortest transformation sequence from beginWord to endWord using wordList dictionary, or 0 if no such sequence exists.
  *    - Every adjacent pair of words differs by a single letter.
  *    - Note that beginWord does not need to be in wordList.
  * Example : Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]  - Output: 5
  * Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
  *
	* Pattern :
	*	1.	Shortest path asked asked : Hence BFS
	*	2.	Level Order BFS, since since 'size' of path is asked
	*/

#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

class Solution {
    // Helper function to check if word2 is a valid transformation from word1
    bool isValidNextWord(const string& word1, const string& word2) {
        if (word1.size() != word2.size() || word1 == word2)  // 1. size should be same, 2. word1 != word2
            return false;

        int mismatchCount = 0;
        for (size_t i = 0; i < word1.size(); ++i) {
            if (word1[i] != word2[i]) {
                if (++mismatchCount > 1)   // Max 1 letter mismatch allowed
                    return false;
            }
        }
        return true;
    }

public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (beginWord.size() != endWord.size() || beginWord.empty())  // Size not same, not possible to get endWord
            return 0;

        // Check if endWord exists in the wordList
        bool endWordFound = false;
        for (const auto& word : wordList) {
            if (word == endWord) {
                endWordFound = true;
                break;
            }
        }
        if (!endWordFound)  // End word not in dictionary, not possible to get endWord
            return 0;

        // BFS for shortest transformation sequence
        queue<string> q;
        q.push(beginWord);
        vector<bool> visited(wordList.size(), false);
        int transformationLength = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            ++transformationLength;
            // Level order BFS (at each level, size of path is same)
            while (levelSize--) {
                string currentWord = q.front();
                q.pop();

                if (currentWord == endWord)  // Reached endWord
                    return transformationLength;

                for (size_t i = 0; i < wordList.size(); ++i) {
                    if (!visited[i] && isValidNextWord(currentWord, wordList[i])) {
                        visited[i] = true;    // mark visited during insertion into queue
                        q.push(wordList[i]);
                    }
                }
            }
        }

        return 0;  // Couldn't get endWord
    }
};
