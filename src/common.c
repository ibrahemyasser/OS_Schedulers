#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../inc/header.h"

double calculateTurnaroundTime(Process *processes, int n,int scheduler)
{
    double counter=0,sum=0;
    switch (scheduler)
    {
    case SJF_NUM:
        counter=0;

        processes[0].waiting_time =0;
        processes[0].turnAround_time = processes[0].execution_time;
        sum=processes[0].turnAround_time;
        for (int i = 1; i < n; i++)
        {

            processes[i].waiting_time = processes[i-1].execution_time + processes[i-1].waiting_time;
            processes[i].turnAround_time = processes[i].waiting_time + processes[i].execution_time;
            counter++;
            sum += processes[i].turnAround_time;
        }

        break;
    case FCFS_NUM:
        counter=0;
        processes[0].turnAround_time=processes[0].CPU_time;
        sum=processes[0].turnAround_time;
        for(int i=1;i<n;i++)
        {
            processes[i].waiting_time = processes[i-1].CPU_time+processes[i-1].waiting_time;
            processes[i].turnAround_time= processes[i].CPU_time+processes[i].waiting_time-processes[i].arrival_time;
            counter++;
            sum += processes[i].turnAround_time;

        }
        break;
    case RR_NUM:
        counter=0;
        processes[0].turnAround_time=processes[0].CPU_time;
        sum=processes[0].turnAround_time;
        for(int i=1;i<n;i++)
        {
            processes[i].waiting_time = processes[i-1].CPU_time+processes[i-1].waiting_time;
            processes[i].turnAround_time= processes[i].CPU_time+processes[i].waiting_time-processes[i].arrival_time;
            counter++;
            sum += processes[i].turnAround_time;

        }
        break;
    default:
        break;
    }
    return (sum/(counter+1));
}

double calculateResponseTime(Process *processes, int n,int scheduler)
{
    double counter=0,sum=0;
    switch (scheduler)
    {
    case SJF_NUM:
        counter=0;

        processes[0].response_time = processes[0].waiting_time;
        sum=processes[0].response_time;
        for (int i = 1; i < n; i++)
        {
            processes[i].response_time = processes[i].waiting_time;
            counter++;
            sum += processes[i].response_time;
        }
        break;
    case FCFS_NUM:
        counter=0;
        sum=0;
        processes[0].response_time =0;
        for (int i = 1; i < n; i++)
        {
            processes[i].waiting_time = processes[i-1].CPU_time + processes[i-1].waiting_time;
            processes[i].response_time = processes[i].waiting_time-processes[i].arrival_time;
            counter++;
            sum += processes[i].response_time;
        }
        break;

    case RR_NUM:
        counter=0;
        sum=0;
        processes[0].response_time =0;
        for (int i = 1; i < n; i++)
        {
            processes[i].waiting_time = processes[i-1].CPU_time + processes[i-1].waiting_time;
            processes[i].response_time = processes[i].waiting_time-processes[i].arrival_time;
            counter++;
            sum += processes[i].response_time;
        }
        break;



    default:
        break;
    }
   return (sum/(counter+1));
}

void getIntegerOnly(int *ptr){
    char *p, s[100];

    while (fgets(s, sizeof(s), stdin)) {
        *ptr = strtol(s, &p, 10);
        if (p == s || *p != '\n') {
            printf("(integer Only) ");
        } else break;
    }
}
