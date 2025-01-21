#include <bits/stdc++.h>
#include <2Array_stack_queue.cpp>

typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
//前序遍历
void PreOrder(BiTree T){
    if(T != NULL){
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}
//中序遍历
void InOrder(BiTree T){
    if(T != NULL){
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}
//后序遍历
void PostOrder(BiTree T){
    if(T != NULL){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}
//层序遍历
void LevelOrder(BiTree T){
    InitQueue(Q);
    BiTree p;
    EnQueue(Q, T);
    while(!IsEmpty(Q)){
        DeQueue(Q, p);
        visit(p);
        if(p->lchild != NULL)
            EnQueue(Q, p->lchild);
        if(p->rchild != NULL)
            EnQueue(Q, p->rchild);
    }
}
//构造哈夫曼树
typedef struct{
    int weight;
    int parent, lchild, rchild;
}HTNode;
void HuffmanTree(HTNode HT[], int w[], int n){
    for(int i = 0; i < 2*n-1; i++){
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    }
    for(int i = 0; i < n; i++){
        HT[i].weight = w[i];
    }
    for(int i = 0; i < 2*n-1; i++){
        Select(HT, i, s1, s2);  //得到权重最小的两个根结点在ＨＴ数组中的下标s1,s2
        HT[i].weight = HT[s1].weight + HT[s2].weight;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[s1].parent = i;
        HT[s2].parent = i;
    }
}
//哈夫曼编码
void HuffmanEncoding(HTNode HT[], char* HuffCode[], int n){
    auto temp = new char[n];
    temp[n-1] = '\0';
    for(int i = 0; i < n; i++){
        start = n-1;
        pos = i;
        parent = HT[pos].parent;
        while(parent != -1){
            if(HT[parent].lchild == pos)
                temp[--start] = '0';
            else
                temp[--start] = '1';
            pos = parent;
            parent = HT[parent].parent;
        }
        HuffCode[i] = new char[n-start];
        strcpy(HuffCode[i], &temp[start]);
    }
    delete temp;
}
//哈夫曼解码
void HuffmanDecoding(HTNode HT[], char A[]){
    int p = 0;
    int len = strlen(A);
    for(int i = 0; i < len; i++){
        if(HT[p].lchild == -1 && HT[p].rchild == -1){
            printf("%d", HT[p].weight);
            p = 0;
            continue;
        }
        if(A[i] == '0'){
            if(HT[p].lchild == -1){
                printf("编码错误");
                break;
            }
            else
                p = HT[p].lchild;
        }
        else if(A[i] == '1'){
            if(HT[p].rchild == -1){
                printf("编码错误");
                break;
            }
            else
                p = HT[p].rchild;
        }
    }
}

//线索二叉树
//存储结构
typedef struct TreadNode{
    int data;
    struct TreadNode *lchild, *rchild;
    int ltag, rtag;
}ThreadNode, *ThreadTree;

//中序线索化
void InThread(ThreadTree &p, ThreadTree &pre){
    if(p != NULL){
        InThread(p->lchild, pre);
        if(p->lchild == NULL){
            p->lchild = pre;
            p->ltag = 1;
        }
        if(pre != NULL && pre->rchild == NULL){
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
        InThread(p->rchild, pre);
    }
}

void CreatInThread(ThreadTree T){
    ThreadTree pre;
    if(T != NULL){
        InThread(T, pre);
        pre->rchild = NULL;
        pre->rtag = 1;
    }
}

//中序线索二叉树的遍历
//中序线索二叉树的中序序列下的第一个节点
ThreadNode *Firstnode(ThreadNode *p){
    while(p->ltag)
    p = p->lchild;
    return p;
}
//中序线索二叉树中节点p在中序序列下的后继
ThreadNode *Nextnode(ThreadNode *p){
    if(p->rtag == 0)
    return Firstnode(p->rchild);
    else
    return p->rchild;
}

void InOrder(ThreadNode *T){
    for(ThreadNode *p = Firstnode(T); p != NULL; p = Nextnode(p))
        visit(p);
}
//二叉排序树
//查找
BSTNode *BST_Search(BiTree T, int key){
    while(T != NULL && key != T->data){
        if(key < T->data)
            T = T->lchild;
        else
            T = T->rchild;
    }
    return T;
}
//插入
int BST_Insert(BiTree &T, int k){
    if(T == NULL){
        T = (BiTree)malloc(sizeof(BSTNode));
        T->data = key;
        T->lchild = T->rchild = NULL;
        return 1;
    }
    else if(k == T->data)
        return 0;
    else if(k < T->data)
        return BST_Insert(T->lchild, k);
    else if(k > T->data)
        return BST_Insert(T->rchild, k);
}
//构造二叉排序树
void Creat_BST(BiTree &T, int str[], int n){
    T = NULL;
    int i = 0;
    while(i < n){
        BST_Insert(T, str[i]);
        i++;
    }
}










