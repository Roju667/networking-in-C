#include <stdio.h>
#include <winsock2.h>

#include <io.h>
#include <stdlib.h>
#include <sys/types.h>

#define BUFF_SIZE 256

int main() {
  int server_socket;
  struct sockaddr_in server_address, client_address;
  int client_address_size = 0;
  int result = 0;
  int str_lenght = 0;
  char msg_recieved[BUFF_SIZE] = {0};

  memset(&server_address, 0, sizeof(server_address));
  memset(&client_address, 0, sizeof(client_address));

  server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if ((int)INVALID_SOCKET == server_socket) {
    printf("Error while creating a server socket \n");
  } else {
    printf("Server socket created, descriptor %d \n", server_socket);
  }

  server_address.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9005);

  result = bind(server_socket, &server_address, sizeof(server_address));

  if (0 != result) {
    printf("Error while binding a socket to a port \n");
  } else {
    printf("Binding OK \n");
  }

  while (1) {

    str_lenght =
        recvfrom(server_socket, msg_recieved, BUFF_SIZE, 0,
                 (struct sockaddr *)&client_address, &client_address_size);

    if (strcmp("q\n", msg_recieved) == 0 || strcmp("Q\n", msg_recieved) == 0) {

      result = sendto(server_socket, "Closing echo server \n",
                      strlen("Closing echo server \n"), 0,
                      (struct sockaddr *)&client_address, client_address_size);
      break;
    } else {
      result = sendto(server_socket, msg_recieved, str_lenght, 0,
                      (struct sockaddr *)&client_address, client_address_size);
    }

    if (SOCKET_ERROR == result) {
      printf("Error sending an UDP msg \n");
    }
  }

  closesocket(server_socket);

  return 0;
}