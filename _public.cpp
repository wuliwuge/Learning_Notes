#include "_public.h"

// 数组形式的栈
// Stack CreateStack() // 生成栈，其最大长度为Size

int Stack::IsFull(Stack S, int Size) // 判断栈S是否已满
{
    if (S->Top + 1 == MaxSize) {
        return 0;
    } else {
        return -1;
    }
}

void Stack::Push(Stack S, ElementType item) // 将元素item压入栈中
{
    if (S->Top == MaxSize - 1) {
        printf("栈满\n"); return ;
    } else {
        S->Data[++(S->Top)] = item; // 首先将Top置为新的栈顶再将item压入
    }
}

int Stack::IsEmpty(Stack S) // 判断栈S是否为空 
{
    return S->Top;
}

ElementType Stack::Pop(Stack S) // 删除Top元素，并返回该栈顶元素
{
    if (S->Top == -1) {
        printf("栈空\n");
        return ERROR; 
    } else {
        return S->Data[(S->Top)--];
    }
}

// 