#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../inc/header.h"



void SJF_Scheduler(Process *processes, int n)
{
    printf("\nShortest Job first assumes that all processes arrive at the same time.\n");
    SJF_sortProcesses(processes, n);
    SJF_IO_Handler(processes, n);

    double avrage_turn = calculateTurnaroundTime(processes,n,SJF_NUM);
    double avrage_res=calculateResponseTime(processes,n,SJF_NUM);

    SJF_printResults(processes, n);
    printf("average of Turnaround time=%0.2f\n",avrage_turn);
    printf("average of Response time=%0.2f\n",avrage_res);
}

void SJF_IO_Handler(Process *processes, int n)
{
    
}

void SJF_sortProcesses(Process *processes, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (processes[i].CPU_time > processes[j].CPU_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}
void SJF_printResults(Process *processes, int n)
{
    int spaces = 0;
    printf("Process Name\tTurn around\tResponse time\tGantt chart\n");
    for(int i = 0;i < n;i++)
    {
        int IO_start = processes[i].IO_start_time;
        int IO_time = processes[i].IO_time;

        printf("%s\t\t|",processes[i].process_name);
        printf("\t%d\t|",processes[i].turnAround_time);
        printf("\t%d\t|",processes[i].response_time);
        for(int j = 0; j < processes[i].CPU_time; j++)
        {
            if(i==0)
            {
                spaces += processes[i].CPU_time;
                break;
            }
            else
            {
                for (int i = 0; i < spaces ; i++)
                {
                    printf(" ");
                }
                spaces += processes[i].CPU_time;    
                break;
            }
        }
        for(int j = 0; j < processes[i].CPU_time; j++)
        {
            if(j >= IO_start && IO_time-- > 0)
            {
                printf("i");    
            }else
            {
                printf("%s",processes[i].pro_specifier);
            }
            
        }
        printf("\n\v");
    }
    printf("\n\n");
}