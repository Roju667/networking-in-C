#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define BUFF_SIZE 1024U
#define THANKS_BUFF_SIZE 8U
#define NO_REQUIRED_ARGS 3

int create_tcp_socket(void);
void connect_to_server(int client_socket, int port_number, char *server_ip,
                       struct sockaddr_in *server_address);
unsigned int receive_amount_of_thanks(int client_socket);
void receive_file(int client_socket, char *destination, size_t dest_size);
void send_appreciation(int client_socket, unsigned int no_thanks);

int main(int argc, char **argv) {

  int client_socket;
  unsigned int no_thanks = 0;
  struct sockaddr_in server_address;
  WORD wVersionRequested = MAKEWORD(2, 2);
  WSADATA wsaData;
  char back_msg[BUFF_SIZE] = {0};

  if (argc < NO_REQUIRED_ARGS) {
    printf("Not enough function arguments \n");
    return -1;
  }

  if (WSAStartup(wVersionRequested, &wsaData) != 0) {
    printf("WSA Startup error \n");
  }

  client_socket = create_tcp_socket();
  connect_to_server(client_socket, atoi(argv[1]), argv[2], &server_address);
  no_thanks = receive_amount_of_thanks(client_socket);
  receive_file(client_socket, back_msg, sizeof(back_msg));
  send_appreciation(client_socket, no_thanks);

  close(client_socket);
  return 0;
}

int create_tcp_socket(void) {

  int socket_fd = INVALID_SOCKET;

  socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if ((int)INVALID_SOCKET == socket_fd) {
    printf("Error while creating a socket \n");
  } else {
    printf("Socket %d created \n", socket_fd);
  }

  return socket_fd;
}

void connect_to_server(int client_socket, int port_number, char *server_ip,
                       struct sockaddr_in *server_address) {
  int connect_result = SOCKET_ERROR;

  printf("port : %d ip: %s \n", port_number, server_ip);

  server_address->sin_addr.S_un.S_addr = inet_addr(server_ip);
  server_address->sin_family = AF_INET;
  server_address->sin_port = htons(port_number);

  connect_result = connect(client_socket, (struct sockaddr *)server_address,
                           sizeof(*server_address));

  if (SOCKET_ERROR == connect_result) {
    printf("Error while connecting to server \n");
  } else {
    printf("Connected to server \n");
  }

  return;
}

unsigned int receive_amount_of_thanks(int client_socket) {

  int no_bytes = 0;
  unsigned int no_thanks = 0;
  char thanks_buff[THANKS_BUFF_SIZE] = {0};

  no_bytes = recv(client_socket, thanks_buff, sizeof(thanks_buff), 0);

  if (SOCKET_ERROR == no_bytes) {
    printf("Error receving number of thank yous \n");
    return 0;
  }

  no_thanks = atoi(thanks_buff);
  return no_thanks;
}

void receive_file(int client_socket, char *destination, size_t dest_size) {

  int no_bytes = 0;

  no_bytes = recv(client_socket, destination, dest_size, 0);

  if (SOCKET_ERROR == no_bytes) {
    printf("Error receving file \n");
  } else {
    printf("Received : %s", destination);
  }

  return;
}

void send_appreciation(int client_socket, unsigned int no_thanks) {

  int send_result = SOCKET_ERROR;

  for (size_t i = 0; i < no_thanks; i++) {
    send_result =
        send(client_socket, "Thank you \n", strlen("Thank you \n"), 0);

    if (SOCKET_ERROR == send_result) {
      printf("Error sending a thank you \n");
    } else {
      printf("Sending Thanks \n");
    }
  }

  return;
}