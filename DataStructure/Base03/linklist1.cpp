/*
    程序名：linklist1.c 此程序演示带头结点的单链表的实现，数据元素为整数
    2023-2-20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include <iostream>
using namespace std;

typedef int ElemType;  // 自定义链表的数据类型

typedef struct LNode
{
    ElemType data; // 存放结点的元素
    struct LNode *next;  // 指向下一个结点的指针
}LNode, *LinkList;

// 初始化链表LL，返回值：失败返回NULL，成功返回头结点的地址。
LNode *InitList1();

// 传入指针变量地址的方法。
// 初始化链表，返回值：0-失败；1-成功
int InitList2(LinkList *LL);

// C++引用的初始方法，在Linux下需要g++编译。
// 初始化链表，返回值：0-失败，1-成功
int InitList3(LinkList &LL);

// 如果参数采用传LL的值，LL的值只能传进去，无法返回，这种方法是不行的
int InitList4(LinkList LL);

// 销毁链表LL
void DestroyList1(LinkList LL);

// 销毁链表LL
// 传入指针的地址的方法
void DestroyList2(LinkList *LL);

// C++引用的方法，在linux下，需要g++编译
void DestroyList3(LinkList &LL);

// 清空链表。
void ClearList(LinkList LL);

// 在链表LL的第ii个位置插入元素ee，返回值：0-失败；1-成功
int InsertList(LinkList LL, uint32_t ii, ElemType *ee);

// 打印链表中全部元素
void PrintList(LinkList LL);

// 在链表LL的头部插入元素ee，返回值：0-失败，1-成功。
int PushFront(LinkList LL, ElemType *ee);

// 在链表LL的尾部插入元素ee，返回值：0-失败，1-成功
int PushBack(LinkList LL, ElemType *ee);

// 删除链表LL中的第ii个结点，返回值：0-位置ii不合法；1-成功
int DeleteNode(LinkList LL, uint32_t ii);

// 删除链表LL中第一个结点，返回值：0-位置不合法；1-成功
int PopFront(LinkList LL);

// 删除链表LL中最后一个结点，返回值：0-位置不合法；1-成功
int PopBack(LinkList LL);

// 求链表的长度，返回值：>=0-表LL结点的个数
int LengthList(LinkList LL);

// 判断链表是否为空，返回值：0-非空或者失败，1-空
int IsEmpty(LinkList LL);

// 获取链表中的ii个结点，成功返回结点的地址，失败返回空
// 注意：ii可以取值为0，表示头结点
LNode *LocateNode(LinkList LL, uint32_t ii);

// 查找元素ee在链表LL中的结点地址，如果找到返回NULL，否则返回结点的地址
LNode *LocateElem(LinkList LL, ElemType *ee);

// 在指定结点pp之后插入元素ee，返回值：0-失败，1-成功
int InsertNextNode(LNode *pp, ElemType *ee);

// 在指定结点pp之前插入元素ee，返回值：0-失败，1-成功
int InsertPriorNode(LNode *pp, ElemType *ee);

// 删除指定结点
int DeleteNode1(LNode *pp);

// 采用归并的方法，将两个升序的链表La和Lb，合并成一个升序的链表Lc
int MergeList(LinkList La, LinkList Lb, LinkList Lc);

// 把链表pp结点之后的结点原地逆置（反转），返回值：0-失败，1-成功
void ReverseList(LNode *pp);

int main()
{
    LinkList LL = NULL;
	LL = InitList1();  // 方式1获取头结点

	printf("LL=%p\n", LL);  // 打印头结点地址

	ElemType ee;  // 创建一个数据元素

	printf("在表中插入元素 (1, 2, 3, 4, 5, 6, 7, 8, 9, 10). \n");

	ee = 1; InsertList(LL, 1, &ee);
	ee = 2; InsertList(LL, 1, &ee);
	ee = 3; InsertList(LL, 1, &ee);
	ee = 4; InsertList(LL, 1, &ee);
	ee = 5; InsertList(LL, 1, &ee);
	ee = 6; InsertList(LL, 1, &ee);
	ee = 7; InsertList(LL, 1, &ee);
	ee = 8; InsertList(LL, 1, &ee);
	ee = 9; InsertList(LL, 1, &ee);
	ee = 10; InsertList(LL, 1, &ee);

	// printf("length=%d\n", LengthList(LL));  // 当前不知道算不算头结点
	PrintList(LL);

	DeleteNode(LL, 2);  //

	PrintList(LL);

	LinkList tmp = LL->next->next;  // 当前指向data为8处
	cout << tmp->data << endl;

	// 在data为8的前面插入元素 77

	ee = 77;
	InsertPriorNode(tmp, &ee);

	PrintList(LL);


	// 此处验证 merge函数
	LinkList L1 = NULL, L2 = NULL, L3 = NULL;
	InitList2(&L1);
	InitList3(L2);
	InitList3(L3);
	ee = 1;
	PushBack(L1, &ee);
	ee = 3;
	PushBack(L1, &ee);
	ee = 5;
	PushBack(L1, &ee);
	ee = 7;
	PushBack(L1, &ee);
	ee = 9;
	PushBack(L1, &ee);

	ee = 2;
	PushBack(L2, &ee);
	ee = 4;
	PushBack(L2, &ee);
	ee = 6;
	PushBack(L2, &ee);
	ee = 8;
	PushBack(L2, &ee);
	ee = 10;
	PushBack(L2, &ee);

	printf("merge start\n");
	PrintList(L1);
	PrintList(L2);
	MergeList(L1, L2, L3);
	PrintList(L3);
	printf("merge end\n");
	

	DestroyList1(LL);
	DestroyList1(L1);
	DestroyList1(L2);
	DestroyList1(L3);
}

// 初始化链表LL，返回值：失败返回NULL，成功返回头结点的地址。
LNode *InitList1()
{	
	LinkList p = (LNode*)malloc(sizeof(LNode));
	return p;
}

// 传入指针变量地址的方法。
// 初始化链表，返回值：0-失败；1-成功
int InitList2(LinkList *LL)
{
	LNode *p = (LNode*)malloc(sizeof(LNode));
	if (p == NULL) // 空间不足
		return 0;

	*LL = p;

	return 1;
}

// C++引用的初始方法，在Linux下需要g++编译。
// 初始化链表，返回值：0-失败，1-成功
int InitList3(LinkList &LL)
{
	LNode *p = (LNode*)malloc(sizeof(LNode));
	if (p == NULL) // 空间不足
		return 0;

	LL = p;
	
	return 1;
}

// 如果参数采用传LL的值，LL的值只能传进去，无法返回，这种方法是不行的
int InitList4(LinkList LL);

// 销毁链表LL，包含头结点
void DestroyList1(LinkList LL)
{
	printf("DestroyList1 begining!!!\n");
	LinkList tmp = NULL;
	while(LL != NULL)
	{
		tmp = LL->next;
		free(LL);
		LL = tmp;
	}
}

// 销毁链表LL
// 传入指针的地址的方法
void DestroyList2(LinkList *LL)
{
	DestroyList1(*LL);
}

// C++引用的方法，在linux下，需要g++编译
void DestroyList3(LinkList &LL)
{
	// DestroyList1(LL);
	LNode *next = NULL;

	while(LL != NULL) {
		next = LL->next;
		free(LL);
		LL = next;
	}
}

// 清空链表。
void ClearList(LinkList LL);

// 在链表LL的第ii个位置插入元素ee，返回值：0-失败；1-成功
int InsertList(LinkList LL, uint32_t ii, ElemType *ee)
{
	if (LL == NULL || ii == 0) { printf("链表为空\n"); return 0; }
	// 猜测0为头结点，其余则是加一
	// 找到ii-1的位置
	while((ii - 1) && LL != NULL) {
		LL = LL->next;	
		--ii;
	}	
	
	if (LL == NULL)
		return 0;

	LNode *newNode = (LinkList)malloc(sizeof(LNode));
	newNode->data = *ee;
	newNode->next = LL->next;
	LL->next = newNode;
	return 1;
}

// 打印链表中全部元素
void PrintList(LinkList LL)
{
	if (LL == NULL) {printf("链表为空\n"); return;}
	LL = LL->next;
	// 当前只打印内置类型，类类型需要重写
	while (LL != NULL) {
		printf("%d ", LL->data);
		LL = LL->next;
	}
	printf("\n");
}

// 在链表LL的头部插入元素ee，返回值：0-失败，1-成功。
int PushFront(LinkList LL, ElemType *ee)
{
	return InsertList(LL, 1, ee);
}

// 在链表LL的尾部插入元素ee，返回值：0-失败，1-成功
int PushBack(LinkList LL, ElemType *ee)
{
	if (LL == NULL) { printf("链表为空\n"); return 0; }
	// 暂不考虑 空指针的情况
	while (LL->next != NULL) {
		LL = LL->next;
	}

	LNode *p = (LinkList)malloc(sizeof(LNode));
	p->data = *ee;
	p->next = NULL;

	LL->next = p;
}

// 删除链表LL中的第ii个结点，返回值：0-位置ii不合法；1-成功
int DeleteNode(LinkList LL, uint32_t ii)
{
	if (LL == NULL) { printf("链表为空\n"); return 0; }
	while ((ii - 1) && LL != NULL) { // 寻找ii的前继结点，且不为空
		LL = LL->next;
		--ii;
	}

	if (!LL) {
		printf("位置不合法\n");
		return 0; 
	}

	LinkList tmp = LL->next;
	if (tmp) {  // 如果位置ii存在元素则删除，否则啥也不干
		LL->next = tmp->next;
		free(tmp);
	}

	return 1;
}

// 删除链表LL中第一个结点，返回值：0-位置不合法；1-成功
int PopFront(LinkList LL);

// 删除链表LL中最后一个结点，返回值：0-位置不合法；1-成功
int PopBack(LinkList LL);

// 求链表的长度，返回值：>=0-表LL结点的个数
int LengthList(LinkList LL)
{
	// 头结点不算
	uint32_t ipos = 0;

	if (LL == NULL) {
		printf("链表为空\n");
		return ipos;
	}
	LL = LL->next;

	while (LL) {
		++ipos;
		LL = LL->next;
	}

	return ipos;
}

// 判断链表是否为空，返回值：0-非空或者失败，1-空
int IsEmpty(LinkList LL)
{
	// 猜测头结点除外
	if (LL == NULL) { printf("链表为空\n"); return 0; }
	if (LL->next == NULL) return 1;
	return 0;
}

// 获取链表中的ii个结点，成功返回结点的地址，失败返回空
// 注意：ii可以取值为0，表示头结点
LNode *LocateNode(LinkList LL, uint32_t ii)
{
	if (LL == NULL) { printf("链表为空\n"); return NULL; }

	while (ii && LL != NULL) {
		--ii;
		LL = LL->next;
	}

	return LL;  // 如果为空则代表ii位置有误
}

// 查找元素ee在链表LL中的结点地址，如果没找到返回NULL，否则返回结点的地址
LNode *LocateElem(LinkList LL, ElemType *ee)
{
	if (LL == NULL) { printf("链表为空\n"); return NULL; }

	LL = LL->next; // 从位置为1，也就是头结点之后开始查找
	while (LL) {
		if (LL->data == *ee) break; // 也可以在此处返回，没差
		LL = LL->next;
	}

	return LL;
}

// 在指定结点pp之后插入元素ee，返回值：0-失败，1-成功
int InsertNextNode(LNode *pp, ElemType *ee)
{
	if (pp == NULL) { printf("pp 为空\n"); return 0; }

	LinkList newNode = (LinkList)malloc(sizeof(LNode));
	newNode->data = *ee;

	newNode->next = pp->next;
	pp->next = newNode;
	return 1;
}

// 在指定结点pp之前插入元素ee，返回值：0-失败，1-成功
int InsertPriorNode(LNode *pp, ElemType *ee)
{
	// 由于单链表插入数据需要知道前继结点，所以此处只能采用偷梁换柱
	if (pp == NULL) { printf("pp 为空\n"); return 0; }

	LinkList newNode = (LinkList)malloc(sizeof(LNode));
	newNode->data = pp->data;  // 偷梁换柱
	pp->data = *ee;
	newNode->next = pp->next;
	pp->next = newNode;

	return 1;

}

// 删除指定结点
int DeleteNode1(LNode *pp)
{
	// 由于找不到前驱结点，所以只能将pp的后继结点的值拷贝到pp结点，然后删除pp的后继结点
	if (pp == NULL) { printf("pp 为空\n"); return 0; } 
	LinkList tmp = pp->next;
	if (tmp == NULL){
		free(pp);
		return 0;
		// 但是这样的话，pp的前驱的next指针指向的是一个空悬地址
	} else {
		pp->data = tmp->data;
		pp->next = tmp->next;
		free(tmp);
	}
}

// 采用归并的方法，将两个升序的链表La和Lb，合并成一个升序的链表Lc
int MergeList(LinkList La, LinkList Lb, LinkList Lc)
{
	if (Lc == NULL) { printf("Lc 为空\n"); return 0; }
	if (La == NULL && Lb != NULL) Lc->next = Lb->next;
	if (Lb == NULL && La != NULL) Lc->next = La->next;

	La = La->next;
	Lb = Lb->next;

	while (La && Lb ) { // 其中有一个为空，则循环结束
		Lc->next = (LinkList)malloc(sizeof(LNode));
		Lc = Lc->next;
		if (La->data < Lb->data) {
			Lc->data = La->data;
			La = La->next;
		} else {
			Lc->data = Lb->data;
			Lb = Lb->next;
		}
	}

	while (La) {
		Lc->next = (LinkList)malloc(sizeof(LNode));
		Lc = Lc->next;
		Lc->data = La->data;
		La = La->next;
	}

	while (Lb) {
		Lc->next = (LinkList)malloc(sizeof(LNode));
		Lc = Lc->next;
		Lc->data = Lb->data;
		Lb = Lb->next;
	}
	Lc->next = NULL;
	return 1;
}

// 把链表pp结点之后的结点原地逆置（反转），返回值：0-失败，1-成功
void ReverseList(LNode *pp);

