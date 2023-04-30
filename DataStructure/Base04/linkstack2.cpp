// 2023-4-29
// 栈的链式存储实现

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef int ElemType;  // 自定义数据类型为整形

typedef struct SNode
{
	ElemType data;
	struct SNode *next;
}SNode, *LinkStack;

// 链栈SS的初始化操作，分配头结点，返回头结点的地址。
SNode *InitStack();

// 销毁链栈SS。
void DestroyStack(LinkStack SS);

// 元素入栈，返回值：0-失败；1-成功。
int Push(LinkStack SS, ElemType *ee);

// 元素出栈，返回值：0-失败；1-成功。
int Pop(LinkStack SS, ElemType *ee);

// 求链栈的长度，返回值：栈SS中元素的个数。
int  Length(LinkStack SS);

// 清空链栈。
void Clear(LinkStack SS);

// 判断链栈是否为空，返回值：1-空，0-非空或失败。
int  IsEmpty(LinkStack SS);

// 打印链栈中全部的元素。
void PrintStack(LinkStack SS);

// 获取栈顶元素，返回值：0-失败；1-成功。
// 只查看栈顶元素的值，元素不出栈。
int GetTop(LinkStack SS, ElemType *ee);

int main()
{
	LinkStack SS;     // 创建链栈。
  
	SS=InitStack();  // 初始化链栈。
	
	printf("栈的长度是%d\n",Length(SS));
	
	ElemType ee;     // 创建一个数据元素。
	
	printf("元素（1、2、3、4、5、6、7、8、9、10）入栈。\n");
	ee=1;  Push(SS, &ee);
	ee=2;  Push(SS, &ee);
	ee=3;  Push(SS, &ee);
	ee=4;  Push(SS, &ee);
	ee=5;  Push(SS, &ee);
	ee=6;  Push(SS, &ee);
	ee=7;  Push(SS, &ee);
	ee=8;  Push(SS, &ee);
	ee=9;  Push(SS, &ee);
	ee=10; Push(SS, &ee);
	
	printf("栈的长度是%d\n",Length(SS));
	
	if (GetTop(SS,&ee)==1)  printf("栈顶的元素值为%d\n",ee);
	
	PrintStack(SS);
	
	if (Pop(SS,&ee)==1)  printf("出栈的元素值为%d\n",ee);
	if (Pop(SS,&ee)==1)  printf("出栈的元素值为%d\n",ee);
	if (Pop(SS,&ee)==1)  printf("出栈的元素值为%d\n",ee);
	if (Pop(SS,&ee)==1)  printf("出栈的元素值为%d\n",ee);
	if (Pop(SS,&ee)==1)  printf("出栈的元素值为%d\n",ee);
	if (Pop(SS,&ee)==1)  printf("出栈的元素值为%d\n",ee);
	if (Pop(SS,&ee)==1)  printf("出栈的元素值为%d\n",ee);
	if (Pop(SS,&ee)==1)  printf("出栈的元素值为%d\n",ee);
	if (Pop(SS,&ee)==1)  printf("出栈的元素值为%d\n",ee);
	if (Pop(SS,&ee)==1)  printf("出栈的元素值为%d\n",ee);
	if (Pop(SS,&ee)==1)  printf("出栈的元素值为%d\n",ee);
	if (Pop(SS,&ee)==1)  printf("出栈的元素值为%d\n",ee);
	
	// 销毁链栈SS。
	DestroyStack(SS); SS=0;  // 销毁链栈后把SS置为空，防止野指针。
	
	return 0;
}

// 链栈SS的初始化操作，分配头结点，返回头结点的地址。
SNode *InitStack()
{
	LinkStack tmp = (LinkStack)malloc(sizeof(SNode));
	if (!tmp) { printf("分配空间失败。\n"); return NULL;}

	memset(&tmp->data, 0, sizeof(ElemType));
	tmp->next = NULL;
	
	return tmp;
}

// 销毁链栈SS。
void DestroyStack(LinkStack SS)
{
	// 销毁链栈SS是指释放链栈全部的结点，包括头结点
	LinkStack tmp;

	while (SS) {
		tmp = SS->next;
		free(SS);
		SS = tmp;
	}
}


// 元素入栈，返回值：0-失败；1-成功。
int Push(LinkStack SS, ElemType *ee)
{
	if (SS == NULL || ee == NULL) { printf("链栈SS或元素ee为空。\n"); return 0;}

	LinkStack node = (LinkStack)malloc(sizeof(SNode));
	if (!node) return 0;

	memcpy(&node->data, ee, sizeof(ElemType));
	node->next = SS->next;
	SS->next = node;
	return 1;
}

// 元素出栈，返回值：0-失败；1-成功。
int Pop(LinkStack SS, ElemType *ee)
{
	if (SS == NULL || ee == NULL) { printf("链栈SS或元素ee为空。\n"); return 0;}
	
	if (IsEmpty(SS)) {printf("栈为空。\n"); return 0;}

	memcpy(ee, &SS->next->data, sizeof(ElemType));

	LinkStack tmp = SS->next;
	SS->next = tmp->next;

	free(tmp);

	return 1;
}

// 求链栈的长度，返回值：栈SS中元素的个数。
int  Length(LinkStack SS)
{
	if (!SS) return 0;

	unsigned int ipos = 0;
	LinkStack tmp = SS->next;

	while (tmp) {
		++ipos;
		tmp = tmp->next;
	}

	return ipos;
}

// 清空链栈。
void Clear(LinkStack SS)
{
	// 清空链栈SS是指释放链栈全部的结点，但不包括头结点。
	if (!SS) return;

	LinkStack tmp1 = SS->next, tmp2;
	SS->next = NULL;

	while (tmp1) {
		tmp2 = tmp1->next;
		free(tmp1);
		tmp1 = tmp2;
	}
}

// 判断链栈是否为空，返回值：1-空，0-非空或失败。
int  IsEmpty(LinkStack SS)
{
	if (SS == NULL) return 0;
	if (!SS->next) return 1;
	return 0;
}

// 打印链栈中全部的元素。
void PrintStack(LinkStack SS)
{
	if (!SS) return ;
	if (IsEmpty(SS)) {printf("栈为空。\n"); return;}

	LinkStack tmp = SS->next;

	int kk = 0;
	while (tmp) {
		printf("SS[%d],value=%d\n",kk++, tmp->data);
    	tmp=tmp->next;
	}
}

// 获取栈顶元素，返回值：0-失败；1-成功。
// 只查看栈顶元素的值，元素不出栈。
int GetTop(LinkStack SS, ElemType *ee)
{
	if (!SS || !ee) return 0;

	if (IsEmpty(SS)) { printf("栈为空。\n"); return 0;}

	memcpy(ee, &SS->next->data, sizeof(ElemType));

	return 1;
}