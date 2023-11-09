#include <stdio.h>
const int MAXN = 10;
const int INF = 10000; // 设置一个较大的值作为无穷大
void prim(int n, int graph[MAXN][MAXN]) 
{
    int parent[MAXN]; // 存储最小生成树的父节点
    int key[MAXN];    // 存储与最小生成树连接的最小权值
    bool inMST[MAXN]; // 用于跟踪顶点是否已经在最小生成树中
    // 初始化key和inMST数组
    for (int i = 0; i < n; i++) 
    {
        key[i] = INF;
        inMST[i] = false;
    }
    key[0] = 0;      // 从第一个顶点开始
    parent[0] = -1;  // 第一个顶点没有父节点
    // Prim算法主要部分
    for (int count = 0; count < n - 1; count++) 
    {
        int u = -1;
        // 找到key值最小的顶点
        for (int v = 0; v < n; v++) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) 
            {
                u = v;
            }
        }
        inMST[u] = true;
        // 更新key值和parent数组
        for (int v = 0; v < n; v++) 
        {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) 
            {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }
    // 输出最小生成树的结果
    printf("edge\tweight\n");
    for (int i = 1; i < n; i++) 
    {
        printf("%d - %d\t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}
int main() 
{
    int n; // 顶点数
    int graph[MAXN][MAXN]={INF}; // 邻接矩阵表示的图
    // 输入顶点数
    printf("enter number of vertex: ");
    scanf("%d", &n);
    // 输入邻接矩阵
    printf("set the edge:\n");
    int start,end,weight;
    printf("enter start end weight(or -1 -1 -1 to end):\n");
    while(1)
    {
        scanf("%d %d %d",&start,&end,&weight);
        if(start==-1||end==-1)
        {
            break;
        }
        else if(start==end)
        {
            printf("start should not equal end");
            continue;
        }
        graph[start-1][end-1]=weight;
        graph[end-1][start-1]=weight;
    }
    // 调用Prim算法计算最小生成树
    prim(n, graph);
    return 0;
}
