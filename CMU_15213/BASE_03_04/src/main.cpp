// C++ 库
#include <iostream>
using namespace std;

// C中的库
#include <stdio.h>
#include "cpu/register.h"
#include "memory/instruction.h"
#include "memory/dram.h"


int main()
{
    uint64_t a = 0x12340000;
    uint64_t b = 0xabcd;

    a + b;
    return 0;
}
/*
gdb下，打上断点 run 在 disas --> 可以反汇编
反汇编命令disas/disass/disassemble

       功能：将内存中的机器码程序以指令助记符的形式显示出来。

       格式： disas/disass/disassemble 函数名/起始地址[,结束地址]

       例如：

       disas main，显示main函数对应的汇编代码 
————————————————
版权声明：本文为CSDN博主「moonsheep_liu」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/moonsheep_liu/article/details/39099969
*/


