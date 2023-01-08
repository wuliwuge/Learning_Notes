// C语言、位操作、树状数组

#include <stdlib.h>
#include <stdio.h>

void test01()
{
    // elf：executable object file
    // print: 打印 f:format 格式化输出
    printf("Hello world\n");
}

void test02()
{
    int a = 2147483647;
    printf("0x%x\n", a + 1); // overflow  0x80000000
}

unsigned LowBit(unsigned x)
{
    // 返回 最低位位1到低位的值
    // eg：0b1010 返回 0b10
    return x & ((~x) + 1);

    /*
        why:
        segment array -> tree like array : 树状数组 -》 会使用到 LowBit 操作
        归纳法：
          x         ~x       -x（取反加一，本质是overflow 处 做了 180度的旋转，其实就是不同的符号 表示同一个东西(同构)）
        aaaaaaa1  bbbbbbb0  bbbbbbb1 
          x  &  (-x)  -->  aaaaaaa1 & bbbbbbb1 = 00000001
        那如果 1 不在最低为喃？-》同理
          x        ~x        -x
        aaaa1000  bbbb0111  bbbb1000
          x  &  (-x)  -->  aaaa1000 & bbbb1000 = 00001000
    */
}

// 位操作
void test03()
{
    /*
        0 -> 1 非
        1 -> 0 非
        0 & 0 = 0、1 & 0 = 0、1 & 1 = 1、0 & 1 = 0 与
        0 | 0 = 0、1 | 0 = 1、1 | 1 = 1、0 | 1 = 1 或
    */
   int a = 2147483647;
   int b = 1;
   printf("0x%x\n", LowBit(0b1010));
}

// 树状数组
void test04()
{
    
    // T代表树状数组，S代表前缀和数组
    unsigned n = 7;
    
    printf("S[%u] = ", n);
    printf("T[%u] + ", n);
    n = n - LowBit(n);
    printf("T[%u] + ", n);
    n = n - LowBit(n);
    printf("T[%u] + ", n);
    n = n - LowBit(n);
    printf("T[%u]", n); // T0 = 0

    // S[7] = T[7] + T[6] + T[4] 此处以7项前缀和，与 树状数组的关系
    // 如果是求S7 那么需要 遍历 n(7), 如果是树状数组的话 logN --》 时间复杂度低
}

// 如何判断16进制数中那些数是字母那些数字
unsigned Letter(unsigned x)
{
    /*
        一个16进制的数可以通过 4bit 来表示
        下图0表示 该16进制数位数字，1表示为字母
                   X3X2 = 00    X3X2 = 01    X3X2 = 10    X3X2 = 11
        X1X0 = 00    0(0)        0(4)         0(8)         1(c) 
        X1X0 = 01    0(1)        0(5)         0(9)         1(d)
        X1X0 = 10    0(2)        0(6)         1(a)         1(e)
        X1X0 = 11    0(3)        0(7)         1(b)         1(f)
        通过上面观察所得：当X3=1 X2=1 时 真值表为1，当X3=1 X1=1时 真值图也为1 so 当X3为1时，只要 X2 和 X1 有一个为1即可表示为字母，与X0无关
        代码结果可得：X3 & (X2 | X1) = 1 则 该16进制为字母

    */

   unsigned a = x;
   /*
        X3 X2 X1 X0   - hex 
    &   0  0  1  0   &- hex constant - 0x2
        0  0  X1 0   
        0x22222222 & a -> 将32位中 8个 16机制数的 X1 取出
        同理取出 X2
        0  1  0  0   &- hex constant 0x4
        0  X2 0  0
        0x44444444 & a -> 将X2取出
        。。。。 
   */

    unsigned x1 = a & 0x22222222;
    unsigned x2 = a & 0x44444444;
    unsigned x3 = a & 0x88888888;

    return (x3 >> 3) & ((x2 >> 2) | (x1 >> 1)); // 将 x3 x2 x1 移动到同一位置
    // printf("0x%x : %x\n", 0xabcd1123， Letter(0xabcd1123));
}

// 32
int main()
{
    printf("0x%x : %x\n", 0xabcd1123, Letter(0xabcd1123));
    return 0;
}