#include <stdio.h>
#include <stdlib.h>

// Represents a sub-array frame and its current processing state
typedef struct {
    int low;
    int high;
    int state; // 0: process left child, 1: process right child, 2: merge
} Frame;

// Dynamic Stack structure
typedef struct {
    Frame *data;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    if (!stack) return NULL;
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (Frame*) malloc(stack->capacity * sizeof(Frame));
    return stack;
}

void push(Stack *stack, Frame frame) {
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->data = (Frame*) realloc(stack->data, stack->capacity * sizeof(Frame));
    }
    stack->data[++(stack->top)] = frame;
}

Frame pop(Stack *stack) {
    return stack->data[(stack->top)--];
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void freeStack(Stack *stack) {
    if (stack) {
        if (stack->data) free(stack->data);
        free(stack);
    }
}

// Function to merge two sorted sub-arrays
void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *L = (int*) malloc(n1 * sizeof(int));
    int *R = (int*) malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[low + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

// Non-recursive Top-Down Merge Sort using explicit Stack
void mergeSortTopDownStack(int arr[], int n) {
    if (n <= 1) return;

    Stack *stack = createStack(n * 2);
    if (!stack) return;

    Frame startFrame = {0, n - 1, 0};
    push(stack, startFrame);

    while (!isEmpty(stack)) {
        int topIdx = stack->top;
        int low = stack->data[topIdx].low;
        int high = stack->data[topIdx].high;
        int state = stack->data[topIdx].state;

        if (low >= high) {
            pop(stack);
            continue;
        }

        int mid = low + (high - low) / 2;

        if (state == 0) {
            // State 0: Move to left half
            stack->data[topIdx].state = 1;
            Frame leftChild = {low, mid, 0};
            push(stack, leftChild);
        } 
        else if (state == 1) {
            // State 1: Move to right half
            stack->data[topIdx].state = 2;
            Frame rightChild = {mid + 1, high, 0};
            push(stack, rightChild);
        } 
        else if (state == 2) {
            // State 2: Merge sorted halves and return up the stack
            merge(arr, low, mid, high);
            pop(stack);
        }
    }

    freeStack(stack);
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10, 19, 50, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original Array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    mergeSortTopDownStack(arr, n);

    printf("\nSorted Array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}