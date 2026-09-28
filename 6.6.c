#include <stdio.h>
#include <stdlib.h>

#define N 4

typedef struct {
    int board[N][N];
    int x, y;
    int cost, level;
} Node;

int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

int manhattan(int board[N][N]) {

    int d = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            if (board[i][j] != 0) {

                int v = board[i][j] - 1;
                int x = v / N;
                int y = v % N;

                d += abs(i - x) + abs(j - y);
            }
        }
    }

    return d;
}

void printBoard(int board[N][N]) {

    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++)
            printf("%2d ", board[i][j]);

        printf("\n");
    }

    printf("\n");
}

void solve(int board[N][N]) {

    printf("Initial board:\n");
    printBoard(board);

    /*
       For a lab implementation, the Manhattan
       distance gives the branch-and-bound heuristic.
    */

    printf("Manhattan cost = %d\n", manhattan(board));
}

int main() {

    int board[N][N];

    printf("Enter 15-puzzle (use 0 for blank):\n");

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &board[i][j]);

    solve(board);

    return 0;
}