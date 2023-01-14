// cpu、寄存器、汇编、指针 --》深入理解计算机系统03
// 汇编、译码、虚拟地址  --》深入理解计算机系统04   

/*
    objdump -d main.exe > ./1.txt 输出可执行文件的汇编和机器码 以文本的形式表示 至于这个命令的细节，自行百度
    65b:   55       push   %rbp
    当前简单理解：译码
    cpu 指向 65b这个地址 拿出 55 译码成  push  %rbp   .... 后续深入
*/

/* 以64位简单理解内存分配
    0xffffffffffffffff   --》 虚拟地址
    |                |
    |    kernel      |  --》内核所在位置
    |                |
    ------------------
    |                |  high addr --> 栈底
    |    stack       |  
    |                |  low  addr --> top
    ------------------
    |                |
    |                |
    |    heap        |
    |                |
    ------------------
    |                |
    |    text        | --> 存放 code 等。
    |                |
    0x0000000000000000
*/

/*  随遇随记 
    rsp：存放top指针
    mov 源 --》dest 
    mov %rdi,-0x18(%rbp) --> 取出rbp寄存器的值 与 0x18相减 得到一个值(其实就是某个地址) 将这个地址中的值拿出来 --》 
    mov $0xabcd,%eax  --> 将这个值(0xabcd) 放入eax寄存器中。
    rip：存放 pc(Program counter 程序计数器，)
)
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> // uint32_t uint64_t..

uint64_t add(uint64_t a, uint64_t b)
{
    uint64_t c = a + b;
    return c;
}

// 简单模拟cpu
typedef struct CPU_STRUCT
{
    union
    {
        struct {
            uint8_t al;
            uint8_t ah;
        };
        uint16_t ax;
        uint32_t eax;
        uint64_t rax;
        
    };
    
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rsp;
    uint64_t rip;
} reg_t;

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
}od_type_t;

// 定义操作内存
typedef struct OD
{
    od_type_t type;
    int64_t imm;  // 立即数
    uint64_t scal; // 乘数
    int64_t *reg1; // 寄存器1
    uint64_t *reg2; // 寄存器2

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
uint64_t decode_od(od_t od)
{
    if (od.type == IMM) {
        return od.imm;
    } 
    else if (od.type == REG) {
        // return od.reg;  // 这里还有点bug
    }
    else {
        uint64_t addr = MM_LEN + 0xff;
        return mm[addr % MM_LEN];
    }
}

void test01()
{
    // 小端
    reg_t cpu;
    cpu.rax = 0x1234abcd5678ffaa;
    printf("eax: %08x\n", cpu.eax); // eax: 5678ffaa
    printf("ax: %04x\n", cpu.ax);   // ax: ffaa
    printf("al: %02x\n", cpu.al);   // al: aa
    printf("ah: %02x\n", cpu.ah);   // ah: ff
}

int main()
{
    // uint64_t a = 0x1234;
    // uint64_t b = 0xabcd0000;
    // uint64_t c = add(a, b);

    // test01();

    // uint32_t a = 0x1000;
    // printf("0x%x\n", *(uint64_t *)a); 将 0x1000 转换成 uint64_t 的地址，再将这坨地址按照 uint64_t 取出

    return 0;
}

/*
    有限状态机：由 cpu * mem 组成 --》 当我们执行一条指令时，那么 (cpu mem) 从一个状态 转到 另一个状态

*/