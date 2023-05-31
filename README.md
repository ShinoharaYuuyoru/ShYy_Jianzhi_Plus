# 《剑指Offer专项突破版》题解

<https://leetcode.cn/problem-list/e8X3pBZi/>

## JZP1：整数除法

1. 方法：暴力循环。循环减去`b`。时间复杂度`O(n)`。TLE。
2. 方法：二分循环。每次减去最大`b * 2^n, 其中n为自然数`。复杂度`O(logn)`。
   1. 情况：`a`和`b`不同号。
      1. 将二者都统一为正数或负数，最后处理符号。
      2. 统一为正数还是负数？负数。
   2. 情况：当`a == INT_MIN`，`b == -1`时
      1. 结果溢出，返回题设要求`INT_MAX`。
   3. 情况：当`a == INT_MIN`，`b == 1`时
      1. `quotient`累加进行到`quotient == 0x40000000`时会继续循环进行累加，导致下一次`quotient == 0x80000000`，造成溢出。
      2. 直接返回`INT_MIN`。
   4. 情况：退出累加条件
      1. 因为全程使用负数进行累加，因此`now_divisor`不可小于`(INT_MIN / 2)`，否则退出累加。
      2. 当前的`a`应当小于2倍`now_divisor`,否则退出累加。
   5. 备注：
      1. 32位`int`的范围为`[-2^31, 2^31-1]`。
         1. `INT_MAX == 2^31-1 == 0x7fffffff`
         2. `INT_MIN == -2^31 == 0x80000000`
         3. `(INT_MIN / 2) == -2^30 == 0xc0000000`

----------

## JZP2：二进制加法

1. 方法：暴力竖式加法。直接对字符串进行竖式加法。时间复杂度`O(n)`。
   1. 注意：使用`i`和`j`从数组的最后往前扫，因为`i`和`j`会以`-1`值作为退出循环判断条件，因此必须使用`int`类型，而不是`unsigned int`。
   2. 注意：如果两个数位数相等，最后有可能会多出一个进位，要加上此进位。

----------

## JZP3：前 n 个数字二进制中 1 的个数

1. 方法：暴力扫描。若`((i_cpy & 1) == 1)`则累计，然后`i_cpy >> 1`。时间复杂度`O(kn)`，其中`k`为整数的二进制位数。
2. 方法：优化暴力扫描。由数字的二进制表示，可发现规律：`i_cpy & (i_cpy - 1)`可消除掉`i_cpy`的最右边的`1`，然后令`i_cpy = i_cpy & (i_cpy - 1)`，直至`i_cpy == 0`。时间复杂度`O(kn)`，其中`k`为整数的二进制位数。
3. 方法：动态规划。根据`方法2`，可发现规律：`i`始终比`i & (i - 1)`多1个`1`。时间复杂度`O(n)`。
   1. 初始条件：`result[0] = 0`。
   2. 递推公式：`result[i] = result[i & (i - 1)] + 1`。
4. 方法：动态规划。当`i`为奇数时，`i / 2`中`1`的个数比`i`中的要少1个；当`i`为偶数时，`i / 2`中`1`的个数和`i`中的相同。时间复杂度`O(n)`。
   1. 初始条件：`result[0] = 0`。
   2. 递推公式：`result[i] = result[i >> 1] + (i & 1)`。
