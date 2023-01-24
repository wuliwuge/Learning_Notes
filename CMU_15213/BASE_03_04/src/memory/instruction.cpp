#include "memory/instruction.h"
#include "cpu/mmu.h"
#include "cpu/register.h"
#include "memory/dram.h"

handler_t handler_table[NUM_INSTRUCTION];

uint64_t decode_od(od_t od) // 如果在 Makefile中开了 -Werror 但是这个函数未使用，可以使用 __attribute__((unused))来正常编译
{
    if (od.type == IMM)
    {
        return od.imm;
    } else if (od.type == REG)
    {
        return (uint64_t)od.reg1;
    } else {
        // mm
        uint64_t vaddr = 0;

        if (od.type == MM_IMM)
        {
            vaddr = *(uint64_t *)&od.imm;
        } else if (od.type == MM_REG) {
            // store reg
            vaddr = *(od.reg1);
        } else if (od.type == MM_IMM_REG) {
            // store reg
            vaddr = od.imm + *(od.reg1);
        } else if (od.type == MM_REG1_REG2) {
            // store reg
            vaddr = *od.reg1 + *od.reg2;
        } else if (od.type == MM_IMM_REG1_REG2) {
            // store reg
            vaddr = *od.reg1 + *od.reg2 + od.imm;
        } else if (od.type == MM_REG2_S) {
            // store reg
            vaddr = od.scal * *od.reg2;
        } else if (od.type == MM_IMM_REG2_S) {
            // store reg
            vaddr = od.imm + od.scal * *od.reg2;
        } else if (od.type == MM_REG1_REG2_S) {
            // store reg
            vaddr = *od.reg1 + od.scal * *od.reg2;
        } else if (od.type == MM_IMM_REG1_REG2_S) {
            // store reg
            vaddr = od.imm + *od.reg1 + od.scal * *od.reg2;
        }

        return vaddr;
    }
}

void instruction_cycle()
{
    inst_t *instr = (inst_t *)reg.rip; // 从rip(程序计数器)中取出 当前需要执行的指令
    // inst_t instr = program[reg.rip]; --> 写法2
    
    // 解析结果：imm: imm reg: value  mm: paddr 要么是立即数、要么是寄存器值、要么是真实物理地址
    uint64_t src = decode_od(instr->src);
    uint64_t dest = decode_od(instr->dest);

    handler_t handler = handler_table[instr->op];
    // eg: add_reg_reg_handler(src = &rax, dst = &rbx)
    handler(src, dest);

    printf("    %s\n", instr->code);
}

void init_handler_table()
{
    // 将函数指针放入对应的函数数组中
    handler_table[mov_reg_reg] = &move_reg_reg_handler;
    handler_table[add_reg_reg] = &add_reg_reg_handler;
    handler_table[call] = &call_handler;
}

void add_reg_reg_handler(uint64_t src, uint64_t dst)
{
    // 这里的意思将传入的 src 和 dst的地址中的值取出来相加在放到 dst地址中，再将计数器移动到下一个位置
    *(uint64_t *)dst = *(uint64_t *)dst + *(uint64_t *)src;
    reg.rip = reg.rip + sizeof(inst_t);

    /*
    eg: add_reg_reg_handler(src = &rax, dst = &rbx)
    rax pmm[0x1234] = 0x12340000  --> 如果我没理解错的话，寄存器 rax真实的物理地址 0x1234 --> 里面存的值 0x12340000
    rbx pmm[0x1235] = 0xabcd 

    src: 0x1234
    dst: 0x1235

    *(uint64_t *)src = 0x12340000
    *(uint64_t *)dst = 0xabcd

    结果：
    0x12340000 + 0xabcd = 0x1234abcd

    pmm[0x1235] = 0x1234abcd

    */
}

void move_reg_reg_handler(uint64_t src, uint64_t dst)
{
    // src: reg
    // dest: reg
    *(uint64_t *)dst = *(uint64_t *)src;
    reg.rip = reg.rip + sizeof(inst_t);
}

void call_handler(uint64_t src, uint64_t dst)
{
    // src: imm address of called function
    reg.rsp -= 8; // 整体设计实现参照csapp中的call --> 后续研读
    // write return address to rsp memory
    write64bits_dram(va2pa(reg.rsp), reg.rip + sizeof(inst_t)); // 本质保存的是main的call后的指令的地址

    reg.rip = src;
}