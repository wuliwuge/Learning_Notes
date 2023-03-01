// 栈的顺序存储实现

#include <stdio.h>
#include <string.h>

#define MAXSIZE 10     // 顺序栈的最大长度 --》此处采用的静态数组实现

typedef int ElemType;  // 自定义数据类型为整形

typedef struct
{
	ElemType data[MAXSIZE]; // 用数组存储顺序栈的元素
	int top;                // 栈顶指针，从0到MAXSIZE - 1，-1表示栈空
						    // 也可以从i到MAXSIZE，0表示空栈
}SeqStack, *PSeqStack;


// 顺序栈SS的初始化操作
void InitStack(PSeqStack SS);


// 销毁顺序栈SS
void DestroyStack(PSeqStack SS);

// 元素入栈，返回值：0-失败，1-成功
int Push(PSeqStack SS, ElemType *ee);


// 元素出栈，返回值：0-失败，1-成功
int Pop(PSeqStack SS, ElemType *ee);


// 求顺序栈的长度，返回值：栈SS中元素的个数
int Length(PSeqStack SS);

// 清空顺序栈
void Clear(PSeqStack SS);


// 判断顺序栈是否为空，返回值：1-空，0-非空或失败
int IsEmpty(PSeqStack SS);


// 判断顺序栈是否已满，返回值：1-已满，0-未满或失败
int IsFull(PSeqStack SS);


// 打印顺序栈中全部元素
void PrintStack(PSeqStack SS);


// 获取栈顶元素，返回值：0-失败，1-成功
// 只查看栈顶元素的值，元素不出栈
int GetTop(PSeqStack SS, ElemType *ee);

int main()
{
	SeqStack SS;  // 创建顺序栈

	InitStack(&SS); // 初始化顺序栈

	printf("栈的长度是%d\n", Length(&SS));

	ElemType ee;  // 创建一个数据元素


	printf("元素 (1, 2, 3, 4, 5, 6, 7, 8, 9, 10) 入栈。\n");

	ee=1;  Push(&SS, &ee);
	ee=2;  Push(&SS, &ee);
	ee=3;  Push(&SS, &ee);
	ee=4;  Push(&SS, &ee);
	ee=5;  Push(&SS, &ee);
	ee=6;  Push(&SS, &ee);
	ee=7;  Push(&SS, &ee);
	ee=8;  Push(&SS, &ee);
	ee=9;  Push(&SS, &ee);
	ee=10;  Push(&SS, &ee);

	printf("栈的长度是%d\n", Length(&SS));  // shift + k可以在vi中查看man手册

	// 只查看栈顶元素的值，元素不出栈
	if (GetTop(&SS, &ee) == 1) printf("栈顶的元素值为%d\n", ee);

	PrintStack(&SS);

	if (Pop(&SS, &ee) == 1) printf("出栈的元素值为%d\n", ee);
	if (Pop(&SS, &ee) == 1) printf("出栈的元素值为%d\n", ee);
	if (Pop(&SS, &ee) == 1) printf("出栈的元素值为%d\n", ee);
	if (Pop(&SS, &ee) == 1) printf("出栈的元素值为%d\n", ee);
	if (Pop(&SS, &ee) == 1) printf("出栈的元素值为%d\n", ee);
	if (Pop(&SS, &ee) == 1) printf("出栈的元素值为%d\n", ee);
	if (Pop(&SS, &ee) == 1) printf("出栈的元素值为%d\n", ee);
	if (Pop(&SS, &ee) == 1) printf("出栈的元素值为%d\n", ee);
	if (Pop(&SS, &ee) == 1) printf("出栈的元素值为%d\n", ee);
	if (Pop(&SS, &ee) == 1) printf("出栈的元素值为%d\n", ee);
	if (Pop(&SS, &ee) == 1) printf("出栈的元素值为%d\n", ee);
	if (Pop(&SS, &ee) == 1) printf("出栈的元素值为%d\n", ee);
	if (Pop(&SS, &ee) == 1) printf("出栈的元素值为%d\n", ee);
	
	return 0;
}

// 顺序栈SS的初始化操作
void InitStack(PSeqStack SS)
{
	Clear(SS); // 清空顺序栈
}


// 销毁顺序栈SS
void DestroyStack(PSeqStack SS)
{
	// 这个是静态数组应该不用销毁吧	
}

// 元素入栈，返回值：0-失败，1-成功
int Push(PSeqStack SS, ElemType *ee)
{
	if (IsFull(SS) == 1) return 0;
	memcpy(&SS->data[++SS->top], ee, sizeof(ElemType));
	return 1;
}


// 元素出栈，返回值：0-失败，1-成功
int Pop(PSeqStack SS, ElemType *ee)
{
	if (IsEmpty(SS)	== 1) return 0;
	memcpy(ee, &SS->data[SS->top--], sizeof(ElemType));
	return 1;
}


// 求顺序栈的长度，返回值：栈SS中元素的个数
int Length(PSeqStack SS)
{
	if (SS == NULL) return 0;
	return SS->top + 1;
}

// 清空顺序栈
void Clear(PSeqStack SS)
{
	if (SS == NULL) return;
	memset(SS, 0, sizeof(SeqStack));
	SS->top = -1;
}


// 判断顺序栈是否为空，返回值：1-空，0-非空或失败
int IsEmpty(PSeqStack SS)
{
	if (SS == NULL) return 0;
	if (SS->top == -1) return 1;
	return 0;
}


// 判断顺序栈是否已满，返回值：1-已满，0-未满或失败
int IsFull(PSeqStack SS)
{
	if (SS == NULL) return 0;
	if (SS->top + 1 == MAXSIZE) return 1;
	return 0;
}


// 打印顺序栈中全部元素
void PrintStack(PSeqStack SS)
{
	for (int i = 0; i <= SS->top; ++i)
		printf("%d ", *(SS->data + i));  // 如果不是int类型需要重新适配
	printf("\n");
}


// 获取栈顶元素，返回值：0-失败，1-成功
// 只查看栈顶元素的值，元素不出栈
int GetTop(PSeqStack SS, ElemType *ee)
{
	if (SS == NULL || ee == NULL) return 0;	

	memcpy(ee, &SS->data[SS->top], sizeof(ElemType));

	return 1;
}
