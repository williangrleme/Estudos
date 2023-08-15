#include <stdio.h>
#include<stdlib.h>


typedef struct no {
	int dado;
	struct no *proximo;	
}no;

 typedef struct {
 	no *topo;
 }pilha;
 
 void criar (pilha *p){
 	p->topo=NULL;
 } 
 
 int vazia(pilha *p){
 	if (p->topo == NULL){
 		return 1;
	 }
	 else {
	 	return 0;
	 }
 }

void push (int c,pilha *p){
	no *novo;
	
	novo=(no *)malloc(sizeof(no));
	novo->proximo=NULL;
	novo->dado=c;
	
	
	if (vazia(p)){
		p->topo=novo; 
	}
	else {
	novo->proximo=p->topo;
	p->topo=novo;
	}

}

void imprimir (pilha *p){
	no *auxiliar;

	if (vazia(p)){
		printf ("pilha vazia\n");
	}
	else {
		auxiliar=p->topo;
		while (auxiliar != NULL){
			printf ("%d\n", auxiliar->dado);
			fflush(stdin);
			auxiliar=auxiliar->proximo;
		}
	
	
	}
	
}

int pop (pilha *p){
	no *auxiliar;
	int x;
	
if (vazia(p)){
	return 0;
}
else {
	auxiliar=p->topo;
	x=p->topo->dado;
	p->topo=auxiliar->proximo;
	free(auxiliar);
}
return x;
}

void ordenar(pilha *p1, pilha *p2, pilha *p3,pilha *cont){

int x,a,b;

while (p1->topo != NULL){
	x=pop(p1);
	push(x,p3);
	push(x,cont);
}

while (p2->topo != NULL){
	x=pop(p2);
	push(x,p3);
	push(x,cont);
}

 
while (cont->topo != NULL) { // até ordenar todos elementos
pop(cont);
a=pop(p3);

while (p3->topo != NULL){ 
b=pop(p3);
if (a>b){
	push(b,p2);
}
else {
	push(a,p2);
	a=b;
}
}

if (a != NULL) { // coloquei esse if porque por algum motivo ele inseria varios 0 na pilha ordenada, e colocava eles no topo como se eu tivesse inserido
push(a,p1);
}
a=pop(p2);

while (p2->topo != NULL){
b=pop(p2);
if (a>b){
	push(b,p3);
}
else {
	push(a,p3);
	a=b;
}
}
if (a != NULL) { 
push(a,p1);
}
}
printf ("Pilha ordenada:\n");
imprimir(p1);
}

void primo(pilha *p1, pilha *p2, pilha *p3){
	
int x,y,i;
int result=0;

while (p1->topo != NULL){
	x=pop(p1);
	push(x,p3);
}

while (p2->topo != NULL){
	x=pop(p2);
	push(x,p3);
}

 
while (p3->topo != NULL) { 
y=pop(p3);
result=0;

for (i=2; i <= y/2; i++){
	if (y % i == 0){
		result=result+1;
		break;
	}
}
if (result == 0){
	push(y,p2);
	push(y,p1); // pra nao perder o numero
}
else {
	push(y,p1);
}
}
printf ("Pilha apenas com numeros primos:\n");
imprimir(p2);
}





int main (){
	
int c,op,op2;

pilha *p1;
pilha *p2;
pilha *p3;
pilha *cont;


criar (&p1);
criar(&p2);
criar (&p3);
criar(&cont);

do {
	
	printf("1-Empilhar\n2-Ordenar\n3-Armazenar apenas numeros primos\n4-Imprimir\n0-Sair\n");
	scanf ("%d", &op);	
	fflush(stdin);
	
	switch (op){
		case 1:
			printf ("Deseja empilhar em qual pilha? 1 ou 2?\n");
			scanf ("%d",&op2);
			if (op2 == 1){
				printf("Digite o numero a ser empilhado:\n");
				scanf("%d",&c);
				fflush(stdin);
				push(c,&p1);
			}
			if (op2 == 2){
				printf("Digite o numero a ser empilhado:\n");
				scanf("%d",&c);
				fflush(stdin);
				push(c,&p2);
			}
			if (op2 != 1 && op2 !=2){
				printf("Comando invalido\n");
			}
			break;
		case 2:
			ordenar(&p1,&p2,&p3,&cont);
			break;
		case 3:
		primo(&p1,&p2,&p3);
			break;
		case 4:
		printf ("PILHA[1]\n");
		imprimir(&p1);
		printf ("PILHA[2]\n");
		imprimir(&p2);
		break;
		case 0:
		printf ("Ate mais :D\n");
		break;
	
		default:
			printf ("Comando invalido\n");
	}
	
}
while (op!=0);
}



