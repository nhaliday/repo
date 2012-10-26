#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define P 0.6;
#define MAXN 1000
#define SENT -1

int ok() {
    double d = rand() / (double) RAND_MAX;
    return d < P;
}

void mkgrid(int N, int M, int grid[MAXN][MAXN]) {
    int i, j;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < M; ++j) {
            grid[i][j] = ok() ? SENT : 0;
        }
    }
}

void printgrid(int N, int M, int grid[MAXN][MAXN]) {
    int i, j;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < M; ++j) {
            if (j != 0) {
                printf(" ");
            }
            printf("%5d", grid[i][j]);
        }
        printf("\n");
    }
}

void dfs(int N, int M, int grid[MAXN][MAXN], int r, int c, int v) {
    if (r < 0 || r >= N) return;
    if (c < 0 || c >= M) return;
    if (grid[r][c] != SENT) return;

    grid[r][c] = v;
    dfs(N, M, grid, r - 1, c, v);
    dfs(N, M, grid, r + 1, c, v);
    dfs(N, M, grid, r, c - 1, v);
    dfs(N, M, grid, r, c + 1, v);
}

void flood(int N, int M, int grid[MAXN][MAXN]) {
    int ncomp = 0;
    int i, j;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < M; ++j) {
            if (grid[i][j] == SENT) {
                dfs(N, M, grid, i, j, ++ncomp);
            }
        }
    }
}

int spans(int N, int M, int grid[MAXN][MAXN]) {
    int j1, j2;
    for (j1 = 0; j1 < M; ++j1) {
        for (j2 = 0; j2 < M; ++j2) {
            if (grid[0][j1] > 0 && grid[0][j1] == grid[N - 1][j2]) {
                return grid[0][j1];
            }
        }
    }
    return 0;
}

int grid[MAXN][MAXN];
int main(int argc, char **argv) {
    srand(time(NULL));

    int N, M;
    sscanf(argv[1], "%d", &N);
    sscanf(argv[2], "%d", &M);

    mkgrid(N, M, grid);
    printgrid(N, M, grid);
    flood(N, M, grid);
    printf("\n");
    printgrid(N, M, grid);
    int sp = spans(N, M, grid);
    if (sp == 0) {
        printf("Does not span.\n");
    } else {
        printf("Spans through component %d.\n", sp);
    }
}
