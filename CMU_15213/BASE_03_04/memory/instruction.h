#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> // uint32_t uint64_t..


// 模拟内存包含主存和寄存器
/*
    immediate: 立即数
    register：寄存器
    memory：主存
*/

// 定义内存
#define MM_LEN (1000)
uint8_t mm[MM_LEN];  // 定义1000个字节的内存

// 定义操作符
typedef enum OP
{
    MOV,  // 0
    PUSH, // 1
    CALL, // 2
}op_t;

// 定义如何进行取址
typedef enum OD_TYPE
{
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
    int64_t *reg1; // 寄存器1
    uint64_t *reg2; // 寄存器2

    char code[100];  // 命令本身

}od_t;

typedef struct INSTRUCT_STRUCT
{
    op_t op; // mov, push --> 操作符
    od_t src; // 源operand(操作数)
    od_t dest; // 目标operand
}inst_t;

#define INST_LEN (100)
inst_t program[INST_LEN];

// 译码
uint64_t decode_od(od_t od);

// 译码
uint64_t decode_od(od_t od)
{
    if (od.type == IMM) {
        return od.imm;
    } 
    else if (od.type == REG) {
        return *(uint64_t *)od.reg;
    }
    else {
        uint64_t addr = MM_LEN + 0xff;
        return mm[addr % MM_LEN];
    }
}