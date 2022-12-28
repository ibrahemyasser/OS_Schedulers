#include "../inc/header.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


void SRTF_Scheduler(Process *processes, int n)
{

ProcessGantt gantt[MAX_LINE_LENGTH];
//int proc_name[REALLY_BIG_NUM];
//int io[REALLY_BIG_NUM] = {0}; 
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
      //proc_name[current_time] = processes[next_process].process_id;
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
/*
      int x = current_time;
    if (processes[next_process].IO_start_time  == current_time - gantt[next_process].start_time) {
      for (int i = 0; i < processes[next_process].IO_time; i++,x++) {
          printf("Time %d: Process %s waiting for I/O\n", x, processes[next_process].process_name);
            //current_time++; //uncomment for making the IO take a time slice and not make any context switching
          io[current_time] = -1;
          //break;
        }
      }

*/



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

/*
    for (size_t i = 0; i < current_time; i++)
    {
        int tempo = proc_name[i];
        int tempio = io[i];
        if(tempio == -1){
            printf(" IO ");
        }
        printf("%s|",processes[tempo - 1].process_name);
    }
*/
  // Print the results
  printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurn-Around Time\n");
  for (int i = 0; i < num_processes; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, processes[i].arrival_time, processes[i].CPU_time, processes[i].waiting_time, processes[i].turnAround_time);
  }
  printf("Average waiting time: %.2f\n", average_waiting_time);
  printf("Average turn-around time: %.2f\n", average_turnAround_time);



}

// Function to compare two processes based on their remaining time
int comparator(const void *a, const void *b) {
  Process *p1 = (Process *)a;
  Process *p2 = (Process *)b;
  return p1->arrival_time - p2->arrival_time;
}