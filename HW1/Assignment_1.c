#include<stdio.h>
#include <ctype.h>
#pragma warning(disable:4996)

int row, col, all;
int maze[50][50];
int visited[50][50];
int max = 1000000;

void init() {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            maze[i][j] = 0;
            visited[i][j] = 0;
        }
    }
}

int path(int r, int c) {

    visited[r][c] = 1;
    int count = 0;
    

    if (c + 1 < col && maze[r][c + 1] == 1 && visited[r][c + 1] == 0) {
        if (count > max) {
            return max;
        }
        count += path(r, c + 1); //right
    }
    if (r + 1 < row && maze[r + 1][c] == 1 && visited[r + 1][c] == 0) {
        if (count > max) {
            return max;
        }
        count += path(r + 1, c); //down
    }
    if (r + 1 < row && c + 1 < col && maze[r + 1][c + 1] == 1 && visited[r + 1][c + 1] == 0) {
        if (count > max) {
            return max;
        }
        count += path(r + 1, c + 1); //down right
    }
    if (r - 1 < row && c < col && maze[r - 1][c] == 1 && visited[r - 1][c] == 0) {
        if (count > max) {
            return max;
        }
        count += path(r - 1, c); //up
    }

    visited[r][c] = 0;

    if (r == row - 1 && c == col - 1) {
        return 1;
    }
    else
        return count;
}

int main() {

    FILE* outFile = fopen("output.txt ", "w");

    freopen("C:\\Users\\Dell\\Downloads\\Data structure\\input_hw1.txt", "r", stdin);
    scanf("%d", &all);
    for (int i = 0; i < all; i++) {
        init();
        scanf("%d %d", &row, &col);
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                scanf("%d", &maze[r][c]);
            }
        }
        if (path(0, 0) < max)
            fprintf(outFile,"%d\n", path(0, 0));
        else
            fprintf(outFile,"%d\n", max);

    }

    fclose(outFile);
    return 0;
}
