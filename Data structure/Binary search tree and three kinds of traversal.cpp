#include <stdio.h>
#include <stdlib.h>
struct BstNode
{
    int data;
    struct BstNode* left;
    struct BstNode* right;
};
struct Stack
{
	BstNode* data;
	Stack* link;
};
void push(Stack* &top, BstNode* data)
{
	struct Stack* temp = (Stack*)malloc(sizeof(struct Stack));
	temp->data = data;
	temp->link = top;
	top = temp;
}
BstNode* pop(Stack* &top)
{
	BstNode* n = top->data;
	struct Stack* temp = top;
	top = top->link;
	free(temp);
	return n;
}
int isEmpty(struct Stack* stack)
{
    return (stack == NULL);
}
struct BstNode* CreateBstNode(int data)
{
    struct BstNode* newNode = (struct BstNode*)malloc(sizeof(struct BstNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
struct BstNode* Insert(struct BstNode* root, int data)
{
    if (root == NULL)
    {
        root = CreateBstNode(data);
    }
    else if (data <= root->data)
    {
        root->left = Insert(root->left, data);
    }
    else
    {
        root->right = Insert(root->right, data);
    }
    return root;
}
struct BstNode* CreateTree(struct BstNode* root)
{
    printf("enter the number (or -1 to end): ");
    int value;
    while (1)
    {
        scanf("%d", &value);
        if (value == -1)
        {
            break;
        }
        root = Insert(root, value);
    }
    return root;
}
void PreOrderTree(BstNode* node)
{
    if (node != NULL)
    {
        printf("%d ", node->data);
        PreOrderTree(node->left);
        PreOrderTree(node->right);
    }
}
void InOrderTree(BstNode* root) 
{
    Stack* stack = NULL;
    BstNode* current = root;
    while (current != NULL || !isEmpty(stack)) 
	{
        while (current != NULL) 
		{
            push(stack, current);
            current = current->left;
        }
        BstNode* temp = pop(stack);
        printf("%d ", temp->data); 
        current = temp->right;
    }
}
void PostOrderTree(BstNode* node)
{
    if (node != NULL)
    {
        PostOrderTree(node->left);
        PostOrderTree(node->right);
        printf("%d ", node->data);
    }
}
int main()
{
    struct BstNode* root = NULL;
    root = CreateTree(root);
    printf("Preorder Traversal: ");
    PreOrderTree(root);
    printf("\n");
	printf("InOrderTree Traversal: ");
    InOrderTree(root);
    printf("\n");
    printf("Postorder Traversal: ");
    PostOrderTree(root);
    printf("\n");
    return 0;
}
