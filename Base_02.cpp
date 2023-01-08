// ������������ת��

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>

void test01()
{
    /*
        10������ ����ı�ʾ
        123.12  ->  1.2312 * 10^2(��ѧ������)
        1*10^2 + 2*10^1 + 3*10^0 + 1*10^-1 + 2*10^-2
        2����ͬ��
        1010.0101 -> 1.0100101 * 2^3 (�ݲ������з���)
        1*2^3 + 0*2^2 + 1*2^1 + 0*2^0 + 0*2^-1 + 1*2^-2 + 0*2^-3 + 1*2^-4
        8     +   0   +   2   +  0    +  0     +  0.25  +   0    +  0.00625

        C�и����ʾ��
        1.Normalized(�淶����) --> �޷���ʾ0��
        (-1)^s(signal) * 1.f(fraction) * 2^(e - 127)  �˴���ȥ127���ƫִ����(bias)��Ϊ��ƽ��С������������������ֻȡ��������� ��IEEE���ġ�doubleͬ��
        ��flaotΪ����
        s��m[31]   e:[30:23]   f:[22:0]

        2.Denormalized(�ǹ�)
        s       e                     f
        s  0 0 0 0 0 0 0 0            f   --> ��ȫΪ0    
        (-1)^s + 0.f * 2^(e - 127) --> �ǹ�Լ�Ļ� fΪ 0.xxx ��չ�˸�С��������

        3.infinity(����)
        s       e                     f
        s  1 1 1 1 1 1 1 1           f(23��0)   -->

        4.NaN(not a number)
        s       e                     f
        s  1 1 1 1 1 1 1 1            f(��ȫΪ0)   -->
    */

    // 2.Denormalized(�ǹ�)
    unsigned a = 0x00400000;
    std::cout << *(float*)&a << std::endl;  // 5.87747e-039
    std::cout << pow(2, -127) * 0.1 << std::endl; // 5.87747e-040 �е���죬��֪����������

    // 3.infinity(����)
    a = 0x7f800000;// 0 11111111 0000..00
    std::cout << *(float*)&a << std::endl;  // inf �з������ʾ������޷������ʾ������
    a = 0xff800000; // 1 11111111 0000...0   
    std::cout << *(float*)&a << std::endl;  // -inf �з������ʾ������޷������ʾ������

    // 4.NaN(not a number)
    a = 0xffffffff;
    std::cout << *(float*)&a << std::endl;  // ����ȫΪ0 ���� f��ȫΪ0�� nan

    // e �� fȫ0
    a = 0x00000000; 
    std::cout << *(float*)&a << std::endl; // +0
    a = 0x80000000;
    std::cout << *(float*)&a << std::endl; // -0

}


int main()
{
    test01();

}