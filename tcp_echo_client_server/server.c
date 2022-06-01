#include <stdio.h>
#include <stdlib.h>

#include <io.h>
#include <sys/types.h>
#include <unistd.h>
#include <winsock2.h>

#define BUFF_SIZE 256U

int main() {

  char server_msg[BUFF_SIZE] = {0};
  int result = 0;

  int server_socket = INVALID_SOCKET;
  struct sockaddr_in server_address, client_address;
  int client_address_len = sizeof(client_address);
  int client_socket;

  int string_lenght = 0;
  WORD wVersionRequested = MAKEWORD(2, 2);
  WSADATA wsaData;

  if (WSAStartup(wVersionRequested, &wsaData) != 0) {
    perror("WSA Startup error \n");
  };

  // create socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  printf("Server socket descriptor %d created \n", server_socket);

  if ((int)INVALID_SOCKET == server_socket) {
    perror("Creating socket error \n");
    return 1;
  }

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9090);
  server_address.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

  // bind socket to ip and port
  result = bind(server_socket, (struct sockaddr *)&server_address,
                sizeof(server_address));

  if (result == SOCKET_ERROR) {
    perror("Binding socket error\n");
    closesocket(server_socket);
    return 1;
  }

  if ((result = listen(server_socket, 1)) != 0) {
    perror("Listen error\n");
  }

  for (size_t i = 0; i < 5; i++) {
    client_socket = accept(server_socket, (struct sockaddr *)&client_address,
                           &client_address_len);
    printf("Client socket descriptor %d accepted \n", client_socket);

    if (client_socket == -1) {
      perror("Error accepting client socket \n");
    } else {
      printf("Client %d connected \n", i + 1);
    }

    do {
      string_lenght = recv(client_socket, server_msg, BUFF_SIZE, 0);

      if (string_lenght >= 0) {
        printf("Bytes recieved :%d \n", string_lenght);
      } else {
        printf("Recieve failure %d \n", string_lenght);
      }

      send(client_socket, server_msg, string_lenght, 0);

    } while (string_lenght != 0);

    closesocket(client_socket);
    printf("Client %d disconeccted \n", i + 1);
  }

  closesocket(server_socket);

  return 0;
}