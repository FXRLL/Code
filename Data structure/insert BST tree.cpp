#include <stdio.h>
#include <stdlib.h>
struct BstNode
{
    int data;
    struct BstNode* left;
    struct BstNode* right;
};
void InOrderTree(BstNode* node)
{
    if (node != NULL)
    {
        InOrderTree(node->left);
        printf("%d ", node->data);
        InOrderTree(node->right);
    }
}
BstNode* CreateBstNode(int data)
{
    struct BstNode* newNode = (struct BstNode*)malloc(sizeof(struct BstNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
BstNode* Insert(struct BstNode* root, int data)
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
BstNode* CreateTree(struct BstNode* root)
{
    printf("enter the number to create the tree(or -1 to end):\n");
    int value;
    while (1)
    {
        scanf("%d", &value);
        if (value == -1)
        {
            break;
        }
        root = Insert(root, value);
        printf("InOrderTree Traversal:\n");
        InOrderTree(root);
        printf("\n");
    }
    return root;
}
int main()
{
    struct BstNode* root = NULL;
    root = CreateTree(root);
    printf("the tree has been created\n");
}
