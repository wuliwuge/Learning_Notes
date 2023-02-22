#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define MAXSIZE 100
typedef int ElemType;      

typedef struct
{
	int data[MAXSIZE];	 
	unsigned int length;     
}SeqList, *PSeqList;

void InitList(PSeqList LL);

void DestrooyList(PSeqList LL);

int InsertList(PSeqList LL, unsigned int ii, ElemType *ee); 

int PushFront(PSeqList LL, ElemType *ee);

int PushBack(PSeqList LL, ElemType *ee);

int LengthList(PSeqList LL);

int GetElem(PSeqList LL, unsigned int ii, ElemType *ee);

void ClearList(PSeqList LL);

int IsEmpty(PSeqList LL);

void PrintList(PSeqList LL);

int LocateElem(PSeqList LL, ElemType *ee);

int DelteElem(PSeqList LL, unsigned int ii);

int PopFront(PSeqList LL);

int PopBack(PSeqList LL);

int MergeList(PSeqList La, PSeqList Lb, PSeqList Lc);


int main()
{
	SeqList LL;  
	
	ElemType ee; 

	InitList(&LL); 

	printf("�ڱ��в���Ԫ��(1, 2, 3, 4, 5, 6, 7, 8, 9, 10). \n");

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

void InitList(PSeqList LL)
{
	if (LL == NULL) { printf("˳���Ϊ��\n"); return;}
	
	ClearList(LL);
}

void DestrooyList(PSeqList LL)
{
}

int InsertList(PSeqList LL, unsigned int ii, ElemType *ee) 
{
	if (LL == NULL || ee == NULL) { return 0; }
	if (ii < 0 || ii > LL->length + 1) { return 0;} 

	int k;
	for (k = LL->length; k >= ii; --k)
		memcpy(&LL->data[k], &LL->data[k-1], sizeof(ElemType));
	
	memcpy(&LL->data[ii - 1], ee, sizeof(ElemType));

	++LL->length;

	return 1;
}

int PushFront(PSeqList LL, ElemType *ee)
{
	return InsertList(LL, 1, ee);
}

int PushBack(PSeqList LL, ElemType *ee)
{
	return InsertList(LL, LL->length + 1, ee);
}

int LengthList(PSeqList LL)
{
	if (LL == NULL) return 0;
	return LL->length;
}

int GetElem(PSeqList LL, unsigned int ii, ElemType *ee)
{
	if (LL == NULL || ee  == NULL) return 0;

	if (ii < 0 || ii > LL->length) {printf("��������Ԫ�ط�Χ\n"); return 0;}

	memcpy(ee, &LL->data[ii - 1], sizeof(ElemType));

	return 1;
}

void ClearList(PSeqList LL)
{
	if (LL == NULL) return;	

	LL->length = 0;
	memset(&LL->data[0], 0, LL->length * sizeof(ElemType));
}

int IsEmpty(PSeqList LL)
{
	if (LL = NULL) return 0;
	return LL->length > 0;
}

void PrintList(PSeqList LL)
{
	if (LL = NULL) return ;

printf("start\n");  
	int k;
 	for (k = 0; k != LL->length; ++k) {
		printf("%-03d", LL->data[k]);  
	}

	printf("\n");
}

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

int PopFront(PSeqList LL)
{
	return DelteElem(LL, 1);
}

int PopBack(PSeqList LL)
{
	return DelteElem(LL, LL->length);
}

int MergeList(PSeqList La, PSeqList Lb, PSeqList Lc);

