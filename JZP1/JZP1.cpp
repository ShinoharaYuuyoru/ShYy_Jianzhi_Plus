/* YOU CAN NOT USE `*', `/', AND `%' OPERATORS! */

#include <climits>
#include <iostream>

using namespace std;

int divide(int dividend, int divisor) {
    // 0x80000000: INT_MIN
    // 0x7fffffff: INT_MAX
    // 0xc0000000: INT_MIN / 2

    // The only case causes int overflow
    if ((dividend == (int)0x80000000) && (divisor == -1)) {
        return 0x7fffffff;
    }

    // Change positive to negative
    bool isNegative = false;
    if (dividend > 0) {
        dividend = 0 - dividend;
        isNegative = !isNegative;
    }
    if (divisor > 0) {
        divisor = 0 - divisor;
        isNegative = !isNegative;
    }

    // Start divide
    int result = 0;
    // dividend and divisor are all negative, so `<=`
    while (dividend <= divisor) {
        int newDivisor = divisor;
        int quotient = 1;
        while ((newDivisor >= (int)0xc0000000) && (dividend <= newDivisor + newDivisor)) {
            quotient += quotient;
            newDivisor += newDivisor;
        }

        result += quotient;
        dividend -= newDivisor;
    }

    result = (isNegative == false ? result : (0 - result));
    return result;
}

int main() {
    cout << divide(0x81234567, 0xe3216547) << endl;
}
