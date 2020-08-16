#include <stdio.h>
#define maxSize 7
typedef struct {
	int data;
	int cur;
}component;
//将结构体数组中所有分量链接到备用链表中
void reserveArr(component *array);
//初始化静态链表
int initArr(component *array);
//向链表中插入数据，body表示链表的头结点在数组中的位置，add表示插入元素的位置，num表示要插入的数据
void insertArr(component * array, int body, int add, int num);
//删除链表中存有num的结点,返回新数据链表中第一个节点所在的位置
int deletArr(component * array, int body, int num);
//查找存储有num的结点在数组的位置
int selectNum(component * array, int body, int num);
//将链表中的字符oldElem改为newElem
void amendElem(component * array, int body, int oldElem, int newElem);
//输出函数
void displayArr(component * array, int body);
//从备用链表中摘除空闲节点的实现函数
int mallocArr(component * array);
//将摘除下来的节点链接到备用链表上
void freeArr(component * array, int k);

int main() {
	component array[maxSize];
	int body = initArr(array);
	int selectAdd;
	printf("静态链表为：\n");
	displayArr(array, body);

	printf("在第3的位置上插入元素4:\n");
	insertArr(array, body, 3, 4);
	displayArr(array, body);

	printf("删除数据域为1的结点:\n");
	body = deletArr(array, body, 1);
	displayArr(array, body);

	printf("查找数据域为4的结点的位置:\n");
	selectAdd = selectNum(array, body, 4);
	printf("%d\n", selectAdd);
	printf("将结点数据域为4改为5:\n");
	amendElem(array, body, 4, 5);
	displayArr(array, body);
	return 0;
}
//创建备用链表
void reserveArr(component *array) {
	int i = 0;
	for (i = 0; i < maxSize; i++) {
		array[i].cur = i + 1;//将每个数组分量链接到一起
	}
	array[maxSize - 1].cur = 0;//链表最后一个结点的游标值为0
}

//提取分配空间
int mallocArr(component * array) {
	//若备用链表非空，则返回分配的结点下标，否则返回0（当分配最后一个结点时，该结点的游标值为0）
	int i = array[0].cur;
	if (array[0].cur) {
		array[0].cur = array[i].cur;
	}
	return i;
}

//初始化静态链表
int initArr(component *array) {
	int tempBody = 0, body = 0;
	int i = 0;
	reserveArr(array);
	body = mallocArr(array);
	//建立首元结点
	array[body].data = 1;
	array[body].cur = 0;
	//声明一个变量，把它当指针使，指向链表的最后的一个结点，当前和首元结点重合
	tempBody = body;
	for (i = 2; i < 4; i++) {
		int j = mallocArr(array); //从备用链表中拿出空闲的分量
		array[j].data = i;      //初始化新得到的空间结点
		array[tempBody].cur = j; //将新得到的结点链接到数据链表的尾部
		tempBody = j;             //将指向链表最后一个结点的指针后移
	}
	array[tempBody].cur = 0;//新的链表最后一个结点的指针设置为0
	return body;//body表示链表的头结点在数组中的位置
}

void displayArr(component * array, int body) {
	int tempBody = body;//tempBody准备做遍历使用
	while (array[tempBody].cur) {
		printf("%d,%d ", array[tempBody].data, array[tempBody].cur);
		tempBody = array[tempBody].cur;
	}
	printf("%d,%d\n", array[tempBody].data, array[tempBody].cur);

}

//向链表中插入数据，body表示链表的头结点在数组中的位置，add表示插入元素的位置，num表示要插入的数据
void insertArr(component * array, int body, int add, int num) {
	int tempBody = body;//tempBody做遍历结构体数组使用
	int i = 0, insert = 0;
	//找到要插入位置的上一个结点在数组中的位置
	for (i = 1; i < add; i++) {
		tempBody = array[tempBody].cur;
	}
	insert = mallocArr(array);//申请空间，准备插入
	array[insert].data = num;

	array[insert].cur = array[tempBody].cur;//新插入结点的游标等于其直接前驱结点的游标
	array[tempBody].cur = insert;//直接前驱结点的游标等于新插入结点所在数组中的下标
}

//删除结点函数，num表示被删除结点中数据域存放的数据
int deletArr(component * array, int body, int num) {
	int tempBody = body;
	int del = 0;
	int newbody = 0;
	//找到被删除结点的位置
	while (array[tempBody].data != num) {
		tempBody = array[tempBody].cur;
		//当tempBody为0时，表示链表遍历结束，说明链表中没有存储该数据的结点
		if (tempBody == 0) {
			printf("链表中没有此数据");
			return;
		}
	}
	//运行到此，证明有该结点
	del = tempBody;
	tempBody = body;
	//删除首元结点，需要特殊考虑
	if (del == body) {
		newbody = array[del].cur;
		freeArr(array, del);
		return newbody;
	}
	else
	{
		//找到该结点的上一个结点，做删除操作
		while (array[tempBody].cur != del) {
			tempBody = array[tempBody].cur;
		}
		//将被删除结点的游标直接给被删除结点的上一个结点
		array[tempBody].cur = array[del].cur;
		//回收被摘除节点的空间
		freeArr(array, del);
		return body;
	}  
}

//在以body作为头结点的链表中查找数据域为elem的结点在数组中的位置
int selectNum(component * array, int body, int num) {
	//当游标值为0时，表示链表结束
	while (array[body].cur != 0) {
		if (array[body].data == num) {
			return body;
		}
		body = array[body].cur;
	}
	//判断最后一个结点是否符合要求
	if (array[body].data == num) {
		return body;
	}
	return -1;//返回-1，表示在链表中没有找到该元素
}

//在以body作为头结点的链表中将数据域为oldElem的结点，数据域改为newElem
void amendElem(component * array, int body, int oldElem, int newElem) {
	int add = selectNum(array, body, oldElem);
	if (add == -1) {
		printf("无更改元素");
		return;
	}
	array[add].data = newElem;
}

//备用链表回收空间的函数，其中array为存储数据的数组，k表示未使用节点所在数组的下标
void freeArr(component * array, int k) {
	array[k].cur = array[0].cur;
	array[0].cur = k;
}


