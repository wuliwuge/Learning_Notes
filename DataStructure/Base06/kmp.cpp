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

/*  next 数组的计算
    模式串：hello   发生匹配失败的情况  前缀字符串    前后缀             值
                    h                   空                            0  
                    he                   h          无                1
                    hel                  he        h e               0+1=1
                    hell                 hel       h l he el         0+1=1
                    hello                hell      h l he ll hel ell 0+1=1
    下标是从1开始的next数组为 [0,1,1,1,1]
    下标是从0开始的next数组为 [-1,0,0,0,0] --> 这也是C中采用的情况
    #######################################################################
    模式串：ababc    发生匹配失败的情况  前缀字符串    前后缀             值
                     a                   空                            0
                     ab                  a         null                1
                     aba                 ab       a b                  0+1=1
                     abab                aba      a a ab ba            1+1=2
                     ababc               abab     a b ab ab aba bab    2+1=3
    下标是从1开始的next数组为 [0,1,1,2,3]
    下标是从0开始的next数组为 [-1,0,0,1,2]                 
*/


/*  kmp算法的优化
    主要逻辑是如果对于当前的字符不匹配，那么就要根据next数组的值取进行回溯，那如果回溯位置的
    字符与未回溯的一样，这样的比较其实没有意义，这也就是next数组优化的情况 --》nextval数组
    模式串：baabaa
                   b                    空                             0
                   ba                   b             null             1
                   baa                 ba         b a                 0+1=1
                   baab                baa        b a ba aa           0+1=1
                   baaba               baab       b b ba ab baa aab   1+1=2
                   baabaa            baaba     b a ba ba baa aba baab aaba 2+1=3
    下标是从1开始的next数组为 [0,1,1,1,2,3]
    下标是从0开始的next数组为 [-1,0,0,0,1,2]
    nextval 数组就是在next数组的基础上，从第二个字符开始回溯到其新的指针指向的字符与当前是否一致，如果不一致则保留next数组的值。
    如果一致则，将指向回溯位置的next数组的值，填到当前位置的nextval数组中。nextval数组的第一个值为-1
    1> 下标为1的字符是 'a' 回溯位置的下标为0 字符为'b' 值不同所以 nextval[1] = next[1] 的值
    2> 下标为2的字符是 'a' 回溯位置的下标是0 字符为'b' 值不同所以 nextval[2] = next[2]
    3> 下标为3的字符是 'b' 回溯位置的下标是0 字符为'b' 值相同所以 nextval[3] = nextval[next[3]] --> 注意nextval是修改过后的数组，所以从左到右都是新的优化后的值
    4> 下标为4的字符是 'a' 回溯位置的下标是1 字符为'a' 值相同所以 nextval[4] = nextval[next[4]] --> 同理
    5> 下标为5的字符是 'a' 回溯位置的下标是2 字符为'a' 指向同所以 nextval[5] = nextval[next[5]]
    so:netval数组: [-1,0,0,-1,0,0]


    再次以aaaaaa为例：
                  a                   空                               0
                  aa                  a             null               1
                  aaa                 aa            a a                1+1=2
                  aaaa               aaa      a a aa aa                2+1=3
                  aaaaa             aaaa     a a aa aa aaa aaa         3+1=4
                  aaaaaa           aaaaa   a a aa aa aaa aaa aaaa aaaa 4+1=5
    下标是从0开始的next数组为 [-1,0,1,2,3,4]
    1> 下标为1的字符是 'a' 回溯位置的下标是0 字符为'a' 值相同所以 nextval[1] = nextval[next[1]]
    2> 下标为2的字符是 'a' 回溯位置的下标是1 字符为'a' 值相同所以 nextval[2] = nextval[next[2]]  -->由于下标1的位置已经更新所以这里也是最新的
    3> 下标为3的字符是 'a' 回溯位置的下标是2 字符为'a' 值相同所以 nextval[3] = nextval[next[3]]
    4> 下标为4的字符是 'a' 回溯位置的下标是3 字符为'a' 值相同所以 nextval[4] = nextval[next[4]]
    5> 下标为5的字符是 'a' 回溯位置的下标是4 字符为'a' 值相同所以 nextval[5] = nextval[next[5]]
    nextval数组：[-1,-1,-1,-1,-1,-1]
*/

