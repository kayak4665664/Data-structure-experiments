#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int M, N, i, j, ways, location_mark[2], direction_mark,
    path_tag = 0, directions_tag = 0, amount = 0, move[5], location[2] = {1, 1};
int maze[MAX_SIZE][MAX_SIZE], paths[MAX_SIZE * MAX_SIZE][MAX_SIZE * MAX_SIZE];
int Path[MAX_SIZE * MAX_SIZE][2], Directions[MAX_SIZE * MAX_SIZE][3];

void Initial_Maze();
void Explore_Maze();
int Ways_to_Go(int x, int y);
void Go(int direction);
void Push_Path();
void Push_Directions(int direction);
void Pop_Path();
void Pop_Directions();
void Store_Paths();
void Print_Path();

int main() {
    Initial_Maze();
    Explore_Maze();
    Print_Path();
    return 0;
}

void Initial_Maze() {
    printf("������������������\n");
    scanf("%d%d", &M, &N);
    printf("\n�������Թ���\n");
    for (i = 0; i < N + 2; i++) {
        maze[0][i] = 1;
        maze[M + 1][i] = 1;
    }
    for (i = 1; i < M + 1; i++) {
        maze[i][0] = 1;
        maze[i][N + 1] = 1;
    }
    for (i = 1; i <= M; i++) {
        for (j = 1; j <= N; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
}

void Explore_Maze() {
    memset(Path, 0, sizeof(Path));
    memset(Directions, 0, sizeof(Directions));
    memset(move, 0, sizeof(move));
    while (!(!Ways_to_Go(location[0], location[1]) && !directions_tag &&
             (location[0] != M && location[1] != N))) {
        Push_Path();
        if (location[0] == M && location[1] == N) {
            Store_Paths();
            if (directions_tag) {
                Pop_Directions();
                while (!(Path[path_tag - 1][0] == location_mark[0] &&
                         Path[path_tag - 1][1] == location_mark[1])) {
                    Pop_Path();
                }
            } else {
                break;
            }
        } else {
            if (ways == 0) {
                Pop_Directions();
                while (!(Path[path_tag - 1][0] == location_mark[0] &&
                         Path[path_tag - 1][1] == location_mark[1])) {
                    Pop_Path();
                }
            } else {
                direction_mark = move[4];
                if (ways > 1) {
                    for (i = move[4] + 1; i < 4; i++) {
                        if (move[i]) {
                            Push_Directions(i);
                        }
                    }
                }
            }
        }
        Go(direction_mark);
        memset(move, 0, sizeof(move));
    }
}

int Ways_to_Go(int x, int y) {
    ways = 0;
    if (!maze[x - 1][y]) {
        ++ways;
        move[UP] = 1;
    }
    if (!maze[x + 1][y]) {
        ++ways;
        move[DOWN] = 1;
    }
    if (!maze[x][y - 1]) {
        ++ways;
        move[LEFT] = 1;
    }
    if (!maze[x][y + 1]) {
        ++ways;
        move[RIGHT] = 1;
    }
    if (ways) {
        for (i = 0; i < 4; i++) {
            if (move[i]) {
                move[4] = i;
                break;
            }
        }
    }
    return ways;
}

void Go(int direction) {
    maze[location[0]][location[1]] = 1;
    if (direction == UP) {
        location[0] -= 1;
    }
    if (direction == DOWN) {
        location[0] += 1;
    }
    if (direction == LEFT) {
        location[1] -= 1;
    }
    if (direction == RIGHT) {
        location[1] += 1;
    }
}

void Push_Path() {
    Path[path_tag][0] = location[0];
    Path[path_tag][1] = location[1];
    ++path_tag;
}

void Push_Directions(int direction) {
    Directions[directions_tag][0] = location[0];
    Directions[directions_tag][1] = location[1];
    Directions[directions_tag][2] = direction;
    ++directions_tag;
}

void Pop_Path() {
    --path_tag;
    maze[Path[path_tag][0]][Path[path_tag][1]] = 0;
    location[0] = Path[path_tag - 1][0];
    location[1] = Path[path_tag - 1][1];
}

void Pop_Directions() {
    --directions_tag;
    location_mark[0] = Directions[directions_tag][0];
    location_mark[1] = Directions[directions_tag][1];
    direction_mark = Directions[directions_tag][2];
}

void Store_Paths() {
    paths[amount][0] = path_tag;
    for (i = 1, j = 0; j < path_tag; i += 2, j++) {
        paths[amount][i] = Path[j][0];
        paths[amount][i + 1] = Path[j][1];
    }
    ++amount;
}

void Print_Path() {
    printf("\n·��������%d\n\n", amount);
    if (amount != 0) {
        int min = paths[0][0];
        int mark = 0;
        for (i = 0; i < amount; i++) {
            if (paths[i][0] < min) {
                min = paths[i][0];
                mark = i;
            }
        }
        printf("���·�����£�\n\n");
        printf("���·�����ȣ�%d  ", paths[mark][0] - 1);
        for (i = 1; i <= paths[mark][0] * 2 - 1; i += 2) {
            if (i != paths[mark][0] * 2 - 1) {
                printf("(%d,%d)->", paths[mark][i], paths[mark][i + 1]);
            } else {
                printf("(%d,%d)\n\n", paths[mark][i], paths[mark][i + 1]);
            }
        }
        if (amount > 1) {
            printf("\n\n����·�����£�\n\n");
            for (i = 0; i < amount; i++) {
                if (i != mark) {
                    printf("·�����ȣ�%d  ", paths[i][0] - 1);
                    for (j = 1; j <= paths[i][0] * 2 - 1; j += 2) {
                        if (j < paths[i][0] * 2 - 1) {
                            printf("(%d,%d)->", paths[i][j], paths[i][j + 1]);
                        } else {
                            printf("(%d,%d)\n\n", paths[i][j], paths[i][j + 1]);
                        }
                    }
                }
            }
        }
    }
}