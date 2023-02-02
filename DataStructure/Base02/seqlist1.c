// 顺序表的静态实现, 当前就按照纯C实现吧。
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define MAXSIZE 100
//using ElemType = int;      // 自定义顺序表的元素类型 c++
typedef int ElemType;      // 自定义顺序表的元素类型

typedef struct
{
	int data[MAXSIZE];	 // 静态顺序表的容量
	unsigned int length;     // 当前容器中元素的个数
}SeqList, *PSeqList;


// 顺序表LL的初始化
void InitList(PSeqList LL);

// 销毁顺序表LL
void DestrooyList(PSeqList LL);

// 在顺序表LL的第ii个位置插入元素ee，返回值: 0-失败，1-成功
int InsertList(PSeqList LL, unsigned int ii, ElemType *ee); 

// 在顺序表LL的头结点插入元素ee, 返回值：0-失败，1-成功
int PushFront(PSeqList LL, ElemType *ee);

// 在顺序表LL的尾结点插入元素ee, 返回值：0-失败，1-成功
int PushBack(PSeqList LL, ElemType *ee);

// 求顺序表的长度，返回值：>=0 表LL的元素个数
int LengthList(PSeqList LL);

// 获取顺序表中第ii个元素的值，存放在ee中，返回值：0-失败，1-成功
int GetElem(PSeqList LL, unsigned int ii, ElemType *ee);

// 清空顺序表
void ClearList(PSeqList LL);

// 判断顺序表是否为空，返回值：1-空，0非空或者失败
int IsEmpty(PSeqList LL);

// 打印顺序表中全部元素
void PrintList(PSeqList LL);

// 查找ee在顺序表中的位置，返回值：0-元素ee在表LL中不存在，>0 元素ee在表中的位置，非下标
int LocateElem(PSeqList LL, ElemType *ee);

// 删除顺序表LL中的第ii个元素，返回值：0-位置ii不合法，1-成功
int DelteElem(PSeqList LL, unsigned int ii);

// 删除顺序表LL中头元素，返回值：0-位置ii不合法；1-成功
int PopFront(PSeqList LL);

// 删除顺序表LL中尾元素，返回值：0-位置ii不合法；1-成功
int PopBack(PSeqList LL);

// 采用归并的方法，将两个升序的顺序表La和Lb，合并成一个升序顺序表Lc。
int MergeList(PSeqList La, PSeqList Lb, PSeqList Lc);


int main()
{
	SeqList LL;  // 创建顺序表
	
	ElemType ee; // 创建一个数据元素

	InitList(&LL); // 初始化顺序表

	printf("在表中插入元素(1, 2, 3, 4, 5, 6, 7, 8, 9, 10). \n");

	ee=1; InsertList(&LL, 1, &ee);
	ee=2; InsertList(&LL, 1, &ee);
	ee=3; InsertList(&LL, 1, &ee);
	ee=4; InsertList(&LL, 1, &ee);
	ee=5; InsertList(&LL, 1, &ee);
	ee=6; InsertList(&LL, 1, &ee);
	ee=7; InsertList(&LL, 1, &ee);
	ee=8; InsertList(&LL, 1, &ee);
	ee=9; InsertList(&LL, 1, &ee);
	ee=10; InsertList(&LL, 1, &ee);

	PrintList(&LL);

	return 0;
}

// 顺序表LL的初始化
void InitList(PSeqList LL)
{
	if (LL == NULL) { printf("顺序表为空\n"); return;}
	
	ClearList(LL);
}

// 销毁顺序表LL
void DestrooyList(PSeqList LL)
{
	// 这又不是堆区创建的咋销毁啊?? 
}

