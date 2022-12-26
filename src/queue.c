
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include "../inc/header.h"






// Define a struct to represent an element in the queue




// Define the struct type
typedef struct {
    int value;
    int priority;
} Proc;

typedef struct {
    int maxSize;
    Proc queArray[MAX_SIZE];
    int nProcs;
    int front;
    int rear;
    int tmp;
} CircularPriorityQ;

// Priority queue functions
void insert(CircularPriorityQ *q, Proc roc);
Proc pop(CircularPriorityQ *q);
Proc peekMin(CircularPriorityQ *q);
bool isEmpty(CircularPriorityQ *q);
bool isFull(CircularPriorityQ *q);
void display(CircularPriorityQ *q);

int main(void) {
    // Create a priority queue
    CircularPriorityQ q;
    q.maxSize = MAX_SIZE;
    q.nProcs = 0;
    q.front = 0;
    q.rear = 0;

    // Insert some Procs
    Proc Proc1 = {10, 3};
    insert(&q, Proc1);
    Proc Proc2 = {20, 2};
    insert(&q, Proc2);
    Proc Proc3 = {30, 1};
    insert(&q, Proc3);
    Proc Proc4 = {40, 4};
    insert(&q, Proc4);
    Proc Proc5 = {50, 5};
    insert(&q, Proc5);

    // Display the queue
    printf("Queue: ");
    display(&q);

    // Remove an Proc
    Proc removedProc = pop(&q);
    printf("Removed Proc: Value: %d, Priority: %d\n", removedProc.value, removedProc.priority);

    // Display the queue
    printf("Queue: ");
    display(&q);

    return 0;
}

// Priority queue functions

void insert(CircularPriorityQ *q, Proc Proc) {
    if (q->nProcs == q->maxSize) {
        printf("The queue is full\n");
        return;
    }

    int j;
    if (q->nProcs == 0) {
        // If no Procs, insert at 0
        q->queArray[q->nProcs++] = Proc;
    } else {
        // If Procs, start at end and shift upward if necessary
        for (j = q->rear; j != q->front; j = (j - 1) % q->maxSize) {
            if (Proc.priority <= q->queArray[abs(j)].priority) {
                q->queArray[(abs(j) + 1) % q->maxSize] = q->queArray[abs(j)];
            } else {
                break;
            }
        }

        // Insert new Proc at correct position
        if ((j == q->front) && (Proc.priority <= q->queArray[abs(j)].priority)) {
            q->queArray[(abs(j) + 1) % q->maxSize] = q->queArray[abs(j)];
            q->queArray[abs(j)] = Proc;
            q->nProcs++;
            q->rear = (q->rear + 1) % q->maxSize;
            return;
        }
        q->queArray[(abs(j) + 1) % q->maxSize] = Proc;
        q->nProcs++;
        q->rear = (q->rear + 1) % q->maxSize;
    }
}

Proc pop(CircularPriorityQ *q) {

    q->tmp = q->front;
    q->front = (q->front + 1) % q->maxSize;
    q->nProcs--;
    return q->queArray[q->tmp];
}


Proc peekMin(CircularPriorityQ *q) {
    return q->queArray[q->front];
}

bool isEmpty(CircularPriorityQ *q) {
    return (q->nProcs == 0);
}

bool isFull(CircularPriorityQ *q) {
    return (q->nProcs == q->maxSize);
}

void display(CircularPriorityQ *q) {
    if (q->nProcs == 0) {
        printf("The queue is empty\n");
    } else {
        for (int i = q->front, j = 0; j < q->nProcs; i = (i + 1) % q->maxSize, j++) {
            printf("Value: %d, Priority: %d\n", q->queArray[i].value, q->queArray[i].priority);
        }
    }
}
