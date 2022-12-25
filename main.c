#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE_LENGTH 100
#define REALLY_BIG_NUM 400

#define SJF_NUM         1
#define FCFS_NUM        2
#define SRTF_NUM        3
#define MLFQ            4
#define RR_NUM          5

int sch_choose;
char c;
// Define a struct to hold the data for each process
typedef struct {
    int     process_id;
    char    process_name[MAX_LINE_LENGTH];
    int     arrival_time;
    int     CPU_time ;
    int     execution_time;
    int     remaining_time;
    int     IO_time;
    int     IO_start_time;
    char    process_status[MAX_LINE_LENGTH] ;
    int     first_runtime;
    int     waiting_time;
    int     turnAround_time;
    int     response_time;
    char    pro_specifier[MAX_LINE_LENGTH];
} Process;

typedef struct {
  int start_time;
  int end_time;
} ProcessGantt;


void SJF_Scheduler(Process *processes, int n);
void SJF_sortProcesses(Process *processes, int n);
void SJF_printResults(Process *processes, int n);

void FCFS_Scheduler(Process *processes, int n);
void MLFQ_Scheduler(Process *processes,int n);
void SRTF_Scheduler(Process *processes, int n);
void RR_Scheduler(Process *processes, int n);
double calculateResponseTime(Process *processes, int n,int scheduler);
double calculateTurnaroundTime(Process *processes, int n,int scheduler);
void choose_scheduler(Process *processes, int n);
void getIntegerOnly(int *ptr);
int comparator(const void *a, const void *b);
void FCFS_sortProcesses(Process *processes, int n);

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
        processes[i].remaining_time = processes[i].CPU_time;
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
void FCFS_Scheduler(Process *processes, int n)
{
    FCFS_sortProcesses(processes,n);
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
void SJF_Scheduler(Process *processes, int n)
{
    printf("\nShortest Job first assumes that all processes arrive at the same time.\n");
    SJF_sortProcesses(processes, n);
    double avrage_turn = calculateTurnaroundTime(processes,n,SJF_NUM);
    double avrage_res=calculateResponseTime(processes,n,SJF_NUM);

    SJF_printResults(processes, n);
    printf("average of Turnaround time=%0.2f\n",avrage_turn);
    printf("average of Response time=%0.2f\n",avrage_res);
}

void SRTF_Scheduler(Process *processes, int n)
{

ProcessGantt gantt[MAX_LINE_LENGTH];
int proc_name[REALLY_BIG_NUM];
int io[REALLY_BIG_NUM] = {0}; 
int num_processes = n;
  // Sort the processes by arrival time
  qsort(processes, num_processes, sizeof(Process), comparator);

  // Initialize the current time to 0 and the number of remaining processes to the total number of processes
  int current_time = 0;
  int remaining_processes = num_processes;

  // Initialize the Gantt chart
  for (int i = 0; i < num_processes; i++) {
    gantt[i].start_time = -1;
    gantt[i].end_time = -1;
  }

  // Run the scheduling algorithm until all processes have completed
  while (remaining_processes > 0) {
    int next_process = -1;
    int shortest_remaining_time = INT_MAX;

    // Find the process with the shortest remaining time
    int old_proc;
    for (int i = 0; i < num_processes; i++) {
      if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time && processes[i].remaining_time < shortest_remaining_time) {
        next_process = i;
        shortest_remaining_time = processes[i].remaining_time;
      }
    }

        printf("Time %d: ", current_time);
    if (next_process == -1) {
      printf("CPU idle\n");
    } else {
      printf("Process %s running\n", processes[next_process].process_name);
      proc_name[current_time] = processes[next_process].process_id;
    }


    // Run the next process for one time unit
    if (next_process != -1) {
      if (gantt[next_process].start_time == -1) {
        gantt[next_process].start_time = current_time;
      }
      processes[next_process].remaining_time--;
      current_time++;

    
/*
//-------------------------------- UNCOMMENT THIS BLOCK IF U WANT TO SEE TIME OF I/O TAKE NOT INCLUDED AND MAKE A CONTEXT SWITCH------------------


      // Check if the current process has an I/O operation at this time
    if (processes[next_process].IO_start_time  == current_time - gantt[next_process].start_time) {
      for (int i = 0; i < processes[next_process].IO_time; i++,x++) {
          printf("Time %d: Process %s waiting for I/O\n",current_time, processes[next_process].process_name);

            //current_time++; //uncomment for making the IO take a time slice and not make any context switching

          io[current_time] = -1;
          //break;
        }
      }
*/

//-------------------------------- UNCOMMENT THIS BLOCK TO SEE THE TIME OF I/O TAKE AND MAKE A CONTEXT SWITCH------------------

      int x = current_time;
    if (processes[next_process].IO_start_time  == current_time - gantt[next_process].start_time) {
      for (int i = 0; i < processes[next_process].IO_time; i++,x++) {
          printf("Time %d: Process %s waiting for I/O\n", x, processes[next_process].process_name);
            //current_time++; //uncomment for making the IO take a time slice and not make any context switching
          io[current_time] = -1;
          //break;
        }
      }





      // If the process has completed, update its waiting and turn-around times and end time in the Gantt chart
      if (processes[next_process].remaining_time == 0) {
        remaining_processes--;
        processes[next_process].turnAround_time = current_time - processes[next_process].arrival_time;
        processes[next_process].waiting_time = processes[next_process].turnAround_time - processes[next_process].CPU_time;
        gantt[next_process].end_time = current_time;
      }
    } else {
      // If there are no processes to run, increment the current time
      current_time++;
    }
  }
/*
  // Print the Gantt chart
  printf("Gantt chart:\n");
  for (int i = 0; i < num_processes; i++) {
    for (int j = gantt[i].start_time; j < gantt[i].end_time; j++) {
      printf("|");
    }
  }
  printf("\n");
*/
  // Calculate the average waiting and turn-around times
  float total_waiting_time = 0;
  float total_turnAround_time = 0;
  for (int i = 0; i < num_processes; i++) {
    total_waiting_time += processes[i].waiting_time;
    total_turnAround_time += processes[i].turnAround_time;
  }
  float average_waiting_time = total_waiting_time / num_processes;
  float average_turnAround_time = total_turnAround_time / num_processes;


    for (size_t i = 0; i < current_time; i++)
    {
        int tempo = proc_name[i];
        int tempio = io[i];
        if(tempio == -1){
            printf(" IO ");
        }
        printf("%s|",processes[tempo - 1].process_name);
    }

  // Print the results
  printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurn-Around Time\n");
  for (int i = 0; i < num_processes; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, processes[i].arrival_time, processes[i].CPU_time, processes[i].waiting_time, processes[i].turnAround_time);
  }
  printf("Average waiting time: %.2f\n", average_waiting_time);
  printf("Average turn-around time: %.2f\n", average_turnAround_time);



}

void MLFQ_Scheduler(Process *processes,int n)
{

}
void RR_Scheduler(Process *processes, int n)
{

}

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


// Function to compare two processes based on their remaining time
int comparator(const void *a, const void *b) {
  Process *p1 = (Process *)a;
  Process *p2 = (Process *)b;
  return p1->arrival_time - p2->arrival_time;
}