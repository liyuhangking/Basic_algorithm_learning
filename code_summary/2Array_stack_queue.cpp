#include <bits/stdc++.h>

#define MaxSize 50
#define True 1
#define False 0
//栈结构体
typedef struct{
    int data[MaxSize];
    int top;
}SqStack;

//初始化栈
void InitStack(SqStack &S){
    S.top = -1;
}

//判栈空
bool StackEmpty(SqStack S){
    if(S.top == -1){
        return True;
    }
    else
        return False;
}

//进栈
bool Push(SqStack &S, int x){
    if(S.top == MaxSize - 1)
        return False;
    S.data[++S.top] = x;
    return True;
}

bool Pop(SqStack &S, int &x){
    if(S.top == -1)
        return False;
    x = S.data[S.top--];
    return True;
}

//队列结构体
typedef struct{
    int data[MaxSize];
    int front,rear;
}SqQueue;

//初始化队列
void InitQueue(SqQueue &Q){
    Q.front = Q.rear = 0;
}

//队列判空
bool IsEmpty(SqQueue Q){
    if(Q.front == Q.rear)
        return True;
    else
        return False;
}

//入队
bool EnQueue(SqQueue &Q, int x){
    if((Q.rear + 1)% MaxSize == Q.front)//队满
        return False;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    return True;
}

//出队
bool DeQueue(SqQueue &Q, int x){
    if(Q.rear == Q.front)//队空
        return False;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return True;
}

//链队结构体
typedef struct LinkNode{
    int data;
    struct LinkNode *next;
}LinkNode;

typedef struct{
    LinkNode *front, *rear;
}LinkQueue;

//中缀表达式，转后缀表达式
char *RPExpression(char *e){
    InitStack(s);   //运算符栈s
    InitQueue(q);   //存放逆波兰式的队列q
    char ch;
    int length = 0;
    Push(s, '#');
    for(char *p = e; *p != '\0'; p++){
        switch(*p){

            case '(':
                Push(s, *p);
                break;
            case ')':
                while(GetTop(s) != '('){
                    Pop(s, ch);
                    EnQueue(q, ch);
                }
                Pop(s, q);
                break;
            case '+':
            case '-':
                for(ch = GetTop(s); ch != '#'; ch = GetTop(s1)){
                    if(ch == '(')
                        break;
                    else{
                        Pop(s, ch);
                        EnQueue(q, ch);
                        length++;
                    }
                }
                Push(s, *p);
                break;
            case '*':
            case '/':
                for(ch = GetTop(s); ch != '#'&& ch != '+' && ch != '-'; ch = GetTop(s)){
                    if(ch == '(')
                        break;
                    else{
                        Pop(s, ch);
                        EnQueue(q, ch);
                        length++;
                    }
                }
                Push(s, *p);
                break;
            default:
                EnQueue(q, *p);
                length++;
        }
    }
    while(!StackEmpty(s) && GetTop(s) != '#'){
        Pop(s, ch);
        EnQueue(q, ch);
        length++;
    }
    char *result = new char [length];
    int i = 0;
    while(!IsEmpty(q)){
        DeQueue(q, ch);
        result[i] = ch;
        i++;
    }
    return result;
}
//稀疏矩阵的存储
typedef struct{
    int r, c;   //行row，列column
    int x;
}Triple;
typedef struct{
    Triple data[MaxSize];
    int mu, nu, tu; //矩阵行数，列数，非0元个数
}TSMatrix;

//稀疏矩阵的转置
void TransposeMatrix(TSMatrix A, TSMatrix & B){
    B.mu = A.mu;B.nu = A.nu;B.tu = B.tu;
    if(A.tu){
        int p = 1;
        for(int col = 1; col <= A.nu; col++){
            for(int q = 1; q <= A.tu; q++){
                if(col == A.data[q].c){
                    B.data[p].r = A.data[q].r;
                    B.data[p].c = A.data[q].c;
                    B.data[p].x = A.data[q].x;
                    p++;
                }
            }
        }
    }
}

//稀疏矩阵的加法

//0/1背包
const int n = 5, c = 40;
int dp[n][c];
int w[];

for(int i = 1; i <= n; i++){
    for(int j = 0; j <= c; j++){
        if(w[i] > j)
            dp[i][j] = dp[i-1][j];
        else
            dp[i][j] = max{dp[i-1][j], dp[i-1][j-w[i]] + p[i]};
    }
}
