// 浮点数、类型转换
// 这大哥讲的我头疼，可以在有点基础之上，直接去看 csapp
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <stdint.h>

void test01()
{
    /*
        10进制下 浮点的表示
        123.12  ->  1.2312 * 10^2(科学计数法)
        1*10^2 + 2*10^1 + 3*10^0 + 1*10^-1 + 2*10^-2
        2进制同理
        1010.0101 -> 1.0100101 * 2^3 (暂不考虑有符号)
        1*2^3 + 0*2^2 + 1*2^1 + 0*2^0 + 0*2^-1 + 1*2^-2 + 0*2^-3 + 1*2^-4
        8     +   0   +   2   +  0    +  0     +  0.25  +   0    +  0.00625

        C中浮点表示：
        1.Normalized(规范化的) --> 无法表示0等
        (-1)^s(signal) * (1+f)(fraction) * 2^E(E=(e - bias))  此处减去127这个偏执常数(bias)是为了平衡小的有理数，而不仅仅只取大的有理数 由IEEE定的。double同理。 bias = 2^(k - 1) - 1  k 表示 e 的位数
        以flaot为例：
        s：m[31]   e:[30:23]   f:[22:0]

        2.Denormalized(非规)
        s       e                     f
        s  0 0 0 0 0 0 0 0            f   --> 阶全为0    
        (-1)^s + 0.f * 2^(1 - 127) --> 非规约的话 f为 0.xxx 扩展了更小的有理数  E = 1 - bias (非规格化)

        3.infinity(无穷)
        s       e                     f
        s  1 1 1 1 1 1 1 1           f(23个0)   -->

        4.NaN(not a number)
        s       e                     f
        s  1 1 1 1 1 1 1 1            f(不全为0)   -->
    */

    // 2.Denormalized(非规)
    unsigned a = 0x00400000;  // 0 000 0000 0100 ....0
    std::cout << *(float*)&a << std::endl;  // 5.87747e-039
    std::cout << pow(2, -126) * 0.5 << std::endl; // 5.87747e-039

    // 3.infinity(无穷)
    a = 0x7f800000;// 0 11111111 0000..00
    std::cout << *(float*)&a << std::endl;  // inf 有符号则表示负无穷，无符号则表示正无穷
    a = 0xff800000; // 1 11111111 0000...0   
    std::cout << *(float*)&a << std::endl;  // -inf 有符号则表示负无穷，无符号则表示正无穷

    // 4.NaN(not a number)
    a = 0xffffffff;
    std::cout << *(float*)&a << std::endl;  // 阶数全为0 但是 f不全为0则 nan

    // e 和 f全0
    a = 0x00000000; 
    std::cout << *(float*)&a << std::endl; // +0
    a = 0x80000000;
    std::cout << *(float*)&a << std::endl; // -0

}

uint32_t uint2float(uint32_t u)
{
    if (u == 0) {
        return 0;
    }

    // must exist highest 1 : 存在最高位 1
    int n = 0;
    for (int i = 0; i < 31; ++i) { // 寻找最高位1
        if ((u >> i) == 0x1) {
            n = i;
            break;
        }
    }

    // 这里判断 前导1 的位置 如果大于 23 需要做近似，小于则不需要，意思是听懂了，逻辑给我看晕了。md
    /* 其他人的理解。
        后边uint32转浮点讲的有点乱，写一下我自己的理解。单精度浮点数因为有阶码的存在，尾数的有效位只有23位，
        一个32位的无符号数u转换过来可能会有精度损失，所以首先要判断是否需要近似，因为浮点数默认省略了一个1，所以只要1右侧的所有数是小于等于23位就不需要近似。
        在不需要近似的情况下，符号位可以直接获得，尾数可以通过对应的掩码求出，阶码对应小数点从最后浮动到了1右侧，浮动了n个数，所以减去127后等于n。
        当需要近似的时候，其实就是在小数点后23位的地方做一个十进制里的四舍六入五成双操作，十进制中的.5是均分了这个区间的位置，
        对应到二进制里，其实就是.1000后边都是零这样一个数，如果比这个数大，就可以直接向上入，比他小就可以直接切断舍去，当相等的时候，要成双，在二进制里，奇偶性是很好判断的，
        小数点前是0就是偶数，是1就是奇数，再近似计算就好。
    https://gist.github.com/yangminz/a724fff09454cefa680373f3ff64e2a4
    https://blog.csdn.net/qq_45698833/article/details/112859354?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522167318269516782429742248%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=167318269516782429742248&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-3-112859354-null-null.142^v70^wechat,201^v4^add_ask&utm_term=cmu%20uint32%20%E8%BD%AC%E6%8D%A2%E6%88%90%20float&spm=1018.2226.3001.4187

    浮点数的舍入 还有点小疑问。。。还得再看看。。。
    */

}

void test02()
{
    using namespace std;

    unsigned a = 0b01000110011011011011010000000000;
    cout << a << endl;
    cout << *(float*)&a << endl;
    printf("%f\n", (1 * pow(2,-1) + 1 * pow(2, -2) + 1 * pow(2, -4) + 1 * pow(2, -5) + 1 * pow(2, -7) + 1 * pow(2, -8) + 1 * pow(2, -10) + 1 * pow(2, -11) + 1 * pow(2, -13)));
    cout << pow(2, 13) * 1.857056 << endl;
    cout << pow(2, 4 -1) - 1 <<endl;
}

int main()
{
    

    test01();
}