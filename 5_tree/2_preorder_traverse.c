/******************************************************
 * Filename     : 2_preorder_traverse.c
 * Last modified: 2021-12-21 06:46
 * Author       : jzzh
 * Email        : jzzh@szbaijie.cn
 * Company site : http://www.szbaijie.cn/index.php
 * Description  :二叉树先序遍历的实现思想是：

	1、访问根节点；
    2、访问当前节点的左子树；
    3、若当前节点无左子树，则访问当前节点的右子树；
 操作：

    访问该二叉树的根节点，找到 1；
    访问节点 1 的左子树，找到节点 2；
    访问节点 2 的左子树，找到节点 4；
    由于访问节点 4 左子树失败，且也没有右子树，因此以节点 4 为根节点的子树遍历完成。但节点 2 还没有遍历其右子树，因此现在开始遍历，即访问节点 5；
    由于节点 5 无左右子树，因此节点 5 遍历完成，并且由此以节点 2 为根节点的子树也遍历完成。现在回到节点 1 ，并开始遍历该节点的右子树，即访问节点 3；
    访问节点 3 左子树，找到节点 6；
    由于节点 6 无左右子树，因此节点 6 遍历完成，回到节点 3 并遍历其右子树，找到节点 7；
    节点 7 无左右子树，因此以节点 3 为根节点的子树遍历完成，同时回归节点 1。由于节点 1 的左右子树全部遍历完成，因此整个二叉树遍历完成；

    访问该二叉树的根节点，找到 1；
    访问节点 1 的左子树，找到节点 2；
    访问节点 2 的左子树，找到节点 4；
    由于访问节点 4 左子树失败，且也没有右子树，因此以节点 4 为根节点的子树遍历完成。但节点 2 还没有遍历其右子树，因此现在开始遍历，即访问节点 5；
    由于节点 5 无左右子树，因此节点 5 遍历完成，并且由此以节点 2 为根节点的子树也遍历完成。现在回到节点 1 ，并开始遍历该节点的右子树，即访问节点 3；
    访问节点 3 左子树，找到节点 6；
    由于节点 6 无左右子树，因此节点 6 遍历完成，回到节点 3 并遍历其右子树，找到节点 7；
    节点 7 无左右子树，因此以节点 3 为根节点的子树遍历完成，同时回归节点 1。由于节点 1 的左右子树全部遍历完成，因此整个二叉树遍历完成；

 ******************************************************/
#include <stdio.h>
#include <string.h>
#define TElemType int
int top=-1;//top变量时刻表示栈顶元素所在位置
//构造结点的结构体
typedef struct BiTNode{
	TElemType data;//数据域
	struct BiTNode *lchild,*rchild;//左右孩子指针
}BiTNode,*BiTree;
//初始化树的函数
void CreateBiTree(BiTree *T){
	*T=(BiTNode*)malloc(sizeof(BiTNode));
	(*T)->data=1;
	(*T)->lchild=(BiTNode*)malloc(sizeof(BiTNode));
	(*T)->rchild=(BiTNode*)malloc(sizeof(BiTNode));
	(*T)->lchild->data=2;
	(*T)->lchild->lchild=(BiTNode*)malloc(sizeof(BiTNode));
	(*T)->lchild->rchild=(BiTNode*)malloc(sizeof(BiTNode));
	(*T)->lchild->rchild->data=5;
	(*T)->lchild->rchild->lchild=NULL;
	(*T)->lchild->rchild->rchild=NULL;
	(*T)->rchild->data=3;
	(*T)->rchild->lchild=(BiTNode*)malloc(sizeof(BiTNode));
	(*T)->rchild->lchild->data=6;
	(*T)->rchild->lchild->lchild=NULL;
	(*T)->rchild->lchild->rchild=NULL;
	(*T)->rchild->rchild=(BiTNode*)malloc(sizeof(BiTNode));
	(*T)->rchild->rchild->data=7;
	(*T)->rchild->rchild->lchild=NULL;
	(*T)->rchild->rchild->rchild=NULL;
	(*T)->lchild->lchild->data=4;
	(*T)->lchild->lchild->lchild=NULL;
	(*T)->lchild->lchild->rchild=NULL;
}
//前序遍历使用的进栈函数
void push(BiTNode** a,BiTNode* elem){
	a[++top]=elem;
}
//弹栈函数
void pop( ){
	if (top==-1) {
		return ;
	}
	top--;
}
//模拟操作结点元素的函数，输出结点本身的数值
void displayElem(BiTNode* elem){
	printf("%d ",elem->data);
}
//拿到栈顶元素
BiTNode* getTop(BiTNode**a){
	return a[top];
}
//先序遍历非递归算法
void PreOrderTraverse(BiTree Tree){
	BiTNode* a[20];//定义一个顺序栈
	BiTNode * p;//临时指针
	push(a, Tree);//根结点进栈
	while (top!=-1) {
		p=getTop(a);//取栈顶元素
		pop();//弹栈
		while (p) {
			displayElem(p);//调用结点的操作函数
			//如果该结点有右孩子，右孩子进栈
			if (p->rchild) {
				push(a,p->rchild);
			}
			p=p->lchild;//一直指向根结点最后一个左孩子
		}
	}
}
int main(){
	BiTree Tree;
	CreateBiTree(&Tree);
	printf("先序遍历: \n");
	PreOrderTraverse(Tree);
	printf("\n");
}
