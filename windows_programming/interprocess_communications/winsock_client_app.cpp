#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// https://docs.microsoft.com/en-gb/windows/desktop/WinSock/winsock-client-application

#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27051"
#define DEFAULT_BUFLEN 512

int main(int argc, char* argv[]) {
  WSADATA wsa_data;
  // Initialize Winsock
  int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
  if (result != 0) {
    std::cout << "WSAStartup failed : " << result << "\n";
    return 1;
  }

  struct addrinfo* res = nullptr, hints;
  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  // Resolve the server address and port
  result = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &res);
  if (result != 0) {
    std::cout << "getaddrinfo failed : " << result << "\n";
    WSACleanup();
    return 1;
  }

  // To create a socket
  SOCKET connect_socket = INVALID_SOCKET;
  struct addrinfo* ptr = res;
  connect_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
  if (connect_socket == INVALID_SOCKET) {
    std::cout << "Error at socket() : " << WSAGetLastError() << "\n" ;
    freeaddrinfo(res);
    WSACleanup();
    return 1;
  }

  // To connect to a socket
  if (connect(connect_socket, ptr->ai_addr, (int)ptr->ai_addrlen) == SOCKET_ERROR) {
    std::cout << "connect to a socket failed : " << WSAGetLastError() << "\n";
    closesocket(connect_socket);
    connect_socket = INVALID_SOCKET;
    return 1;
  }

  freeaddrinfo(res);
  if (connect_socket == INVALID_SOCKET) {
    std::cout << "Unable to connect to server! \n";
    WSACleanup();
    return 1;
  }

  // Sending and Receiving Data on the Client
  int recv_buflen = DEFAULT_BUFLEN;
  char* send_buf = "first socket client app";
  char recv_buf[DEFAULT_BUFLEN];
  if (result = send(connect_socket, send_buf, (int)strlen(send_buf), 0) == SOCKET_ERROR) {
    std::cout << "send failed : " << WSAGetLastError() << "\n";
    closesocket(connect_socket);
    WSACleanup();
    return 1;
  }
  std::cout << "Bytes send : " << result << "\n";
  if (result = shutdown(connect_socket, SD_SEND) == SOCKET_ERROR) {
    std::cout << "shutdown send failed : " << WSAGetLastError() << "\n";
    closesocket(connect_socket);
    WSACleanup();
    return 1;
  }

  // Receive data until the server closes the connection
  do 
  {
    result = recv(connect_socket, recv_buf, recv_buflen, 0);
    if (result > 0) std::cout << "Bytes received : " << result << "\n";
    else if (result == 0) std::cout << "Connection closed \n";
    else std::cout << "recv failed : " << WSAGetLastError() << "\n";
  } while (result > 0);

  // Disconnecting the Client
  if (shutdown(connect_socket, SD_SEND) == SOCKET_ERROR) {
    std::cout << "shutdown failed : " << WSAGetLastError() << "\n";
    closesocket(connect_socket);
    WSACleanup();
    return 1;
  }

  // Cleanup
  closesocket(connect_socket);
  WSACleanup();

  return 0;
}