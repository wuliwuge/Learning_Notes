/*
 * 此程序演示二叉树的前序遍历、中序遍历、后序遍历，包含递归和非递归两种方法
 * 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stack> // 使用c++的栈

///////////////////////////////////////////////
// 二叉树的数据结构
typedef struct BiTNode
{
  char   data;               // 存放结点的数据元素
  struct BiTNode *lchild;    // ָ指向左子结点地址的指针
  struct BiTNode *rchild;    // ָ指向右子结点地址的指针
}BiTNode,*BiTree;
///////////////////////////////////////////////


// 求二叉树的高度
int TreeDepth(BiTree TT);

// 访问结点元素
void visit(BiTNode *pp);

// 采用递归的方法对二叉树的先序遍历
void PreOrder(BiTree TT);
// 采用非递归的方法对二叉树的先序遍历
void PreOrder1(BiTree TT);

// 采用递归的方法对二叉树的中序遍历
void InOrder(BiTree TT);
// 采用非递归的方法对二叉树的中序遍历
void InOrder1(BiTree TT);

// 采用递归的方法对二叉树的后序遍历
void PostOrder(BiTree TT);
// 采用非递归的方法对二叉树的后序遍历
void PostOrder1(BiTree TT);

// 释放二叉树资源
void FreeTree(BiTree TT);

int main()
{
  BiTree TT=0; // 声明树指针变量

  /*
  // 手工构建一个如下结构的二叉树
             1
          /     \
         2       3
        / \     /
       4   5   6
      / \ / \
     7  8 9  0
  */

  // 分配结点
  TT=(BiTNode *)malloc(sizeof(BiTNode));
  TT->data='1';
  TT->lchild=TT->rchild=0;

  // 第二层的第一个结点
  TT->lchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->data='2'; TT->lchild->lchild=TT->lchild->rchild=0;

  // 第二层的第二个结点
  TT->rchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->rchild->data='3'; TT->rchild->lchild=TT->rchild->rchild=0;

  // 第三层的第一个结点
  TT->lchild->lchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->lchild->data='4'; TT->lchild->lchild->lchild=TT->lchild->lchild->rchild=0;

  // 第三层的第二个结点
  TT->lchild->rchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->rchild->data='5'; TT->lchild->rchild->lchild=TT->lchild->rchild->rchild=0;

  // 第三层的第三个结点
  TT->rchild->lchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->rchild->lchild->data='6'; TT->rchild->lchild->lchild=TT->rchild->lchild->rchild=0;

  // 第四层的第一个结点
  TT->lchild->lchild->lchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->lchild->lchild->data='7'; TT->lchild->lchild->lchild->lchild=TT->lchild->lchild->lchild->rchild=0;

  // 第四层的第二个结点
  TT->lchild->lchild->rchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->lchild->rchild->data='8'; TT->lchild->lchild->rchild->lchild=TT->lchild->lchild->rchild->rchild=0;

  // 第四层的第三个结点
  TT->lchild->rchild->lchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->rchild->lchild->data='9'; TT->lchild->rchild->lchild->lchild=TT->lchild->rchild->lchild->rchild=0;

  // 第四层的第四个结点
  TT->lchild->rchild->rchild=(BiTNode *)malloc(sizeof(BiTNode));
  TT->lchild->rchild->rchild->data='0'; TT->lchild->rchild->rchild->lchild=TT->lchild->rchild->rchild->rchild=0;

  // 二叉树先序遍历结果
  printf("先序遍历结果1："); PreOrder(TT); printf("\n");
  printf("先序遍历结果2："); PreOrder1(TT); printf("\n");

  // 二叉树中序遍历
  printf("中序遍历结果1："); InOrder(TT); printf("\n");
  printf("中序遍历结果2："); InOrder1(TT); printf("\n");

  // 二叉树后续遍历
  printf("后序遍历结果1："); PostOrder(TT); printf("\n");
  printf("后序遍历结果2："); PostOrder1(TT); printf("\n");


  // 求二叉树的高度
  printf("树的高度是：%d\n",TreeDepth(TT));

  // 释放二叉树
  FreeTree(TT);
  return 0;
}


// 求二叉树的高度
int TreeDepth(BiTree TT)
{
  if (TT == nullptr) return 0;
  unsigned int left = 0, right = 0;
  left = TreeDepth(TT->lchild);
  right = TreeDepth(TT->rchild);

  return left > right ? left + 1 : right + 1;
}

// 访问结点元素
void visit(BiTNode *pp)
{
  printf("%c ", pp->data);
}

// 采用递归的方法对二叉树的先序遍历
void PreOrder(BiTree TT)
{
  if (TT == nullptr) return;
  visit(TT);
  PreOrder(TT->lchild);
  PreOrder(TT->rchild);
}
// 采用非递归的方法对二叉树的先序遍历
void PreOrder1(BiTree TT)
{
  if (TT == nullptr) return ;

  std::stack<BiTree> SS;

  while (!SS.empty() || TT) {
    if (TT) {
      visit(TT);
      SS.push(TT);
      TT = TT->lchild;
    } else {
      TT = SS.top();
      TT = TT->rchild;
      SS.pop();
    }
  }

}

// 采用递归的方法对二叉树的中序遍历
void InOrder(BiTree TT)
{
  if (TT == nullptr) return;
  InOrder(TT->lchild);
  visit(TT);
  InOrder(TT->rchild);
}
// 采用非递归的方法对二叉树的中序遍历
void InOrder1(BiTree TT)
{
    if (TT == nullptr) return ;

  std::stack<BiTree> SS;

  while (!SS.empty() || TT) {
    if (TT) {
      SS.push(TT);
      TT = TT->lchild;
    } else {
      TT = SS.top();
      visit(TT);
      TT = TT->rchild;
      SS.pop();
    }
  }
}

// 采用递归的方法对二叉树的后序遍历
void PostOrder(BiTree TT)
{
    if (TT == nullptr) return;
  PostOrder(TT->lchild);
  PostOrder(TT->rchild);
  visit(TT);
}
// 采用非递归的方法对二叉树的后序遍历
void PostOrder1(BiTree TT)
{
  if (TT == nullptr) return ;

  std::stack<BiTree> SS;

  BiTree tmp = nullptr; // 用于记录被访问过的结点地址

  while (!SS.empty() || TT) {
    if (TT) {
      SS.push(TT);
      TT = TT->lchild;
    } else {
      TT = SS.top();
      // 如果当前结点存在右节点且没有被访问过则
      if (TT->rchild && tmp != TT->rchild) {
        TT = TT->rchild;
        SS.push(TT);
        TT = TT->lchild; // 转向右子树的左结点
      } else {
        visit(TT);
        tmp = TT;  // 记录访问过的结点地址
        SS.pop();
        TT = nullptr;
      }
    }
  }
  
}

void FreeTree(BiTree TT)
{
  if (TT == nullptr) return;
  FreeTree(TT->lchild);
  FreeTree(TT->rchild);
  free(TT);  
}