// https://docs.microsoft.com/en-gb/windows/desktop/Sync/using-synchronization

#include <Windows.h>

#include <iostream>

#pragma comment(lib, "User32.lib")

typedef struct tagMY_DATA
{
  char* text;
  DWORD value;
} MY_DATA;

#define _SECOND 10000000

VOID CALLBACK TimerAPCProc(LPVOID arg, DWORD, DWORD)
{
  MY_DATA* data = static_cast<MY_DATA*>(arg);
  std::cout << "Message: " << data->text << "\nValue: " << data->value << "\n\n";
  MessageBeep(0);
}

void WaitableTimerAPC()
{
  HANDLE timer;
  __int64 due_time;
  LARGE_INTEGER li_due_time;
  MY_DATA data;
  data.text = "This is my data";
  data.value = 100;

  timer = CreateWaitableTimer(nullptr, FALSE, "MyTimer");
  if (timer != nullptr) {
    __try {
      // Create an integer that will be used to signal the timer 5 seconds from now.
      due_time = -5 * _SECOND;
      // Copy the relative time into a LARGE_INTEGER.
      li_due_time.LowPart = static_cast<DWORD>(due_time & 0xFFFFFFFF);
      li_due_time.HighPart = static_cast<LONG>(due_time >> 32);

      BOOL success = SetWaitableTimer(timer, &li_due_time, 2000, TimerAPCProc, &data, FALSE);
      if (success) {
        for ( ; data.value < 1000; data.value += 100)
          SleepEx(INFINITE, TRUE);
      } else {
        std::cout << "SetWaitableTimer failed with error: " << GetLastError() << "\n";
      }
    } __finally {
      CloseHandle(timer);
    }
  }
}

int main(int argc, char* agrv[])
{
  WaitableTimerAPC();

  return 0;
}