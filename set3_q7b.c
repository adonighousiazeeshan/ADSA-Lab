#include <stdio.h>

#define MAX 100

int stack1[MAX], stack2[MAX];
int top1 = -1, top2 = -1;

// Enqueue
void enqueue(int value)
{
    // Move all elements from stack1 to stack2
    while (top1 != -1)
    {
        stack2[++top2] = stack1[top1--];
    }

    // Insert new element into stack1
    stack1[++top1] = value;

    // Move all elements back to stack1
    while (top2 != -1)
    {
        stack1[++top1] = stack2[top2--];
    }

    printf("%d inserted\n", value);
}

// Dequeue
void dequeue()
{
    if (top1 == -1)
    {
        printf("Queue is Empty\n");
        return;
    }

    printf("%d deleted\n", stack1[top1--]);
}

// Display
void display()
{
    if (top1 == -1)
    {
        printf("Queue is Empty\n");
        return;
    }

    printf("Queue: ");

    for (int i = top1; i >= 0; i--)
    {
        printf("%d ", stack1[i]);
    }

    printf("\n");
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                enqueue(value);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}