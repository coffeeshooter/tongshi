
#include<iostream>  
#define MVNum 100  
#define MaxInt 32767 //����ֵ������  
using namespace std;
typedef int ArcType;
typedef char VerTextType[20];
int* D = new int[MVNum];
bool* S = new bool[MVNum];
int* Path = new int[MVNum];
typedef struct ArcNode //�߽��  
{
    int adjver; //�ñ���ָ��Ķ���λ��  
    struct ArcNode* nextarc; //ָ����һ���ߵ�ָ��  
    ArcType   weight;
} ArcNode;

typedef struct VNode //������Ϣ  
{
    VerTextType data;
    ArcNode* firstarc;
} VNode, AdjList[MVNum];

typedef struct node
{
    AdjList vertices;
    int     vexnum; //ͼ�ĵ�ǰ������  
    int     arcnum; //ͼ�ĵ�ǰ����  
} ALGraph;

//�ٽӱ�洢��ʽ���·����dijkstra��,���Ӷ�O(n^2)  
void ShortestPath_DIJ2(ALGraph G, int v0, ArcType D[], int Path[])
{
    int ok[MVNum], i, j; // ok�������Ƿ�ȷ�����·��  
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

//ͼ���ڽӾ���  
typedef struct
{
    char vexs[MVNum];                        //�����   
    int arcs[MVNum][MVNum];                 //�ڽӾ���  
}Graph;

void InitGraph(Graph& G, int vex)
{
    cout << "���������ƣ���a" << endl;
    for (int i = 0; i < vex; ++i) {
        cout << "�������" << (i + 1) << "���������:";
        cin >> G.vexs[i];
    }
    cout << endl;

    for (int i = 0; i < vex; ++i)  //��ʼ���ڽӾ��󣬱ߵ�Ȩֵ����Ϊ����ֵMaxInt   
        for (int j = 0; j < vex; ++j)
        {
            if (j != i)
                G.arcs[i][j] = MaxInt;
            else
                G.arcs[i][j] = 0;
        }
}

//ȷ����v��G�е�λ��  
int LocateVex(Graph G, char v, int vex) {
    for (int i = 0; i < vex; ++i)
        if (G.vexs[i] == v)
            return i;
    return -1;
}

//����������G  
void CreateUDN(Graph& G, int vex, int arc)
{
    int i, j, k;

    cout << "����������Ķ���(node1 node2 weight)" << endl;
    for (k = 0; k < arc; ++k) {  //�����ڽӾ���   
        char v1, v2;
        int o;
        cout << "�������" << (k + 1) << "���������Ķ���Ͷ�Ӧ��Ȩֵ:";
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
                cout << "��" << "\t";
        }
        cout << endl;
    }
}

//��Dijkstra�㷨��������G��v0���㵽���ඥ������·��   
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
        for (w = 0; w < n; ++w)                              //���´�v0����������V?S�����ж�������·������   
            if (!S[w] && (D[v] + G.arcs[v][w] < D[w])) {
                D[w] = D[v] + G.arcs[v][w];                 //����D[w]   


                Path[w] = v;                                //����w��ǰ��  
            }

    }
    for (int i = 0; i < vex; i++) {
        if (D[i] != 0)
            if (D[i] != MaxInt)
                cout << "��" << G.vexs[i] << "���·������:" << D[i] << endl;
            else
            {
                cout << "��" << G.vexs[i] << "���·������:" << "�޷�����" << endl;
            }
    }
}



int main()
{
    Graph G;
    int vexnum, arcnum;
    cout << "��ֱ������ܶ��������ܱ���:";
    cin >> vexnum >> arcnum;
    cout << endl;
    InitGraph(G, vexnum);
    int v = 0;
    CreateUDN(G, vexnum, arcnum);
    cout << endl;
    cout << "�Ѵ�������ͼG" << endl << endl;
    DisplayGraph(G, vexnum);
    int v0 = LocateVex(G, '0', vexnum);
    ShortestPath_DIJ(G, v0, vexnum);
}