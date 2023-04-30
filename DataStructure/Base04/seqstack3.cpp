// 2023-4-30
// 此程序演示用顺序栈实现中缀表达式转后缀表达式。

/* 
	算术表达式由操作数(运算数)、运算符(操作符) 和 界限符(括号等)三部分组成。
	在算术表达式中，界限符反应出计算的顺序，必不可少，如果没有界限符，麻烦会少很多

	波兰。。发明了一种表示表达式的方法，不用界限符也能无歧义的表示运算顺序。
	以下为抄的：我对前辈们的智慧怀敬畏之心，智慧的光芒流传千古，不学习是我们个人的损失，
	如果你们以后成为了大佬，希望不要骄傲，只是因为你站在巨人的肩膀上。

	中缀表达式
	后缀表达式(Reverse Polish notation 逆波兰表达式)
	前缀表达式(Polish notation 波兰表达式)

	##########################################################

	中缀表达式                    后缀表达式                 前缀表达式
	a + b                      a b +                        + a b
	a/b                        ab/                          /ab
	a + b - c                  ab+ c - (bc-a+ 注意事项3)  - +ab c
	a+b-c*d                   ab+ cd* -                   - +ab *cd
	a*b+c*d                  ab* cd* +                    + *ab *cd
	a+b-c*d/e+f              ab+ cd*e / - f +             +-+ab/*cde f
	a+b-c*(d/e)+f            ab+ cde/* - f +              +-+ab *c/de f

	注意事项：
	1）运算的顺序是先括号，在乘除，在加减
	2）运算的顺序不唯一，后缀表达式也不唯一
	3）如果左边的运算符能先计算，就优先计算左边

	A+B-C*(D/E)+F             AB + CDE /* -F+              +-+AB * C/DEF
	 1 4 3  2  5                 1     2 34 5

	1）操作数一定是从左到右排列 --》 即是改为后缀表达式也是这样的。
	2）后缀表达式的 运算符优先级是按照先后排序的。

	################################################
	中缀                               后缀
	a+b-a*((c+d)/e-f)+g                ab+acd+e/f-*-g+

	中缀表达式转后缀表达式规则如下：
	1）数字和字母直接追加到后缀表达式后面
	2）左括号直接入栈
	3）如果是右括号 ')' ，进入循环，依次弹出栈中的运算符并追加到后缀表达式后面 ，如果弹出的是左括号 '(' ，循环终止、
	4）如果当前字符是运算符 '+'、'-'、'*'、'/'，则进入循环；
	   a）获取栈顶元素
	   b）如果栈顶元素的优先级比当前运算符高或相同，则弹出并追加到后缀表达式后面
	   c）如果栈空、或栈顶元素的优先级比当前运算符的低或遇到了左括号 '('，循环终止，循环结束后，当前运算符入栈
	5）扫描完中缀表达式后，弹出栈中剩下的运算符，追加到后缀表达式后面

	###################################################
	后缀表达式求值
	从左到右扫描后缀表达式
	1）如果是操作数，则直接入栈。
	2）如果是操作符则将栈中的头两个元素出栈，进行计算，如果此时的操作符是最后一个，则输出结果结束，否将新值入栈，继续 1 和 2
	这里暂时没有实现
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>  // isalnum

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

// 把中缀表达式str1转换成后缀表达式str2
int torpolish(char *str1,char *str2);

int main()
{
	char str1[101],str2[101];
	memset(str1,0,sizeof(str1));
	memset(str2,0,sizeof(str2));

	printf("请输入待转换的表达式：");
	fgets(str1,100,stdin);     // 不建议使用gets函数，gets函数编译时可能会出现警告
	str1[strlen(str1)-1]=0;    // 删除str1最后的换行。
	printf("输入转换的表达式=%s=\n",str1);

	// 把中缀表达式str1转换为后缀表达式str2
	if (torpolish(str1,str2) == 0) { printf("转换失败\n"); return -1; }

	printf("转换成功=%s=。\n",str2);

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
	if (IsEmpty(SS) == 1) { printf("栈为空\n"); return 0; }
	memcpy(ee, &SS->data[SS->top], sizeof(ElemType));

	return 1;
}

int torpolish(char *str1,char *str2)
{
	if (!str1 && !str2) return 0;

	ElemType ee;
	SeqStack SS;
	InitStack(&SS);

	while (*str1) {
		if (isalnum(*str1)) {   // 条款1
			*str2++ = *str1++;
		} else if (*str1 == '(') {
			Push(&SS, str1++);  // 左括号直接入栈
		} else if (*str1 == ')') {
			while (1) {
				if (!Pop(&SS, &ee)) return 0;
				if (ee == '(') break;
				*str2++ = ee;
			}
			str1++;
		} else if (*str1 == '+' || *str1  == '-' || *str1 == '*' || *str1 == '/') {
			while (1) {
				if (!GetTop(&SS, &ee)) break;
				
				int prv1, prv2;
				if (*str1 == '+' || *str1 == '-') prv1 = 1;
				else if ( *str1 == '*' || *str1 == '/') prv1 = 2;

				if (ee == '+' || ee == '-') prv2 = 1;
				else if ( ee == '*' || ee == '/') prv2 = 2;
				else if (ee == '(') break;

				if (prv2 >= prv1) {  // 栈顶元素的优先级大于等于当前运算符的优先级
					Pop(&SS, &ee);
					*str2++ = ee;
				} else {
					break;
				}
			}
			Push(&SS, str1++);
		} else {
			return 0;
		}
		
	}
	
	while (!IsEmpty(&SS)) {
		Pop(&SS, &ee);
		*str2++ = ee;
	}
	*str2 = 0;
	return 1;
}

