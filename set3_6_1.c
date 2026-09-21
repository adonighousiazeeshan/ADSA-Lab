#include <stdio.h>

#define MAX 5

int queue[MAX];
int front = -1;
int rear = -1;

/* Insert an element into the circular queue */
void enqueue(int value)
{
    if ((rear + 1) % MAX == front)
    {
        printf("Queue Overflow\n");
        return;
    }

    if (front == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = (rear + 1) % MAX;
    }

    queue[rear] = value;
    printf("%d inserted into queue\n", value);
}

/* Delete an element from the circular queue */
void dequeue()
{   
    int value;

    if (front == -1)
    {
        printf("Queue Underflow\n");
        return;
    }

    value = queue[front];

    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % MAX;
    }

    printf("%d deleted from queue\n", value);
}

/* Display the circular queue */
void display()
{
    int i;

    if (front == -1)
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Circular Queue: ");

    i = front;

    while (1)
    {
        printf("%d ", queue[i]);

        if (i == rear)
            break;

        i = (i + 1) % MAX;
    }

    printf("\n");
}

/* Display the front element */
void peek()
{
    if (front == -1)
    {
        printf("Queue is empty\n");
    }
    else
    {
        printf("Front element = %d\n", queue[front]);
    }
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n--- Circular Queue Using Array ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Peek\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
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
                peek();
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}