
#include<iostream>  
#define MVNum 100  
#define MaxInt 32767 //极大值，即∞  
using namespace std;
typedef int ArcType;
typedef char VerTextType[20];
int* D = new int[MVNum];
bool* S = new bool[MVNum];
int* Path = new int[MVNum];
typedef struct ArcNode //边结点  
{
    int adjver; //该边所指向的顶点位置  
    struct ArcNode* nextarc; //指向下一条边的指针  
    ArcType   weight;
} ArcNode;

typedef struct VNode //顶点信息  
{
    VerTextType data;
    ArcNode* firstarc;
} VNode, AdjList[MVNum];

typedef struct node
{
    AdjList vertices;
    int     vexnum; //图的当前顶点数  
    int     arcnum; //图的当前边数  
} ALGraph;

//临接表存储方式最短路径（dijkstra）,复杂度O(n^2)  
void ShortestPath_DIJ2(ALGraph G, int v0, ArcType D[], int Path[])
{
    int ok[MVNum], i, j; // ok数组标记是否确定最短路径  
    for (i = 0; i < G.vexnum; i++) {
        ok[i] = 0;
        Path[i] = -1;
        D[i] = MaxInt;
    }
    D[v0] = 0;
    for (i = 0; i < G.vexnum; i++) {
        int min_node = -1;
        for (j = 0; j < G.vexnum; j++) {
            if (ok[j] == 0 && (min_node == -1 || D[j] < D[min_node])) {
                min_node = j;
            }
        }
        if (min_node == -1) break;
        ok[min_node] = 1;

        ArcNode* cur = G.vertices[min_node].firstarc;
        while (cur != NULL) {
            if (ok[cur->adjver] == 0 && D[cur->adjver] > D[min_node] + cur->weight) {
                D[cur->adjver] = D[min_node] + cur->weight;
                Path[cur->adjver] = min_node;
            }
            cur = cur->nextarc;
        }
    }

}

//图的邻接矩阵  
typedef struct
{
    char vexs[MVNum];                        //顶点表   
    int arcs[MVNum][MVNum];                 //邻接矩阵  
}Graph;

void InitGraph(Graph& G, int vex)
{
    cout << "输入点的名称，如a" << endl;
    for (int i = 0; i < vex; ++i) {
        cout << "请输入第" << (i + 1) << "个点的名称:";
        cin >> G.vexs[i];
    }
    cout << endl;

    for (int i = 0; i < vex; ++i)  //初始化邻接矩阵，边的权值均置为极大值MaxInt   
        for (int j = 0; j < vex; ++j)
        {
            if (j != i)
                G.arcs[i][j] = MaxInt;
            else
                G.arcs[i][j] = 0;
        }
}

//确定点v在G中的位置  
int LocateVex(Graph G, char v, int vex) {
    for (int i = 0; i < vex; ++i)
        if (G.vexs[i] == v)
            return i;
    return -1;
}

//创建无向网G  
void CreateUDN(Graph& G, int vex, int arc)
{
    int i, j, k;

    cout << "输入边依附的顶点(node1 node2 weight)" << endl;
    for (k = 0; k < arc; ++k) {  //构造邻接矩阵   
        char v1, v2;
        int o;
        cout << "请输入第" << (k + 1) << "条边依附的顶点和对应的权值:";
        cin >> v1 >> v2 >> o;
        i = LocateVex(G, v1, vex);  j = LocateVex(G, v2, vex);
        G.arcs[j][i] = G.arcs[i][j] = o;
    }
}

void DisplayGraph(Graph G, int vex)
{
    int i, j;
    for (i = 0; i < vex; ++i) {
        for (j = 0; j < vex; ++j) {
            if (G.arcs[i][j] != MaxInt)
                cout << G.arcs[i][j] << "\t";
            else
                cout << "∞" << "\t";
        }
        cout << endl;
    }
}

//用Dijkstra算法求无向网G的v0顶点到其余顶点的最短路径   
void ShortestPath_DIJ(Graph G, int v0, int vex) {
    int v, i, w, min;
    int n = vex;
    for (v = 0; v < n; ++v) {
        S[v] = false;
        D[v] = G.arcs[v0][v];
        if (D[v] < MaxInt)  Path[v] = v0;
        else Path[v] = -1;
    }

    S[v0] = true;
    D[v0] = 0;

    for (i = 1; i < n; ++i) {
        min = MaxInt;
        for (w = 0; w < n; ++w)
            if (!S[w] && D[w] < min) {
                v = w;
                min = D[w];
            }//if             
        S[v] = true;
        for (w = 0; w < n; ++w)                              //更新从v0出发到集合V?S上所有顶点的最短路径长度   
            if (!S[w] && (D[v] + G.arcs[v][w] < D[w])) {
                D[w] = D[v] + G.arcs[v][w];                 //更新D[w]   


                Path[w] = v;                                //更改w的前驱  
            }

    }
    for (int i = 0; i < vex; i++) {
        if (D[i] != 0)
            if (D[i] != MaxInt)
                cout << "到" << G.vexs[i] << "最短路径长度:" << D[i] << endl;
            else
            {
                cout << "到" << G.vexs[i] << "最短路径长度:" << "无法到达" << endl;
            }
    }
}



int main()
{
    Graph G;
    int vexnum, arcnum;
    cout << "请分别输入总顶点数和总边数:";
    cin >> vexnum >> arcnum;
    cout << endl;
    InitGraph(G, vexnum);
    int v = 0;
    CreateUDN(G, vexnum, arcnum);
    cout << endl;
    cout << "已创建无向图G" << endl << endl;
    DisplayGraph(G, vexnum);
    int v0 = LocateVex(G, '0', vexnum);
    ShortestPath_DIJ(G, v0, vexnum);
}