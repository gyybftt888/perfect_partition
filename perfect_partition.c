#include <stdio.h>
#include <stdlib.h>

#define SUCESS 0
#define MALLOC_FAIL 1
#define SIZE 15
int cnt = 0;

typedef struct node {
    int element;
    struct node *next, *prev;
} node;

node *table[SIZE];

void push(int element, int index) {
    node *newnode = (node *)malloc(sizeof(node));
    if (!newnode)
        return MALLOC_FAIL;
    newnode->element = element;
    newnode->next = NULL;
    newnode->prev = NULL;
    if (table[index] == NULL) {
        table[index] = newnode;
        return;
    }
    node *current = table[index];
    while (current != NULL) {
        if (current->next == NULL) {
            newnode->prev = current;
            current->next = newnode;
            return;
        }
        current = current->next;
    }
}

void pop(int index) {
    node *current = table[index];
    while (current != NULL) {
        if (current->next == NULL) {
            if (current->prev != NULL) {
                current->prev->next = NULL;
            } else {
                table[index] = NULL;
            }
            free(current);
            return;
        }
        current = current->next;
    }
}

void print(int index) {
    if (table[index] == NULL)
        return;
    node *current = table[index];
    printf("{");
    while (current != NULL) {
        if (current->next != NULL)
            printf("%d, ", current->element);
        else
            printf("%d", current->element);
        current = current->next;
    }
    printf("}");
}

void combination(int n, int m, int element) {
    if (element > n) {
        if (table[m] == NULL) {
            cnt++;
            for (int i = 0; i < n; i++) {
                print(i);
                if (table[i + 1] != NULL) {
                    printf(",");
                } else {
                    printf("\n");
                    break;
                }
            }
        }
        return;
    }
    // PUSH
    for (int i = 0; i < n; i++) {
        if (table[i] != NULL) {
            push(element, i);
            combination(n, m, element + 1);
            pop(i);
        }
    }
    // NEW
    for (int i = 0; i < n; i++) {
        if (table[i] == NULL) {
            push(element, i);
            combination(n, m, element + 1);
            pop(i);
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int m;
    if (argc == 3)
        m = atoi(argv[2]);
    else
        m = n;
    for (int i = 0; i < SIZE; i++)
        table[i] = NULL;
    combination(n, m, 1);
    printf("Result Count: %d\n", cnt);
    return SUCCESS;
}