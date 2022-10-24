/* data_structure目录下的文件主要是用来验证 数据结构相关知识的*/

#ifndef _PUBLIC_
#define _PUBLIC_

// C相关的头文件
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* C++ 相关头文件 */
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
using namespace std;

 /* 2.1.6广义表与多重链表 只是浅听了一下*/

 /* 2.2：堆栈 */

/* 后缀表达式 
 * 后缀表达式求值策略:
 * 1.遇到运算数时，先记住当前的运算数
 * 2.遇到运算符时，对运算符前最近的两个数进行相应操作
 * 62/3-42*+=? // 从左向右进行扫描规则如上
 * 1> 6/2 = 3
 * 2> 33-42*+=
 * 3> 3-3 = 0
 * 4> 042* -->  4*2 = 8
 * 5> 08+=  -->  0 + 8
 * 6> 最终结果就是 8
 */
// 所以使用栈来解决这类问题
/*
    1.遇到数字进行入栈 ，遇到运算符将top 和 top - 1的两个运算数 pop出来进行运算，然后压栈，继续扫描后续的运算符或数。
    时间复杂度：T(N) = O(N)
    栈（Stack）：具有一定操作约束的线性表
    只在一端（栈顶，Top）做插入，删除
    插入数据：入栈（Push）
    删除数据：出栈（Pop)
    后入先出：Last In First Out（LIFO）
*/

// 操作集：长度为MaxSize的栈S Stack，栈元素item ElementType
// 数组形式的堆栈
#define MaxSize 100
typedef int ElementType;
ElementType ERROR = -1;  // ElementType的特殊值，标识错误

namespace Stack {
typedef struct SNode {
    ElementType Data[MaxSize];
    int Top;
}SNode, *Stack;

Stack CreateStack(int Size); // 生成栈，其最大长度为Size
int IsFull(Stack S, int Size); // 判断栈S是否已满
void Push(Stack S, ElementType item); // 将元素item压入栈中
int IsEmpty(Stack S); // 判断栈S是否为空
ElementType Pop(Stack S); // 删除Top元素，并返回该栈顶元素


// 链表形式的栈
/* 链栈的Top应当在单链表的表头*/
typedef struct LNode {
    ElementType Data;
    struct LNode *Next;
}LNode, *LSNode;

/* 中缀表达式 --> 后缀表达式
 * 1> 从头到尾读取中缀表达式的每个对象，对不同对象按不同情况处理。
 * 2> 运算数：直接输出
 * 3> 左括号：压入栈
 * 4> 右括号：将栈顶的运算符弹出并输出，直到遇到左括号(出栈，不输出)
 * 5> 运算符：
 *      * 若优先级大于栈顶运算符时，则把它压栈
 *      * 若优先级小于栈顶运算符时，将栈顶运算符弹出并输出；
 *        再比较新的栈顶运算符，直到改运算符大于栈顶运算符优先级为止，然后将该运算符压栈
 * 6> 若各对象处理完毕，则把栈中存留的运算符一并输出。
 * 7> () 中的 其他运算符不认为比 () 的优先级低，可以理解为 () 中的表达式 为新的一个表达式。 
 */


}

namespace Queue {
    /* 队列 
     * 具有一定操作约束的线性表
     * 插入和删除操作：只能在一端插入，而在另一端删除
     * 数据插入：入队列（AddQ）
     * 数据删除：出队列（DeleteQ)
     * 先来先服务
     * 先进先出：FIFO
     */

    /* 类型名称：队列(Queue)
     * 数据对象集：一个有0个或多个元素的有穷线性表
     * 操作集：长度为MaxSize的队列Q，队列元素item --> ElementType
     * Queue CreatQueue(int MaxSize);   // 生成长度为MaxSize的空队列
     * int IsFullQ(Queue Q, int Maxsize); // 判断队列Q是否已满
     * void AddQ(Queue Q, ElementType item); // 将数据元素item插入队列Q中
     * int IsEmptyQ(Queue Q); // 判断队列Q是否为空
     * ElementType DeleteQ(Queue Q); // 将队头数据元素从队列中删除并返回
    */

