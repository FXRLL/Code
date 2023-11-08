#include <stdio.h>
#include <stdlib.h>
struct Stack
{
	int data;
	Stack* link;
};
void push(Stack* &top, int number)
{
	struct Stack* temp = (Stack*)malloc(sizeof(struct Stack));
	temp->data = number;
	temp->link = top;
	top = temp;
}
int pop(Stack* &top)
{
	int n = top->data;
	struct Stack* temp = top;
	top = top->link;
	free(temp);
	return n;
}
struct Node
{
    int data;
    Node* left;
    Node* right;
};
CreateTree()
{

}
PreOrderTree()
{

}
InOrderTree()
{

}
LaOrderTree()
{

}
