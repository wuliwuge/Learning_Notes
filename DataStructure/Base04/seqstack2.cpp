// 2023-4-30
// 程序演示用顺序栈检查括号是否匹配，支持()[]{}三种括号。是在seqstack1.cpp 上做的修改

#include <stdio.h>
#include <string.h>

#define MAXSIZE 100     // 顺序栈的最大长度 --》此处采用的静态数组实现  XXX

typedef char ElemType;  // 自定义数据类型为char  /// XXX

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


// 检查表达式括号是否匹配，返回值：0-不匹配，1-匹配。
int checkbrackets(char *str);

int main()
{
	char str[101];
	memset(str,0,sizeof(str));

	printf("请输入待检查的字符串：");
	fgets(str,100,stdin);    // 不建议用gets函数，gets函数编译时可能会出现警号。
	str[strlen(str)-1]=0;    // 删除str最后的换行。
	printf("输入的字符串是=%s=\n",str);

	if (checkbrackets(str) == 0) { printf("匹配失败。\n"); return -1; }

	printf("匹配成功。\n");

	return 1;
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



// 检查表达式括号是否匹配，返回值：0-不匹配，1-匹配。
int checkbrackets(char *str)
{
	if (!str) { printf("输入串为空。\n"); return 0;}

	SeqStack SS;  // 创建顺序栈
	ElemType ee;

	InitStack(&SS); // 初始化顺序栈

	for (int i = 0; i < strlen(str); ++i) {
		if (str[i] == '[' || str[i] == '(' || str[i] == '{') {
			Push(&SS, str + i);
		} else if (str[i] == ']' || str[i] == ')' || str[i] == '}') {
			// 一定要判断出栈结果，如果栈中没有元素，匹配失败。
      		if (Pop(&SS,&ee) != 1) return 0;

			if (str[i] == ')' && ee != '(') return 0;
			if (str[i] == '}' && ee != '{') return 0;
			if (str[i] == ']' && ee != '[') return 0;
		} else {
			printf("不是字符 {} () [] 中的其一。\n");
			return 0; 
		}
	}

	// 如果栈中还有元素则返回0。
	return IsEmpty(&SS);
}