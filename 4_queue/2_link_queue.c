/******************************************************
* Filename     : 2_link_queue.c
* Last modified: 2021-12-19 17:06
* Author       : jzzh
* Email        : jzzh@szbaijie.cn
* Company site : http://www.szbaijie.cn/index.php
* Description  : 
******************************************************/
#include <stdio.h>
#include <stdlib.h>
typedef struct QNode{
    int data;
    struct QNode * next;
}QNode;
QNode * initQueue(){
    QNode * queue=(QNode*)malloc(sizeof(QNode));
    queue->next=NULL;
    return queue;
}
QNode* enQueue(QNode * rear,int data){
    QNode * enElem=(QNode*)malloc(sizeof(QNode));
    enElem->data=data;
    enElem->next=NULL;
    //使用尾插法向链队列中添加数据元素
    rear->next=enElem;
    rear=enElem;
    return rear;
}
QNode* DeQueue(QNode * top,QNode * rear){
    if (top->next==NULL) {
        printf("队列为空\n");
        return rear;
    }
    QNode * p=top->next;
    printf("%d \n",p->data);
    top->next=p->next;
    if (rear==p) {
//		printf("%d \n",top->data);
//		printf("%d \n",rear->data);
        rear=top;
    }
    free(p);
    return rear;
}
int main() {
    QNode *top,*rear;
    top=rear=initQueue();//创建头结点
    //向链队列中添加结点，使用尾插法添加的同时，队尾指针需要指向链表的最后一个元素
    rear=enQueue(rear, 1);
    rear=enQueue(rear, 2);
    rear=enQueue(rear, 3);
    rear=enQueue(rear, 4);
    //入队完成，所有数据元素开始出队列
    rear=DeQueue(top, rear);
    rear=DeQueue(top, rear);
    rear=DeQueue(top, rear);
    rear=DeQueue(top, rear);
    rear=DeQueue(top, rear);
    return 0;
}

