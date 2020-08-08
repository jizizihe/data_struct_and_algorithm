#include <stdio.h>
#include <stdlib.h>  //malloc()、exit()
//顺序表存储数据时，会提前申请一整块足够大小的物理空间，然后将数据依次存储起来，存储时做到数据元素之间不留一丝缝隙。
#define Size 5
typedef struct Table {
	int * head;//声明了一个名为head的长度不确定的数组，也叫“动态数组”
	int length;//记录当前顺序表的长度
	int size;//记录顺序表分配的存储容量
}table;

table initTable() {
	table t;
	t.head = (int*)malloc(Size * sizeof(int));
	if (!t.head)
	{
		printf("初始化失败");
		exit(0);
	}
	t.length = 0;
	t.size = Size;
	return t;
}
//输出顺序表中元素的函数
void displayTable(table t) {
	int i;
	for (i = 0; i < t.length; i++) {
		printf("%d ", t.head[i]);
	}
	printf("\n");
}
int main() {
	int i;
	table t = initTable();
	//向顺序表中添加元素
	for (i = 1; i <= Size; i++) {
		t.head[i - 1] = i;
		t.length++;
	}
	printf("顺序表中存储的元素分别是：\n");
	displayTable(t);
	return 0;
}

