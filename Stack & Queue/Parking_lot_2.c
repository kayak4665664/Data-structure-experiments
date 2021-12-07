#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUCK 3
#define BUS 2
#define CAR 1
#define TOP0 0
#define TOP1 1
#define PARKING_LOT 0
#define ROAD 1
#define LEAVE 0
#define NOT_LEAVE 1
#define NO_TIME 0
#define MOVE 0
#define MOVE_BACK 1

typedef struct Sqstack {
    int num;
    int time;
    int vehicle;
    struct Sqstack* base[2];
    struct Sqstack* top[2];
    struct Sqstack* mark;
} Sqstack;

typedef struct QueueNode {
    int num;
    int time;
    int vehicle;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
    QueueNode* leave;
} Queue;

int size, statu, num, time, vehicle, de_num, de_time, de_vehicle;
int parking_lot_data[10][3], road_data[10][3], i = 0, j, k = 0, m = 0, n = 0;
float parking_lot_fare, road_fare;
Sqstack parking_lot;
Queue road;

void InitSqstack(Sqstack* S, int size);
void Push(Sqstack* S, int num, int time, int vehicle, int side);
void Pop(Sqstack* S, int time);
int SearchSqstack(Sqstack* S, int num);
void Move(Sqstack* S, int move_or_move_back);

void InitQueue(Queue* Q);
void EnQueue(Queue* Q, int num, int time, int vehicle);
void DeQueue(Queue* Q, int time, int leave_or_not_leave);
int SearchQueue(Queue* Q, int num);

void StoreData(int parking_lot_or_road);
void PrintData(int parking_lot_or_road);
void PrintSqstack(Sqstack* S);
void PrintQueue(Queue* Q);

int main() {
    scanf("%d%f%f", &size, &parking_lot_fare, &road_fare);
    InitQueue(&road);
    InitSqstack(&parking_lot, size + 1);

    do {
        scanf("%d%d%d%d", &statu, &num, &time, &vehicle);
        if (statu == 0 && num != 0)
            if (parking_lot.top[0] > parking_lot.top[1])
                EnQueue(&road, num, time, vehicle);
            else
                Push(&parking_lot, num, time, vehicle, TOP0);
        else {
            if (road.front->next != NULL)
                if (SearchQueue(&road, num)) {
                    while (road.front->next != road.leave) {
                        DeQueue(&road, NO_TIME, NOT_LEAVE);
                        EnQueue(&road, de_num, de_time, de_vehicle);
                    }
                    DeQueue(&road, time, LEAVE);
                    StoreData(ROAD);
                }
            if (SearchSqstack(&parking_lot, num)) {
                Move(&parking_lot, MOVE);
                Pop(&parking_lot, time);
                StoreData(PARKING_LOT);
                if (parking_lot.top[1] < parking_lot.base[1])
                    Move(&parking_lot, MOVE_BACK);
                if (road.front->next != NULL) {
                    Push(&parking_lot, road.front->next->num,
                         (int)(time - (time - road.front->next->time) *
                                          (road_fare / parking_lot_fare)),
                         road.front->next->vehicle, TOP0);
                    DeQueue(&road, NO_TIME, LEAVE);
                }
            }
        }
    } while (time != 0);

    PrintData(PARKING_LOT);
    PrintData(ROAD);
    PrintSqstack(&parking_lot);
    PrintQueue(&road);

    return 0;
}

void InitSqstack(Sqstack* S, int size) {
    S->base[0] = (Sqstack*)malloc(size * sizeof(Sqstack));
    if (!S->base[0]) exit(OVERFLOW);
    S->top[0] = S->base[0];
    S->top[1] = S->base[1] = S->base[0] + (size - 2);
}

void Push(Sqstack* S, int num, int time, int vehicle, int side) {
    if (side == TOP0) {
        S->top[0]->num = num;
        S->top[0]->time = time;
        S->top[0]->vehicle = vehicle;
        S->top[0]++;
    } else {
        S->top[1]->num = num;
        S->top[1]->time = time;
        S->top[1]->vehicle = vehicle;
        S->top[1]--;
    }
}

void Pop(Sqstack* S, int time) {
    S->top[0]--;
    de_num = S->top[0]->num;
    de_time = time - (S->top[0]->time);
    de_vehicle = S->top[0]->vehicle;
}

