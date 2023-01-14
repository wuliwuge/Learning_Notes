// cpu���Ĵ�������ࡢָ�� --�������������ϵͳ03
// ��ࡢ���롢�����ַ  --�������������ϵͳ04   

/*
    objdump -d main.exe > ./1.txt �����ִ���ļ��Ļ��ͻ����� ���ı�����ʽ��ʾ ������������ϸ�ڣ����аٶ�
    65b:   55       push   %rbp
    ��ǰ����⣺����
    cpu ָ�� 65b�����ַ �ó� 55 �����  push  %rbp   .... ��������
*/

/* ��64λ������ڴ����
    0xffffffffffffffff   --�� �����ַ
    |                |
    |    kernel      |  --���ں�����λ��
    |                |
    ------------------
    |                |  high addr --> ջ��
    |    stack       |  
    |                |  low  addr --> top
    ------------------
    |                |
    |                |
    |    heap        |
    |                |
    ------------------
    |                |
    |    text        | --> ��� code �ȡ�
    |                |
    0x0000000000000000
*/

/*  ������� 
    rsp�����topָ��
    mov Դ --��dest 
    mov %rdi,-0x18(%rbp) --> ȡ��rbp�Ĵ�����ֵ �� 0x18��� �õ�һ��ֵ(��ʵ����ĳ����ַ) �������ַ�е�ֵ�ó��� --�� 
    mov $0xabcd,%eax  --> �����ֵ(0xabcd) ����eax�Ĵ����С�
    rip����� pc(Program counter �����������)
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

// ��ģ��cpu
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

// ģ���ڴ��������ͼĴ���
/*
    immediate: ������
    register���Ĵ���
    memory������
*/

// �����ڴ�
#define MM_LEN (1000)
uint8_t mm[MM_LEN];  // ����1000���ֽڵ��ڴ�

// ���������
typedef enum OP
{
    MOV,  // 0
    PUSH, // 1
    CALL, // 2
}op_t;

// ������ν���ȡַ
typedef enum OD_TYPE
{
    IMM, REG, 
    MM_IMM, MM_REG, MM_IMM_REG, MM_REG1_REG2,
    MM_IMM_REG1_REG2, MM_REG2_S, MM_IMM_REG2_S,
    MM_REG1_REG2_S, MM_IMM_REG1_REG2_S,
}od_type_t;

// ��������ڴ�
typedef struct OD
{
    od_type_t type;
    int64_t imm;  // ������
    uint64_t scal; // ����
    int64_t *reg1; // �Ĵ���1
    uint64_t *reg2; // �Ĵ���2

}od_t;

typedef struct INSTRUCT_STRUCT
{
    op_t op; // mov, push --> ������
    od_t src; // Դoperand(������)
    od_t dest; // Ŀ��operand
}inst_t;

#define INST_LEN (100)
inst_t program[INST_LEN];

// ����
uint64_t decode_od(od_t od)
{
    if (od.type == IMM) {
        return od.imm;
    } 
    else if (od.type == REG) {
        // return od.reg;  // ���ﻹ�е�bug
    }
    else {
        uint64_t addr = MM_LEN + 0xff;
        return mm[addr % MM_LEN];
    }
}

void test01()
{
    // С��
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
    // printf("0x%x\n", *(uint64_t *)a); �� 0x1000 ת���� uint64_t �ĵ�ַ���ٽ������ַ���� uint64_t ȡ��

    return 0;
}

/*
    ����״̬������ cpu * mem ��� --�� ������ִ��һ��ָ��ʱ����ô (cpu mem) ��һ��״̬ ת�� ��һ��״̬

*/