5. 其他popcount算法。时间复杂度均为`O(n)`。Ref：[popcount 算法分析](https://zhuanlan.zhihu.com/p/341488123)
   1. lookup_popcount
      1. 打uint8_t的表，每次计算8bit。在打表时用到了`方法4`中提到的规律。
   2. parallel_popcount
      1. 对给出的数`n`，以每`k`位为一组（当`k == 1`时为初始`k`值，可得`n`的popcount值），那么考虑`2k`位时，有：`n == a * 2^k + b`，其中`a`为高`k`位，`b`为低`k`位，可得`n`的popcount值为`a + b`。以此类推，对32位的值只需迭代5次，64位需迭代6次。下面为迭代MASK：

      ```C
         01010101 01010101 01010101 01010101 == 0x55555555 == (0xffffffff / (0x2+1)) == (0xffffffff / (2^(2^0) + 1))
         00110011 00110011 00110011 00110011 == 0x33333333 == (0xffffffff / (0x4+1)) == (0xffffffff / (2^(2^1) + 1))
         00001111 00001111 00001111 00001111 == 0x0F0F0F0F == (0xffffffff / (0x10+1)) == (0xffffffff / (2^(2^2) + 1))
         00000000 11111111 00000000 11111111 == 0x00FF00FF == (0xffffffff / (0x100+1)) == (0xffffffff / (2^(2^3) + 1))
         00000000 00000000 11111111 11111111 == 0x0000FFFF == (0xffffffff / (0x10000+1)) == (0xffffffff / (2^(2^4) + 1))
      ```

   3. nifty_popcount
      1. 优化的parallel_popcount。在末尾通过`% 255`完成计算。
         1. 证明：设一个`k`进制数`B(B_n B_(n-1) ... B_1 B_0)`，其中`n`表示共有`n`位数，`0 <= B_i < k`。那么数`B`亦可记作：`B = (B_n * k^(n-1)) + (B_(n-1) * k^(n-2) + ... + (B_1 * K) + (B_0))`。根据定理`k^i 与 1，对(k - 1)同余`，上式中的每一项均对`k - 1`同余，因此`B 与 SUM(B_n, B_(n-1), ... B_1, B_0)， 对(k - 1)同余`。于是有结论：**一个`k`进制数模`k - 1`的结果，等于此k进制数的各位的和再模`k - 1`**。
         2. 在上述结论之上，如果能确定`SUM(B_n, B_(n-1), ... B_1, B_0) < (k - 1)`，则可将上述结论加强为：`popcount(B) = B % (k - 1)`。为了使用此加强结论，对于32位整型的最大popcount值32，因为`(2^(2^2) - 1) < 32 < (2^(2^3) - 1)`，因此必须对原数至少进行**3次**迭代，成为256进制，最后对255取模；对于64位整型，最大popcount值64亦满足此不等式，也对255取模。
   4. hacker_popcount
      1. 优化的parallel_popcount。
      2. 请翻阅[Hacker's Delight 2nd Edition](https://www.semanticscholar.org/paper/Hacker's-Delight-Warren/f5bf32bade6ae00d33d99d5f53fcc7b4c466c68c)，Chapter 5. Counting Bits。
   5. hakmem_popcount
      1. 优化的parallel_popcount，结合了nifty_popcount。
      2. 请翻阅[Hacker's Delight 2nd Edition](https://www.semanticscholar.org/paper/Hacker's-Delight-Warren/f5bf32bade6ae00d33d99d5f53fcc7b4c466c68c)，Chapter 5. Counting Bits。
      3. 以下为*HACKMEM 169*原文

      ```C
      /*
      HAKMEM Popcount

      Consider a 3 bit number as being
         4a+2b+c
      if we shift it right 1 bit, we have
         2a+b
      subtracting this from the original gives
         2a+b+c
      if we shift the original 2 bits right we get
         a
      and so with another subtraction we have
         a+b+c
      which is the number of bits in the original number.

      Suitable masking  allows the sums of  the octal digits  in a 32 bit  number to
      appear in  each octal digit.  This  isn't much help  unless we can get  all of
      them summed together.   This can be done by modulo  arithmetic (sum the digits
      in a number by  molulo the base of the number minus  one) the old "casting out
      nines" trick  they taught  in school before  calculators were  invented.  Now,
      using mod 7 wont help us, because our number will very likely have more than 7
      bits set.   So add  the octal digits  together to  get base64 digits,  and use
      modulo 63.   (Those of you  with 64  bit machines need  to add 3  octal digits
      together to get base512 digits, and use mod 511.)

      This is HACKMEM 169, as used in X11 sources.
      Source: MIT AI Lab memo, late 1970's.
      */
      int hakmem_popcount(uint32_t n) {
         unsigned int tmp;
         tmp = n - ((n >> 1) & 033333333333) - ((n >> 2) & 011111111111);
         return ((tmp + (tmp >> 3)) & 030707070707) % 63;
      }
      ```

----------

## JZP4：只出现一次的数字

1. 方法：所有数字的二进制位累加取余。时间复杂度`O(n)`。
   1. 对所有数字进行二进制位数的累加，并对累加结果遍历。
      1. 如果某位累加结果能被`3`整除，则说明在此位只能由出现`3`次的数组成，因此出现`1`次的数在此位必为`0`。
      2. 如果某位累加结果除`3`余`1`，则说明在此位只能由出现`1`次的数组成，因此出现`1`次的数在此位必为`1`。
   2. 推广：若数组中只有一个数字出现`m`次，其他数字均出现`n`次，请找出唯一出现`m`次的数。假设`m`不能被`n`整除。
      1. 对所有数字进行二进制位数的累加，并对累加结果遍历。
         1. 如果某位累加结果能被`n`整除，说明在此位只能由出现`n`次的数组成，因此出现`m`次的数在此位必为`0`。
         2. 如果某位累加结果除`n`余`m（当 m < n）`或`(m - n)（当 m > n）`（简单来说，有余数），则说明在此位只能由出现`m`次的数组成，因此出现`m`次的数在此位必为`1`。

----------

## JZP5：单词长度的最大乘积

1. 方法：暴力遍历。对所有字符串两两比较。时间复杂度`O(n^2 * k^2)`，其中`n`为给出的字符串个数，`k`为字符串的平均长度。TLE。
2. 方法：哈希表。时间复杂度`O(kn + n^2)`，其中`n`为给出的字符串个数，`k`为字符串的平均长度。
   1. 构建哈希表：因为所有字符串均由`a - z`构成，因此对每个字符串构建长度为`26`的布尔型哈希表，记录字符串中出现的字符即可。此过程时间复杂度为`O(kn)`。
   2. 然后对所有字符串两两比较，比较对应的哈希表。每次比较仅需比较`26`次。若在同一个位置上二者均为`true`，则结束比较；若比较到最后均无上述情况，则计算二者长度的乘积并记录最大值。
3. 方法：优化哈希表。在`方法1`的基础上，优化使用一个整型表示每个字符串的哈希表。时间复杂度`O(kn + n^2)`。
   1. 构建哈希表：对每个字符串使用一个整型表示其哈希表。其中第`0`位表示是否出现字符`a`，第`1`位表示是否出现字符`b`，以此类推。
   2. 然后对所有字符串两两比较。计算两个字符串是否有同样的字符，仅需将二者哈希表对应的整型进行**与运算**。若结果为`0`则表示没有相同的字符，反之则有。
