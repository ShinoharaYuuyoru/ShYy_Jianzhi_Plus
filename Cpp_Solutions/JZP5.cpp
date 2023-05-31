#include <string>
#include <vector>
using namespace std;

// 1
class Solution {
   public:
    int maxProduct(vector<string>& words) {
        int result = 0;

        for (unsigned int i = 0; i < words.size(); i++) {
            for (unsigned int j = i + 1; j < words.size(); j++) {
                bool flag = false;
                for (unsigned int k = 0; k < words[i].size(); k++) {
                    for (unsigned int l = 0; l < words[j].size(); l++) {
                        if (words[i][k] == words[j][l]) {
                            flag = true;
                            break;
                        }
                    }
                    if (flag == true) {
                        break;
                    }
                }
                if (flag == false) {
                    unsigned int mult_result = words[i].size() * words[j].size();
                    result = ((mult_result > result) ? mult_result : result);
                }
            }
        }

        return result;
    }
};

// 2
class Solution {
   public:
    int maxProduct(vector<string>& words) {
        int result = 0;

        vector<vector<bool> > word_char_hash(words.size(), vector<bool>(26, false));
        for (unsigned int i = 0; i < words.size(); i++) {
            for (unsigned int j = 0; j < words[i].size(); j++) {
                word_char_hash[i][words[i][j] - 'a'] = true;
            }
        }

        for (unsigned int i = 0; i < words.size(); i++) {
            for (unsigned int j = i + 1; j < words.size(); j++) {
                bool flag = false;
                for (unsigned int k = 0; k < 26; k++) {
                    if (word_char_hash[i][k] && word_char_hash[j][k]) {
                        flag = true;
                        break;
                    }
                }
                if (flag == false) {
                    unsigned int mult_result = words[i].size() * words[j].size();
                    result = ((mult_result > result) ? mult_result : result);
                }
            }
        }

        return result;
    }
};

// 3
class Solution {
   public:
    int maxProduct(vector<string>& words) {
        int result = 0;

        vector<unsigned int> word_char_hash(words.size(), 0);
        for (unsigned int i = 0; i < words.size(); i++) {
            for (unsigned int j = 0; j < words[i].size(); j++) {
                word_char_hash[i] |= (1 << (words[i][j] - 'a'));
            }
        }

        for (unsigned int i = 0; i < words.size(); i++) {
            for (unsigned int j = i + 1; j < words.size(); j++) {
                if ((word_char_hash[i] & word_char_hash[j]) == 0) {
                    unsigned int mult_result = words[i].size() * words[j].size();
                    result = ((mult_result > result) ? mult_result : result);
                }
            }
        }

        return result;
    }
};
