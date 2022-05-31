#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <winsock2.h>

#define BUFF_SIZE 256U

// TCP CLIENT

int main() {

  int result = 0;
  WSADATA wsaData;

  // Initialize Winsock
  result = WSAStartup(MAKEWORD(2, 0), &wsaData);
  if (result != NO_ERROR) {
    printf("Error at WSAStartup()\n");
    return 1;
  }

  // create socket
  int network_socket = INVALID_SOCKET;
  network_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (network_socket == INVALID_SOCKET) {
    printf("socket function failed with error: %u\n", WSAGetLastError());
    WSACleanup();
    return 1;
  }

  // specify address of the socket
  struct sockaddr_in server_adderss;
  server_adderss.sin_family = AF_INET;
  server_adderss.sin_port = htons(9090);
  server_adderss.sin_addr.S_un.S_addr = INADDR_ANY;

  int connection_status =
      connect(network_socket, (struct sockaddr *)&server_adderss,
              sizeof(server_adderss));

  if (connection_status == -1) {
    printf("connection error \n");
  } else {
    // recieve data from server
    char server_response[BUFF_SIZE];
    recv(network_socket, server_response, sizeof(server_response), 0);

    printf("data : %s", server_response);
  }

  closesocket(network_socket);

  return 0;
}