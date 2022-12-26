#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../inc/header.h"


int sch_choose;
char c;

int main() {
    int num_ofDataset_processes = 0,
    user_processes = 0,
    choose;
    system("cls");  //clears the screen
    system("color A");
    printf("\033[%dm", 30 + 4);
    // Open the file for reading
    FILE *fp = fopen("../dataset.txt", "r");

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
        processes[i].remaining_time = processes[i].CPU_time;
        i++;
        num_ofDataset_processes++;
    }
    Queue_Init();

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

void choose_scheduler(Process *processes, int n)
{
    printf("Select the scheduler:\n1-First Come First Served\n2-Shortest Job First\n3-Shortest Remaining Time First\n4-Multi-Level Feedback Queue \n5-Round Robin\n");
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
        MLFQ_Scheduler(processes,n);
        break;
    case 5:
        RR_Scheduler(processes,n);
        break;    
    
    default:
    printf("Invalid number!.");
        break;
    }
}