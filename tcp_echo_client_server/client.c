#include <stdio.h>
#include <stdlib.h>

#include <io.h>
#include <sys/types.h>
#include <winsock2.h>

#define BUFF_SIZE 256U

// TCP CLIENT

int main() {

  WORD wVersionRequested = MAKEWORD(2, 2);
  WSADATA wsaData;

  char message[BUFF_SIZE] = {0};
  char back_message[BUFF_SIZE] = {0};
  int string_lenght = 0;

  int client_socket = INVALID_SOCKET;
  struct sockaddr_in server_adderss;
  int send_status = 0;

  // Initialize Winsock
  if (WSAStartup(wVersionRequested, &wsaData) != 0) {
    perror("WSA Startup error");
  };

  // create socket
  client_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (client_socket == (int)INVALID_SOCKET) {
    printf("socket function failed with error: %u\n", WSAGetLastError());
    WSACleanup();
    return 1;
  }

  printf("Client socket descriptor %d created \n", client_socket);

  // specify address of the socket where we want to connect
  memset((void *)&server_adderss, 0, sizeof(server_adderss));
  server_adderss.sin_family = AF_INET;
  server_adderss.sin_port = htons(9090);
  server_adderss.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

  int connection_status =
      connect(client_socket, (struct sockaddr *)&server_adderss,
              sizeof(server_adderss));

  if (connection_status == -1) {
    printf("connection error \n");
  } else {
    printf("Connected to server socket %d", client_socket);
    while (1) {

      // get input from keyboard
      fputs("Input message(Q to quit) : ", stdout);
      fgets(message, BUFF_SIZE, stdin);

      if (!strcmp(message, "Q\n") || !strcmp(message, "q\n")) {
        break;
      }
      // send message
      send_status = send(client_socket, message, strlen(message), 0);

      if (send_status >= 0) {
        printf("Number of bytes send %d \n", send_status);
      } else {
        printf("Send error \n");
      }

      string_lenght = recv(client_socket, back_message, BUFF_SIZE - 1, 0);

      if (string_lenght >= 0) {
        back_message[string_lenght] = 0;
        printf("Message back from server : %s \n", back_message);
      } else {
        printf("Recieve failure \n");
      }
    }
  }

  closesocket(client_socket);

  return 0;
}