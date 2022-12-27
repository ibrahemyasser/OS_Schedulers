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
    readyQueue.no_completed= 0;
    
    Process queue_holder;
    queue_holder.holder = true;
    queue_holder.arrival_time=10000000;
    // initiaze the queue
    for (int i = 0; i < n; i++)
    {
        insert(&readyQueue,processes[i]);
    }
    
    ftime(&readyQueue);
    insert(&readyQueue,queue_holder);
    while(dec1sec(processes,&readyQueue,n));
    
   
}


void run(Process *processes ,CircularPriorityQ *q,Process proc){
     // if there is no I/O
        if(proc.IO_time ==0){
            if(proc.CPU_time > QUANTUM)
            {
                for (int i = 0; i<QUANTUM; i++){
                printf("time [%d]:  %s \n",q->time,proc.process_name);
                decnonzero(q);
                q->time += 1;    
                }
                proc.CPU_time -=QUANTUM;
                insert(q,proc);
                
            }   

            else{
                for (int i = 0; i<proc.CPU_time; i++){
                printf("time [%d]:  %s \n",q->time,proc.process_name);
                 q->time += 1  ;
                 decnonzero(q);
                }

                processes[proc.process_id-1].end_time = q->time-1 ;
                q->no_completed +=1;
                printf("time [%d]: process %s termainates \n",q->time-1,proc.process_name);


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
                               decnonzero(q);
                            }
                        
                        proc.IO_start_time -=QUANTUM;
                        proc.CPU_time -=QUANTUM;
                        insert(q,proc);
                       
                    }
                    else{
                        for (int i = 0; i<proc.IO_start_time; i++){
                            printf("time [%d]:  %s \n",q->time,proc.process_name);
                             q->time += 1; 
                             decnonzero(q);         
                        }
                        printf("time [%d]:  %s will execute I/O \n",q->time ,proc.process_name);
                        proc.arrival_time += proc.IO_time;
                        proc.CPU_time -=proc.IO_start_time;
                        proc.IO_time= 0;
                        insert(q,proc);
                      
                    }
                }
        }
}
void RR_printResults(Process *processes, int n)
{
   
    printf("Process Name\tTurn around\tResponse time\tGantt chart\n");
    for(int i = 0;i < n;i++)
    {
    

        printf("%s\t\t|",processes[i].process_name);
        printf("\t%d\t|",processes[i].first_runtime);
        printf("\t%d\t|",processes[i].first_runtime);
        
}
}