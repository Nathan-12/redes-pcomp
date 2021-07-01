#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Definir a porta do Servidor
#define PORT 1123

// Sockets buffers length 
#define LEN 4096

int main(int argc, char *argv[], char ip[]) {

    struct sockaddr_in server;
    int sockfd;

    int len = sizeof(server);
    int slen;

    char resposta[LEN];
    char enviada[LEN];

    char enderecoIp[20];

    fprintf(stdout, "Iniciando Cliente ...\n");

    // Cria um socket para o cliente
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error na criação do socket do cliente: ");
        return EXIT_FAILURE;
    }

    // Definindo as configurações de conexão 
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    printf("Digite o IP para realizar a conexão: ");
    fgets (enderecoIp, sizeof enderecoIp, stdin);
    printf ("IP digitado: %s\n", enderecoIp);
    server.sin_addr.s_addr = inet_addr(enderecoIp);
    memset(server.sin_zero, 0x0, 8);

     // Tentando fazer a conexão com o servidor 
    if (connect(sockfd, (struct sockaddr*) &server, len) == -1) {
        perror("Não foi possível se conectar com o servidor!");
        return EXIT_FAILURE;
    }

    printf("\n Digite '!' para encerrar conexao\n\n");
     while (true) {

        // Zerando os buffers
        memset(resposta, 0x0, LEN);
        memset(enviada, 0x0, LEN);

        fprintf(stdout, "Mande mensagem para o servidor: ");
        fgets(enviada, LEN, stdin);
        // Manda mensagem para o servidor via socket
        send(sockfd, enviada, strlen(enviada), 0);

        // Recebe a resposta do servidor
        slen = recv(sockfd, resposta, LEN, 0);
        printf("Resposta do servidor: %s\n", resposta);
            
        // Mensagem do fim da conexão
        if(strcmp(resposta, "!") == 0)
            break;
    }

    // Fecha a conexão
    close(sockfd);

    fprintf(stdout, "Conexão encerrada !\n\n");

    return EXIT_SUCCESS;
}