   typedef struct QNode {
        ElementType Data[MaxSize];
        int rear;
        int front;
   }QNode, *Queue;
   /* 队列的顺序存储实现 
    * 1> 通常由一个一维数组和一个记录队列头元素位置的变量front，
    *    以及一个记录队列尾元素位置的变量rear组成。
    * 最初初始化的一个MaxSize的数组，其front 和 rear 都指向 下标为 -1的位置
    * 如果插入一个元素 则 Data[++rear] 来存放这个元素，
    * 如果删除一个元素 则 front++， 其余不变
    * 这样可能造成一个情况 后面 rear == MaxSize - 1了 不能在向后面插入元素了
    * 但是前面由于删除元素，还存在空的位置，那么可以把前面的位置利用起来
    * 顺环队列
    * front == rear (可能队空也可能队满，如果将所有空间利用的话) --> 代表队空，舍弃一个存储空间
    * 解决方案：
    * 使用额外标记：Size或者tag来表示 当前 队列中元素的情况
    * 仅使用n-1个数组空间 --> 舍弃一个存储空间
    * 
   */

  // location：2.3.2 队列的链式存储
    /* 在链头作 front 链尾 作 rear*/

/*

struct Node {
    ElementType Data;
    struct Node *Next;
};

struct QNode { // 链队列结构
    struct Node *rear;  // 指向队尾结点
    sturct Node *front; // 指向队头结点
}

typedef struct QNode *Queue;


// 不带头结点的链式队列出队操作示例
ElementType DeleteQ(Queue PtrQ)
{
    struct Node *FrontCell;
    ElemnetType FrontElem;

    if (PtrQ->front == nullptr) {
        printf("队空\n"); return ERROR;
    }

    FrontCell = PtrQ->front; // 记录front结点
    FrontElem = PtrQ->front->Data; // 记录front结点返回值

    if (PtrQ->front == PtrQ->rear) { // 若队列中只有一个元素，那么 front == rear
        PtrQ->front = PtrQ->rear = nullptr; // 删除元素后队列置为空
    } else {
        PtrQ->front = FrontCell->Next;
    }
    free(FrontCell);
    return FrontElem;
}

// 不带头结点的链式队列入队操作示例
int DeleteQ(Queue PtrQ, ElementType data)
{
    struct Node *FrontCell = (struct Node*)malloc(sizeof(struct Node));
    FrontCell->Data = data;

    if (PtrQ->front == nullptr) { // 如果front == rear == NULL时
        PtrQ->front = PtrQ->rear = FrontCell;
    } else {
        FrontCell->Next = PtrQ->front->Next;
        PtrQ->front = FrontCell;
    }

    return SUCCESSS;
}

*/


/* 多项式加法运算 
 * 采用不带头结点的单向链表，按照指数递减的顺序排列各项
 * 

typedef struct PloyNode {
    int coef; // 系数
    int expon; // 指数
    struct PloyNode *link;  // 指向下一个节点的指针
}PolyNode, *Polynomial;
Polynomial P1, P2;

算法思路：两个指针P1, P2分别指向这两个多项式的第一个结点，不断循环：
P1->expon == P2->expon: 系数相加，若结果不为0，则作为结果多项式对应项的系数，同时，P1 P2 都分别指向下一项
如果是新建结点则无需移动，
P1->expon > P2->expon: 将P1当前项存入结果多项式，并使P1指向下一项
P1->expon < P2->expon: 将P2当前项存入结果多项式，并使P2指向下一项
当某一个多项式处理完成时，将剩余一个全部复制到结果多项式中


Polynomial PolyAdd(Polynomial P1, Polynomial P2)
{
   Polynomial front, rear, temp;
   int sum = 0;
   rear = (Polynomial)malloc(sizeof(struct PolyNode)); // 临时结点使得 front 和 rear初始值一样，后续将会删除
   front = rear;

   while(P1 && P2){ // 当两个多项式都有非零项待处理时
        switch(Compare(P1->expon, P2->expon)){
            case 1: // 代表P1此时的指数大于 P2
                Attach(P1->coef, P1->expon, &rear);
                P1 = P1->link;
                break;
            case -1:
                Attach(P2->coef, P2->expon, &rear);
                P2 = P2->link;
                break;
            case 0:
                sum = P1->coef + P2->ceof;
                if (sum) Attach(sum, P1->expon, &rear);
                P1 = P1->link;
                P2 = P2->link;
                break;
        }
   } 

    // 将未处理完的另一个结点的数据依次复制到结果多项式中
   for (; P1; P1 = P1->link) Attach(P1->coef, P1->expon, &rear);
   for (; P2; P2 = P2->link) Attach(P2->coef, P2->expon, &rear);
   rear->link = NULL;
   temp = front;
   front = front->link; // 使得front指向结果多项式第一个非0项
   free(temp);          // 释放临时空表结点
   return front;
}

*/

}

