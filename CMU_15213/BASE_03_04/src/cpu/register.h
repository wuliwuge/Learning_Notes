#ifndef __REGISTER__H
#define __REGISTER__H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> // uint32_t uint64_t..


// 简单模拟cpu
typedef struct REG_STRUCT
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

extern reg_t reg;

#endif /* __REGISTER__H */