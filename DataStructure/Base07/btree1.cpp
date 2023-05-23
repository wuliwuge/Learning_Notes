// 20230523
// 此程序用于演示二叉树的层次遍历
/*
    思路：首先将二叉树的根节点入队，进入一个循环，弹出一个元素，
    再将它的左右儿子入队，然后循环往复，直至队空结束。
*/

#include <queue>  // 借助c++的队列
using namespace std;

#include <stdlib.h>
#include <stdio.h>

// 二叉树的数据结构
typedef struct BiTNode
{
    char data;               // 存放结点的数据元素
    struct BiTNode *lchild;  // 指向左子结点地址的指针
    struct BiTNode *rchild;  // 指向右子结点地址的指针
}BiTNode, *BiTree;


// 儿叉树的层次遍历
void LevelOrder(BiTree TT);

int main()
{
  BiTree TT=0; // 声明树指针变量

  /*
  // 手工构造一个如下结构的二叉树
             1
          /     \
         2       3
        / \     /
       4   5   6
      / \ / \
     7  8 9  0
  */

  // 分配根结点
  TT=(BiTNode *)malloc(sizeof(BiTNode));
  TT->data='1';
  TT->lchild=TT->rchild=0;

  // 第二层第一个结点
  TT->lchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->data='2'; TT->lchild->lchild=TT->lchild->rchild=0;

  // 第二层第二个结点
  TT->rchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->rchild->data='3'; TT->rchild->lchild=TT->rchild->rchild=0;

  // 第三层第一个结点
  TT->lchild->lchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->lchild->data='4'; TT->lchild->lchild->lchild=TT->lchild->lchild->rchild=0;

  // 第三层第二个结点
  TT->lchild->rchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->rchild->data='5'; TT->lchild->rchild->lchild=TT->lchild->rchild->rchild=0;

  // 第三层第三个结点
  TT->rchild->lchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->rchild->lchild->data='6'; TT->rchild->lchild->lchild=TT->rchild->lchild->rchild=0;

  // 第四层第一个结点
  TT->lchild->lchild->lchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->lchild->lchild->data='7'; TT->lchild->lchild->lchild->lchild=TT->lchild->lchild->lchild->rchild=0;

  // 第四层第二个结点
  TT->lchild->lchild->rchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->lchild->rchild->data='8'; TT->lchild->lchild->rchild->lchild=TT->lchild->lchild->rchild->rchild=0;

  // 第四层第三个结点
  TT->lchild->rchild->lchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->rchild->lchild->data='9'; TT->lchild->rchild->lchild->lchild=TT->lchild->rchild->lchild->rchild=0;

  // 第四层第四个结点
  TT->lchild->rchild->rchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->rchild->rchild->data='0'; TT->lchild->rchild->rchild->lchild=TT->lchild->rchild->rchild->rchild=0;

  // 二叉树层次遍历
  printf("层次遍历结果："); LevelOrder(TT); printf("\n");

  return 0;
}

void LevelOrder(BiTree TT)
{
    if (!TT) { printf("结点为空。\n"); }

    queue<BiTree> q;
    q.push(TT);

    while (!q.empty()) 
    {
        BiTree tmp = q.front();
        q.pop();

        if (tmp->lchild) q.push(tmp->lchild);
        if (tmp->rchild) q.push(tmp->rchild);

        printf("%c ", tmp->data);
    }
    printf("\n");
}
