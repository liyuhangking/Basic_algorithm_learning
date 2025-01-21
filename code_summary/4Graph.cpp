#include <bits/stdc++.h>
#include <2Array_stack_queue.cpp>
#define MaxVertexNum 100
const int INF = 0x3f3f3f3f;
//邻接表
typedef struct ArcNode{         //边表结点
    int adjvex;                 //该弧所指向的顶点的位置
    struct ArcNode *nextarc;    //指向下一条弧的指针
}ArcNode;
typedef struct VNode{
    int data;                   //顶点信息
    ArcNode *firstarc;          //指向第一条依附该顶点的弧的指针
}VNode,AdjList[MaxVertexNum];
typedef struct{
    AdjList vertices;
    int vexnum, arcnum;
}ALGraph, Graph;                       //以邻接表存储的图

//邻接矩阵
typedef struct{
    int vex[MaxVertexNum];                  //顶点表
    int edge[MaxVertexNum][MaxVertexNum];   //邻接矩阵边表
    int vexnum,arcnum;
}MGraph, Graph;

//Breadth-First-Search,BFS
SqQueue Q;
bool visited[MaxVertexNum];
void BFSTraverse(Graph G){
    for(int i = 0; i < G.vexnum; ++i)
        visited[i] = false;
    InitQueue(Q);
    for(int i = 0; i < G.vexnum; ++i){
        if(!visited[i])
            BFS(G, i);
    }
}
//邻接表
void BFS(ALGraph G, int i){
    visit(i);       //对该节点最相应的操作，依题而定
    visited[i] = true;
    EnQueue(Q, i);
    while(!IsEmpty(Q)){
        DeQueue(Q, v);  //队首顶点v出队
        for(auto p = G.vertices[v].firstarc; p; p = p->nextarc){
            auto w = p->adjvex;
            if(visited[w] == false){
                visit(w);
                visited[w] = true;
                EnQueue(Q, w);
            }
        }
    }
}

//邻接矩阵
void BFS(MGraph G, int i){
    visit(i);
    visited[i] = true;
    EnQueue(Q, i);
    while(!IsEmpty(Q)){
        DeQueue(Q, v);
        for(auto w = 0; w < G.vexnum; w++){
            if(visited[w] == false){
                visit(w);
                visited[w] = true;
                EnQueue(Q, w);
            }
        }
    }
}
//Depth-First-Search,DFS
void DFSTraverse(Graph G){
    for(int i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for(int i = 0; i < G.vexnum; i++){
        if(!visited[i])
            DFS(G, i);
    }
}
//邻接表
void DFS(ALGraph G, int i){
    visit(i);
    visited[i] = true;
    for(auto p = G.vertices[i].firstarc; p; p = p->nextarc){
        auto j = p->adjvex;
        if(visited[j] == false)
            DFS(G, j);
    }   
}
//邻接矩阵
void DFS(MGraph G, int i){
    visit(i);
    visited[i] = true;
    for(int j = 0; j < G.vexnum; j++){
        if(visited[j] == false && G.edge[i][j] == 1)
            DFS(G, j);
    }
}

//拓扑排序
bool TopologicalSort(Graph G){
    InitStack(S);
    int i;
    for(i = 0; i < G.vexnum; i++)
        if(indegree[i] == 0)        //入度为0的点indegree
            Push(S, i);
    int count = 0;
    while(!IsEmpty(S)){
        Pop(S, i);
        print[count++] = i;         //输出顶点
        for(p = G.vertices[i].firstarc; p; p = p->nextarc){
            v = p->adjvex;
            if(!(--indegree[v]))
                Push(S, v);
        }

    }
    if(count < G.vexnum)
        return false;
    else
        return true;
}

//最小生成树MST，Prim
void Prim(MGraph G, int start){
    int lowcost[G.vexnum];
    int adjvex[G.vexnum];
    for(int i = 0; i < G.vexnum; i++){
        lowcost[i] = G.edge[start][i];
        adjvex[i] = start;
    }
    lowcost[start] = 0;
    int min;    //最小值
    int k;      //最小值的下标
    for(int i = 0; i < G.vexnum - 1; i++){
        min = INF;  //INF为正无穷
        for(int j = 0; j < G.vexnum; j++){
            if(lowcost[j] != 0 && lowcost[j] < min){
                min = lowcost[j];
                k = j;
            }
        }
        lowcost[k] = 0;
        //更新lowcost、adjvex
        for(int j = 0; j < G.vexnum; j++){
            if(lowcost[j] != 0 && lowcost[j] > G.edge[k][j]){
                lowcost[j] = G.edge[k][j];
                adjvex[j] = k;
            }
        }
    }
}

//最短路径Dijkstra
void Dijkstra(MGraph G, int v, int path[], int dist[]){
    int flag[G.vexnum];
    for(int i = 0; i < G.vexnum; i++){
        flag[i] = 0;
        dist[i] = G.edge[v][i];
        if(G.edge[v][i] < INF)
            path[i] = v;
        else
            path[i] = -1;
        flag[v] = 1;
        dist[v] = 0;
        int min;
        int k;
        for(int i = 0; i < G.vexnum; i++){
            min = INF;
            for(int j = 0; j < G.vexnum; j++){
                if(flag[j] == 0 && dist[j] < min){
                    min = dist[j];
                    k = j;
                }
            }
            flag[k] = 1;
            //更新path和dist数组
            for(int j = 0; j < G.vexnum; j++){
                if(flag[j] == 0 && dist[j] > min + G.edge[k][j]){
                    dist[j] = min + G.edge[k][j];
                    path[j] = k;
                }
            }
        }
    }
}

//图的连通性
bool Judge(Graph G){
    for(int i = 0; i < G.vexnum; i++){
        visited[i] = false;
    }
    DFS(G, 0);
    for(int i = 0; i < G.vexnum; i++){
        if(!visited[i]){
            return false;
        }
    }
    return true;
}

//有向图的转置
typedef struct{     //顶点
    int info[MaxSize];
}VertexNode;

typedef struct{
    int weigth;
}EdgeNode;

typedef struct{
    EdgeNode Edge[MaxSize][MaxSize];
    VertexNode vertex;
    int vexnum, arcnum;
}M_Graph;

void GraphTranspose(M_Graph G){
    int size = G.vexnum;
    for(int i = 0; i < size; i++){
        for(int j = i; j < size; j++){
            int temp = G.Edge[i][j].weigth;
            G.Edge[i][j].weigth = G.Edge[j][i].weigth;
            G.Edge[j][i].weigth = temp;
        }
    }
}

//图中任意两节点之间的所有路径(DFS变种)
void FindPath(Graph G, int u, int v, int path[], int d){
    int w, i;
    ArcNode *p;
    d++;
    path[d] = u;    //将当前节点添加到路径中
    visited[u] = 1;     //将当前节点标记为已访问
    if(u == v)
        print(path[]);
    for(p = G.vertices[u].firstarc; p; p = p->nextarc){
        w = p->adjvex;
        if(visited[w] == false){
            FindPath(G, w, v, path, d);
        }
    }
    visited[u] = 0;
}