#include <stdio.h>
#include <string.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

static int visited[MAX_ROW][MAX_COL];
static int parent_row[MAX_ROW][MAX_COL];
static int parent_col[MAX_ROW][MAX_COL];

// 按“上、右、下、左”的顺序搜索，能得到测试期望的 DFS 路径
static const int dr[] = {-1, 0, 1, 0};
static const int dc[] = {0, 1, 0, -1};

static int dfs(int row, int col) {
	if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL) {
		return 0;
	}
	if (maze[row][col] == 1 || visited[row][col]) {
		return 0;
	}

	visited[row][col] = 1;
	if (row == MAX_ROW - 1 && col == MAX_COL - 1) {
		return 1;
	}

	for (int i = 0; i < 4; i++) {
		int nr = row + dr[i];
		int nc = col + dc[i];
		if (dfs(nr, nc)) {
			parent_row[nr][nc] = row;
			parent_col[nr][nc] = col;
			return 1;
		}
	}

	return 0;
}

int main(void)
{
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            parent_row[i][j] = -1;
            parent_col[i][j] = -1;
        }
    }

    if (!dfs(0, 0)) {
        printf("No path!\n");
        return 0;
    }

    int path_row[MAX_ROW * MAX_COL];
    int path_col[MAX_ROW * MAX_COL];
    int count = 0;
    int row = MAX_ROW - 1;
    int col = MAX_COL - 1;

    while (row != -1 && col != -1) {
        path_row[count] = row;
        path_col[count] = col;
        count++;
        if (row == 0 && col == 0) {
            break;
        }
        int pr = parent_row[row][col];
        int pc = parent_col[row][col];
        row = pr;
        col = pc;
    }

    for (int i = 0; i < count; i++) {
        printf("(%d, %d)\n", path_row[i], path_col[i]);
    }

	return 0;
}
