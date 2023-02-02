// ˳���ľ�̬ʵ��, ��ǰ�Ͱ��մ�Cʵ�ְɡ�
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define MAXSIZE 100
//using ElemType = int;      // �Զ���˳����Ԫ������ c++
typedef int ElemType;      // �Զ���˳����Ԫ������

typedef struct
{
	int data[MAXSIZE];	 // ��̬˳��������
	unsigned int length;     // ��ǰ������Ԫ�صĸ���
}SeqList, *PSeqList;


// ˳���LL�ĳ�ʼ��
void InitList(PSeqList LL);

// ����˳���LL
void DestrooyList(PSeqList LL);

// ��˳���LL�ĵ�ii��λ�ò���Ԫ��ee������ֵ: 0-ʧ�ܣ�1-�ɹ�
int InsertList(PSeqList LL, unsigned int ii, ElemType *ee); 

// ��˳���LL��ͷ������Ԫ��ee, ����ֵ��0-ʧ�ܣ�1-�ɹ�
int PushFront(PSeqList LL, ElemType *ee);

// ��˳���LL��β������Ԫ��ee, ����ֵ��0-ʧ�ܣ�1-�ɹ�
int PushBack(PSeqList LL, ElemType *ee);

// ��˳���ĳ��ȣ�����ֵ��>=0 ��LL��Ԫ�ظ���
int LengthList(PSeqList LL);

// ��ȡ˳����е�ii��Ԫ�ص�ֵ�������ee�У�����ֵ��0-ʧ�ܣ�1-�ɹ�
int GetElem(PSeqList LL, unsigned int ii, ElemType *ee);

// ���˳���
void ClearList(PSeqList LL);

// �ж�˳����Ƿ�Ϊ�գ�����ֵ��1-�գ�0�ǿջ���ʧ��
int IsEmpty(PSeqList LL);

// ��ӡ˳�����ȫ��Ԫ��
void PrintList(PSeqList LL);

// ����ee��˳����е�λ�ã�����ֵ��0-Ԫ��ee�ڱ�LL�в����ڣ�>0 Ԫ��ee�ڱ��е�λ�ã����±�
int LocateElem(PSeqList LL, ElemType *ee);

// ɾ��˳���LL�еĵ�ii��Ԫ�أ�����ֵ��0-λ��ii���Ϸ���1-�ɹ�
int DelteElem(PSeqList LL, unsigned int ii);

// ɾ��˳���LL��ͷԪ�أ�����ֵ��0-λ��ii���Ϸ���1-�ɹ�
int PopFront(PSeqList LL);

// ɾ��˳���LL��βԪ�أ�����ֵ��0-λ��ii���Ϸ���1-�ɹ�
int PopBack(PSeqList LL);

// ���ù鲢�ķ����������������˳���La��Lb���ϲ���һ������˳���Lc��
int MergeList(PSeqList La, PSeqList Lb, PSeqList Lc);


