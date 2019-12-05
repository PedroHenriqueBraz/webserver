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



#define PORT 8082 //porta do servidor 



int main(int argc, char const *argv[])

{

    int server_fd; //socket file descriptor

    int new_socket;

    long value_read;

    struct sockaddr_in address; 

    int addrlen = sizeof(address);



    char *msg = "msg do servidor";



    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))== 0)  //criando socket tcp/ip

    {

        perror("In socket");

        exit(EXIT_FAILURE);

    }

    

    address.sin_family = AF_INET;

    address.sin_addr.s_addr = INADDR_ANY;

    address.sin_port = htons(PORT);

    

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)

    {

        perror("In bind");

        exit(EXIT_FAILURE);

    }

    if (listen(server_fd, 10) < 0)

    {

        perror("In listen");

        exit(EXIT_FAILURE);

    }

    while(1)

    {

        printf("\n+++++ Aguardando conexao ++++++++\n\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  // cria socket especifico para conexao

        {

            perror("In accept");

            exit(EXIT_FAILURE);

        }

        
        char buffer[30000] = {0};

        value_read = read( new_socket , buffer, 30000);

        printf("%s\n",buffer );

        write(new_socket , msg , strlen(msg));

        printf("------------------Mensagem enviada para o cliente-------------------\n");

        close(new_socket);

    }

    return 0;

}

