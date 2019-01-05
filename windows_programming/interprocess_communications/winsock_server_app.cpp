#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// https://docs.microsoft.com/en-gb/windows/desktop/WinSock/winsock-server-application

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
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;
  // Resolve the server address and port
  result = getaddrinfo(nullptr, DEFAULT_PORT, &hints, &res);
  if (result != 0) {
    std::cout << "getaddrinfo failed : " << result << "\n";
    WSACleanup();
    return 1;
  }

  // To create a socket for the server
  SOCKET listen_socket = INVALID_SOCKET;
  listen_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (listen_socket == INVALID_SOCKET) {
    std::cout << "Error at socket() : " << WSAGetLastError() << "\n";
    freeaddrinfo(res);
    WSACleanup();
    return 1;
  }

  // To bind a socket
  result = bind(listen_socket, res->ai_addr, (int)res->ai_addrlen);
  freeaddrinfo(res); // No longer needed address information
  if (result == SOCKET_ERROR) {
    std::cout << "bind failed with error : " << WSAGetLastError() << "\n";
    closesocket(listen_socket);
    WSACleanup();
    return 1;
  }

  // To listen on a socket
  if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR) {
    std::cout << "listen failed with error : " << WSAGetLastError() << "\n";
    closesocket(listen_socket);
    WSACleanup();
    return 1;
  }
  
  // To accept a connection on a socket
  SOCKET client_socket = INVALID_SOCKET;
  client_socket = accept(listen_socket, nullptr, nullptr);
  if (client_socket == INVALID_SOCKET) {
    std::cout << "accept failed : " << WSAGetLastError() << "\n";
    closesocket(listen_socket);
    WSACleanup();
    return 1;
  }

  // To receive and send data on a socket
  int recv_buflen = DEFAULT_BUFLEN, send_result;
  char recv_buf[DEFAULT_BUFLEN];
  do 
  {
    result = recv(client_socket, recv_buf, recv_buflen, 0);
    if (result > 0) {
      std::cout << "Bytes received : " << result << "\n";
      // Echo the buffer back to the sender
      if (send_result = send(client_socket, recv_buf, result, 0) == SOCKET_ERROR) {
        std::cout << "send failed : " << WSAGetLastError() << "\n";
        closesocket(client_socket);
        WSACleanup();
        return 1;
      }
      std::cout << "Bytes send : " << send_result << "\n";
    } else if (result == 0) {
      std::cout << "Connection closing... \n";
    } else {
      std::cout << "recv failed : " << WSAGetLastError() << "\n";
      closesocket(client_socket);
      WSACleanup();
      return 1;
    }
  } while (result > 0);

  // Disconnecting the Server
  if (shutdown(client_socket, SD_SEND) == SOCKET_ERROR) {
    std::cout << "shutdown failed : " << WSAGetLastError() << "\n";
    closesocket(client_socket);
    WSACleanup();
    return 1;
  }

  // Cleanup
  closesocket(client_socket);
  WSACleanup();

  return 0;
}