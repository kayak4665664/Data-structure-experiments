#include <stdio.h>
#define SIZE 10

int n, compare, move, sort_list[SIZE][101], data[2][101];
int InsertSort_Stability = 0, BubbleSort_Stability = 0, QuickSort_Stability = 0,
    SelectSort_Stability = 0, MergeSort_Stability = 0;

void Initial();
void Sort();
void InsertSort(int list[]);
void BubbleSort(int list[]);
void QuickSort(int list[]);
void Qsort(int (*list)[101], int low, int high);
int Partition(int (*list)[101], int low, int high);
void SelectSort(int list[]);
int SelectMinKey(int list[], int mark);
void MergeSort(int list[]);
void MSort(int (*SR)[101], int (*TR1)[101], int s, int t);
void Merge(int (*SR)[101], int (*TR)[101], int i, int m, int n);
void Stability();

int main() {
    Initial();
    Sort();
    Stability();
    return 0;
}

void Initial() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= 100; j++) {
            scanf("%d", &sort_list[i][j]);
        }
    }
}

void Sort() {
    for (int i = 0; i < n; i++) {
        InsertSort(sort_list[i]);
        BubbleSort(sort_list[i]);
        QuickSort(sort_list[i]);
        SelectSort(sort_list[i]);
        MergeSort(sort_list[i]);
    }
}

void InsertSort(int list[]) {
    compare = 0, move = 0;
    for (int i = 1; i < 101; i++) {
        data[0][i] = list[i];
        data[1][i] = i;
    }
    for (int i = 2, j; i <= 100; i++) {
        ++compare;
        if (data[0][i] < data[0][i - 1]) {
            data[0][0] = data[0][i];
            data[1][0] = data[1][i];
            data[0][i] = data[0][i - 1];
            data[1][i] = data[1][i - 1];
            move += 2;
            for (j = i - 2; data[0][0] < data[0][j]; j--, ++compare, ++move) {
                data[0][j + 1] = data[0][j];
                data[1][j + 1] = data[1][j];
            }
            ++compare;
            data[0][j + 1] = data[0][0];
            data[1][j + 1] = data[1][0];
            ++move;
        }
    }
    printf("%-7d %-7d ", compare, move);
    for (int i = 1; i < 101; i++) {
        if (data[0][i] == data[0][i + 1] && data[1][i] > data[1][i + 1]) {
            ++InsertSort_Stability;
            break;
        }
    }
}

void BubbleSort(int list[]) {
    compare = 0, move = 0;
    int flag = 1;
    for (int i = 1; i < 101; i++) {
        data[0][i] = list[i];
        data[1][i] = i;
    }
    for (int i = 0; i < 100 && flag; i++) {
        flag = 0;
        for (int j = 1; j < 100 - i; j++) {
            ++compare;
            if (data[0][j + 1] < data[0][j]) {
                data[0][0] = data[0][j + 1];
                data[1][0] = data[1][j + 1];
                data[0][j + 1] = data[0][j];
                data[1][j + 1] = data[1][j];
                data[0][j] = data[0][0];
                data[1][j] = data[1][0];
                flag = 1;
                move += 3;
            }
        }
    }
    printf("%-7d %-7d ", compare, move);
    for (int i = 1; i < 101; i++) {
        if (data[0][i] == data[0][i + 1] && data[1][i] > data[1][i + 1]) {
            ++BubbleSort_Stability;
            break;
        }
    }
}

void QuickSort(int list[]) {
    compare = 0, move = 0;
    for (int i = 1; i < 101; i++) {
        data[0][i] = list[i];
        data[1][i] = i;
    }
    Qsort(data, 1, 100);
    printf("%-7d %-7d ", compare, move);
    for (int i = 1; i < 101; i++) {
        if (data[0][i] == data[0][i + 1] && data[1][i] > data[1][i + 1]) {
            ++QuickSort_Stability;
            break;
        }
    }
}

void Qsort(int (*list)[101], int low, int high) {
    int pivotloc;
    if (low < high) {
        pivotloc = Partition(list, low, high);
        Qsort(list, low, pivotloc - 1);
        Qsort(list, pivotloc + 1, high);
    }
}

