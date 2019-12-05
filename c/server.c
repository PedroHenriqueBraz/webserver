// criar o socket 
// identificar o socket
// esperar por uma conexao
// responder request
// fechar socket

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PORT 8082

int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    long value;
    struct sockaddr_in address; 
    int addrlen = sizeof(address);

    char *hello = "Hello from server";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))== 0)
    {
        peeror("In socket");
        exit(EXIT_FAILURE);
    }
}