#include "../inc/header.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void RR_Scheduler(Process *processes, int n)
{
    CircularPriorityQ readyQueue;
    readyQueue.maxSize = MAX_SIZE;
    readyQueue.nProcs = 0;
    readyQueue.front = 0;
    readyQueue.rear = 0;
    readyQueue.time = 0;
    
    // initiaze the queue
    for (int i = 0; i < n; i++)
    {
        insert(&readyQueue,processes[i]);
    }
    
    while(dec1sec(&readyQueue));
    
}


void run(CircularPriorityQ *q,Process proc){
     // if there is no I/O
        if(proc.IO_time ==0){
            if(proc.CPU_time > QUANTUM)
            {
                for (int i = 0; i<QUANTUM; i++){
                printf("time [%d]:  %s \n",q->time,proc.process_name);
                q->time += 1;    
                }
                proc.CPU_time -=QUANTUM;
                proc.arrival_time +=QUANTUM;
                insert(q,proc);
            }   

            else{
                for (int i = 0; i<proc.CPU_time; i++){
                printf("time [%d]:  %s \n",q->time,proc.process_name);
                 q->time += 1  ;
                }// no need to it will termainates   
            }
        }

 // if there is an I/O
        else{
                if(proc.IO_start_time ==0){
                    printf("time [%d]:  %s will execute I/O \n",q->time ,proc.process_name);
                    proc.arrival_time +=proc.IO_time;
                    proc.IO_time = 0;
                    insert(q,proc);
                }
                
                else{
                    
                    if(proc.IO_start_time > QUANTUM){
                        for (int i = 0; i<QUANTUM; i++){
                            printf("time [%d]:  %s \n",q->time,proc.process_name);
                               q->time += 1 ;  
                            }
                        proc.arrival_time += QUANTUM;
                        proc.IO_start_time -=QUANTUM;
                        proc.CPU_time -=QUANTUM;
                        insert(q,proc);
                    }
                    else{
                        for (int i = 0; i<proc.IO_start_time; i++){
                            printf("time [%d]:  %s \n",q->time,proc.process_name);
                             q->time += 1;          
                        }
                        printf("time [%d]:  %s will execute I/O \n",q->time ,proc.process_name);
                        proc.arrival_time += proc.IO_start_time + proc.IO_time;
                        proc.CPU_time -=proc.IO_start_time;
                        proc.IO_time= 0;
                        insert(q,proc);
                    }
                }
        }
}