// 浮点数、类型转换

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>

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
        (-1)^s(signal) * 1.f(fraction) * 2^(e - 127)  此处减去127这个偏执常数(bias)是为了平衡小的有理数，而不仅仅只取大的有理数 由IEEE定的。double同理。
        以flaot为例：
        s：m[31]   e:[30:23]   f:[22:0]

        2.Denormalized(非规)
        s       e                     f
        s  0 0 0 0 0 0 0 0            f   --> 阶全为0    
        (-1)^s + 0.f * 2^(e - 127) --> 非规约的话 f为 0.xxx 扩展了更小的有理数

        3.infinity(无穷)
        s       e                     f
        s  1 1 1 1 1 1 1 1           f(23个0)   -->

        4.NaN(not a number)
        s       e                     f
        s  1 1 1 1 1 1 1 1            f(不全为0)   -->
    */

    // 2.Denormalized(非规)
    unsigned a = 0x00400000;
    std::cout << *(float*)&a << std::endl;  // 5.87747e-039
    std::cout << pow(2, -127) * 0.1 << std::endl; // 5.87747e-040 有点差异，不知道那理解错了

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


int main()
{
    test01();

}