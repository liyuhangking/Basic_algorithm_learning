#include <bits/stdc++.h>

//单链表的结构体
typedef struct LNode{
    int data;
    LNode *next;
}LNode, *LinkList;

//链表长度
int ListLen(LinkList L){
    int len = 0;
    LNode *p = L->next;
    while(p != NULL){
        len++;
        p = p->next;
    }
    printf("%d\n", len);
    return len;
}

//返回单链表中间节点
LNode *FindMidNode(LinkList L){
    int len = ListLen(L);
    int count = 0;
    LinkList p = L->next;
    while(p != NULL){
        count++;
        if(count == len/2)
            break;
        p = p->next;
    }
    return p;
}

//按关键字查找+删除（前后指针）
void DeletX(LinkList L, int x){
    LinkList pre = L;
    LinkList p = L->next;
    while(p != NULL){
        if(p->data == x){
            LNode *q = p;
            p = p->next;
            pre->next = p;
            free(q);
        }else{
            pre = p;
            p = p->next;
        }
    }
}

//查找+插入(假设1,2,3,5；插入4，保证有序)
void Insert(LinkList L, int x){
    LNode *pre = L;
    LNode *p = L->next;
    while(p != NULL){
        if(p->data == x)
            break;
        else{
            pre = p;
            p = p->next;
        }
    }
    LNode *q = (LinkList)malloc(sizeof(LNode));
    q->data = x;
    pre->next = q;
    q->next = p;
}

//头插法，将链表原地逆置
void ListReserve(LinkList L){
    LinkList head = (LinkList)malloc(sizeof(LNode));
    head->next = NULL;
    while(L->next != NULL){
        LNode *p = L->next;
        L->next = L->next->next;
        p->next = head->next;
        head->next = p;
    }
    L->next = head->next;
    free(head);
}

//尾插法（保持原序）
//题设C={a1,b1,a2,b2,......,an,bn}为线性表，设计就地算法，使得A={a1,a2....},B={bn,...,b2,b1}
LinkList A = NULL;
LinkList B = NULL;
void func(LinkList C){
    A = (LinkList)malloc(sizeof(LNode));
    A->next = NULL;
    LNode *tailA = A;
    B = (LinkList)malloc(sizeof(LNode));
    B->next = NULL;
    int count = 1;
    while(C->next != NULL){
        LinkList p = C->next;
        C->next = C->next->next;
        if(count%2==1){
            tailA->next = p;
            p->next = NULL;
            tailA = p;
        }else{
            p->next = B->next;
            B->next = p;
        }
        count++;
    }
}