#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MOVE 0
#define MOVE_BACK 1

typedef struct Sqstack
{
	int num;
	int time;
	struct Sqstack* base;
	struct Sqstack* top;
	struct Sqstack* mark;
	int size;
	int maxsize;
}Sqstack;

typedef struct QueueNode
{
	int num;
	struct QueueNode* next;
}QueueNode;

typedef struct Queue
{
	QueueNode* front;
	QueueNode* rear;
	QueueNode* leave;
}Queue;

int size, statu, num, time, de_time, de_num, data[10][2], i = 0, j, k = 0;
float fare;
Sqstack parking_lot, temp_parking_lot;
Queue road;

void InitSqstack(Sqstack* S, int size);
void Push(Sqstack* S, int num, int time);
void Pop(Sqstack* S, int time);
int SearchSqstack(Sqstack* S, int num);
void Move(Sqstack* S, Sqstack* P, int move_or_move_back);

void InitQueue(Queue* Q);
void EnQueue(Queue* Q, int num);
void DeQueue(Queue* Q);
int SearchQueue(Queue* Q, int num);

void StoreData();
void PrintData();
void PrintSqstack(Sqstack* S);
void PrintQueue(Queue* Q);

int main()
{
	scanf("%d%f", &size, &fare);
	InitSqstack(&parking_lot, size + 1);
	InitSqstack(&temp_parking_lot, size);
	InitQueue(&road);
	do
	{
		scanf("%d%d%d", &statu, &num, &time);
		if (statu == 0 && num != 0)
			if (parking_lot.size < parking_lot.maxsize)
				Push(&parking_lot, num, time);
			else
				EnQueue(&road, num);
		else
		{
			if (road.front->next != NULL)
				if (SearchQueue(&road, num))
				{
					while (road.front->next != road.leave)
					{
						DeQueue(&road);
						EnQueue(&road, de_num);
					}
					DeQueue(&road);
				}
			if (SearchSqstack(&parking_lot, num))
			{
				Move(&parking_lot, &temp_parking_lot, MOVE);
				Pop(&parking_lot, time);
				StoreData();
				if (temp_parking_lot.size)
					Move(&temp_parking_lot, &parking_lot, MOVE_BACK);
				if (road.front != road.rear)
				{
					Push(&parking_lot, road.front->next->num, time);
					DeQueue(&road);
				}
			}
		}
	} while (time != 0);

	PrintData();
	PrintSqstack(&parking_lot);
	PrintQueue(&road);

	return 0;
}

void InitSqstack(Sqstack* S, int size)
{
	S->base = (Sqstack*)malloc(size * sizeof(Sqstack));
	if (!S->base)
		exit(OVERFLOW);
	S->top = S->base;
	S->size = 0;
	S->maxsize = size - 1;
}

void Push(Sqstack* S, int num, int time)
{
	S->top->num = num;
	S->top->time = time;
	S->top++;
	S->size++;
}

void Pop(Sqstack* S, int time)
{
	S->top--;
	de_num = S->top->num;
	de_time = time - (S->top->time);
	S->size--;
}

int SearchSqstack(Sqstack* S, int num)
{
	for (S->mark = S->base; S->mark < S->top; S->mark++)
		if (S->mark->num == num)
			return 1;
	return 0;
}

void Move(Sqstack* S, Sqstack* P,int move_or_move_back)
{
	if (move_or_move_back == MOVE)
	{
		for (S->top--; S->top > S->mark; S->top--)
		{
			Push(P, S->top->num, S->top->time);
			S->size--;
		}
		S->top++;
	}
	else
	{
		for (S->top--; S->top > S->base; S->top--)
		{
			Push(P, S->top->num, S->top->time);
			S->size--;
		}
		Push(P, S->top->num, S->top->time);
		S->size--;
	}
}

void InitQueue(Queue* Q)
{
	Q->front = (QueueNode*)malloc(sizeof(QueueNode));
	Q->rear = Q->front;
	if (!Q->front)
		exit(OVERFLOW);
	Q->front->next = NULL;
}

void EnQueue(Queue* Q, int num)
{
	QueueNode* enter_node;
	enter_node = (QueueNode*)malloc(sizeof(QueueNode));
	if (!enter_node)
		exit(OVERFLOW);
	enter_node->num = num;
	enter_node->next = NULL;
	Q->rear->next = enter_node;
	Q->rear = enter_node;
}

void DeQueue(Queue* Q)
{
	QueueNode* delete_node;
	delete_node = Q->front->next;
	de_num = delete_node->num;
	Q->front->next = delete_node->next;
	free(delete_node);
}

int SearchQueue(Queue* Q, int num)
{
	for (Q->leave = Q->front; Q->leave->next != NULL; Q->leave = Q->leave->next)
		if (Q->leave->num == num)
			return 1;
	if (Q->leave->num == num)
		return 1;
	return 0;
}

void StoreData()
{
	data[i][0] = de_num;
	data[i++][1] = de_time;
	k++;
}

void PrintData()
{
	if (k)
		for (j = 0; j < i; j++)
			printf("%d %.2f\n", data[j][0], fare * data[j][1]);
}

void PrintSqstack(Sqstack* S)
{
	if (S->top != S->base)
	{
		for (S->mark = S->base; S->mark < S->top; S->mark++)
			printf("%d ", S->mark->num);
		printf("\n");
	}
}

void PrintQueue(Queue* Q)
{
	if (road.front->next != NULL);
	{
		for (Q->leave = Q->front->next; Q->leave->next != NULL; Q->leave = Q->leave->next)
			printf("%d ", Q->leave->num);
		printf("%d\n", Q->leave->num);
	}
}