// 根据模式串tstr，计算next数组，字符串的起始位置从0开始
void getnext(char *tstr, int *next)
{
    if (!tstr || !next) {
        return ;
    }

    int tlen = strlen(tstr);   // 模式串的长度

    // 如果模式串的长度小于3，无需计算next数组，直接返回
    if (tlen == 0) return;
    if (tlen == 1) {next[0] = -1; return;}
    if (tlen == 2) {next[0] = -1; next[1] = 0; return;}

    // 否则
    next[0] = -1;  // 位置0直接填入 -1
    next[1] = 0;   // 位置1直接填入 0

    for (int ii = 2; ii < tlen; ++ii) {
        
        int maxlen = 0;   // 最长公共前后缀的长度

        // 用一个循环，得到全部的前后缀，并判断最长公共前后缀
        for (int jj = 1; jj < ii; ++jj) {
            char p1[tlen], p2[tlen];
            memset(p1, 0, sizeof(p1));
            memset(p2, 0, sizeof(p2));

            strncpy(p1, tstr, jj);  // 取前缀
            strncpy(p2, tstr + ii - jj, jj);  // 取后缀

            // 如果前后缀是相同的，则记下jj的值
            if (strcmp(p1, p2) == 0) maxlen = jj;
        }

        next[ii] = maxlen;  // 因为是从0开始计算的，所以也不用+1操作
    } 

    return ;
}

// 根据模式串tstr和next数组，计算nextval数组，下标是从0开始的
void getnextval(char *tstr, int *next, int *nextval) 
{
    if (!tstr || !next || !nextval) return;

    int tlen = strlen(tstr);

    nextval[0] = -1;  // 下标0固定写-1

    for (int i = 1; i != tlen; ++i) {
        if (tstr[i] == tstr[next[i]]) {
            nextval[i] = nextval[next[i]];
        } else {
            nextval[i] = next[i];
        }
    }
}


// 采用kmp算法，查找目标串sstr中模式串tstr出现的位置，字符串的起始位置从0开始
// 成功返回模式串tstr在目标串sstr中第一次出现的数组下标，失败返回-1
int index_kmp(char *sstr, char *tstr)
{
    int ii = 0, jj = 0;
    int slen = strlen(sstr), tlen = strlen(tstr);

    // 获取next数组
    int next[tlen];
    getnext(tstr, next);

    // 根据模式串tstr和next数组计算 nextval数组
    int nextval[tlen];
    getnextval(tstr, next, nextval);

    while (ii < slen && jj < tlen) {
        if (jj == -1 || sstr[ii] == tstr[jj]) {
            ++ii; ++jj;
        } else {
            // jj = next[jj]; // 根据next数组模式串指针回溯
            jj = nextval[jj]; // 根据nextval数组模式串指针回溯
        }
    }

    if (jj == tlen) return ii - tlen;

    return -1;
}

int main() 
{
    ////////////////////////////////////////////////////
    // 获取模式串的next数组，字符串的位置从0开始
    char tmp[100];
    memset(tmp,0,sizeof(tmp));
    strcpy(tmp,"baabaa");
    int next[100];
    getnext(tmp,next);
    printf("next    "); int kk;for (kk=0;kk<strlen(tmp);kk++) printf("%d ",next[kk]); printf("\n");
    ////////////////////////////////////////////////////

    ////////////////////////////////////////////////////
    // 根据模式串tstr和next数组计算nextval数组，下标从0开始
    int nextval[100];
    getnextval(tmp,next,nextval);
    printf("nextval "); int ll;for (ll=0;ll<strlen(tmp);ll++) printf("%d ",nextval[ll]); printf("\n");
    ////////////////////////////////////////////////////

    ////////////////////////////////////////////////////
    // 判断模式串和目标串是否匹配
    // char sstr[100]; memset(sstr,0,sizeof(sstr));
    // char tstr[100]; memset(tstr,0,sizeof(tstr));
    // strcpy(sstr,"aabaabcbcabaabc");
    // strcpy(tstr,"abaabc");
    // printf("index_bf =%d\n", index_bf(sstr,tstr));
    // printf("index_kmp=%d\n",index_kmp(sstr,tstr));
    ////////////////////////////////////////////////////
}
