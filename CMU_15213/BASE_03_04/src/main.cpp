// C++ 库
#include <iostream>
using namespace std;

// C中的库
#include <stdio.h>

#include "cpu/register.h"
#include "memory/instruction.h"
#include "memory/dram.h"
#include "disk/elf.h"
#include "cpu/mmu.h"

int main()
{
    // 加载操作符运算
    init_handler_table();

    // init 寄存器
    reg.rax = 0x12340000;
    reg.rbx = 0x0;
    reg.rcx = 0x8000660;
    reg.rdx = 0xabcd;
    reg.rsi = 0x7ffffffee2f8;
    reg.rdi = 0x1;
    reg.rbp = 0x7ffffffee210;
    reg.rsp = 0x7ffffffee1f0;

    reg.rip = (uint64_t)&program[11]; // main 的入口

    // 初始化内存
    // 虚拟地址转物理地址, 栈的高地址为起始地址 所以 高地址在前，且栈底为 rbp 栈顶(top)rsp
    write64bits_dram(va2pa(0x7ffffffee210), 0x08000660); // rbp
    write64bits_dram(va2pa(0x7ffffffee208), 0x0); 
    write64bits_dram(va2pa(0x7ffffffee200), 0xabcd); 
    write64bits_dram(va2pa(0x7ffffffee1f8), 0x12340000); 
    write64bits_dram(va2pa(0x7ffffffee1f0), 0x08000660); // rsp

    // uint64_t pa = va2pa(0x7ffffffee210);

    // printf("%016lx\n", *((uint64_t *)(&mm[pa]))); // 自主验证
    // printf("%016lx\n", read64bits_dram(pa));      // read func 验证
    
    print_register();
    print_stack();
    
    // run inst
    for (int i = 0; i != 15; ++i) {
        if (i == 7)
        {
            cout << "debuging" << endl;
        }
        instruction_cycle();

        print_register();
        print_stack();
    }

    // verify
    int match = 1;
    match = match && (reg.rax == 0x1234abcd);
    match = match && (reg.rbx == 0x0);
    match = match && (reg.rcx == 0x8000660);
    match = match && (reg.rdx == 0x12340000);
    match = match && (reg.rsi == 0xabcd);
    match = match && (reg.rdi == 0x12340000);
    match = match && (reg.rbp == 0x7ffffffee210);
    match = match && (reg.rsp == 0x7ffffffee1f0);

    if (match == 1)
    {
        cout << "register match" << endl;
    }
    else 
    {
        cout << "register not match" << endl;
    }


    match = match && (read64bits_dram(va2pa(0x7ffffffee210)) == 0x08000660);  // rbp
    match = match && (read64bits_dram(va2pa(0x7ffffffee208)) == 0x1234abcd); 
    match = match && (read64bits_dram(va2pa(0x7ffffffee200)) == 0xabcd); 
    match = match && (read64bits_dram(va2pa(0x7ffffffee1f8)) == 0x12340000); 
    match = match && (read64bits_dram(va2pa(0x7ffffffee1f0)) == 0x08000660); // rsp

    if (match == 1)
    {
        cout << "memory match" << endl;
    }
    else 
    {
        cout << "memory not match" << endl;
    }

    return 0;  
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

/*
    gdb x命令 有多种参数 百度
    examine命令 x ：查看内存地址中的值
    格式：x/<n/f/u> 
    ni ni命令类似于n命令， 所不同的是，这两个命令（si/ni）所针对的是汇编指令，而s/n针对的是源代码。
    info reg -- info r 查看寄存器的值
*/

/*
    简单理解指令如何工作的，包含虚拟地址，物理地址等。
    inst --> 指令
    mm  --> 内存 不确定这里是寄存器还是主存的值
cpu --> vaddr --> 当前这个内存的值是 虚拟地址 由cpu生成
    mmu --> 翻译虚拟地址
    paddr --> 真实的物理地址
    sram(cache) --> 如果在缓存中找到这个物理地址，那么将值返回给cpu
    memory(dram) --> 如果没有在缓存中命中，那么在主存中查找，成功返回给 cpu
    disk --> 如果在主存中野找不到，那么在磁盘中寻找 --> 这不基本不会发生。

*/
