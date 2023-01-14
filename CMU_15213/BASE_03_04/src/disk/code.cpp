// dick：磁盘
#include <stdlib.h>
#include "memory/instruction.h"
#include "disk/elf.h"
#include "cpu/register.h"

inst_t program[INST_LEN] = {
    {
        MOV,
        {REG, 0, 0, (uint64_t *)&reg.rax, nullptr, "MOV rax rbx"},
        {REG, 0, 0, (uint64_t *)&reg.rbx, nullptr, "MOV rax rbx"},
    },
};