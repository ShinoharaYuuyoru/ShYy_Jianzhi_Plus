class Solution {
   public:
    int divide(int dividend, int divisor) {
        // 0x80000000: INT_MIN
        // 0x7fffffff: INT_MAX
        // 0xc0000000: INT_MIN / 2

        // The case causes int type overflow in `result`
        if ((dividend == (int)0x80000000) && (divisor == -1)) {
            return 0x7fffffff;
        }
        // The case causes int type overflow in `quotient` if continue calculating
        if ((dividend == (int)0x80000000) && (divisor == 1)) {
            return 0x80000000;
        }

        // Confirm result positive or negative
        // Change positive dividend/divisor to negative
        bool is_negative = false;
        if (dividend > 0) {
            dividend = 0 - dividend;
            is_negative = !is_negative;
        }
        if (divisor > 0) {
            divisor = 0 - divisor;
            is_negative = !is_negative;
        }

        // Do divide
        int result = 0;
        // dividend and divisor are all negative, so `<=`
        while (dividend <= divisor) {
            int now_divisor = divisor;
            int quotient = 1;

            // Get min now_divisor and max quotient
            while ((now_divisor >= (int)0xc0000000) && (dividend <= (now_divisor + now_divisor))) {
                quotient += quotient;
                now_divisor += now_divisor;
            }

            result += quotient;
            dividend -= now_divisor;
        }

        result = (is_negative == false ? result : (0 - result));

        return result;
    }
};
