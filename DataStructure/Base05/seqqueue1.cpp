// 2023-4-29
// 顺环队列

/*  采用静态数组来作为队列的容器 
    int front;  // 队列的头指针
    int rear;  // 队列的尾指针，指向队尾元素。

    循环队列指针的移动：

    代码一：
    rear = rear + 1;
    if (rear > = MAXSIZE) rear = rear - MAXSIZE;  // 如果下标超出了静态数组的容量时。需要重新计算新的下标（前提是队列未满）

    代码二：--》更为简便的写法
    rear = (rear + 1) % MAXSIZE;  // 取模（余数）

    计算队列的长度：

    代码一：
    length = rear - front + 1;
    if (length < 0) length = length + MAXSIZE;

    代码二：--》更为简便的写法
    length = (rear - front + 1) % MAXSIZE;
*/

/*  循环队列实现方案其一：牺牲一个存储单元的方案 --> 主要是为了区分队空和队满，我知道我之后肯定会忘的，建议画个图
    int front;  // 队列的头指针
    int rear;  // 队列的尾指针，指向队尾的下一个元素

    初始化：front = rear = 0;

    队空：front == rear

    队满：((rear + 1) % MAXSIZE) == fornt

    队长：(rear - front + MAXSIZE) % MAXSIZE
*/


/*  循环队列实现方案其二：增加辅助变量的方案
    int front;  // 队列的头指针
    int rear;  // 队列的尾指针，指向队尾的下一个位置
    int length; // 队列的实际长度

    初始化：front = rear = length = 0;

    队空：length == 0

    队满：length == MAXSIZE

    队长：直接取length变量的值
*/

/*  循环队列实现方案其三：牺牲一个存储单元的方案
    int front;  // 队列的头指针
    int rear;  // 队列的尾指针，指向队尾元素

    初始化：front = 0; rear = MAXSIZE - 1;

    队空：front == ((rear + 1) % MAXSIZE)

    队满：((rear + 2) % MAXSIZE) == fornt

    队长：(rear - front + 1 + MAXSIZE) % MAXSIZE
*/

/*  循环队列实现方案其四：增加辅助变量的方案
    int front;  // 队列的头指针
    int rear;  // 队列的尾指针，指向队尾元素
    int length; // 队列的实际长度

    初始化：front = 0； rear = MAXSIZE - 1;

    队空：length == 0

    队满：length == MAXSIZE

    队长：直接取length变量的值
*/

// 此程序演示循环队列的数组实现，队尾指针指向队尾的下一个元素，没有length的辅助变量。
#include <stdio.h>
#include <string.h>

#define MAXSIZE 10       // 循环队列的最大长度，最多可以存放MAXSIZE-1个元素。

typedef int ElemType;    // 自定义循环队列的数据元素为整数。

typedef struct
{
  ElemType data[MAXSIZE];   // 用数组存储循环队列中的元素。
  int front;                // 队列的头指针。
  int rear;                 // 队列的尾指针，指向队尾的下一个元素。
}SeqQueue,*PSeqQueue;

// 循环队列QQ的初始化操作。
void InitQueue(PSeqQueue QQ);

// 销毁循环队列QQ。
void DestroyQueue(PSeqQueue QQ);

// 元素入队，返回值：0-失败；1-成功。
int InQueue(PSeqQueue QQ, ElemType *ee);

// 元素出队，返回值：0-失败；1-成功。
int OutQueue(PSeqQueue QQ, ElemType *ee);

// 求循环队列的长度，返回值：>=0-队列QQ元素的个数。
int  Length(PSeqQueue QQ);

// 清空循环队列。
void Clear(PSeqQueue QQ);

// 判断循环队列是否为空，返回值：1-空，0-非空或失败。
int  IsEmpty(PSeqQueue QQ);

// 判断循环队列是否已满，返回值：1-已满，0-未满或失败。
int IsFull(PSeqQueue QQ);

// 打印循环队列中全部的元素。
void PrintQueue(PSeqQueue QQ);

// 获取队头元素，返回值：0-失败；1-成功。
// 只查看队头元素的值，元素不出队。
int GetHead(PSeqQueue QQ, ElemType *ee);

