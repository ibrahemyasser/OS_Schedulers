#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include "../inc/header.h"






// Priority queue functions

void insert(CircularPriorityQ *q, Process Proc) {
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
            if (Proc.arrival_time < q->queArray[abs(j)].arrival_time) {
                q->queArray[(abs(j) + 1) % q->maxSize] = q->queArray[abs(j)];
            } else {
                break;
            }
        }

        // Insert new Proc at correct position
        if ((j == q->front) && (Proc.arrival_time < q->queArray[abs(j)].arrival_time)) {
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

Process pop(CircularPriorityQ *q) {

    q->tmp = q->front;
    q->front = (q->front + 1) % q->maxSize;
    q->nProcs--;
    return q->queArray[q->tmp];
}


Process peekMin(CircularPriorityQ *q) {
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
           printf("process ID: %d, arrival time: %d\n", q->queArray[i].process_id, q->queArray[i].arrival_time);
        }
    }
}

bool dec1sec(Process *processes,CircularPriorityQ *q,int n) {
    
    if ((q->no_completed ==n)) {
        printf("\n======================================\n");
        printf("all of the process has been executed\n\n");
        return 0;
    } else {
        bool ready = false;//  to check if in that second any process was ready 
        for (int i = q->front, j = 0; j < q->nProcs; i = (i + 1) % q->maxSize, j++) {
            if(q->queArray[i].holder == true) // the the process was the queue holder move to next process
                continue;

           if(q->queArray[i].arrival_time==0){
            if(q->queArray[i].first_runtime ==-1)
                processes[q->queArray[i].process_id-1].first_runtime =q->time;
            
            run(processes,q,pop(q));
            ready = true;
            }
            else 
           { q->queArray[i].arrival_time-=1;
                      
    }}
    if(ready == false)
    q->time +=1; //if there wasn't any process ready in that secod incremen time
}
       return 1;
}

void ftime(CircularPriorityQ *q){

 for (int i = q->front, j = 0; j < q->nProcs; i = (i + 1) % q->maxSize, j++) {
           q->queArray[i].first_runtime =-1;
           q->queArray[i].holder =false;
        }

}

void decnonzero(CircularPriorityQ *q){

 for (int i = q->front, j = 0; j < q->nProcs; i = (i + 1) % q->maxSize, j++) {
           if(q->queArray[i].arrival_time !=0)
                q->queArray[i].arrival_time -=1;
        }

}