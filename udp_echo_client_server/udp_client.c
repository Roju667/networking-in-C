#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <io.h>
#include <stdbool.h>

#define BUFF_SIZE 256U

void init_server_address(struct sockaddr_in *server_address);
bool is_message_quit(const char* message);

int main()
{
    int client_socket;
    int result = 0;
    char message[BUFF_SIZE];
    char back_message[BUFF_SIZE];
    struct sockaddr_in server_address;
    int server_address_size = sizeof(server_address);
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;

    if (WSAStartup(wVersionRequested, &wsaData) != 0)
    {
        perror("WSA Startup error");
    };

    client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    init_server_address(&server_address);

    while (1)
    {
        fputs("Insert new message(q to quit):", stdout);
        fgets(message, sizeof(message), stdin);

        result = sendto(client_socket, message, strlen(message), 0, (struct sockaddr *)&server_address, server_address_size);

        if (SOCKET_ERROR == result)
        {
            printf("Error sending a message by UDP \n ");
            break;
        }

        if (is_message_quit(message))
        {
            break;
        }

        result = recvfrom(client_socket, back_message, BUFF_SIZE, 0, (struct sockaddr *)&server_address, &server_address_size);

        if (SOCKET_ERROR == result)
        {
            printf("Error receiving message from server \n");
        }
        else
        {
            back_message[result] = 0;
            printf("echo : %s", back_message);
        }
    }

    printf("Closing a socket \n");
    closesocket(client_socket);

    return 0;
}

void init_server_address(struct sockaddr_in *server_address)
{
    memset((void *)server_address, 0, sizeof(*server_address));
    server_address->sin_addr.S_un.S_addr = inet_addr("192.168.1.6");
    server_address->sin_family = AF_INET;
    server_address->sin_port = htons(9005);

    return;
}

bool is_message_quit(const char* message)
{
    return (strcmp(message, "q\n") == 0 || strcmp(message, "Q\n") == 0);
}