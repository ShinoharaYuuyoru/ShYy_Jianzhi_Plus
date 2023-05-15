class Solution {
   public:
    int divide(int a, int b) {
        // 0x80000000: INT_MIN
        // 0x7fffffff: INT_MAX
        // 0xc0000000: INT_MIN / 2

        int result = 0;

        // The case causes int type overflow in `result`
        if ((a == (int)0x80000000) && (b == -1)) {
            return 0x7fffffff;
        }
        // The case causes int type overflow in `quotient` if continue calculating
        if ((a == (int)0x80000000) && (b == 1)) {
            return (int)0x80000000;
        }

        // Confirm result positive or negative
        // Change positive a/b to negative
        bool is_negative = false;
        if (a > 0) {
            a = 0 - a;
            is_negative = !is_negative;
        }
        if (b > 0) {
            b = 0 - b;
            is_negative = !is_negative;
        }

        // Do divide
        // a and b are all negative, so `<=`
        while (a <= b) {
            int now_divisor = b;
            int quotient = 1;

            // Get min now_divisor and max quotient
            while ((now_divisor >= (int)0xc0000000) && (a <= (now_divisor + now_divisor))) {
                quotient += quotient;
                now_divisor += now_divisor;
            }

            result += quotient;
            a -= now_divisor;
        }

        result = (is_negative == false ? result : (0 - result));

        return result;
    }
};
