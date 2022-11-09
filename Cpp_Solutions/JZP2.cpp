#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string addBinary(string a, string b) {
    string res = "";

    unsigned int carry_bit = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;
    while (i >= 0 || j >= 0) {
        unsigned int a_bit = (i >= 0 ? a[i] - '0' : 0);
        unsigned int b_bit = (j >= 0 ? b[j] - '0' : 0);
        i--;
        j--;

        unsigned int sum = a_bit + b_bit + carry_bit;
        carry_bit = (sum >= 2 ? 1 : 0);
        unsigned int sum_bit = (sum >= 2 ? sum - 2 : sum);

        char bit_res = '0' + sum_bit;
        res.push_back(bit_res);
    }
    if (carry_bit == 1) {
        res.push_back('1');
    }

    reverse(res.begin(), res.end());
    return res;
}

int main() {
    cout << addBinary("10101011101010101", "10000001111111") << endl;
}
