#include <vector>
#include <algorithm> // for std::min, std::max

class Solution {
public:
    /**
     * Finds the two unique numbers in an array where all other numbers (except these 2 unique numbers) appears twice.
	 * Theoretical concept : XOR of different bits = 1, XOR of same bits = 0
	 * Practical Concept 1 : num ^ 0 = num (i.e. initialize the variable that will be used for XORS with 0, it won't affect the result)
  	 * Practical Concept 2 : num ^ num = 0 (i.e. if same number occurring even times, it will cancel out) - VERY IMPORTANT
	 * Practical Concept 3 : To check whether a bit is set, check : if (num & (1 << position))
     * Practical Concept 4 : To set a bit at a position, do : num |= (1 << position)
	 * Practical Concept 5 : To unset a bit at a position, do : num &= (1 << position)
     * Practical Concept 6 : Always use parenthesis while using bitwise operators &, |, ^ in conditions, because they have less precedence than == , e.g. if (0 == (b & c))
	 * Practical Concept 7 : Remember, (num & (1 << position)) is not equal to 1, it's equal to a number like 00100 (i.e. 4 in this case), so checking if(num & (1 << position))  is right, but if((num & (1 << position)) == 1) is wrong.
     * Practical Concept 8 : (n & n-1) unsets last set bit of n. 
	 * This last concept is used to check number of set bits in a number. e.g. while (n) { n = n & (n - 1); count++; }
     * It is also used to check if a number is power of 2 (i.e. it has only 1 set bit). e.g. if (n && (n & (n - 1)) == 0) // if n is not equal to 0 and n is power of 2
     *
     * @param nums Input vector of integers
     * @return A vector containing the two unique numbers, sorted in ascending order
     */
    std::vector<int> findUniqueNumbers(const std::vector<int>& nums) {
        int xorOfAll = 0;

        // Step 1: XOR all elements. Result is XOR of the two unique numbers.
        for (const int& num : nums) {
            xorOfAll ^= num;
        }

        // Step 2: Find the rightmost set bit in xorOfAll.
        // This bit is set in one unique number and not in the other.
        int differingBitPosition = 0;
        while (((xorOfAll >> differingBitPosition) & 1) == 0 && differingBitPosition < 32) {
            ++differingBitPosition;
        }

        // Step 3: Divide numbers into two groups based on differingBitPosition
        // and XOR within the group that has the set bit at differingBitPosition.
        int firstUnique = 0;
        for (const int& num : nums) {
            if ((num >> differingBitPosition) & 1) {
                firstUnique ^= num;
            }
        }

        // Step 4: Find the second unique number using the XOR of both.
        int secondUnique = xorOfAll ^ firstUnique;

        // Step 5: Return the result in ascending order.
        return std::vector<int>{std::min(firstUnique, secondUnique), std::max(firstUnique, secondUnique)};
    }
};