namespace Polynomial {
 /* 小白专场 
 * 一元多项式的加法与乘法运算
*/
 
 设计函数分别求两个一元多项式的乘积与和
 ### 输入样例
 4 3 4 -5 2 6 1 -2 0 // 其含义为：4代表有四个多项式 两个一组， 第一个数为系数，第二个为指数
 // 3*X^4 -5*x^2 + 6*x^1 -2*x^0
 ....
  
  求解思路：
  1.多项式表示
  2.程序框架
  3.读多项式
  4.加法实现
  5.乘法实现
  6.多项式输出
  
  1> 多项式表示
  仅表示非零项
  数组形式：
  编程简单，调试容易
  需要事先确定数组大小
  
  链表形式：
  动态性强
  编程略微复杂，调试比较困难
  
  ###一种比较好的实现方法是：动态数组
  
  下面为链表表示：
  
  数据结构设计：
  typedef struct PolyNode {
    int coef; // 系数
    int expon; // 指数
    struct PolyNode *link;
  }PolyNode, *Polynomial;
 
 
 ##程序框架搭建
 int main() 
 {
   读入多项式1
   读入多项式2
   乘法运算并输出
   加法运算并输出
   return 0：
 }
 
 ##需要设计的函数
 读一个多项式
 两个多项式相乘
 两个多项式相加
 多项式输出
 
 
 int main() 
 {
   Polynomial P1, P2, PP, PS;
   P1 = ReadPoly();
   P2 = ReadPoly();
   PP = Mult(P1, P2);
   PrintPoly(PP);
   PS = Add(P1, P2);
   PrintPoly(PS);
  
   return 0;
 }
 
 
 ##如何读入多项式
 Polynomial ReadPoly()
 {
   int N, c, e;
   Polynomial Front, Rear, Tmp;
   Rear = (Polynomial)malloc(sizeof(PolyNode)); // 使用一个空白节点方便后续Attch时无需判NULL和 Front可直接可用
   Rear->link = NULL;
   Front = Rear;
   scanf("%d", &N);
    while (N--) {
      scanf("%d %d", &c, &e);
      Attach(c, e, &Rear);
    }
   
   Tmp = Front;
   Front = Front->link;
   free(Tmp);
   return Front;
 }
 //思路：输入有几个多项式 N ,然后输入系数和指数 构造一个结构体 是的 Rear记录新的多项式的链入，最后返回这个 链表的头
 
 void Attach(int c, int e, Polynomial *pRear)
 {
   Polynomial P;
   P = (Polynomial)malloc(sizoef(PolyNode));
   P->ceof = c;
   P->expon = e;
   P->link = NULL;
   (*pRear)->link = P;
   *pRear = p; // 修改pRear的值使其指向新的尾元素
 }
 
 ##如何将两个多项式相加，前面有思路
 
 
 ##如何将两个多项式相乘
 方法1：将乘法运算转换为加法运算
 
