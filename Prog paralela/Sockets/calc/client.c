#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#define BUFFER_SIZE 1024
#define PORTA_SERVIDOR 2020
#define FIM_TRANSMISSAO "by"

/* Exibe uma mensagem de erro e termina o programa */
void msg_err_exit(char *msg) {
fprintf(stderr, msg);
system("PAUSE");
exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	
int Socket = 0;
char remote_ip[32];
int message_length = 0;
unsigned short remote_port = 0;
char num1[20], num2[20],op[20];
char message[BUFFER_SIZE];
struct sockaddr_in localAddr;
struct sockaddr_in remoteAddr;
int remoteAddrSize = sizeof(remoteAddr);


WSADATA wsa_data;
//inicia o Winsock 2.0 (DLL)
if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0)
msg_err_exit("WSAStartup() falhou!\n");
printf("IP do servidor: ");
fflush(stdin);
scanf("%s", remote_ip);
fflush(stdin);

//criando o socket local para o servidor
Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
if (Socket==INVALID_SOCKET) { //Se ocorreu erro na criacao do socket
WSACleanup();
msg_err_exit("socket(): Erro ao criar socket!\n");
}
// preenchendo o remoteAddr (servidor)
memset(&remoteAddr, 0, sizeof(remoteAddr));
remoteAddr.sin_family = AF_INET;
remoteAddr.sin_addr.s_addr = inet_addr(remote_ip);
remoteAddr.sin_port = htons(PORTA_SERVIDOR);

do {
//limpa o buffer
memset(&message, 0, BUFFER_SIZE);
printf("\nVoce>> Primeiro numero = ");
fflush(stdin);
gets(num1);
fflush(stdin);
printf("Voce>> Segundo numero = ");
fflush(stdin);
gets(num2);
fflush(stdin);
printf("Operacao:\n1-soma\n2-subtracao\n3-divisao\n4-multiplicacao\n");
fflush(stdin);
gets(op);
fflush(stdin);

//verifica se n�o houve o pedido de fim de transmiss�o
if(strcmp(num1, FIM_TRANSMISSAO) == 0 || strcmp(num2,
FIM_TRANSMISSAO) == 0 ){
strcpy(message, FIM_TRANSMISSAO);
}
else{
//concatenando "num1|num2" na mensagem
strcpy(message, num1);
strcat(message, "|");
strcat(message, num2);
strcat(message, "|");
strcat(message, op);
}
message_length = strlen(message);
//envia a mensagem para o servidor
if (sendto(Socket, message, message_length, 0, (struct
sockaddr
*)&remoteAddr, sizeof(remoteAddr))==SOCKET_ERROR) {
WSACleanup();
closesocket(Socket);
msg_err_exit("sendto() failed\n");
}
//recebe a mensagem do servidor
if ((strcmp(message, FIM_TRANSMISSAO))!=0) {
//limpa o buffer
memset(&message, 0, BUFFER_SIZE);
message_length = recvfrom(Socket, message,
BUFFER_SIZE, 0,
(struct sockaddr *) &remoteAddr,
&remoteAddrSize);
if(message_length == SOCKET_ERROR)
msg_err_exit("recvfrom(): Erro ao receber mensagem\n");
//exibe a mensagem na tela
printf("\nServidor>> %s\n", message);
}
} while(strcmp(message, FIM_TRANSMISSAO)); //sai quando enviar ou receber um "by"
printf("Encerrando...\n");
WSACleanup();
closesocket(Socket);
system("PAUSE");
return 0;
}//Fim mai
