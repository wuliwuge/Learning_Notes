// dick：磁盘
#include <stdlib.h>
#include "memory/instruction.h"
#include "disk/elf.h"
#include "cpu/register.h"

inst_t program[INST_LEN] = {
    // uint64_t add(uint64_t, uint64_t) 这里是模拟up在gdb下的add函数的 反汇编命令
    {
        push_reg,  // 压栈
        { REG,    0,  0,  (uint64_t *)&reg.rbp, nullptr },
        { EMPTY,  0,  0,  nullptr,              nullptr },
        "push    \%rbp"
    },
    {
        mov_reg_reg,
        { REG,    0,  0,  (uint64_t *)&reg.rsp, nullptr },
        { REG,    0,  0,  (uint64_t *)&reg.rbp, nullptr },
        "mov    \%rsp,\%rbp"
    },
    {
        mov_reg_mem,
        { REG,    0,  0,  (uint64_t *)&reg.rdi, nullptr },
        { MM_IMM_REG,    -0x18,  0,  (uint64_t *)&reg.rbp, nullptr },
        "mov    \%rdi,-0x18(\%rbp)"
    },
    {
        mov_reg_mem,
        { REG,    0,  0,  (uint64_t *)&reg.rsi, nullptr },
        { MM_IMM_REG,    -0x20,  0,  (uint64_t *)&reg.rbp, nullptr },
        "mov    \%rsi,-0x20(\%rbp)"
    },
    {
        mov_mem_reg,
        { MM_IMM_REG,    -0x18,  0,  (uint64_t *)&reg.rbp, nullptr },
        { REG,    0,  0,  (uint64_t *)&reg.rdx, nullptr },
        "mov    -0x18(\%rbp),\%rdx"
    },
    {
        mov_mem_reg,
        { MM_IMM_REG,    -0x20,  0,  (uint64_t *)&reg.rbp, nullptr },
        { REG,    0,  0,  (uint64_t *)&reg.rax, nullptr },
        "mov    -0x20(\%rbp),\%rax"
    },
    {
        add_reg_reg,
        { REG,    0,  0,  (uint64_t *)&reg.rdx, nullptr },
        { REG,    0,  0,  (uint64_t *)&reg.rax, nullptr },
        "add    \%rdx,\%rax"
    },
    {
        mov_reg_mem,
        { REG,    0,  0,  (uint64_t *)&reg.rax, nullptr },
        { MM_IMM_REG,    -0x8,  0,  (uint64_t *)&reg.rbp, nullptr },
        "mov    \%rax,-0x8(\%rbp)"
    },
    {
        mov_mem_reg,
        { MM_IMM_REG,    -0x8,  0,  (uint64_t *)&reg.rbp, nullptr },
        { REG,    0,  0,  (uint64_t *)&reg.rax, nullptr },
        "mov    -0x8(\%rbp),\%rax"
    },
    {
        pop_reg,  // 弹出栈
        { REG,    0,  0,  (uint64_t *)&reg.rbp, nullptr },
        { EMPTY,    0,  0,  nullptr, nullptr },
        "pop    \%rbp"
    },
    {
        ret,  // 从这个函数退出
        { EMPTY,    0,  0,  nullptr, nullptr },
        { EMPTY,    0,  0,  nullptr, nullptr },
        "retq"
    },
    // main entry point 主函数入口
    {
        mov_reg_reg,
        { REG,    0,  0,  (uint64_t *)&reg.rdx, nullptr },
        { REG,    0,  0,  (uint64_t *)&reg.rsi, nullptr },
        "mov    \%rdx,\%rsi"
    },
    {
        mov_reg_reg,
        { REG,    0,  0,  (uint64_t *)&reg.rax, nullptr },
        { REG,    0,  0,  (uint64_t *)&reg.rdi, nullptr },
        "mov    \%rax,\%rdi"
    },
    {
        call,  // call 的是 add函数的起始地址
        { IMM,    (uint64_t)&(program[0]),  0,  nullptr, nullptr },
        { EMPTY,    0,  0,  nullptr, nullptr },
        "callq    <add>"
    },
    {
        mov_reg_mem,
        { REG,    0,  0,  (uint64_t *)&reg.rax, nullptr },
        { MM_IMM_REG,    -0x8,  0,  (uint64_t *)&reg.rbp, nullptr },
        "mov    \%rax,-0x8(\%rbp)"
    }
};