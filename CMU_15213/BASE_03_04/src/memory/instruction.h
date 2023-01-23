#ifndef __INSTRUCTION__H
#define __INSTRUCTION__H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> // uint32_t uint64_t..

// int a = 10; // 此处不知道为啥会多重定义，先记下来。

#define NUM_INSTRUCTION (30)

// 定义操作符
typedef enum OP
{
    mov_reg_reg,  // 0
    mov_reg_mem,  // 1
    move_mem_reg, // 2
    push_reg,     // 3
    pop_reg,      // 4
    call,         // 5
    ret,          // 6
    add_reg_reg,  // 7
}op_t;

// 定义如何进行取址
typedef enum OD_TYPE
{
    EMPTY,
    IMM, REG, 
    MM_IMM, MM_REG, MM_IMM_REG, MM_REG1_REG2,
    MM_IMM_REG1_REG2, MM_REG2_S, MM_IMM_REG2_S,
    MM_REG1_REG2_S, MM_IMM_REG1_REG2_S, 
} od_type_t;

// 定义操作内存
typedef struct OD
{
    od_type_t type;
    int64_t imm;  // 立即数
    int64_t scal; // 乘数
    uint64_t *reg1; // 寄存器1
    uint64_t *reg2; // 寄存器2 --> 类似访问数组的index

}od_t;

typedef struct INSTRUCT_STRUCT
{
    op_t op; // mov, push --> 操作符
    od_t src; // 源operand(操作数)
    od_t dest; // 目标operand
    char code[100];  // 命令本身
}inst_t;

typedef void (*handler_t)(uint64_t, u_int64_t);


void instruction_cycle();

void add_reg_reg_handler(uint64_t src, uint64_t dst);

void move_reg_reg_handler(uint64_t src, uint64_t dst);


// 用于存放 对应操作符的 函数指针。
static handler_t handler_table[NUM_INSTRUCTION]; // 通过函数初始化

// static handler_t handler_table[NUM_INSTRUCTION] = // 直接初始化
// {
//     &move_reg_reg_handler, // 0
// };
// 不知道为啥，up这个吊毛根本，没有加staic 但是 这个 .h 中的成员被 多个.c文件 include 居然没有重定义 fuck


#endif /* __INSTRUCTION__H */