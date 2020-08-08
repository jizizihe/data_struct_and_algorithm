#include <stdio.h>
#include <stdlib.h>

//与顺序表不同，链表不限制数据的物理存储状态，换句话说，使用链表存储的数据元素，其物理存储位置是随机的。
typedef struct Link {
	int  elem;//数据元素本身，其所在的区域称为数据域；
	struct Link *next;//指向直接后继元素的指针，所在的区域称为指针域；
}link;//link为节点名，每个节点都是一个 link 结构体

//初始化链表的函数
link * initLink();
//用于输出链表的函数
void display(link *p);

int main() {
	link*p = NULL;
	//初始化链表（1，2，3，4）
	printf("初始化链表为：\n");
	p = initLink();
	display(p);
	return 0;
}

link * initLink() {
	int i;
	//1、头指针：一个普通的指针，它的特点是永远指向链表第一个节点的位置
	//2、节点：链表中的节点又细分为头节点、首元节点和其他节点
	//头节点：其实就是一个不存任何数据的空节点，通常作为链表的第一个节点。对于链表来说，头节点不是必须的，它的作用只是为了方便解决某些实际问题；
	//首元节点：由于头节点（也就是空节点）的缘故，链表中称第一个存有数据的节点为首元节点。首元节点只是对链表中第一个存有数据节点的一个称谓，没有实际意义
	//其他节点：链表中其他的节点
	link * p = NULL;//创建头指针
	link * temp = (link*)malloc(sizeof(link));//创建首元节点
	//首元节点先初始化
	temp->elem = 1;
	temp->next = NULL;
	p = temp;//头指针指向首元节点
	for (i = 2; i < 5; i++) {
		link *a = (link*)malloc(sizeof(link));
		a->elem = i;
		a->next = NULL;
		temp->next = a;//将temp节点与新建立的a节点建立逻辑关系
		temp = temp->next;//指针temp每次都指向新链表的最后一个节点，其实就是 a节点，这里写temp=a也对
	}
	return p;
}
void display(link *p) {
	link* temp = p;//将temp指针重新指向头结点,也可以不要。
	//只要temp指针指向的结点的next不是Null，就执行输出语句。
	while (temp) {
		printf("%d ", temp->elem);
		temp = temp->next;
	}
	printf("\n");
}


