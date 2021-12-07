#include <stdio.h>
#define SIZE 10

int n, compare, move, sort_list[SIZE][101], data[101];

void Initial();
void Sort();
void InserSort(int list[]);
void BubbleSort(int list[]);
void QuickSort(int list[]);
void Qsort(int list[], int low, int high);
int Partition(int list[], int low, int high);
void SelectSort(int list[]);
int SelectMinKey(int list[], int mark);
void MergeSort(int list[]);
void MSort(int SR[], int TR1[], int s, int t);
void Merge(int SR[], int TR[], int i, int m, int n);

int main()
{
	Initial();
	Sort();
	return 0;
}

void Initial()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <= 100; j++)
		{
			scanf("%d", &sort_list[i][j]);
		}
	}
}

void Sort()
{
	for (int i = 0; i < n; i++)
	{
		InserSort(sort_list[i]);
		BubbleSort(sort_list[i]);
		QuickSort(sort_list[i]);
		SelectSort(sort_list[i]);
		MergeSort(sort_list[i]);
	}
}

void InserSort(int list[] )
{
	compare = 0, move = 0;
	for (int i = 1; i < 101; i++)
	{
		data[i] = list[i];
	}
	for (int i = 2, j; i <= 100; i++)
	{
		++compare;
		if (data[i] < data[i - 1])
		{
			data[0] = data[i];
			data[i] = data[i - 1];
			move += 2;
			for (j = i - 2; data[0] < data[j]; j--, ++compare, ++move)
			{
				data[j + 1] = data[j];
			}
			++compare;
			data[j + 1] = data[0];
			++move;
		}
	}
	printf("%-7d %-7d ", compare, move);
}

void BubbleSort(int list[])
{
	compare = 0, move = 0;
	int flag = 1;
	for (int i = 1; i < 101; i++)
	{
		data[i] = list[i];
	}
	for (int i = 0; i < 100 && flag; i++)
	{
		flag = 0;
		for (int j = 1; j < 100 - i; j++)
		{
			++compare;
			if (data[j + 1] < data[j])
			{
				data[0] = data[j + 1];
				data[j + 1] = data[j];
				data[j] = data[0];
				flag = 1;
				move += 3;
			}
		}
	}
	printf("%-7d %-7d ", compare, move);
}

void QuickSort(int list[])
{
	compare = 0, move = 0;
	for (int i = 1; i < 101; i++)
	{
		data[i] = list[i];
	}
	Qsort(data, 1, 100);
	printf("%-7d %-7d ", compare, move);
}

void Qsort(int list[], int low, int high)
{
	int pivotloc;
	if(low<high)
	{
		pivotloc = Partition(list, low, high);
		Qsort(list, low, pivotloc - 1);
		Qsort(list, pivotloc + 1, high);
	}
}

int Partition(int list[], int low, int high)
{
	list[0] = list[low];
	++move;
	while (low<high)
	{
		while (low<high&&list[high]>=list[0])
		{
			++compare;
			--high;
		}
		if (low < high)
		{
			++compare;
		}
		list[low] = list[high];
		++move;
		while (low<high&&list[low]<=list[0])
		{
			++compare;
			++low;
		}
		if (low < high)
		{
			++compare;
		}
		list[high] = list[low];
		++move;
	}
	list[low] = list[0];
	++move;
	return low;
}

void SelectSort(int list[])
{
	compare = 0, move = 0;
	for (int i = 1; i < 101; i++)
	{
		data[i] = list[i];
	}
	for (int i = 1; i < 100; i++)
	{
		int j = SelectMinKey(data, i);
		if (i != j)
		{
			int temp = data[i];
			data[i] = data[j];
			data[j] = temp;
			move += 3;
		}
	}
	printf("%-7d %-7d ", compare, move);
}

int SelectMinKey(int list[], int mark)
{
	int min = list[mark];
	for(int i=mark+1;i<101;i++)
	{
		++compare;
		if(list[i]<min)
		{
			min = list[i];
			mark = i;
		}
	}
	return mark;
}

void MergeSort(int list[])
{
	compare = 0, move = 0;
	for (int i = 1; i < 101; i++)
	{
		data[i] = list[i];
	}
	MSort(data,data,1,100);
	printf("%-7d %-7d\n", compare, move);
}

void MSort(int SR[], int TR1[], int s, int t)
{
	if (s == t)
	{
		TR1[s] = SR[s];
	}
	else
	{
		int m = (s + t) / 2;
		int TR2[101];
		MSort(SR, TR2, s, m);
		MSort(SR, TR2, m + 1, t);
		Merge(TR2, TR1, s, m, t);
	}
}

void Merge(int SR[], int TR[], int i, int m, int n)
{
	int j, k, l;
	for (j = m + 1, k = i; i <= m && j <= n; k++)
	{
		++compare;
		if (SR[i] < SR[j])
		{
			TR[k] = SR[i++];
			++move;
		}
		else
		{
			TR[k] = SR[j++];
			++move;
		}
	}
	if (i <= m)
	{
		for (l = i; l <= m; l++)
		{
			TR[k++] = SR[l];
			++move;
		}
	}
	if (j <= n)
	{
		for (l = j; l <= n; l++)
		{
			TR[k++] = SR[l];
			++move;
		}
	}
}
