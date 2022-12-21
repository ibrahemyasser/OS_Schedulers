#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

#define SJF_NUM         1
#define FCFS_NUM        2
#define SRTF_NUM        3
#define PB_NP_NUM       4
#define PB_P_NUM        5
#define RR_NUM          6

int sch_choose;
char c;
// Define a struct to hold the data for each process
typedef struct {
    int     process_id;
    char    process_name[MAX_LINE_LENGTH];
    int     arrival_time;
    int     CPU_time ;
    int     execution_time;
    int     IO_time;
    int     IO_start_time;
    char    process_status[MAX_LINE_LENGTH] ;
    int     first_runtime;
    int     waiting_time;
    int     turnAround_time;
    int     response_time;
    char    pro_specifier[MAX_LINE_LENGTH];
} Process;

void SJF_Scheduler(Process *processes, int n);
void SJF_sortProcesses(Process *processes, int n);
void SJF_printResults(Process *processes, int n);

void FCFS_Scheduler(Process *processes, int n);
void PB_P_Scheduler(Process *processes, int n);
void SRTF_Scheduler(Process *processes, int n);
void PB_NP_Scheduler(Process *processes, int n);
void RR_Scheduler(Process *processes, int n);
void calculateResponseTime(Process *processes, int n,int scheduler);
void calculateTurnaroundTime(Process *processes, int n,int scheduler);
void choose_scheduler(Process *processes, int n);
void getIntegerOnly(int *ptr);

int main() {
    int num_ofDataset_processes = 0,
    user_processes = 0,
    choose;
    system("cls");  //clears the screen
    system("color A");
    printf("\033[%dm", 30 + 4);
    // Open the file for reading
    FILE *fp = fopen("dataset.txt", "r");

    // Check if the file was successfully opened
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Read the first line of the file (the header) and discard it
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, fp);
    fgets(line, MAX_LINE_LENGTH, fp);
    // Create an array of Process structs to hold the data
    Process processes[MAX_LINE_LENGTH];

    // Initialize the index for the processes array
    int i = 0,j = 0;

    // Read the rest of the lines in the file
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        // Parse the data from the line and store it in the struct
        sscanf(line, "%d | %s | %d | %d | %d | %d | %s", &processes[i].process_id, processes[i].process_name, &processes[i].arrival_time, &processes[i].CPU_time, &processes[i].IO_time, &processes[i].IO_start_time, processes[i].pro_specifier);
        // Increment the index for the processes array
        processes[i].execution_time = processes[i].CPU_time - processes[i].IO_time;
        i++;
        num_ofDataset_processes++;
    }

    // Close the file
    fclose(fp);

    // main window
    printf("Start of simulation.\nEnter:\t 1-Create a new process \n\t 2-Start simulation with current dataset\n ");
    getIntegerOnly(&choose);   

    if(choose == 1)
    {
        printf("Enter the number of processes:");
        getIntegerOnly(&user_processes);

        while(j < user_processes)
        {
            processes[num_ofDataset_processes+j].process_id = num_ofDataset_processes+j+1;
            strcpy(processes[num_ofDataset_processes+j].process_status,"ready");
            
            printf("Enter process %d Name: ",j+1);
            scanf(" %[^\n]s",processes[num_ofDataset_processes+j].process_name);
            //fgets(processes[num_ofDataset_processes+j].process_name,10,stdin);
            
            printf("Enter process %d arrival time: ",j+1);
            getIntegerOnly(&processes[num_ofDataset_processes+j].arrival_time);
            
            printf("Enter process %d CPU time: ",j+1);
            getIntegerOnly(&processes[num_ofDataset_processes+j].CPU_time);

            printf("Enter process %d IO time: ",j+1);
            getIntegerOnly(&processes[num_ofDataset_processes+j].IO_time);
            if(processes[i].IO_time)
            {
                printf("Enter process %d IO start time: ",j+1);
                getIntegerOnly(&processes[num_ofDataset_processes+j].IO_start_time);
            }
            
            printf("Enter process %d specifier: ",j+1);
            scanf("%S",&processes[num_ofDataset_processes+j].pro_specifier);
            
            j++;
        }
        choose_scheduler(processes,num_ofDataset_processes+user_processes);
        
    }else if(choose == 2)
    {   
        choose_scheduler(processes,num_ofDataset_processes+user_processes);

    }
    else
    {
        printf("Invalid number!. Please enter a valid number.\n");
    }


    return 0;
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
    int spaces = 0,IO_counter = 0;
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
                printf("IO");    
            }else
            {
                printf("%s",processes[i].pro_specifier);
            }
            
        }
        printf("\t\v");
    }
    printf("\n\n");
}

void choose_scheduler(Process *processes, int n)
{
    printf("Select the scheduler:\n1-First Come First Served\n2-Shortest Job First\n3-Shortest Remaining Time First\n4-Priority-based (non-preemptive)\n5-Priority-based (preemptive)	\n6-Round Robin\n");
    getIntegerOnly(&sch_choose);
    switch (sch_choose)
    {
    case 1:
        FCFS_Scheduler(processes,n);
        break;
    case 2:
        SJF_Scheduler(processes,n);
        break;
    case 3:
        SRTF_Scheduler(processes,n);
        break;
    case 4:
        PB_NP_Scheduler(processes,n);
        break;
    case 5:
        PB_P_Scheduler(processes,n);
        break;
    case 6:
        RR_Scheduler(processes,n);
        break;    
    
    default:
    printf("Invalid number!.");
        break;
    }
}
void FCFS_Scheduler(Process *processes, int n)
{

}
void SJF_Scheduler(Process *processes, int n)
{
    printf("\nShortest Job first assumes that all processes arrive at the same time.\n");
    SJF_sortProcesses(processes, n);
    calculateTurnaroundTime(processes,n,SJF_NUM);
    calculateResponseTime(processes,n,SJF_NUM);
    
    SJF_printResults(processes, n);
}
void PB_P_Scheduler(Process *processes, int n)
{

}
void SRTF_Scheduler(Process *processes, int n)
{

}
void PB_NP_Scheduler(Process *processes, int n)
{

}
void RR_Scheduler(Process *processes, int n)
{

}

void calculateTurnaroundTime(Process *processes, int n,int scheduler)
{
    switch (scheduler)
    {
    case SJF_NUM:
        processes[0].waiting_time =0;
        processes[0].turnAround_time = processes[0].execution_time;
        
        for (int i = 1; i < n; i++)
        {
            processes[i].waiting_time = processes[i-1].execution_time + processes[i-1].waiting_time;
            processes[i].turnAround_time = processes[i].waiting_time + processes[i].execution_time;
        }
        break;
    
    default:
        break;
    }
}
void calculateResponseTime(Process *processes, int n,int scheduler)
{
    switch (scheduler)
    {
    case SJF_NUM:
        processes[0].response_time = processes[0].waiting_time;
        for (int i = 1; i < n; i++)
        {
            processes[i].response_time = processes[i].waiting_time;
        }
        break;
    
    default:
        break;
    }

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