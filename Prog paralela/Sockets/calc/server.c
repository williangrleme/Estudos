#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#define BUFFER_SIZE 1024
#define FIM_TRANSMISSAO "by"
#define PORTA_LOCAL 2020

//Exibe uma mensagem de erro e termina o programa
void msg_err_exit(char *msg) {
fprintf(stderr, msg);
printf("Erro: %i", WSAGetLastError());
system("PAUSE");
exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	
int Socket = 0;
int message_length = 0;
unsigned short remote_port = 0;
char *aux1, *aux2,*aux3;
char r[20];
int n1, n2, op,result;
char message[BUFFER_SIZE];
struct sockaddr_in localAddr;
struct sockaddr_in remoteAddr;
int remoteAddrSize = sizeof(remoteAddr);

WSADATA wsa_data;
//inicia o Winsock 2.0 (DLL)
if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0)
msg_err_exit("WSAStartup() falhou!\n");
//criando o socket local para o servidor
Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
if (Socket==INVALID_SOCKET) { //Se ocorreu erro na criacao do socket
WSACleanup();
msg_err_exit("socket(): Erro ao criar socket!\n");
}

//zera a estrutura local_address
memset(&localAddr, 0, sizeof(localAddr));
localAddr.sin_family = AF_INET; //internet address family
localAddr.sin_port = htons(PORTA_LOCAL); //porta local
localAddr.sin_addr.s_addr=htonl(INADDR_ANY);//assume endereço local
//interligando o socket com o endereço (local)-registrando no Sistema

if (bind(Socket, (struct sockaddr *) &localAddr,
sizeof(localAddr)) ==
SOCKET_ERROR){
WSACleanup();
closesocket(Socket);
msg_err_exit("bind(): Erro ao fazer o bind\n");
}
printf("Aguardando Cliente...\n");

do {
//limpa o buffer
//recebe a mensagem do cliente
message_length = recvfrom(Socket, message,
BUFFER_SIZE, 0, (struct
sockaddr *) &remoteAddr, &remoteAddrSize);
if(message_length == SOCKET_ERROR)
msg_err_exit("recvfrom(): Erro ao receber mensagem\n");

if ((strcmp(message, FIM_TRANSMISSAO))!=0) { //se nao recebeu um by 
//processa a mensagem recebida

aux1 = strtok(message, "|");
aux2 = strtok(NULL, "|");
aux3 = strtok(NULL, "|");

n1 = atoi(aux1);
n2 = atoi(aux2);
op = atoi(aux3);

switch(op){
case 1:
	result = n1+ n2;
	break;
case 2:
	result = n1 - n2;
	break;
case 3:
	result = n1/n2;
	break;
case 4:
	result = n1*n2;
	break;
default:
	break;
}
sprintf(r, "%d", result);
//exibe a mensagem na tela
printf("\nCliente>> %s + %s\n", aux1,aux2);
strcpy(message, "RESPOSTA = ");
strcat(message, r);
printf("\nVoce>> %s\n", message);
////entrada da mensagem
// printf("Voce>> ");
// memset(&message, 0, BUFFER_SIZE);
// fflush(stdin);
// gets(message);
// fflush(stdin);
//envia p/ cliente
message_length = strlen(message);
if (sendto(Socket, message, message_length, 0,
(struct sockaddr
*)&remoteAddr,
sizeof(remoteAddr))==SOCKET_ERROR) {
WSACleanup();
closesocket(Socket);
msg_err_exit("sendto() failed\n");
}
}
else
printf("\nCliente>> %s\n", message);
} while(strcmp(message, FIM_TRANSMISSAO));//sai quando receber ou enviar um by
printf("Encerrando...\n");
WSACleanup();
closesocket(Socket);
system("PAUSE");
return 0;
}//Fim main
