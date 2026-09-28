#include <stdio.h>

int n, W;
int wt[20], val[20];
int maxValue = 0;

void knapsack(int i, int weight, int value) {

    if (i == n) {
        if (value > maxValue)
            maxValue = value;
        return;
    }

    // Include item
    if (weight + wt[i] <= W)
        knapsack(i + 1,
                 weight + wt[i],
                 value + val[i]);

    // Exclude item
    knapsack(i + 1, weight, value);
}

int main() {

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter weights:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &wt[i]);

    printf("Enter values:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &val[i]);

    printf("Enter capacity: ");
    scanf("%d", &W);

    knapsack(0, 0, 0);

    printf("Maximum value = %d\n", maxValue);

    return 0;
}