int SearchSqstack(Sqstack* S, int num) {
    for (S->mark = S->base[0]; S->mark < S->top[0]; S->mark++)
        if (S->mark->num == num) return 1;
    return 0;
}

void Move(Sqstack* S, int move_or_move_back) {
    if (move_or_move_back == MOVE) {
        for (S->top[0]--; S->top[0] > S->mark; S->top[0]--)
            Push(S, S->top[0]->num, S->top[0]->time, S->top[0]->vehicle, TOP1);
        S->top[0]++;
    } else {
        for (S->top[1]++; S->top[1] <= S->base[1]; S->top[1]++)
            Push(S, S->top[1]->num, S->top[1]->time, S->top[1]->vehicle, TOP0);
        S->top[1]--;
    }
}

void InitQueue(Queue* Q) {
    Q->front = (QueueNode*)malloc(sizeof(QueueNode));
    Q->rear = Q->front;
    if (!Q->front) exit(OVERFLOW);
    Q->front->next = NULL;
}

void EnQueue(Queue* Q, int num, int time, int vehicle) {
    QueueNode* enter_node;
    enter_node = (QueueNode*)malloc(sizeof(QueueNode));
    if (!enter_node) exit(OVERFLOW);
    enter_node->num = num;
    enter_node->time = time;
    enter_node->vehicle = vehicle;
    enter_node->next = NULL;
    Q->rear->next = enter_node;
    Q->rear = enter_node;
}

void DeQueue(Queue* Q, int time, int leave_or_not_leave) {
    QueueNode* delete_node;
    delete_node = Q->front->next;
    de_num = delete_node->num;
    if (leave_or_not_leave == LEAVE)
        de_time = time - delete_node->time;
    else
        de_time = delete_node->time;
    de_vehicle = delete_node->vehicle;
    Q->front->next = delete_node->next;
    free(delete_node);
}

int SearchQueue(Queue* Q, int num) {
    for (Q->leave = Q->front; Q->leave->next != NULL; Q->leave = Q->leave->next)
        if (Q->leave->num == num) return 1;
    if (Q->leave->num == num) return 1;
    return 0;
}

void StoreData(int parking_lot_or_road) {
    if (parking_lot_or_road == PARKING_LOT) {
        parking_lot_data[i][0] = de_num;
        parking_lot_data[i][1] = de_time;
        parking_lot_data[i++][2] = de_vehicle;
        k++;
    } else {
        road_data[m][0] = de_num;
        road_data[m][1] = de_time;
        road_data[m++][2] = de_vehicle;
        n++;
    }
}

void PrintData(int parking_lot_or_road) {
    if (parking_lot_or_road == PARKING_LOT) {
        if (k)
            for (j = 0; j < i; j++) {
                if (parking_lot_data[j][2] == CAR)
                    printf("%d %.2f\n", parking_lot_data[j][0],
                           parking_lot_fare * parking_lot_data[j][1]);
                if (parking_lot_data[j][2] == BUS)
                    printf("%d %.2f\n", parking_lot_data[j][0],
                           parking_lot_fare * parking_lot_data[j][1] * 1.5);
                if (parking_lot_data[j][2] == TRUCK)
                    printf("%d %.2f\n", parking_lot_data[j][0],
                           parking_lot_fare * parking_lot_data[j][1] * 3);
            }
    } else {
        if (n)
            for (j = 0; j < m; j++) {
                if (road_data[j][2] == CAR)
                    printf("%d %.2f\n", road_data[j][0],
                           road_fare * road_data[j][1]);
                if (road_data[j][2] == BUS)
                    printf("%d %.2f\n", road_data[j][0],
                           road_fare * road_data[j][1] * 1.5);
                if (road_data[j][2] == TRUCK)
                    printf("%d %.2f\n", road_data[j][0],
                           road_fare * road_data[j][1] * 3);
            }
    }
}

void PrintSqstack(Sqstack* S) {
    if (S->top[0] != S->base[0]) {
        for (S->mark = S->base[0]; S->mark < S->top[0]; S->mark++)
            printf("%d ", S->mark->num);
        printf("\n");
    }
}

void PrintQueue(Queue* Q) {
    if (road.front->next != NULL) {
        for (Q->leave = Q->front->next; Q->leave->next != NULL;
             Q->leave = Q->leave->next)
            printf("%d ", Q->leave->num);
        printf("%d\n", Q->leave->num);
    }
}