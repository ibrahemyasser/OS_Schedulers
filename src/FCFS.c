#include "../inc/header.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void FCFS_Scheduler(Process *processes, int n)
{
    FCFS_sortProcesses(processes,n);
    
    CircularPriorityQ readyQueue;
    readyQueue.maxSize = MAX_SIZE;
    readyQueue.nProcs = 0;
    readyQueue.front = 0;
    readyQueue.rear = 0;
    
    for (int i = 0; i < n; i++)
    {
        printf("%d\n",processes[i].process_id);
        insert(&readyQueue,processes[i]);
    }
    display(&readyQueue);
    

    printf("Process Name\tTurn around\tResponse time\tGantt chart\n");
    int tabs=0;
    double avrage_turn = calculateTurnaroundTime(processes,n,FCFS_NUM);
    double avrage_res= calculateResponseTime(processes,n,FCFS_NUM);
    for(int i=0;i<n;i++)
    {

        printf("%s\t\t|",processes[i].process_name);
        printf("\t%d\t|",processes[i].turnAround_time);
        printf("\t%d\t|",processes[i].response_time);
        for(int c=0;c<tabs;c++)
        {
            printf(" ");
        }
       for(int j=0;j<processes[i].CPU_time;j++)
          {
        if(processes[i].IO_start_time <= j && processes[i].IO_time --> 0)
           {
              printf("i");


           }
             else
             {
                printf("%s",processes[i].pro_specifier);

             }
             tabs++;
          }
          printf("\n");
           }
        printf("average of Turnaround time=%0.2f\n",avrage_turn);
        printf("average of Response time=%0.2f\n",avrage_res);
}

void FCFS_sortProcesses(Process *processes, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}