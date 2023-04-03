#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define MAX 50



int main() {
    freopen("C:\\Users\\Dell\\Downloads\\hw4_input.txt", "r", stdin);
    FILE* outFile = fopen("output.txt ", "w");
    int all;
    scanf("%d\n", &all);

    for (int i = 0; i < all; i++) {
        int n, a[MAX][MAX];
        scanf("%d\n", &n);
        for (int c = 0; c < n; c++) {
            for (int r = 0; r < n; r++) {
                scanf("%d ", &a[r][c]);
            }
        }
        
        int state = 0;

        for (int c = 0; c < n; c++) {
            for (int r = 0; r < n; r++) {
                if (a[r][c] == 1 && a[c][r] == 1)
                    state = 1;
            }
        }
        fprintf(outFile ,"%d\n", state);
    }

    fclose(outFile);
    return 0;
}