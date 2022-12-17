#include <windows.h>
#include <tlhelp32.h>
#include <iostream>	
#include <string>

using namespace std;

void PSList() {
    cout << "\nRunning Processes\n";
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32* processInfo = new PROCESSENTRY32;
    processInfo->dwSize = sizeof(PROCESSENTRY32);
    int index = 0;

    while (Process32Next(hSnapShot, processInfo) != FALSE)
    {
	   cout << endl << "***********************************************";
	   cout << endl << "\t\t\t" << ++index;
	   cout << endl << "***********************************************";
	   cout << endl << "Parent Process ID: " << processInfo->th32ParentProcessID;
	   cout << endl << "Process ID: " << processInfo->th32ProcessID;
	   wcout << endl << "Name: " << processInfo->szExeFile;
	   cout << endl << "Current Threads: " << processInfo->cntThreads;
	   //cout << endl << "Size: " << processInfo->dwSize;
	   cout << endl << "Primary Class Base: " << processInfo->pcPriClassBase;
    }

    CloseHandle(hSnapShot);
    cout << endl;
    cout << endl << "***********************************************";
    cout << endl << endl;

    int processID;
    HANDLE hProcess;
    int choice;
    do {
	   cout << "\nEnter 1 to Delete Process or 0 to exit: ";
	   cin >> choice;
	   if (choice) {
		  cout << endl << "Enter Process ID to terminate that process: ";
		  cin >> processID;
		  hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, processID);
		  if (hProcess == NULL || hProcess == INVALID_HANDLE_VALUE)
		  {
			 cout << "Unable to get handle of process: " << processID;
			 //cout << "\tError is: " << GetLastError();
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
