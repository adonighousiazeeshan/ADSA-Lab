#include <stdio.h>

int n;
int board[20];

int safe(int row, int col) {

    for (int i = 0; i < row; i++) {

        if (board[i] == col ||
            board[i] - i == col - row ||
            board[i] + i == col + row)
            return 0;
    }

    return 1;
}

void solve(int row) {

    if (row == n) {

        for (int i = 0; i < n; i++)
            printf("%d ", board[i] + 1);

        printf("\n");
        return;
    }

    for (int col = 0; col < n; col++) {

        if (safe(row, col)) {

            board[row] = col;
            solve(row + 1);
        }
    }
}

int main() {

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Solutions:\n");
    solve(0);

    return 0;
}