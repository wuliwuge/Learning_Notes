#ifndef __DRAM__H
#define __DRAM__H
#include <stdint.h>
// dram: 主存

// 模拟内存包含主存和寄存器
/*
    immediate: 立即数
    register：寄存器 --> 一般访问 cache(sram) ，其次通过 I/O bus 访问
    memory：主存
*/

// 定义内存
#define MM_LEN (1000)
extern uint8_t mm[MM_LEN];  // 定义1000个字节的内存 ,physical memory 我不知道为啥这里一定需要加一个static md fuck

// virtual address 0x0 --> 0xffffffffffffffff
// physical address 000 --> 999  --> 此处并未非真实硬件下 物理地址 到 虚拟地址的实现 


uint64_t read64bits_dram(uint64_t paddr);
void write64bits_dram(uint64_t paddr, uint64_t data);

void print_register();
void print_stack();

#endif /* __DRAM__H */


/*
例如一个头文件headfile.h这样写

#pragma once

bool Func (){return true;}

在这个头文件被多个地方包含的时候就会出问题，链接时报错: (FuncB报重定义)
“fatal error LNK1169: 找到一个或多个多重定义的符号”

原因是，在headfile.h中定义了函数及其实现，如果被包含时，则会把函数实现放入包含的位置，被包含多次时，则会被放入多次，从而导致Func重定义。

那怕是在头文件中使用了#pragma once或是#ifdef __xxx /#define __xxx/#endif也不能解决这种问题。原因是每个.cpp的编译都是多独立的，对于每个cpp来说，都是包含了Func的声明和实现，所以在链接时就不清楚到底是链接哪一个同名函数了。

解决方法也很简单:

方法一: 添加inline标识，添加完inline标识后，函数的内容代码被直接解释到调用处了，链接时相当于不存在这个函数，也就不存函数重定义的情况。

Inline bool Func () {return true;}

方法二: 添加static标识

static bool Func () {return true;}

方法三: 放入到类中

class ClassA
{
public:
    bool Func () {return true;}
}

对于方法二与方法三，我个人猜测，对于静态函数和类，无论有多少文件包含它，也只会维护一份，链接时也就只能找到这一份，所以也是没有问题。
*/