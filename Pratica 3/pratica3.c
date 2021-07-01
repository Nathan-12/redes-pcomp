#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void) {
 struct sockaddr_in info;
 int socket_entrada, socket_conexao;
 char mensagem; int tamanho_estrutura;
 socket_entrada = socket(AF_INET, SOCK_STREAM, 0);
 if(socket_entrada < 0) { printf("Vixe!\n"); exit(1); }
 info.sin_family = AF_INET;
 info.sin_port = htons(1123);
 info.sin_addr.s_addr = INADDR_ANY;
 tamanho_estrutura = sizeof(info);
 if(bind(socket_entrada, (struct sockaddr *)&info, tamanho_estrutura)==0) {
  while(1) {
   listen(socket_entrada, 30);
   socket_conexao = accept(socket_entrada, (struct sockaddr *)&info, &tamanho_estrutura);
   mensagem='.';
   while(mensagem!='!') { // Finaliza conexão se mensagem é um "!"
    read(socket_conexao, &mensagem, 1);
    write(socket_conexao, &mensagem, 1);
   }
   close(socket_conexao);
  }
 } else { printf("Vixe! Nao deu para vincular endereco ou porta!\n"); exit(1); }
 return(0);
}