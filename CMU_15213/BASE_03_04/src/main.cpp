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
    cout << sizeof(op_t) << endl;
    cout << sizeof(od_t) << endl;
    cout << sizeof(inst_t) << endl;
}
/*
gdb下，打上断点 run 在 disas --> 可以反汇编
    反汇编命令disas/disass/disassemble

    功能：将内存中的机器码程序以指令助记符的形式显示出来。

    格式： disas/disass/disassemble 函数名/起始地址[,结束地址]

    例如：

    disas main，显示main函数对应的汇编代码 
    up主：manifoldflow
*/


