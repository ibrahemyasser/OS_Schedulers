#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <wchar.h>


void PSList() {
    printf("\nRunning Processes\n");
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32* processInfo = new PROCESSENTRY32;
    processInfo->dwSize = sizeof(PROCESSENTRY32);
    int index = 0;

    while (Process32Next(hSnapShot, processInfo) != FALSE)
    {
	   printf("\n***********************************************");
	   printf("\n\t\t\t%d", ++index);
	   printf("\n***********************************************");
	   printf("\nParent Process ID: %lu" , processInfo->th32ParentProcessID);
	   printf("\nProcess ID: %d" , processInfo->th32ProcessID);
	   wprintf(L"\nName: %ls", processInfo->szExeFile);
	   printf("\nCurrent Threads: %d", processInfo->cntThreads);
	   //printf << endl << "Size: " << processInfo->dwSize;
	   printf("\nPrimary Class Base: %d", processInfo->pcPriClassBase);
    }

    CloseHandle(hSnapShot);
    printf("\n");
    printf("\n***********************************************");
    printf("\n\n");

    int processID;
    HANDLE hProcess;
    int choice;
    do {
	   printf("\nEnter 1 to Delete Process or 0 to exit: ");
	   scanf_s("%d", &choice);
	   if (choice) {
		  printf("\nEnter Process ID to terminate that process: ");
		  scanf_s("%d", &processID);
		  hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, processID);
		  if (hProcess == NULL || hProcess == INVALID_HANDLE_VALUE)
		  {
			 printf("Unable to get handle of process: %d" , processID);
			 //printf << "\tError is: " << GetLastError();
		  }
		  else
			 TerminateProcess(hProcess, 0);

		  delete processInfo;
	   }
    }
	   while (choice);
    }

int main()
{
    PSList();
    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
