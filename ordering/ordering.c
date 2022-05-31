#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main() {
  unsigned short host_port = 0x1234;
  unsigned long int host_ip = 0x99887766;

  printf("host address 1 0x%04X \n", host_port);
  printf("network address 1 0x%04X \n", htons(host_port));
  printf("host address 2 0x%08lX \n", host_ip);
  printf("network address 2 0x%08lX \n", htonl(host_ip));

  char *address = "255.255.255.0";
  unsigned long int add_value = inet_addr(address);
  struct in_addr hex_add;
  hex_add.S_un.S_addr = add_value;

  printf("%s internet address val : %08lX \n", address, add_value);
  printf("%08lX hex adress to human form : %s \n", add_value,
         inet_ntoa(hex_add));

  return 0;
}