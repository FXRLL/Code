#include <stdio.h>
#include <queue>
#define MAX_VERTEX_NUM 8
typedef int VertexType;
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
    int weight;
} ArcNode;
typedef struct VNode
{
    int degree, indegree;
    VertexType data;
    ArcNode *firstarc;
} VNode;
typedef struct
{
    VNode vertices[MAX_VERTEX_NUM];
    int vexnum, arcnum;
} ALGraph;
void CreateGraph(ALGraph &G)
{
    printf("Enter the number of vertices: ");
    scanf("%d", &G.vexnum);

    for (int i = 0; i < G.vexnum; i++)
    {
        G.vertices[i].data = i;
        G.vertices[i].degree = 0;
        G.vertices[i].indegree = 0;
        G.vertices[i].firstarc = NULL;
    }

    printf("Enter the number of edges: ");
    scanf("%d", &G.arcnum);

    printf("Enter the edges (format: start_vertex end_vertex weight):\n");
    for (int i = 0; i < G.arcnum; i++)
    {
        int start, end, weight;
        scanf("%d %d %d", &start, &end, &weight);

        ArcNode *newNode = new ArcNode;
        newNode->adjvex = end;
        newNode->weight = weight;
        newNode->nextarc = G.vertices[start].firstarc;
        G.vertices[start].firstarc = newNode;
        G.vertices[start].degree++;
        G.vertices[end].indegree++;
    }
}
void DFS(ALGraph &G, int v, bool visited[])
{
    visited[v] = true;
    printf("%d ", v);
    ArcNode *p = G.vertices[v].firstarc;
    while (p)
    {
        int w = p->adjvex;
        if (!visited[w])
        {
            DFS(G, w, visited);
        }
        p = p->nextarc;
    }
}
void DFSGraph(ALGraph &G)
{
    bool visited[MAX_VERTEX_NUM] = {false};
    printf("Depth-First Traversal Result: ");
    for (int i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            DFS(G, i, visited);
        }
    }
    printf("\n");
}
void BFSGraph(ALGraph &G)
{
    bool visited[MAX_VERTEX_NUM] = {false};
    std::queue<int> q;
    printf("Breadth-First Traversal Result: ");
    for (int i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            visited[i] = true;
            printf("%d ", i);
            q.push(i);

            while (!q.empty())
            {
                int v = q.front();
                q.pop();
                ArcNode *p = G.vertices[v].firstarc;
                while (p)
                {
                    int w = p->adjvex;
                    if (!visited[w])
                    {
                        visited[w] = true;
                        printf("%d ", w);
                        q.push(w);
                    }
                    p = p->nextarc;
                }
            }
        }
    }
    printf("\n");
}
int main()
{
    ALGraph G;
    int choice;
    while (1)
    {
        printf("1. Create Graph\n");
        printf("2. Depth-First Traversal\n");
        printf("3. Breadth-First Traversal\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            CreateGraph(G);
            break;
        case 2:
            if (G.vexnum > 0)
            {
                DFSGraph(G);
            }
            else
            {
                printf("Graph is not created yet.\n");
            }
            break;
        case 3:
            if (G.vexnum > 0)
            {
                BFSGraph(G);
            }
            else
            {
                printf("Graph is not created yet.\n");
            }
            break;
        case 0:
            return 0;
        default:
            printf("Wrong choice. Try again.\n");
        }
    }
    return 0;
}
