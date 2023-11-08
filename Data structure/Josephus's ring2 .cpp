#include <stdio.h>
#include <stdlib.h>
struct Node 
{
    int data;
    Node* next;
};
// 创建一个新节点
Node* createNode(int data) 
{
    struct Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
int main()
{
    int n, m;
    printf("enter the number of people n:");
    scanf("%d", &n);
    printf("enter the number remove m:");
    scanf("%d", &m);
    struct Node* head = createNode(1);
    struct Node* current = head;
    // 创建循环链表
    for (int i = 2; i <= n; i++)
    {
        current->next = createNode(i);
        current = current->next;
    }
    current->next = head;
    // 模拟约瑟夫环过程
    struct Node* prev = current;
    current = head;
        while (current->next != current)
        {
            if (m != 1)
            {
                for (int i = 1; i < m; i++)
                {
                    prev = current;
                    current = current->next;
                }
            }
            prev->next = current->next;
            printf("remove:%d\n", current->data);
            free(current);
            current = prev->next;
        }
    printf("the last one:%d\n", current->data);
    return 0;
}