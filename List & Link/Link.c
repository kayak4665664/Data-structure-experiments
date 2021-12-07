#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
    int data;
    int num;
    struct LNode* next;
} LNode;

int m, n, i, new_data;
LNode *node, *head, *temp = NULL;

void data();
void num();
void Joseph(int x);
void node_delete();
void print(int x);

int main() {
    scanf("%d%d", &m, &n);
    node = (LNode*)malloc(sizeof(LNode));
    head = node;

    data();
    num();

    for (i = 0; i < n - 1; i++) node = node->next;

    Joseph(m);

    return 0;
}

void data() {
    for (i = 0; i < n - 1; i++) {
        scanf("%d", &node->data);
        node->next = (LNode*)malloc(sizeof(LNode));
        node = node->next;
    }
    scanf("%d", &(node->data));
    node->next = head;
    node = head;
}

void num() {
    for (i = 1; i <= n; i++) {
        node->num = i;
        node = node->next;
    }
}

void Joseph(int x) {
    while (n > 0) {
        for (i = 0; i < x - 1; i++) node = node->next;
        new_data = node->next->data;
        print(node->next->num);
        node_delete();
        Joseph(new_data);
    }
}

void node_delete() {
    temp = node->next;
    node->next = node->next->next;
    free(temp);
    n--;
}

void print(int x) { printf("%d ", x); }
