#include <vector>
using namespace std;

class Solution {
   public:
    int singleNumber(vector<int>& nums) {
        vector<int> bit_sums(32, 0);
        for (auto i : nums) {
            for (unsigned int j = 0; j < 32; j++) {
                bit_sums[j] += ((i >> (31 - j)) & 1);
            }
        }

        int result = 0;
        for (auto i : bit_sums) {
            result = (result << 1) + (i % 3);
        }

        return result;
    }
};
