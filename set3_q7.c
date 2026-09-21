#include <stdio.h>

#define MAX 100

int stack1[MAX], stack2[MAX];
int top1 = -1, top2 = -1;

// Push into stack1
void push1(int value)
{
    if (top1 == MAX - 1)
    {
        printf("Queue is Full\n");
        return;
    }

    stack1[++top1] = value;
}

// Push into stack2
void push2(int value)
{
    stack2[++top2] = value;
}

// Pop from stack2
int pop2()
{
    return stack2[top2--];
}

// Enqueue
void enqueue(int value)
{
    push1(value);
    printf("%d inserted\n", value);
}

// Dequeue
void dequeue()
{
    if (top1 == -1 && top2 == -1)
    {
        printf("Queue is Empty\n");
        return;
    }

    // Move elements from stack1 to stack2
    if (top2 == -1)
    {
        while (top1 != -1)
        {
            push2(stack1[top1--]);
        }
    }

    printf("%d deleted\n", pop2());
}

// Display queue
void display()
{
    if (top1 == -1 && top2 == -1)
    {
        printf("Queue is Empty\n");
        return;
    }

    printf("Queue: ");

    // Elements in stack2
    for (int i = top2; i >= 0; i--)
    {
        printf("%d ", stack2[i]);
    }

    // Elements in stack1
    for (int i = 0; i <= top1; i++)
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