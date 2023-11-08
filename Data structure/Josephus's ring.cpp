#include <stdio.h>
#include<stdlib.h>
// 定义一个顺序结构表示的循环队列
#define MAX_SIZE 100
int queue[MAX_SIZE];
int front = -1;
int rear = -1;
void enqueue(int value) // 向队列中插入元素
{
    if ((rear + 1) % MAX_SIZE == front) 
    {
        printf("the queue has been full\n");
    }
    else 
    {
        rear = (rear + 1) % MAX_SIZE;
        queue[rear] = value;
    }
}
int dequeue() // 从队列中移除元素
{
    if (front == rear) 
    {
        printf("the queue is empty\n");
        return -1;
    }
    else 
    {
        front = (front + 1) % MAX_SIZE;
        return queue[front];
    }
}
int main() 
{
    int n, m;
    printf("enter the number of people n:");
    scanf("%d", &n);
    printf("enter the number remove m:");
    scanf("%d", &m);
    for (int i = 1; i <= n; i++) 
    {
        enqueue(i);
    }
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < m - 1; j++) 
        {
            enqueue(dequeue());
        }
        printf("remove:%d\n", dequeue());
    }
    printf("the last one:%d\n", dequeue());
    return 0;
}