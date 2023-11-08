#include <stdio.h>
#include <queue>
struct BstNode 
{
    int data;
    BstNode* left;
    BstNode* right;
};
void LevelOrderTraversal(BstNode* root) 
{
    if (root == NULL)
    {
        return;
    }
    std::queue<BstNode*> q;
    q.push(root);
    while (!q.empty()) 
    {
        BstNode* current = q.front();
        printf("%d ",current->data);
        q.pop();
        if (current->left != NULL) 
        {
            q.push(current->left);
        }
        if (current->right != NULL) 
        {
            q.push(current->right);
        }
    }
}
int main() 
{
    BstNode* root = new BstNode{1, NULL, NULL};
    root->left = new BstNode{2, NULL, NULL};
    root->right = new BstNode{3, NULL, NULL};
    root->left->left = new BstNode{4, NULL, NULL};
    root->left->right = new BstNode{5, NULL, NULL};
    root->left->left = new BstNode{6, NULL, NULL};
    root->left->right = new BstNode{7, NULL, NULL};
    root->right->left = new BstNode{8, NULL, NULL};
    root->right->right = new BstNode{9, NULL, NULL};
    printf("the result is:\n");
    LevelOrderTraversal(root);
    return 0;
}
