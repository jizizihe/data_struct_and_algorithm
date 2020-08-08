#include <stdio.h>
#include <stdlib.h>
#define Size 5
typedef struct Table {
	int * head;
	int length;
	int size;
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
/* 向已有顺序表中插入数据元素，根据插入位置的不同，可分为以下 3 种情况：
 * 插入到顺序表的表头；
 * 在表的中间位置插入元素；
 * 尾随顺序表中已有元素，作为顺序表中的最后一个元素；
 */
//插入函数，其中，elem为插入的元素，add为插入到顺序表的位置
table addTable(table t, int elem, int add)
{
	int i;
	//判断插入本身是否存在问题（如果插入元素位置比整张表的长度+1还大（如果相等，是尾随的情况），或者插入的位置本身不存在，程序作为提示并自动退出）
	if (add > t.length + 1 || add < 1) {
		printf("插入位置有问题");
		return t;
	}
	//做插入操作时，首先需要看顺序表是否有多余的存储空间提供给插入的元素，如果没有，需要申请
	if (t.length >= t.size) {
		t.head = (int *)realloc(t.head, (t.size + 1) * sizeof(int));
		if (!t.head) {
			printf("存储分配失败");
		}
		t.size += 1;
	}
	//插入操作，需要将从插入位置开始的后续元素，逐个后移
	for (i = t.length - 1; i >= add - 1; i--) {
		t.head[i + 1] = t.head[i];
	}
	t.head[add - 1] = elem;
	t.length++;
	return t;
}
//只需找到目标元素，并将其后续所有元素整体前移 1 个位置即可
table delTable(table t, int add) {
	int i;
	if (add > t.length || add < 1) {
		printf("被删除元素的位置有误");
		exit(0);
	}
	for (i = add; i < t.length; i++) {
		t.head[i - 1] = t.head[i];
	}
	t.length--;
	return t;
}
//查找函数，其中，elem表示要查找的数据元素的值
int selectTable(table t, int elem) {
	int i;
	for (i = 0; i < t.length; i++) {
		if (t.head[i] == elem) {
			return i + 1;
		}
	}
	return -1;
}
//更改函数，其中，elem为要更改的元素，newElem为新的数据元素
table amendTable(table t, int elem, int newElem) {
	int add = selectTable(t, elem);
	t.head[add - 1] = newElem;
	return t;
}
void displayTable(table t) {
	int i;
	for (i = 0; i < t.length; i++) {
		printf("%d ", t.head[i]);
	}
	printf("\n");
}
int main() {
	int i, add;
	table t1 = initTable();
	for (i = 1; i <= Size; i++) {
		t1.head[i - 1] = i;
		t1.length++;
	}
	printf("原顺序表：\n");
	displayTable(t1);

	printf("删除元素1:\n");
	t1 = delTable(t1, 1);
	displayTable(t1);

	printf("在第2的位置插入元素5:\n");
	t1 = addTable(t1, 5, 2);
	displayTable(t1);

	printf("查找元素3的位置:\n");
	add = selectTable(t1, 3);
	printf("%d\n", add);

	printf("将元素3改为6:\n");
	t1 = amendTable(t1, 3, 6);
	displayTable(t1);
	return 0;
}


