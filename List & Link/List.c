#include<stdio.h>
#include<stdlib.h>

#define MaxSize 50

typedef struct Sqlist
{
	int data[MaxSize];
	int num[MaxSize];
	int length;
}Sqlist;

int m, n, i, new_data, new_mark;
Sqlist *list;

void list_creat();
void num();
void data();
void Joseph(int x, int y);
void list_delete();
void print(int x);

int main()
{
	scanf("%d%d", &m, &n);

	list_creat();
	num();
	data();
	Joseph(m,0);

	return 0;
}

void list_creat()
{
	list = (Sqlist*)malloc(sizeof(Sqlist));
	list->length = 0;
	list->data[n] = (int)malloc(sizeof(int) * n);
	list->num[n] = (int)malloc(sizeof(int) * n);
}

void num()
{
	for (i = 0; i < n; i++)
	{
		list->num[i] = i + 1;
		list->length++;
	}
}

void data()
{
	for (i = 0; i < n; i++)
		scanf("%d", &list->data[i]);
}

void Joseph(int x,int y)
{
	while (list->length > 0)
	{
		new_mark = (x + y) % list->length;
		if (new_mark != 0)
		{
			new_mark -= 1;
			print(list->num[new_mark]);
			new_data = list->data[new_mark];
			list_delete();
		}
		else
		{
			print(list->num[list->length - 1]);
			new_data = list->data[list->length - 1];
			list->length--;
		}
		Joseph(new_data, new_mark);
	}
}

void list_delete()
{
	for(i= new_mark+1;i<list->length;i++)
	{ 
		list->data[i - 1] = list->data[i];
		list->num[i - 1] = list->num[i];
	}
	list->length--;
}

void print(int x)
{
	printf("%d ", x);
}