int main()
{
	SeqList LL;  // ����˳���
	
	ElemType ee; // ����һ������Ԫ��

	InitList(&LL); // ��ʼ��˳���

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

// ˳���LL�ĳ�ʼ��
void InitList(PSeqList LL)
{
	if (LL == NULL) { printf("˳���Ϊ��\n"); return;}
	
	ClearList(LL);
}

// ����˳���LL
void DestrooyList(PSeqList LL)
{
	// ���ֲ��Ƕ���������զ���ٰ�?? 
}

// ��˳���LL�ĵ�ii��λ�ò���Ԫ��ee������ֵ: 0-ʧ�ܣ�1-�ɹ�
int InsertList(PSeqList LL, unsigned int ii, ElemType *ee) 
{
	if (LL == NULL || ee == NULL) { return 0; }
	if (ii < 0 || ii > LL->length + 1) { return 0;} // ����Ƚϵ������Ա��λ�� �� 1��ʼ

	// ���ﲢû���ж�˳�������
/*
	for (k = LL->length - 1; k >= ii - 1; --k) // �����ǴӴ洢�ռ俪ʼ 0
	{
		// LL->data[k + 1] = LL->data[k]; ������������͵�Ȼ���ԣ�����Ǿۺ���������
		memcpy(&LL->data[k + 1], &LL->data[k], sizeof(ElemType));
	}
// �Լ�����д̫���ˣ���ʵֱ��ʹ�����Ա��λ�ñ�ʾ���ɣ����������±�����ʱ -1����
*/

	int k;
	for (k = LL->length; k >= ii; --k)
		memcpy(&LL->data[k], &LL->data[k-1], sizeof(ElemType));
	
	memcpy(&LL->data[ii - 1], ee, sizeof(ElemType));

	++LL->length;

	return 1;
}

// ��˳���LL��ͷ������Ԫ��ee, ����ֵ��0-ʧ�ܣ�1-�ɹ�
int PushFront(PSeqList LL, ElemType *ee)
{
	return InsertList(LL, 1, ee);
}

// ��˳���LL��β������Ԫ��ee, ����ֵ��0-ʧ�ܣ�1-�ɹ�
int PushBack(PSeqList LL, ElemType *ee)
{
	return InsertList(LL, LL->length + 1, ee);
}

// ��˳���ĳ��ȣ�����ֵ��>=0 ��LL��Ԫ�ظ���
int LengthList(PSeqList LL)
{
	if (LL == NULL) return 0;
	return LL->length;
}

// ��ȡ˳����е�ii��Ԫ�ص�ֵ�������ee�У�����ֵ��0-ʧ�ܣ�1-�ɹ�
int GetElem(PSeqList LL, unsigned int ii, ElemType *ee)
{
	if (LL == NULL || ee  == NULL) return 0;

	if (ii < 0 || ii > LL->length) {printf("��������Ԫ�ط�Χ\n"); return 0;}

	memcpy(ee, &LL->data[ii - 1], sizeof(ElemType));

	return 1;
}

// ���˳���
void ClearList(PSeqList LL)
{
	if (LL == NULL) return;	

	LL->length = 0;
	memset(&LL->data[0], 0, LL->length * sizeof(ElemType));
}


// �ж�˳����Ƿ�Ϊ�գ�����ֵ��1-�գ�0�ǿջ���ʧ��
int IsEmpty(PSeqList LL)
{
	if (LL = NULL) return 0;
	return LL->length > 0;
}

// ��ӡ˳�����ȫ��Ԫ��
void PrintList(PSeqList LL)
{
	if (LL = NULL) return ;

printf("start\n");  // ���������struct������Ҫ�޸�
	int k;
 	for (k = 0; k != LL->length; ++k) {
		printf("%-03d", LL->data[k]);  // ���������struct������Ҫ�޸� �˴���ӡ�δ���ԭ��δ֪
	}

	printf("\n");
}

// ����ee��˳����е�λ�ã�����ֵ��0-Ԫ��ee�ڱ�LL�в����ڣ�>0 Ԫ��ee�ڱ��е�λ�ã����±�
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

// ɾ��˳���LL�еĵ�ii��Ԫ�أ�����ֵ��0-λ��ii���Ϸ���1-�ɹ�
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

// ɾ��˳���LL��ͷԪ�أ�����ֵ��0-λ��ii���Ϸ���1-�ɹ�
int PopFront(PSeqList LL)
{
	return DelteElem(LL, 1);
}

// ɾ��˳���LL��βԪ�أ�����ֵ��0-λ��ii���Ϸ���1-�ɹ�
int PopBack(PSeqList LL)
{
	return DelteElem(LL, LL->length);
}

// ���ù鲢�ķ����������������˳���La��Lb���ϲ���һ������˳���Lc��
int MergeList(PSeqList La, PSeqList Lb, PSeqList Lc);

