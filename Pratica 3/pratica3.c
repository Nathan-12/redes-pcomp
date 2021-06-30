/* rode o servidor, e implemente um código cliente para conectar-se ao servidor e 
enviar todos os caracteres digitados no socket */
/* O cliente não deve mostrar na tela os caracteres digitados, apenas os caracteres que 
receber do servidor. O cliente deve encerrar quando for digitado um '!' */
/* Servico de Eco */
/* para compilar: gcc pratica3-eco.c -o pratica3-eco */
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

/* AULAS REMOTAS: envie o código do programa cliente criado para arthur@ufc.br com o 
assunto PRATICA 3. No corpo do e-mail indique o passo-a-passo de como o programa deve ser compilado.
Caso você tenha feito o programa em Windows, anexe também o programa executável 
compilado e todas as bibliotecas necessárias a sua execução. Só corrigirei a prática cujos arquivos
anexados estiverem abaixo de 1MB. É necessário que o usuário possa passar 
(no programa ou por linha de comando) o IP do servidor para conectar sem precisar recompilar. */