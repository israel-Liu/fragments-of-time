
#include <windows.h>

#include <iostream>

void UsingFileMapping()
{
  HANDLE file = ::CreateFileW(L"fmtest.txt",
                             GENERIC_READ | GENERIC_WRITE,
                             0, nullptr, CREATE_ALWAYS,
                             FILE_ATTRIBUTE_NORMAL, nullptr);

  if (file == INVALID_HANDLE_VALUE) {
    std::cout << L"File is nullptr" << std::endl;
    return;
  }

  HANDLE map_file = ::CreateFileMapping(file, nullptr,
                                        PAGE_READWRITE,
                                        0, 1024, nullptr);

  if (map_file == NULL) {
    std::cout << L"Map file is nullptr, Last error is %d : " << GetLastError() << L"\n";
    return;
  }

  LPVOID map_address = ::MapViewOfFile(map_file, FILE_MAP_ALL_ACCESS,
                                       0, 0, 1024);

  if (map_address == NULL) {
    std::cout << L"Map Address is nullptr, Last error is %d : " << GetLastError() <<  L"\n";
    return;
  }

  std::cout << map_address << L"\n";

  UnmapViewOfFile(map_address);
  CloseHandle(file);
}