// TODO: identificar o request http (ex: get de uma pagina html) 
// e devolver conteudo com status code correto

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PORT 8082 //porta do servidor 

int main(int argc, char const *argv[])
{


    int server_socket_fd; //socket file descriptor
    int new_socket;
    long value_read;
    struct sockaddr_in address; 
    int addrlen = sizeof(address);

    char *msg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length:12\n\nTeste nova msg";

    if ((server_socket_fd = socket(AF_INET, SOCK_STREAM, 0))== 0)  //criando socket tcp/ip
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    // associar o socket criado a um endereco e porta
    if (bind(server_socket_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);

    }

    if (listen(server_socket_fd, 10) < 0)  // comecar a escutar por conexoes, podendo deixar ate 10 conexoes aguardando na fila
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        printf("\n+++++ Aguardando conexao ++++++++\n\n");

        if ((new_socket = accept(server_socket_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  // cria socket especifico para conexao
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        value_read = read( new_socket , buffer, 30000);  //recebe request do cliente
        printf("%s\n",buffer );
        write(new_socket , msg , strlen(msg)); //envia msg para cliente

        printf("------------------Mensagem enviada para o cliente-------------------\n");

        close(new_socket);

    }

    return 0;

}

