#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <winsock2.h>

#define BUFF_SIZE 256U

int main() {

  char server_msg[BUFF_SIZE] = "connected to the server";
  int result = 0;

  // init server_socket descriptor
  unsigned int server_socket = INVALID_SOCKET;
  // create socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (server_socket == INVALID_SOCKET) {
    perror("Creating socket error");
    return 1;
  }

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9090);
  server_address.sin_addr.S_un.S_addr = INADDR_ANY;

  // bind socket to ip and port
  result = bind(server_socket, (struct sockaddr *)&server_address,
                sizeof(server_address));

  if (result == SOCKET_ERROR) {
    perror("Binding socket error");
    closesocket(server_socket);
    return 1;
  }

  if ((result = listen(server_socket, 1)) != 0) {
    perror("Listen error");
  }

  int client_socket;
  client_socket = accept(server_socket, NULL, NULL);

  send(client_socket, server_msg, sizeof(server_msg), 0);

  close(server_socket);

  return 0;
}