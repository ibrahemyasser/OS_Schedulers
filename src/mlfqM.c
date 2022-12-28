#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../inc/header.h"

int sch_choose;
char c;

    queue_t queues[MAX_LEVELS];

  // Create an array of Process structs to hold the data
    Process processes[MAX_LINE_LENGTH];
int num_processes;

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
  

    // Initialize the index for the processes array
    int i = 0,j = 0;

    // Read the rest of the lines in the file
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        // Parse the data from the line and store it in the struct
        sscanf(line, "%d | %s | %d | %d | %d | %d | %s", &processes[i].process_id, processes[i].process_name, &processes[i].arrival_time, &processes[i].CPU_time, &processes[i].IO_time, &processes[i].IO_start_time, processes[i].pro_specifier);
        // Increment the index for the processes array
        processes[i].execution_time = processes[i].CPU_time - processes[i].IO_time;
        processes[i].burst_time=  processes[i].execution_time;
        processes[i].io_time=  processes[i].IO_time;
        processes[i].io_completion_time=0;

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
            scanf("%c",processes[num_ofDataset_processes+j].pro_specifier);
            
            j++;
        }
        num_processes=num_ofDataset_processes+user_processes;
        choose_scheduler(processes,num_ofDataset_processes+user_processes);
        
    }else if(choose == 2)
    {   
        num_processes=num_ofDataset_processes+user_processes;
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

void MLFQSortByArrival(int level){
    for(int i=0;i<queues[level].num_processes;i++){
        Process temp;
        for(int j=i+1; j<queues[level].num_processes;j++){
            if(queues[level].processes[j].arrival_time<queues[level].processes[i].arrival_time){
                temp=queues[level].processes[i];
                queues[level].processes[i]=queues[level].processes[j];
                queues[level].processes[j]=temp;
            }
        }
    }
}

// this function is to check if there's a job that it's time came in higher queues
// recevies the current level;
int checkPriority(int t,int level ,bool current){
   
    if(current){
        for(int i=0;i<queues[level].num_processes;i++){
             if(queues[level].processes[i].arrival_time <=t){ // check for any process that arrived at this time
                      return i;
             }
        }
        return -1;
    }else{
          for(int i=0; i<level;i++){
                for(int j=0; j<queues[i].num_processes; j++){
                    if(queues[i].processes[j].arrival_time<=t)return j;
                }
    }
    return -1;
   }
    }
// function to add all the processes to the highest priority queue at first
void addToHP(){
    for (int i = 0; i < num_processes; i++)
    {
        queues[0].processes[queues[0].num_processes++] = processes[i];
    }
}
void initQueues(){

    // Initialize all queues to be empty
    for (int i = 0; i < MAX_LEVELS; i++)
    {
      //  queues[i].num_processes = 0;
        for (int j = 0; j < MAX_PROCESSES; j++)
        {
            queues[i].processes[j].time_slice=0;
            queues[i].processes[j].first_runtime=-1;
            queues[i].processes[j].waiting_time=0;

        }
    }
     // Set the quantum for each queue
    queues[0].quantum = 2; // Set the quantum for the highest priority queue to 1
    queues[1].quantum = 4; // Set the quantum for the next priority queue to 4
    queues[2].quantum = 6; // Set the quantum for the next priority queue to 6
    // Set the quantum for the remaining queues as desired
}
int checkEmpty(int level){
    return queues[level].num_processes > 0;
}
void incWaitingTime(int time, int level,int current_process,int *response_time){
 // Increment the waiting time for all processes in the current queue
           for(int j=0; j<MAX_LEVELS; j++){
                for (int i = 0; i < queues[level].num_processes; i++)
                {
                    if (i != current_process && queues[j].processes[i].arrival_time>=time)
                    {
                        queues[j].processes[i].waiting_time++;
                        (*response_time)++;
                    }
                }   
           }
}
int handleCpuIntensive(int *time,int level,int current_process,int *completed_processes,int *turnaround_time){
            // then check whether we're executing at the highest priority or not
            if(level) // meaning that level is not 0
            {
                // if we're  not , so run for a second by second in case any higher priority job arrives
                  for(int i=0; i<queues[level].quantum &&( checkPriority(*time,level,false)==-1) && !(queues[level].processes[current_process].completed); i++){
                            queues[level].processes[current_process].burst_time-=1; // decrease the burst *time by quantum                
                             queues[level].processes[current_process].time_slice+=1;
                             *time+=1;
                            
                         if(i==1)  printf("Process %d Executing \t\t\t   Total Elapsed Time: %d\n",queues[level].processes[current_process].process_id,*time);

                                       // If the current process has completed
                            if (queues[level].processes[current_process].burst_time <= 0)
                                {
                                    // Set the turnaround time and mark the process as completed
                                    queues[level].processes[current_process].turnaround_time = *time-queues[level].processes[current_process].arrival_time;
                                    queues[level].processes[current_process].completed = 1;
                                    (*completed_processes)++;
                                    (*turnaround_time)+=queues[level].processes[current_process].turnaround_time;
                                printf("Process %d Completed Execution at %d with Turn Around Time of %d ....\n",queues[level].processes[current_process].process_id,*time,queues[level].processes[current_process].turnaround_time);
                                    
                                    // Remove the completed process from the queue
                                    for (int i = current_process; i < queues[level].num_processes - 1; i++)
                                    {
                                        queues[level].processes[i] = queues[level].processes[i + 1];
                                    }
                                    queues[level].num_processes--;
                                    continue;
                                }
                                // If the time slice has been exceeded but not finished(so it's gonna be moved to the next queue)
                                else if (queues[level].processes[current_process].time_slice == queues[level].quantum && level !=(MAX_LEVELS-1))
                                {
                                    // Move the current process to the next queue
                                 //   queues[level].processes[current_process].arrival_time=time;
                                    queues[level].processes[current_process].time_slice=0;
                                    queues[level + 1 ].processes[queues[level + 1].num_processes++] = queues[level].processes[current_process];
                                    printf("Process %d  Moved to Queue %d \t\t\t\t \n Total Elapsed Time: %d\n",queues[level].processes[current_process].process_id,level+2,*time);
                                    // Remove the process from the current queue
                                    for (int i = current_process; i < queues[level].num_processes - 1; i++)
                                    {
                                        queues[level].processes[i] = queues[level].processes[i + 1];
                                    }
                                    queues[level].num_processes--;
                                }

                                 else if(level==(MAX_LEVELS-1)) // if we're at the last level just execute with the current time slice there's no more movement
                                {
                                       queues[level].processes[current_process].burst_time-=queues[level].quantum; // decrease the burst time by quantum                
                                        queues[level].processes[current_process].time_slice+=queues[level].quantum;
                                        printf("Process %d Executing \t\t\t\t\t \n Total Elapsed Time: %d\n",queues[level].processes[current_process].process_id,*time);
                                }
                        }
                        if(!(checkPriority(*time,level,false)==-1)){
                            return -1; // to indicate the you gotta go to the previous level
                        }
                        
            
            }else{
                             queues[level].processes[current_process].burst_time-=queues[level].quantum; // decrease the burst time by quantum                
                              queues[level].processes[current_process].time_slice+=queues[level].quantum;                                   
                             *time+=queues[level].quantum;
                             printf("Process %d Executing \t\t\t Total Time Elapsed: %d\n",queues[level].processes[current_process].process_id,*time);

                          // If the current process has completed
                    if (queues[level].processes[current_process].burst_time <= 0)
                    {
                        // Set the turnaround time and mark the process as completed
                        queues[level].processes[current_process].turnaround_time = *time-queues[level].processes[current_process].arrival_time;
                        queues[level].processes[current_process].completed = 1;
                        (*completed_processes)++;
                  (*turnaround_time)+=queues[level].processes[current_process].turnaround_time;
                    printf("Process %d Completed Execution with Turn Around Time of :%d ....\n",queues[level].processes[current_process].process_id,queues[level].processes[current_process].turnaround_time);

                        // Remove the completed process from the queue
                        for (int i = current_process; i < queues[level].num_processes - 1; i++)
                        {
                            queues[level].processes[i] = queues[level].processes[i + 1];
                        }
                        queues[level].num_processes--;
                    }
                    // If the time slice has been exceeded but not finished(so it's gonna be moved to the next queue)
                    else if (queues[level].processes[current_process].time_slice >= queues[level].quantum)
                    {
                        // Move the current process to the next queue
                  //      queues[level].processes[current_process].arrival_time=time;
                         queues[level].processes[current_process].time_slice=0;
                        queues[level + 1].processes[queues[level + 1].num_processes++] = queues[level].processes[current_process];
                        printf("Process %d Took All the Allotment And Got Moved to Queue %d\t\t\t \n",queues[level].processes[current_process].process_id,level+2);
                        // Remove the process from the current queue
                        for (int i = current_process; i < queues[level].num_processes - 1; i++)
                        {
                            queues[level].processes[i] = queues[level].processes[i + 1];
                        }
                        queues[level].num_processes--;
                    }
                  // If the current process has exceeded the number of processes in the current queue
                    if (current_process == queues[level].num_processes)
                    {
                        // Reset the current process to the beginning of the queue
                        current_process = 0;
                        }
                    }
                
            return 0;    
}
void handleIO(int *time,int level,int current_process, int *completed_processes,int *turnaround_time){
    if(! queues[level].processes[current_process].io_completion_time){ // if io completion wasn't set ,set it
                        queues[level].processes[current_process].io_completion_time=*time+ queues[level].processes[current_process].io_time;
                            // move it to the last of the queue
                                //increasing time slice one by one 
                                queues[level].processes[current_process].time_slice++;
                                (*time)++;
                                Process temp=queues[level].processes[current_process];
                                for(int j=current_process; j<num_processes; j++){
                                    queues[level].processes[(j)%num_processes]=queues[level].processes[(j+1)%num_processes];
                                        }
                                queues[level].processes[num_processes-1]=temp; // move it to the last element 
                                printf("Process %d Moved to the end of Queue %d \t\t\t Total Time Elapsed: %d\n",queues[level].processes[num_processes-1].process_id,level+1,*time);
                                        // queues[level].processes[current_process].waiting_time++;
                                }
                    else { // it's already set , so check if it completed or not
                                if(queues[level].processes[current_process].io_completion_time<=*time){
                                            queues[level].processes[current_process].io_time=0;
                                            // execute normally
                                            queues[level].processes[current_process].burst_time-=queues[level].quantum;
                                            queues[level].processes[current_process].time_slice+=queues[level].quantum;
                                               // If the current process has completed
                                        if (queues[level].processes[current_process].burst_time <= 0)
                                        {
                                            // Set the turnaround time and mark the process as completed
                                            queues[level].processes[current_process].turnaround_time = *time-queues[level].processes[current_process].arrival_time;
                                            queues[level].processes[current_process].completed = 1;
                                            (*completed_processes)++;
                                          (*turnaround_time)+=queues[level].processes[current_process].turnaround_time;
                                        printf("Process %d Completed Execution with Turn Around Time of :%d ....\n",queues[level].processes[current_process].process_id,queues[level].processes[current_process].turnaround_time);

                                            // Remove the completed process from the queue
                                            for (int i = current_process; i < queues[level].num_processes - 1; i++)
                                            {
                                                queues[level].processes[i] = queues[level].processes[i + 1];
                                            }
                                            queues[level].num_processes--;
                                        }
                                            // check if took the full allotment
                                                // If the time slice has been exceeded but not finished(so it's gonna be moved to the next queue)
                                            else if (queues[level].processes[current_process].time_slice >= queues[level].quantum)
                                            {
                                            if(level!=(MAX_LEVELS-1)){
                                                    // Move the current process to the next queue
                                              // queues[level].processes[current_process].arrival_time=time;
                                               queues[level].processes[current_process].time_slice=0;
                                                queues[level + 1].processes[queues[level + 1].num_processes++] = queues[level].processes[current_process];
                                                printf("Process %d Took All the Allotment And Got Moved to Queue %d\t\t\t \n",queues[level].processes[current_process].process_id,level+2);
                                                // Remove the process from the current queue
                                                for (int i = current_process; i < queues[level].num_processes - 1; i++)
                                                {
                                                    queues[level].processes[i] = queues[level].processes[i + 1];
                                                }
                                                queues[level].num_processes--;
                                            } else{ // just execute normally without  moving
                                                    queues[level].processes[current_process].time_slice+=queues[level].quantum;
                                                    queues[level].processes[current_process].burst_time-=queues[level].quantum;
                                            }
                                            }
                      }else{
                        (*time)++;
                      }
                    }
}

void MLFQ_Scheduler(Process *processes, int num_processes)
{
    int time = 0;
    int * pTime=&time;
    int level = 0;
    int current_process = 0;
    int completed_processes = 0;
    int * pComp=&completed_processes;

    // initializing queues
    addToHP();
    // initializing queues with time_slice =0 and first_runtime=-1;
    initQueues();
    // Add all processes to the high priority queue
   // sort processes by arrival
    MLFQSortByArrival(level);
    // While there are still processes to complete
    while (completed_processes < num_processes)
    {
     int *pTTA=&(queues[level].totalTA);
     int *pTRT=&(queues[level].totalRT);

        sleep(1);
        // If the current queue is not empty
        if (checkEmpty(level))
        {
               current_process=checkPriority(time,level,true); // check if there's any process ready to be run in the mean time 
                                                               // if yes, return the index, if not return -1
                if(current_process==-1){
                    level++;
                    continue;
                }  
           if(queues[level].processes[current_process].first_runtime==-1) queues[level].processes[current_process].first_runtime=time;
            incWaitingTime(time,level,current_process,pTRT); // increment the waiting time of all the processes of the current queue with its time slice
            // check above call again
            // first we check if we're going to execute it normally  or does it has io so we move it the last of the queue
         
            if(queues[level].processes[current_process].io_time==0)  // if true , this means that it's cpu-intensive process
            {
               int ret= handleCpuIntensive(pTime,level,current_process,pComp,pTTA);
               if(ret==-1){
                level--;
                continue;
               }else{
                continue;
               }
            }
                else { // it's not cpu intensive process 
                    handleIO(pTime,level,current_process,pComp,pTTA); 
                }
        }  
    else
    {
        time++;
        level=(level+1)%3;
        current_process = 0;      
    }
    /* if (level == MAX_LEVELS)
        {
            level = 0;
            printf("Done Execution of %d Processes",MAX_PROCESSES);
            break;

        } */
    /*  if(queues[level].num_processes<=0){
            printf("\n\nQueue %d Finished Execution ....\n\n",level);
        } */
    }
   if (completed_processes==num_processes)
        {
            printf("\n\n Done Execution of %d Processes\n \n *****************************\n",MAX_PROCESSES);
            int avg_tatime=0,avg_rttime=0;
            
            for(int i=0; i<MAX_LEVELS;i++){
                avg_tatime+=queues[i].totalTA;
            }
            for(int i=0; i<MAX_LEVELS; i++){
                
                    avg_rttime+=queues[i].totalRT;
            }
            printf("\nAverage TurnAround Time Of Execution %d \nAverage ResponseTime Time Of Execution %d \n\n",avg_tatime/num_processes,avg_rttime/num_processes);
            
            return;
        }
}





