// C���ԡ�λ��������״����

#include <stdlib.h>
#include <stdio.h>

void test01()
{
    // elf��executable object file
    // print: ��ӡ f:format ��ʽ�����
    printf("Hello world\n");
}

void test02()
{
    int a = 2147483647;
    printf("0x%x\n", a + 1); // overflow  0x80000000
}

unsigned LowBit(unsigned x)
{
    // ���� ���λλ1����λ��ֵ
    // eg��0b1010 ���� 0b10
    return x & ((~x) + 1);

    /*
        why:
        segment array -> tree like array : ��״���� -�� ��ʹ�õ� LowBit ����
        ���ɷ���
          x         ~x       -x��ȡ����һ��������overflow �� ���� 180�ȵ���ת����ʵ���ǲ�ͬ�ķ��� ��ʾͬһ������(ͬ��)��
        aaaaaaa1  bbbbbbb0  bbbbbbb1 
          x  &  (-x)  -->  aaaaaaa1 & bbbbbbb1 = 00000001
        ����� 1 �������Ϊૣ�-��ͬ��
          x        ~x        -x
        aaaa1000  bbbb0111  bbbb1000
          x  &  (-x)  -->  aaaa1000 & bbbb1000 = 00001000
    */
}

// λ����
void test03()
{
    /*
        0 -> 1 ��
        1 -> 0 ��
        0 & 0 = 0��1 & 0 = 0��1 & 1 = 1��0 & 1 = 0 ��
        0 | 0 = 0��1 | 0 = 1��1 | 1 = 1��0 | 1 = 1 ��
    */
   int a = 2147483647;
   int b = 1;
   printf("0x%x\n", LowBit(0b1010));
}

// ��״����
void test04()
{
    
    // T������״���飬S����ǰ׺������
    unsigned n = 7;
    
    printf("S[%u] = ", n);
    printf("T[%u] + ", n);
    n = n - LowBit(n);
    printf("T[%u] + ", n);
    n = n - LowBit(n);
    printf("T[%u] + ", n);
    n = n - LowBit(n);
    printf("T[%u]", n); // T0 = 0

    // S[7] = T[7] + T[6] + T[4] �˴���7��ǰ׺�ͣ��� ��״����Ĺ�ϵ
    // �������S7 ��ô��Ҫ ���� n(7), �������״����Ļ� logN --�� ʱ�临�Ӷȵ�
}

// ����ж�16����������Щ������ĸ��Щ����
unsigned Letter(unsigned x)
{
    /*
        һ��16���Ƶ�������ͨ�� 4bit ����ʾ
        ��ͼ0��ʾ ��16������λ���֣�1��ʾΪ��ĸ
                   X3X2 = 00    X3X2 = 01    X3X2 = 10    X3X2 = 11
        X1X0 = 00    0(0)        0(4)         0(8)         1(c) 
        X1X0 = 01    0(1)        0(5)         0(9)         1(d)
        X1X0 = 10    0(2)        0(6)         1(a)         1(e)
        X1X0 = 11    0(3)        0(7)         1(b)         1(f)
        ͨ������۲����ã���X3=1 X2=1 ʱ ��ֵ��Ϊ1����X3=1 X1=1ʱ ��ֵͼҲΪ1 so ��X3Ϊ1ʱ��ֻҪ X2 �� X1 ��һ��Ϊ1���ɱ�ʾΪ��ĸ����X0�޹�
        �������ɵã�X3 & (X2 | X1) = 1 �� ��16����Ϊ��ĸ

    */

   unsigned a = x;
   /*
        X3 X2 X1 X0   - hex 
    &   0  0  1  0   &- hex constant - 0x2
        0  0  X1 0   
        0x22222222 & a -> ��32λ�� 8�� 16�������� X1 ȡ��
        ͬ��ȡ�� X2
        0  1  0  0   &- hex constant 0x4
        0  X2 0  0
        0x44444444 & a -> ��X2ȡ��
        �������� 
   */

    unsigned x1 = a & 0x22222222;
    unsigned x2 = a & 0x44444444;
    unsigned x3 = a & 0x88888888;

    return (x3 >> 3) & ((x2 >> 2) | (x1 >> 1)); // �� x3 x2 x1 �ƶ���ͬһλ��
    // printf("0x%x : %x\n", 0xabcd1123�� Letter(0xabcd1123));
}

// 32
int main()
{
    printf("0x%x : %x\n", 0xabcd1123, Letter(0xabcd1123));
    return 0;
}