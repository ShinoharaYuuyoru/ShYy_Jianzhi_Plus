#include <iostream>
#include <limits>
#include <vector>
using namespace std;

// 1
class Solution {
   public:
    vector<int> countBits(int n) {
        vector<int> result((n + 1), 0);  // Init all elements as 0

        for (int i = 0; i <= n; i++) {
            int i_cpy = i;
            while (1) {
                if (i_cpy == 0) {
                    break;
                }

                if ((i_cpy & 1) == 1) {
                    result[i]++;
                }
                i_cpy = (i_cpy >> 1);
            }
        }

        return result;
    }
};

// 2
class Solution {
   public:
    vector<int> countBits(int n) {
        vector<int> result((n + 1), 0);

        for (int i = 1; i <= n; i++) {
            int i_cpy = i;
            while (1) {
                if (i_cpy == 0) {
                    break;
                } else {
                    result[i]++;
                    i_cpy = (i_cpy & (i_cpy - 1));
                }
            }
        }

        return result;
    }
};

// 3
class Solution {
   public:
    vector<int> countBits(int n) {
        vector<int> result((n + 1), 0);

        for (int i = 1; i <= n; i++) {
            result[i] = result[i & (i - 1)] + 1;
        }

        return result;
    }
};

// 4
class Solution {
   public:
    vector<int> countBits(int n) {
        vector<int> result((n + 1), 0);

        for (int i = 1; i <= n; i++) {
            result[i] = result[i >> 1] + (i & 1);
        }

        return result;
    }
};

// 5.1
class Solution {
   public:
    vector<int> countBits(int n) {
        vector<int> result((n + 1), 0);

        for (int i = 1; i <= n; i++) {
            result[i] = loopup_popcount((uint32_t)i);
        }

        return result;
    }

   private:
    int loopup_popcount(uint32_t n) {
#if 0  // generate the table algorithmically, and you should put it outside.
    static uint8_t table[256] = {0};
    for(uint32_t i = 1; i < 256; ++i)
        table[i] = table[i>>1] + i & 1U;
    
    const uint8_t* p = reinterpret_cast<const uint8_t*>(&n);
    return table[p[0]] + table[p[1]] + table[p[2]] + table[p[3]];
#else
#define BIT2(n) n, n + 1, n + 1, n + 2
#define BIT4(n) BIT2(n), BIT2(n + 1), BIT2(n + 1), BIT2(n + 2)
#define BIT6(n) BIT4(n), BIT4(n + 1), BIT4(n + 1), BIT4(n + 2)
#define BIT8(n) BIT6(n), BIT6(n + 1), BIT6(n + 1), BIT6(n + 2)

        static const uint8_t table[256] = {BIT8(0)};
        return table[n & 0xff] + table[(n >> 8) & 0xff] + table[(n >> 16) & 0xff] + table[(n >> 24) & 0xff];
#endif
    }
};

// 5.2
class Solution {
   public:
    vector<int> countBits(int n) {
        vector<int> result((n + 1), 0);

        for (int i = 1; i <= n; i++) {
            result[i] = parallel_popcount((uint32_t)i);
        }

        return result;
    }

   private:
    int parallel_popcount(uint32_t n) {
#define POW2(c) (1U << (c))
#define MASK(c) (static_cast<uint32_t>(-1) / (POW2(POW2(c)) + 1U))
#define COUNT(x, c) ((x & MASK(c)) + ((x >> POW2(c)) & MASK(c)))
        n = COUNT(n, 0);
        n = COUNT(n, 1);
        n = COUNT(n, 2);
        n = COUNT(n, 3);
        n = COUNT(n, 4);
        //	n = COUNT(n, 5);  // uncomment this line for 64-bit integers
        return n;
#undef COUNT
#undef MASK
#undef POW2
    }
};

// 5.3
class Solution {
   public:
    vector<int> countBits(int n) {
        vector<int> result((n + 1), 0);

        for (int i = 1; i <= n; i++) {
            result[i] = nifty_popcount((uint32_t)i);
        }

        return result;
    }

   private:
    int nifty_popcount(uint32_t n) {
        constexpr uint32_t max = std::numeric_limits<uint32_t>::max();
        constexpr uint32_t MASK_01010101 = max / 3;
        constexpr uint32_t MASK_00110011 = max / 5;
        constexpr uint32_t MASK_00001111 = max / 17;
        n = (n & MASK_01010101) + ((n >> 1) & MASK_01010101);
        n = (n & MASK_00110011) + ((n >> 2) & MASK_00110011);
        n = (n & MASK_00001111) + ((n >> 4) & MASK_00001111);
        return n % 255;
    }
};

// 5.4
class Solution {
   public:
    vector<int> countBits(int n) {
        vector<int> result((n + 1), 0);

        for (int i = 1; i <= n; i++) {
            result[i] = hacker_poopcount((uint32_t)i);
        }

        return result;
    }

   private:
    int hacker_poopcount(uint32_t n) {
        n = n - ((n >> 1) & 0x55555555);
        n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
        n = (n + (n >> 4)) & 0x0f0f0f0f;
        n = n + (n >> 8);
        n = n + (n >> 16);
        return n & 0x3f;
    }
};

// 5.5
class Solution {
   public:
    vector<int> countBits(int n) {
        vector<int> result((n + 1), 0);

        for (int i = 1; i <= n; i++) {
            result[i] = hakmem_popcount_original((uint32_t)i);
        }

        return result;
    }

   private:
    int hakmem_popcount_original(uint32_t n) {
        unsigned int tmp;
        tmp = n - ((n >> 1) & 033333333333) - ((n >> 2) & 011111111111);
        return ((tmp + (tmp >> 3)) & 030707070707) % 63;
    }

    int hakmem_popcount(uint32_t n) {
        uint32_t n_temp;
        n_temp = (n >> 1) & 033333333333;  // Octal. Count bits in each 3-bit field.
        n = n - n_temp;
        n_temp = (n_temp >> 1) & 033333333333;
        n = n - n_temp;
        n = (n + (n >> 3)) & 030707070707;  // 6-bit sums
        return n % 63;
    }
};
