/*
  * Every element appears thrice except for one which occurs once.Find that element which occurs once.
  * Link : https://www.geeksforgeeks.org/problems/find-element-occuring-once-when-all-other-are-present-thrice/1
  * Can't use XOR as my repeatition is also 1 (odd), and others repeatition 3 (also odd). 
  * Hence count bits. now, since bits can overlap, they'll generally be in multiple of 3 (e.g. 6, if 2 numbers ave that bit set)
  */
class Solution {
  public:
    int getSingle(vector<int> &arr) {
        // count occurrence of each bits, if not in multiple of 3, my bits
        int result = 0;
        for (int pos = 0; pos < 32; ++pos)
        {
            int count = 0;
            for (auto& num : arr)
            {
                // see if pos bit is set
                if (num & (1 << pos))
                    ++count;
            }
            // num a multiple of 3
            if (count % 3 != 0)
                result |= (1 << pos);
        }
        return result;
    }
};
