#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int value)
{
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void preorder(struct Node *root)
{
    if (root == NULL)
    {
        printf("Tree is Empty\n");
        return;
    }

    struct Node *stack[MAX];
    int top = -1;

    stack[++top] = root;

    printf("Preorder Traversal: ");

    while (top != -1)
    {
        struct Node *current = stack[top--];

        printf("%d ", current->data);

        // Push right first
        if (current->right != NULL)
        {
            stack[++top] = current->right;
        }

        // Push left second
        if (current->left != NULL)
        {
            stack[++top] = current->left;
        }
    }

    printf("\n");
}

int main()
{
    /*
              1
             / \
            2   3
           / \
          4   5
    */

    struct Node *root = createNode(1);

    root->left = createNode(2);
    root->right = createNode(3);

    root->left->left = createNode(4);
    root->left->right = createNode(5);

    preorder(root);

    return 0;
}