#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h> 
#include <stdbool.h>
#include <string.h>
#include <errno.h>


const int MAX=1000;
void getCurrentRunningProcess(){
   const char* path="/proc";
    DIR *folder;
    int files=0; // num of files in proc
    struct dirent *entry; // directory entry to read entries in  from dir
    folder=opendir(path);
     if(folder == NULL)
    {
        puts("Unable to read directory");
        return;
    }
    int PIDS[MAX];
      while( (entry=readdir(folder)) ) // reading current pids in proc and storing them
    {
        files++;
        if(files>=65){  // starting to save after 65 iteration , to start where the processes are..
            int enti=atoi(entry->d_name);  // checking if the name of the process is valid
            if(enti!=0){
              PIDS[files-65]=enti; // 
            }
        }
    }
    bool flag=false; // flag to be used in case the file couldn't be open , we won't close the dir  twice
    for(int i=0; i<files-65; i++){
            int pid=PIDS[i];
            char filename[1000];
            sprintf(filename, "/proc/%d/stat", pid);
            FILE *f = fopen(filename, "r");
            if(f==NULL){
              closedir(folder);
                flag=true;
                break;
                }
            char comm[2050];
            char state;
            int ppid;
           fscanf(f, "%d %s %c %d", &pid, comm, &state, &ppid);
            if(state==82){
                printf("               %d\n",pid);
                printf("******************************* \n");
                printf("Process ID = %d\n", pid);
                printf("COMM = %s\n", comm);
                printf("State = %c\n", state);
                printf("Parent PID = %d\n", ppid);
                 printf("******************************* \n");
                fclose(f);
                continue;

            }else {
              fclose(f);
            }
           } 
        if(flag)return; // checking flag  so we won't close dirptr twice
       closedir(folder);
    return;
}

void main(){
  
while(1){
  sleep(1);
  getCurrentRunningProcess();
}    

}