int Partition(int (*list)[101], int low, int high) {
    list[0][0] = list[0][low];
    list[1][0] = list[1][low];
    ++move;
    while (low < high) {
        while (low < high && list[0][high] >= list[0][0]) {
            ++compare;
            --high;
        }
        if (low < high) {
            ++compare;
        }
        list[0][low] = list[0][high];
        list[1][low] = list[1][high];
        ++move;
        while (low < high && list[0][low] <= list[0][0]) {
            ++compare;
            ++low;
        }
        if (low < high) {
            ++compare;
        }
        list[0][high] = list[0][low];
        list[1][high] = list[1][low];
        ++move;
    }
    list[0][low] = list[0][0];
    list[1][low] = list[1][0];
    ++move;
    return low;
}

void SelectSort(int list[]) {
    compare = 0, move = 0;
    for (int i = 1; i < 101; i++) {
        data[0][i] = list[i];
        data[1][i] = i;
    }
    for (int i = 1; i < 100; i++) {
        int j = SelectMinKey(data[0], i);
        if (i != j) {
            int temp = data[0][i];
            int temp1 = data[1][i];
            data[0][i] = data[0][j];
            data[1][i] = data[1][j];
            data[0][j] = temp;
            data[1][j] = temp1;
            move += 3;
        }
    }
    printf("%-7d %-7d ", compare, move);
    for (int i = 1; i < 101; i++) {
        if (data[0][i] == data[0][i + 1] && data[1][i] > data[1][i + 1]) {
            ++SelectSort_Stability;
            break;
        }
    }
}

int SelectMinKey(int list[], int mark) {
    int min = list[mark];
    for (int i = mark + 1; i < 101; i++) {
        ++compare;
        if (list[i] < min) {
            min = list[i];
            mark = i;
        }
    }
    return mark;
}

void MergeSort(int list[]) {
    compare = 0, move = 0;
    for (int i = 1; i < 101; i++) {
        data[0][i] = list[i];
        data[1][i] = i;
    }
    MSort(data, data, 1, 100);
    printf("%-7d %-7d\n", compare, move);
    for (int i = 1; i < 101; i++) {
        if (data[0][i] == data[0][i + 1] && data[1][i] > data[1][i + 1]) {
            ++MergeSort_Stability;
            break;
        }
    }
}

void MSort(int (*SR)[101], int (*TR1)[101], int s, int t) {
    if (s == t) {
        TR1[0][s] = SR[0][s];
        TR1[1][s] = SR[1][s];
    } else {
        int m = (s + t) / 2;
        int TR2[2][101];
        MSort(SR, TR2, s, m);
        MSort(SR, TR2, m + 1, t);
        Merge(TR2, TR1, s, m, t);
    }
}

void Merge(int (*SR)[101], int (*TR)[101], int i, int m, int n) {
    int j, k, l;
    for (j = m + 1, k = i; i <= m && j <= n; k++) {
        ++compare;
        if (SR[0][j] < SR[0][i]) {
            TR[0][k] = SR[0][j];
            TR[1][k] = SR[1][j++];
            ++move;
        } else {
            TR[0][k] = SR[0][i];
            TR[1][k] = SR[1][i++];
            ++move;
        }
    }
    if (i <= m) {
        for (l = i; l <= m; l++) {
            TR[0][k] = SR[0][l];
            TR[1][k++] = SR[1][l];
            ++move;
        }
    }
    if (j <= n) {
        for (l = j; l <= n; l++) {
            TR[0][k] = SR[0][l];
            TR[1][k++] = SR[1][l];
            ++move;
        }
    }
}

void Stability() {
    if (!InsertSort_Stability) {
        printf("InsertSort: Stable\n");
    } else {
        printf("InsertSort: Unstable\n");
    }
    if (!BubbleSort_Stability) {
        printf("BubbleSort: Stable\n");
    } else {
        printf("BubbleSort: Unstable\n");
    }
    if (!QuickSort_Stability) {
        printf("QuickSort: Stable\n");
    } else {
        printf("QuickSort: Unstable\n");
    }
    if (!SelectSort_Stability) {
        printf("SelectSort: Stable\n");
    } else {
        printf("SelectSort: Unstable\n");
    }
    if (!MergeSort_Stability) {
        printf("MergeSort: Stable\n");
    } else {
        printf("MergeSort: Unstable\n");
    }
}
