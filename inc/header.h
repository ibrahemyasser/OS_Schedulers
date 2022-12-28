#include <stdbool.h>
#ifndef HEADER_H_
#define HEADER_H_

#define MAX_SIZE 100
#define MAX_LINE_LENGTH 100
#define REALLY_BIG_NUM 400
#define MAX_PROCESSES 10
#define MAX_LEVELS 3


#define SJF_NUM         1
#define FCFS_NUM        2
#define SRTF_NUM        3
#define MLFQ            4
#define RR_NUM          5

#define QUANTUM         2
// Define a struct to hold the data for each process
extern int num_processes;

typedef struct {
    int     process_id;
    char    process_name[MAX_LINE_LENGTH];
    int     arrival_time;
    int     CPU_time ;
    int     execution_time;
    int     remaining_time;
    int     burst_time;
    int     io_time;
    int     io_completion_time;
    int     IO_time;
    int     IO_start_time;
    char    process_status[MAX_LINE_LENGTH] ;
    int     first_runtime;
    int     waiting_time;
    int     turnAround_time;
    int     response_time;
    char    pro_specifier[MAX_LINE_LENGTH];
    int     end_time;    
    int     time_slice; 
    int     turnaround_time;                            
    bool    completed ; 
    bool    holder; 
} Process;

typedef struct queue
{
    Process processes[MAX_PROCESSES];
    int num_processes;
    int quantum;
    int totalTA;
    int totalRT;
} queue_t;



typedef struct {
  int start_time;
  int end_time;
} ProcessGantt;

typedef struct {
    int maxSize;
    Process queArray[MAX_SIZE];
    int nProcs;
    int front;
    int rear;
    int tmp;
    int time;
    int no_completed;
} CircularPriorityQ;

// Priority queue functions
void    insert(CircularPriorityQ *q, Process roc);
Process pop(CircularPriorityQ *q);
Process peekMin(CircularPriorityQ *q);
bool    isEmpty(CircularPriorityQ *q);
bool    isFull(CircularPriorityQ *q);
void    display(CircularPriorityQ *q);
void    Queue_Init(void);

void SJF_Scheduler(Process *processes, int n);
void SJF_sortProcesses(Process *processes, int n);
void SJF_printResults(Process *processes, int n);
void SJF_IO_Handler(Process *processes, int n);

void FCFS_Scheduler(Process *processes, int n);

void MLFQ_Scheduler(Process *processes,int n);
void handleIO(int *time,int level,int current_process, int *completed_processes,int *turnaround_time);
int handleCpuIntensive(int *time,int level,int current_process,int *completed_processes,int *turnaround_time);
void incWaitingTime(int time, int level,int current_process,int *response_time);
int checkEmpty(int level);
void initQueues();
void addToHP(Process *processes);
int checkPriority(int t,int level ,bool current);
void MLFQSortByArrival(int level);

void SRTF_Scheduler(Process *processes, int n);
void RR_Scheduler(Process *processes, int n);
double calculateResponseTime(Process *processes, int n,int scheduler);
double calculateTurnaroundTime(Process *processes, int n,int scheduler);
void choose_scheduler(Process *processes, int n);
void getIntegerOnly(int *ptr);
int comparator(const void *a, const void *b);
void FCFS_sortProcesses(Process *processes, int n);
void run(Process *processes ,CircularPriorityQ *q,Process proc);
bool dec1sec(Process *processes,CircularPriorityQ *q,int n);
void ftime(CircularPriorityQ *q);
void decnonzero(CircularPriorityQ *q);
void RR_printResults(Process *processes, int n);
#endif