// 在顺序表LL的第ii个位置插入元素ee，返回值: 0-失败，1-成功
int InsertList(PSeqList LL, unsigned int ii, ElemType *ee) 
{
	if (LL == NULL || ee == NULL) { return 0; }
	if (ii < 0 || ii > LL->length + 1) { return 0;} // 这里比较的是线性表的位置 从 1开始

	// 这里并没有判断顺序表满了
/*
	for (k = LL->length - 1; k >= ii - 1; --k) // 这里是从存储空间开始 0
	{
		// LL->data[k + 1] = LL->data[k]; 如果是内置类型当然可以，如果是聚合类型则不行
		memcpy(&LL->data[k + 1], &LL->data[k], sizeof(ElemType));
	}
// 自己这里写太挫了，其实直接使用线性表的位置表示即可，在做数组下标运算时 -1即可
*/

	int k;
	for (k = LL->length; k >= ii; --k)
		memcpy(&LL->data[k], &LL->data[k-1], sizeof(ElemType));
	
	memcpy(&LL->data[ii - 1], ee, sizeof(ElemType));

	++LL->length;

	return 1;
}

// 在顺序表LL的头结点插入元素ee, 返回值：0-失败，1-成功
int PushFront(PSeqList LL, ElemType *ee)
{
	return InsertList(LL, 1, ee);
}

// 在顺序表LL的尾结点插入元素ee, 返回值：0-失败，1-成功
int PushBack(PSeqList LL, ElemType *ee)
{
	return InsertList(LL, LL->length + 1, ee);
}

// 求顺序表的长度，返回值：>=0 表LL的元素个数
int LengthList(PSeqList LL)
{
	if (LL == NULL) return 0;
	return LL->length;
}

// 获取顺序表中第ii个元素的值，存放在ee中，返回值：0-失败，1-成功
int GetElem(PSeqList LL, unsigned int ii, ElemType *ee)
{
	if (LL == NULL || ee  == NULL) return 0;

	if (ii < 0 || ii > LL->length) {printf("超出容器元素范围\n"); return 0;}

	memcpy(ee, &LL->data[ii - 1], sizeof(ElemType));

	return 1;
}

// 清空顺序表
void ClearList(PSeqList LL)
{
	if (LL == NULL) return;	

	LL->length = 0;
	memset(&LL->data[0], 0, LL->length * sizeof(ElemType));
}


// 判断顺序表是否为空，返回值：1-空，0非空或者失败
int IsEmpty(PSeqList LL)
{
	if (LL = NULL) return 0;
	return LL->length > 0;
}

// 打印顺序表中全部元素
void PrintList(PSeqList LL)
{
	if (LL = NULL) return ;

printf("start\n");  // 如果这里是struct对象需要修改
	int k;
 	for (k = 0; k != LL->length; ++k) {
		printf("%-03d", LL->data[k]);  // 如果这里是struct对象需要修改 此处打印段错误，原因未知
	}

	printf("\n");
}

// 查找ee在顺序表中的位置，返回值：0-元素ee在表LL中不存在，>0 元素ee在表中的位置，非下标
int LocateElem(PSeqList LL, ElemType *ee)
{
	if (LL == NULL) return 0;

	int k;
	for (k = 0; k != LL->length; ++k)
	{
		if (*ee == LL->data[k]) return k + 1;
	}

	return 0;
}

// 删除顺序表LL中的第ii个元素，返回值：0-位置ii不合法，1-成功
int DelteElem(PSeqList LL, unsigned int ii)
{
	if (LL == NULL) return 0;
	if (ii < 0 || ii > LL->length) return 0;
	
	int k;
	for (k = ii; ii <= LL->length; ++ii)
		memcpy(&LL->data[ii - 1], &LL->data[ii], sizeof(ElemType));

	--LL->length;

	return 1;
}

// 删除顺序表LL中头元素，返回值：0-位置ii不合法；1-成功
int PopFront(PSeqList LL)
{
	return DelteElem(LL, 1);
}

// 删除顺序表LL中尾元素，返回值：0-位置ii不合法；1-成功
int PopBack(PSeqList LL)
{
	return DelteElem(LL, LL->length);
}

// 采用归并的方法，将两个升序的顺序表La和Lb，合并成一个升序顺序表Lc。
int MergeList(PSeqList La, PSeqList Lb, PSeqList Lc);

