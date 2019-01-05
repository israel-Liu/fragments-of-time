// https://docs.microsoft.com/en-us/windows/desktop/procthread/using-processes-and-threads

#include <Windows.h>
#include <strsafe.h>

#include <iostream>

void CreatingProcesses(char* arg) 
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));

  // Start the child process.
  if (!CreateProcess(nullptr, arg, nullptr, nullptr, FALSE, 
                     0, nullptr, nullptr, &si, &pi)) {
    std::cout << "CreateProcess failed " << GetLastError() << ".\n";
    return;
  }

  // Wait until child process exits.
  WaitForSingleObject(pi.hProcess, INFINITE);
  // Close process and thread handles.
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
}

typedef struct tagMY_DATA
{
  int val1;
  int val2;
} MY_DATA, *PMY_DATA;

#define MAX_THREADS 3
#define BUF_SIZE 255

DWORD WINAPI MyThreadFun(LPVOID param)
{
  HANDLE std_out;
  PMY_DATA data_array;
  char msg_buf[BUF_SIZE];
  size_t cch_str_size;
  DWORD chars;

  // Make sure there is a console to receive output results.
  std_out = GetStdHandle(STD_OUTPUT_HANDLE);
  if (std_out == INVALID_HANDLE_VALUE)
    return 1;
  data_array = static_cast<PMY_DATA>(param);
  // Print the parameter values using thread-safe functions. std::cout is thread-safe ?
  StringCchPrintf(msg_buf, BUF_SIZE, "Parameters = %d, %d\n", data_array->val1, data_array->val2);
  StringCchLength(msg_buf, BUF_SIZE, &cch_str_size);
  WriteConsole(std_out, msg_buf, static_cast<DWORD>(cch_str_size), &chars, nullptr);

  return 0;
}

void CreatingThreads()
{
  PMY_DATA data_array[MAX_THREADS];
  DWORD thread_ids[MAX_THREADS];
  HANDLE thread_handles[MAX_THREADS];

  // Create MAX_THREADS worker threads.
  for (int i = 0; i < MAX_THREADS; ++i) {
    // Allocate memory for thread data.
    data_array[i] = static_cast<PMY_DATA>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MY_DATA)));
    if (data_array[i] == nullptr) {
      ExitProcess(2);
    }

    // Generate unique data for each thread to work with.
    data_array[i]->val1 = i;
    data_array[i]->val2 = i + 100;

    // Create the thread to begin execution on its own.
    thread_handles[i] = CreateThread(nullptr, 0, MyThreadFun, data_array[i], 0, &thread_ids[i]);
    if (thread_handles == nullptr) {
      std::cout << "CreateThreads failed " << GetLastError() << ".\n";
      ExitProcess(3);
    }
  }

  // Wait until all threads have terminated.
  WaitForMultipleObjects(MAX_THREADS, thread_handles, TRUE, INFINITE);

  // Close all thread handles and free memory allocations.
  for (int i = 0; i < MAX_THREADS; ++i) {
    CloseHandle(thread_handles[i]);
    if (data_array != nullptr) {
      HeapFree(GetProcessHeap(), 0, data_array[i]);
      data_array[i] = nullptr;
    }
  }

  return;
}

int main(int argc, char* argv[])
{
  //CreatingProcesses(argv[1]);
  CreatingThreads();

  return 0;
}