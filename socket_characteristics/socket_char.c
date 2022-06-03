#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main(void) {
  int tcp_sock;
  int udp_sock;
  int sock_type;
  int buff_size;
  int opt_len = sizeof(sock_type);
  int state;

  WORD wVersionRequested = MAKEWORD(2, 2);
  WSADATA wsaData;

  if (WSAStartup(wVersionRequested, &wsaData) != 0) {
    printf("WSA Startup error \n");
  };

  tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
  udp_sock = socket(AF_INET, SOCK_DGRAM, 0);

  printf("tcp socket : %d \n", SOCK_STREAM);
  printf("udp socket : %d \n", SOCK_DGRAM);

  state =
      getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, (char *)&sock_type, &opt_len);
  if (state != 0) {
    printf("Error reading state \n");
  } else {
    printf("Socket type tcp : %d \n", sock_type);
  }

  state =
      getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, (char *)&sock_type, &opt_len);
  if (state != 0) {
    printf("Error reading state \n");
  } else {
    printf("Socket type udp : %d \n", sock_type);
  }

  state =
      getsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, (char *)&buff_size, &opt_len);
  if (state != 0) {
    printf("Error reading state \n");
  } else {
    printf("Transfer buffer size : %d \n", buff_size);
  }

  state =
      getsockopt(tcp_sock, SOL_SOCKET, SO_RCVBUF, (char *)&buff_size, &opt_len);
  if (state != 0) {
    printf("Error reading state \n");
  } else {
    printf("Receive buffer size : %d \n", buff_size);
  }

  buff_size = 2222;

  state = setsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, (char *)&buff_size,
                     sizeof(buff_size));
  if (state != 0) {
    printf("Error reading state \n");
  }

  buff_size = 4545;

  state = setsockopt(tcp_sock, SOL_SOCKET, SO_RCVBUF, (char *)&buff_size,
                     sizeof(buff_size));
  if (state != 0) {
    printf("Error reading state \n");
  }

  state =
      getsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, (char *)&buff_size, &opt_len);
  if (state != 0) {
    printf("Error reading state \n");
  } else {
    printf("Transfer buffer new size : %d \n", buff_size);
  }

  state =
      getsockopt(tcp_sock, SOL_SOCKET, SO_RCVBUF, (char *)&buff_size, &opt_len);
  if (state != 0) {
    printf("Error reading state \n");
  } else {
    printf("Receive buffer new size : %d \n", buff_size);
  }

  return 0;
}