 方法2：逐项插入，主要是为了保证新的多项式也是 以 指数递减的 怎么插入是个点
 Polynomial Mult(Polynomial P1, Polynomial P2)
 {
   if (!P1 || !P2) return NULL;
   Polynomial Rear, P, t1 = P1, t2 = P2, Tmp;
   int c, e;
   P = (Polynomial)malloc(sizeof(PolyNode));
   P->link = NULL
   Rear = P;
   /*先使用P1的首节点 与 P2的所有节点构建一个新的递减多项式 */
   while (t2) {
     c = t1->ceof * t2->ceof; // 系数相乘指数相加
     e = t1->expon * t2->expon; 
     Attach(c, e, &Rear);
     t2 = t2->link;
   } // 新的多项式构建完成
  
   t1 = P1->link; // 将P1的后继节点全部相乘按照指数递减的方式插入新的多项式中
  
   while (t1) {
     t2 = P2; 
     Rear = P; // 由于P1 和 P2都是从大到小排序的所以无需将Rear写入 t2的循环中
     while (t2) {
       c = t1->ceof * t2->ceof;
       e = t1->expon * t2->expon;
       while (Rear->link && Rear->link->expon > e) { // 寻找新的数据在新的多项式中插入的位置
         Rear = Rear->link; 
       }
      
       if (Rear->link && Rear->link->expon == e) {
         if (c + Rear->link->ceof) {
           Rear->link->ceof += c;
         } else {  // 如果系数相加为0则需要删除该节点
           Tmp = Rear->link;
           Rear->link = Tmp->link;
           free(Tmp); Tmp = NULL;
         }
       } else { // 要么Rear的下一节点比当前系数小，要么不存在
         Tmp = (Polynomial)malloc(sizeof(PolyNode));
         Tmp->expon = e;
         Tmp->ceof = c;
         Tmp->link = Rear->link;
         Rear->link = Tmp;
         Rear = Rear->link; // 因为下一个节点算出来得指数值肯定比当前Tmp的小，所以将Rear移动值Tmp位置处，可减少一个循环判断
       }
       t2 = t2->link;
     }
     t1 = t1->link;
   }
   Tmp = P;
   P = P->link;
   free(Tmp);
   return P;
 }

// 多项式的打印，略去....
 
}

###引子 - 顺序查找
什么是树？
分层次组织在管理上具有更高效率
数据管理的基本操作之一：查找

typedef struct LNode {
  ElementType Data[Maxsize];
  int Length;  // 数组中元素的个数
}LNode, *List;

_ _ _ _ _..._ _...
0 1 2 3 4   9 10...
^
哨兵

顺序查找-没有哨兵-需要判断是否已达边界 
注：第0号下标不存数据，数据从下标为1处开始

int SequentialSearch(List Tbl, ElementType K)
{
  int i; // 无哨兵需要判断 条件的边界
  for (i = Tbl->Data[Tbl->Length]; i > 0 && Tbl->Data[i] != K; i--);
  return i; // 找到返回 i ，没有找到返回0
}

int SequentialSearch(List Tbl, ElementType K)
{
  int i;
  Tbl->Data[0] = K; // 设置哨兵，如果没有在 1 - Length找到则在 0 处终止
  for (i = Tbl->Data[Tbl->Length]; Tbl->Data[i] != K; i--);
  return i; // 找到返回 i ，没有找到返回0
}

T(N) = O(N)
 
 

引子 - 二分查找 - 查找梨子
排好的数组

typedef struct LNode{
  int Length;
  ElementType Data[Length];
}LNode, *List;
int binarysearch(List Prt, int K)
{
  int left = 0, right = Ptr->Length;
  int mid = left + (right - left) / 2;
  while (left < right) {
    if (Ptr->Data[mid] < K) {
      left = mid + 1;
      mid = left + (right - left) / 2;
    } else if (Ptr->Data[mid] > K) {
      right = mid;
      mid = left + (right + left) / 2;
    } else {
      return mid;
    }
  }
 
  return -1;
}


















#endif
