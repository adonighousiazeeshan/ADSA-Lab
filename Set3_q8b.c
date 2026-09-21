#include <stdio.h>

#define MAX 100

int queue1[MAX], queue2[MAX];
int front1 = 0, rear1 = -1;
int front2 = 0, rear2 = -1;

// Push
void push(int value)
{
    if (rear1 == MAX - 1)
    {
        printf("Stack is Full\n");
        return;
    }

    queue1[++rear1] = value;

    printf("%d pushed\n", value);
}

// Pop
void pop()
{
    if (front1 > rear1)
    {
        printf("Stack is Empty\n");
        return;
    }

    // Move all elements except the last one
    while (front1 < rear1)
    {
        queue2[++rear2] = queue1[front1++];
    }

    // Last element is the top of stack
    printf("%d popped\n", queue1[front1]);

    front1++;
    
    // Move elements back to queue1
    front1 = 0;
    rear1 = -1;

    while (front2 <= rear2)
    {
        queue1[++rear1] = queue2[front2++];
    }

    // Reset queue2
    front2 = 0;
    rear2 = -1;
}

// Display
void display()
{
    if (front1 > rear1)
    {
        printf("Stack is Empty\n");
        return;
    }

    printf("Stack: ");

    for (int i = rear1; i >= front1; i--)
    {
        printf("%d ", queue1[i]);
    }

    printf("\n");
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                pop();
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