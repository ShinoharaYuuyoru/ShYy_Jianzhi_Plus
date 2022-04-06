# 剑指Offer专项突破版 面试题题解及思路

## 面试题1：整数除法

```c
int divide(int dividend, int divisor);
```

1. 解法：循环减去`divisor`。复杂度O(n)。  
2. 优化：每次减去最大`divisor * 2^n, n为自然数`。复杂度O(nlogn)。此为**最优算法**。
3. 情况：`dividend`和`divisor`不同号。将二者都统一为正数或负数，最后处理符号。
4. 边界：统一为正数还是负数？负数。`int`的范围为`[-2^(n-1), 2^(n-1)-1]`。那么只有一种情况出现溢出：`dividend = -2^(n-1)`，`divisor = -1`，返回值按题设置为`INT_MAX`。
5. 优化：减去的`divisor`有限制：`INT_MIN / 2`。当`divisor < (INT_MIN / 2)`时可以退出循环。
