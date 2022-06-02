#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define BUFF_SIZE 1024U
#define NO_REQUIRED_ARGS 3

int create_tcp_socket(void);
void bind_socket_to_port(int port_number, int socket_fd,
                         struct sockaddr_in *sock_addr);
void start_socket_listen(int socket_fd);
int accept_socket_connection(int server_fd, struct sockaddr_in *sock_addr,
                             int *addr_len);
unsigned int read_data_from_txt_file(char *destination,
                                     const char *text_file_name);

int main(int argc, char **argv) {

  int server_socket;
  int client_socket;
  unsigned int msg_size = 0;
  struct sockaddr_in server_address, client_address;
  int client_addr_size = sizeof(client_address);
  WORD wVersionRequested = MAKEWORD(2, 2);
  WSADATA wsaData;
  char buffer[BUFF_SIZE] = {0};
  char back_msg[BUFF_SIZE] = {0};
  unsigned int no_thanks_required = atoi(argv[2]);

  if (argc < NO_REQUIRED_ARGS) {
    printf("Not enough function arguments \n");
    return -1;
  }

  if (WSAStartup(wVersionRequested, &wsaData) != 0) {
    printf("WSA Startup error \n");
  };

  server_socket = create_tcp_socket();
  bind_socket_to_port(atoi(argv[1]), server_socket, &server_address);
  start_socket_listen(server_socket);
  client_socket = accept_socket_connection(server_socket, &client_address,
                                           &client_addr_size);
  msg_size = read_data_from_txt_file(buffer, "server_data.txt");
  send(client_socket, argv[2], 8, 0);
  send(client_socket, buffer, msg_size, 0);
  shutdown(client_socket, SD_SEND);

  for (size_t i = 0; i < no_thanks_required; i++) {
    msg_size = recv(client_socket, back_msg, sizeof(back_msg), 0);
    back_msg[msg_size] = 0;
    printf("%s", back_msg);
  }

  printf("Closing server \n");
  close(server_socket);

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

void bind_socket_to_port(int port_number, int socket_fd,
                         struct sockaddr_in *sock_addr) {

  int bind_result = SOCKET_ERROR;

  sock_addr->sin_family = AF_INET;
  sock_addr->sin_port = htons(port_number);
  sock_addr->sin_addr.S_un.S_addr = htonl(INADDR_ANY);

  bind_result =
      bind(socket_fd, (struct sockaddr *)sock_addr, sizeof(*sock_addr));

  if (SOCKET_ERROR == bind_result) {
    printf("Error while binding a socket to port \n");
  } else {
    printf("Socket %d binded to port %d \n", socket_fd, port_number);
  }
  return;
}

void start_socket_listen(int socket_fd) {
  int listen_result;

  listen_result = listen(socket_fd, 5);

  if (SOCKET_ERROR == listen_result) {
    printf("Error while starting listening \n");
  } else {
    printf("Listening... \n");
  }

  return;
}

int accept_socket_connection(int server_fd, struct sockaddr_in *sock_addr,
                             int *addr_len) {
  int accept_result = INVALID_SOCKET;

  accept_result = accept(server_fd, (struct sockaddr *)sock_addr, addr_len);

  if ((int)INVALID_SOCKET == accept_result) {
    printf("Error while accepting socket \n");
  } else {
    printf("Accepted client %d \n", accept_result);
  }

  return accept_result;
}

unsigned int read_data_from_txt_file(char *destination,
                                     const char *text_file_name) {
  FILE *fp;
  unsigned int count = 0;

  fp = fopen(text_file_name, "r");
  count = fread(destination, sizeof(char), BUFF_SIZE, fp);

  printf("%d character read \n", count);

  fclose(fp);

  return count;
}