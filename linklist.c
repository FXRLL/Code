#include <stdio.h>
#include<stdlib.h>
typedef struct Node
{
    int data;
    struct Node* next;
}Node;
void Print(Node* head)
{
    printf("List is: ");
    Node* current = head->next; // 跳过虚拟头节点
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
Node* Headinsert(Node* head, int number)
{
    struct Node* temp = (Node*)malloc(sizeof(struct Node));
    temp->data = number;
    temp->next = head->next;
    head->next = temp;
    return head;
}
void Search(int max, int min, Node* head)
{
    Node* current = head;
    while (current->next != NULL)
    {
        if (current->next->data < max && current->next->data > min)
        {
            Node* temp = current->next;
            current->next = temp->next;
            free(temp);
        }
        else
        {
            current = current->next;
        }
    }
}
int main()
{
    struct Node* head = (Node*)malloc(sizeof(struct Node));
    head->next = NULL;
    int times, number, max, min;
    printf("How many times do you want to input? ");
    scanf("%d", &times);
    for (int i = 0; i < times; i++)
    {
        printf("Please input: ");
        scanf("%d", &number);
        head = Headinsert(head, number);
        Print(head);
    }
    printf("Enter max and min values: ");
    scanf("%d %d", &max, &min);
    Search(max, min, head);
    printf("Processed list: ");
    Print(head);
    return 0;
}
//test