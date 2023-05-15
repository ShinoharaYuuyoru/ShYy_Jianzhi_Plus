class Solution {
public:
    string addBinary(string a, string b) {
        string res = "";

        unsigned int carry_bit = 0;
        int i = a.size() - 1;  // Must use `int` type by using -1 as the end condition in following loop.
        int j = b.size() - 1;
        while (i >= 0 || j >= 0) {
            unsigned int a_bit = (i >= 0 ? (a[i] - '0') : 0);
            unsigned int b_bit = (j >= 0 ? (b[j] - '0') : 0);

            unsigned int sum = a_bit + b_bit + carry_bit;
            unsigned int sum_bit = (sum >= 2 ? (sum - 2) : sum);
            res.push_back(sum_bit + '0');

            carry_bit = (sum >= 2 ? 1 : 0);
            i--;
            j--;
        }

        // Set the highest bit with carry bit
        if (carry_bit == 1) {
            res.push_back('1');
        }

        reverse(res.begin(), res.end());

        return res;
    }
};
