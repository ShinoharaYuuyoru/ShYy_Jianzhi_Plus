# 剑指Offer专项突破版 面试题题解及思路

<https://leetcode.cn/problem-list/e8X3pBZi/>

## JZP1：整数除法

1. 思路：循环减去`divisor`。复杂度O(n)。  
2. 思路：每次减去最大`divisor * 2^n, n为自然数`。复杂度O(nlogn)。
   1. 情况：`dividend`和`divisor`不同号。将二者都统一为正数或负数，最后处理符号。统一为正数还是负数？负数。32位`int`的范围为`[-2^31, 2^31-1]`。那么当`dividend == -2^31`，`divisor == -1`时，结果必溢出，返回值按题设置为`INT_MAX`。
   2. 情况：当`dividend = -2^31`，`divisor = 1`时，使用此算法将`quotient`累加进行到`quotient == 0x40000000`时依旧会进行累加计算。从另一个角度讲，此算法使用了始终为正数的`quotient`作为`result`的临时计算结果，然后最终通过被除数和除数的符号进行符号变换。那么在此情况下会使得`quetient`溢出。因此此情况也要做特殊处理：直接返回`INT_MIN`。
   3. 优化：减去的`divisor`有优化空间：`INT_MIN / 2`。当`divisor < (INT_MIN / 2)`时可以退出`quotient`累加循环。
      1. INT_MAX: 2^31-1 == 0x7FFFFFFF
      2. INT_MIN: -2^31 = 0x80000000
      3. (INT_MIN / 2): -2^30 == 0xC0000000

----------

## JZP2：二进制加法

1. 思路：直接做二进制加法。
   1. 注意：不能简单将`a`和`b`转化为`int`或其他类型，因为没有限制`a`和`b`的长度，会导致溢出。
   2. 注意：如果两个数位数相等，最后有可能会多出一个进位，要加上。

----------
