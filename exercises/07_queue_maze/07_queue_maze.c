#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

typedef struct {
    int row;
    int col;
} Point;

int main(void)
{
    int visited[MAX_ROW][MAX_COL] = {0};
    int parent_row[MAX_ROW][MAX_COL];
    int parent_col[MAX_ROW][MAX_COL];
    Point queue[MAX_ROW * MAX_COL];
    int head = 0;
    int tail = 0;

    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            parent_row[i][j] = -1;
            parent_col[i][j] = -1;
        }
    }

    static const int dr[] = {1, 0, -1, 0};
    static const int dc[] = {0, 1, 0, -1};

    queue[tail++] = (Point){0, 0};
    visited[0][0] = 1;

    while (head < tail) {
        Point cur = queue[head++];
        if (cur.row == MAX_ROW - 1 && cur.col == MAX_COL - 1) {
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nr = cur.row + dr[i];
            int nc = cur.col + dc[i];
            if (nr < 0 || nr >= MAX_ROW || nc < 0 || nc >= MAX_COL) {
                continue;
            }
            if (maze[nr][nc] == 1 || visited[nr][nc]) {
                continue;
            }

            visited[nr][nc] = 1;
            parent_row[nr][nc] = cur.row;
            parent_col[nr][nc] = cur.col;
            queue[tail++] = (Point){nr, nc};
        }
    }

    if (!visited[MAX_ROW - 1][MAX_COL - 1]) {
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
