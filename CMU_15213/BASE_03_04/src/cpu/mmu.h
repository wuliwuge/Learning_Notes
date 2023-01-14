// mmu(memory management unit)：内存管理单元
#ifndef __MMU__H
#define __MMU__H

#include <stdint.h>

uint64_t va2pa(uint64_t addr);

#endif /* __MMU__H */