int main()
{
    SeqQueue QQ;     // 创建循环队列。

    InitQueue(&QQ);  // 初始化循环队列。

    ElemType ee;     // 创建一个数据元素。

    printf("元素（1、2、3、4、5、6、7、8、9、10、11）入队。\n");
    ee=1;  InQueue(&QQ, &ee);
    ee=2;  InQueue(&QQ, &ee);
    ee=3;  InQueue(&QQ, &ee);
    ee=4;  InQueue(&QQ, &ee);
    ee=5;  InQueue(&QQ, &ee);
    ee=6;  InQueue(&QQ, &ee);
    ee=7;  InQueue(&QQ, &ee);
    ee=8;  InQueue(&QQ, &ee);
    ee=9;  InQueue(&QQ, &ee);
    ee=10; InQueue(&QQ, &ee);
    ee=11; InQueue(&QQ, &ee);

    printf("队列的长度是%d\n",Length(&QQ));
    PrintQueue(&QQ);

    if (OutQueue(&QQ,&ee)==1)  printf("出队的元素值为%d\n",ee);
    if (OutQueue(&QQ,&ee)==1)  printf("出队的元素值为%d\n",ee);
    if (OutQueue(&QQ,&ee)==1)  printf("出队的元素值为%d\n",ee);
    if (OutQueue(&QQ,&ee)==1)  printf("出队的元素值为%d\n",ee);
    if (OutQueue(&QQ,&ee)==1)  printf("出队的元素值为%d\n",ee);
    if (OutQueue(&QQ,&ee)==1)  printf("出队的元素值为%d\n",ee);
    if (OutQueue(&QQ,&ee)==1)  printf("出队的元素值为%d\n",ee);

    printf("队列的长度是%d\n",Length(&QQ));
    PrintQueue(&QQ);

        printf("元素（11、12、13、14、15）入队。\n");
    ee=11;  InQueue(&QQ, &ee);
    ee=12;  InQueue(&QQ, &ee);
    ee=13;  InQueue(&QQ, &ee);
    ee=14;  InQueue(&QQ, &ee);
    ee=15;  InQueue(&QQ, &ee);

    printf("队列的长度是%d\n",Length(&QQ));

    PrintQueue(&QQ);

    // 只查看队头元素的值，元素不出队。
    if (GetHead(&QQ,&ee)==1)  printf("队头的元素值为%d\n",ee);

    return 0;
}

// 循环队列QQ的初始化操作。
void InitQueue(PSeqQueue QQ)
{
    if (!QQ) return;
    QQ->front = QQ->rear = 0;
}

// 销毁循环队列QQ。
void DestroyQueue(PSeqQueue QQ)
{
    // 静态循环队列无需释放内存，不需要销毁操作。

    Clear(QQ); // 清空循环队列。

    return;
}

// 元素入队，返回值：0-失败；1-成功。
int InQueue(PSeqQueue QQ, ElemType *ee)
{
    if (!QQ || !ee) return 0; 

    if (IsFull(QQ)) { printf("队列已满。\n"); return 0;}

    int ipos = QQ->rear;
    memcpy(&QQ->data[ipos], ee, sizeof(ElemType));

    QQ->rear = (QQ->rear + 1) % MAXSIZE;

    return 1;
}

// 元素出队，返回值：0-失败；1-成功。
int OutQueue(PSeqQueue QQ, ElemType *ee)
{
    if (!QQ || !ee) return 0;

    if (IsEmpty(QQ)) { printf("队列为空。\n"); return 1;}

    memcpy(ee, QQ->data + QQ->front, sizeof(ElemType)); // 采用指针的形式

    QQ->front = (QQ->front + 1) % MAXSIZE;

    return 1;
}

// 求循环队列的长度，返回值：>=0-队列QQ元素的个数。
int  Length(PSeqQueue QQ)
{
    if (!QQ) return 0;

    return (QQ->rear - QQ->front + MAXSIZE) % MAXSIZE;
}

// 清空循环队列。
void Clear(PSeqQueue QQ)
{
    if (!QQ) return ;

    QQ->front = QQ->rear = 0;

    memset(QQ->data, 0, sizeof(ElemType) * MAXSIZE);
}

// 判断循环队列是否为空，返回值：1-空，0-非空或失败。
int  IsEmpty(PSeqQueue QQ)
{
    if (!QQ) return 0;

    return QQ->front == QQ->rear;
}

// 判断循环队列是否已满，返回值：1-已满，0-未满或失败。
int IsFull(PSeqQueue QQ)
{
    if (!QQ) return 0;

    return (QQ->rear + 1) % MAXSIZE == QQ->front;
}

// 打印循环队列中全部的元素。
void PrintQueue(PSeqQueue QQ)
{
    if (!QQ) return;
    if (IsEmpty(QQ) == 1) { printf("队列为空。\n"); return; }

    for (int i = QQ->front; i != QQ->rear; i = (i + 1) % MAXSIZE) {
        printf("data[%d],value=%d\n", i, QQ->data[i]);
    }
}

// 获取队头元素，返回值：0-失败；1-成功。
// 只查看队头元素的值，元素不出队。
int GetHead(PSeqQueue QQ, ElemType *ee)
{
    if (!QQ && !ee) return 0;

    if (IsEmpty(QQ)) { printf("队列为空。\n"); return 0;}

    memcpy(ee, QQ->data + QQ->front, sizeof(ElemType));

    return 1;
}