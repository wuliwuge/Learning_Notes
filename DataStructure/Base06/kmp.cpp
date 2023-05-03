// 2023-5-3 

#include <stdio.h>
#include <string.h>

// 串的匹配
// BF算法 时间复杂度:O(mn)
int index_bf(char sstr[],char tstr[])  // sstr目标串，tstr模式串
{
    if (!sstr || !tstr) return -1;

    int slen = strlen(sstr), tlen = strlen(tstr);

    int i = 0, j = 0;

    while ( i < slen && j < tlen) {
        if (sstr[i] == tstr[j]) {
            ++i, ++j;
        } else { // 失败进行回溯
            i = i - j + 1; 
            j = 0;
        }
    }

    if (j == tlen) return i - tlen;
    return -1;
}

/*  kmp 算法原理
    1）在匹配的过程中，目标串的指针不需要回溯，只需要回溯模式串的指针即可
    2）如果模式串和目标串前n个字符串匹配成功，遇到匹配失败的字符时，模式串的指针回溯的位置
    由模式串的内容决定（回溯到匹配失败位置前的模式串的内容的最长公共前后缀 的长度 +1），然后继续比较

    最长公共前后缀解释：假设模式串是: ababac 且在最后一个字符匹配失败。
    则:ababa是匹配失败前的模式串的内容.
    前缀有：a ab aba abab 最后一个字符不算，因为是前缀嘛。
    后缀有：a ba aba baba 最前一个字符不算，因为是后缀嘛。
    所以前后缀相等的内容有 a aba 最长为aba 长度等于3
    由 3 + 1 = 4 可得应当将模式串的指针移动到第四个位置 注意这里不是按照 0开始的
*/