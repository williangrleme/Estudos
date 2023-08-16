#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int TAM,px;
char escolha;

typedef struct bloco {
	int tamanho;
	int id;
	int freq;
	struct bloco *prox;
}bloco;

typedef	struct {
	bloco *ini;
	bloco *fim;
}fila;

void criar(fila *principal)
{
	principal->ini = NULL;
	principal->fim = NULL;
}

void alocar(fila *principal, fila *secundaria ,int x,int id, int fr)		//Quando tem espaco na memoria principal pra inserir o bloco
{
	TAM = abs(TAM-x);
	bloco *novo = (bloco *) malloc(sizeof(bloco));
	novo->prox = NULL;
	novo->id = id;
	novo->freq = fr;
	
	if(principal->ini == NULL){			// primeira leva
		principal->ini = novo;
		principal->fim = novo;

		if(x<=4){	//coube de primeira
			novo->tamanho = x;	
			novo->id = id;
			novo->freq = fr;		
		}
		else {		//caso precise alocar mais de um bloco para o dado
		novo->tamanho = 4;
		novo->freq = fr;
		x = abs(x-4); 	//valor que vai pros outros blocos
			while(x > 0){	// ate achar lugar pro dado ser inserido
			bloco *novo2 = (bloco *) malloc(sizeof(bloco));		
			novo2->prox = NULL;
			if(x<=4){	//coube
				novo2->tamanho = x;
				novo2->id = id;
				novo2->freq = fr;
				x = -1;
			}
			else{	//deu ruim
				novo2->tamanho = 4;
				novo2->id = id;
				novo2->freq = fr;
				x = abs(x-4);
			}
			principal->fim->prox = novo2;
			principal->fim = novo2;
		}
		}
	}

	else {		// a fila n ta vazia dai busca um lugar pra alocar o programa
	bloco *aux = principal->ini;
	int i=0,c=x;
	while(aux != NULL){	//contando os blocos
		i = i+4;
		aux = aux->prox;
	}
	while (c>0){		//evitando de ter mais blocos do que o tamanho permite
		if(c<=4){
			c = -1;
			continue;
		}
		else{
			c = c-4;
			i = i+4;
		}
	}
	if(i<px){	//tem bloco sobrando
		if(x<=i){	//cabe nos blocos sobrando
			if(x<=4){	//ocupa 1 bloco
				novo->tamanho = x;
				novo->id = id;
				novo->freq = fr;
				principal->fim->prox = novo;
				principal->fim = novo;
			}
			else {
				novo->tamanho = 4;
				novo->id = id;
				novo->freq = fr;
				principal->fim->prox = novo;
				principal->fim = novo;

				x = abs(x-4);
				while(x>0){		//alocando novos blocos ate caber
					bloco *novo2 = (bloco *) malloc(sizeof(bloco));
					novo2->prox = NULL;
					if(x<=4){
						novo2->tamanho = x;
						novo2->freq = fr;
						novo2->id = id;
						x = -1;
					}
					else{
						novo2->tamanho = 4;
						novo2->freq = fr;
						novo2->id = id;
						x = abs(x-4);
					}
					principal->fim->prox = novo2;
					principal->fim = novo2;
				}
			}
		}
	}
	else {
	printf("Metodo de SWAP:\nF- FIFO\nL- RANDOM\nW- LFU\n");
	fflush(stdin);
	scanf("%c",&escolha);
	swap(principal,secundaria,x,id,fr);
	}
	}
}

int inserir_FIFO(fila *principal, int c,int id,int freq)
{
	bloco *novo = (bloco *) malloc(sizeof(bloco));
	novo->tamanho = c;
	novo->id = id;
	novo->freq = freq;
	novo->prox = NULL;
	
	if(!novo) return 0;
	
	if(principal->ini == NULL) {principal->ini = novo;
	principal->fim = novo;}
	else principal->fim->prox = novo;
	principal->fim = novo;	
	return 1;

}

int remover_FIFO(fila *principal)
{	
	bloco *aux;
	if (principal->ini == NULL){
		printf("Tabela vazia\n");
	}
	
	aux = principal->ini;
	int x = aux->id;
	principal->ini = aux->prox;
	if (principal->ini == NULL)
		principal->fim = NULL;
	free(aux);
	return x;
}

void imprimir(fila *principal)
{
	bloco *aux;
	aux = principal->ini;
	if (principal->ini == NULL){
		printf("Tabela vazia\n");
	} else {
		while(aux!=NULL){
		printf("Programa %d |%dkB| Numero de acessos: |%d|\n",aux->id, aux->tamanho,aux->freq);
		aux = aux->prox;
	}
	}
	printf("\n");
}

void esvaziar (fila *principal){
	bloco *aux = principal->ini;
	bloco *aux2;
	while(aux != NULL){
		aux2 = aux->prox;
		free(aux);
		aux = aux2;
	}
	principal->ini = NULL;
	principal->fim = NULL;
	TAM = px;
}

void joga_na_secundaria(fila *principal,fila *secundaria,int id){
	bloco *aux = principal->ini;
	bloco *aux2,*aux3;
	aux2 = aux;

	while(aux->id != id && aux != NULL){	//ate achar o programa
		aux2 = aux;
		aux = aux->prox;
	} 

	while(aux->id == id && aux != NULL){	// ate tirar o programa da ram
		if(aux == principal->ini){		//caso seja o primeiro
		inserir_FIFO(secundaria,aux->tamanho,aux->id,aux->freq);
		TAM = TAM+principal->ini->tamanho;
		remover_FIFO(principal);
		if(principal->ini == NULL){continue;}	// evitando que aux aponte pra um endereco que foi removido
		else{aux = aux->prox;}
		}
		else {
			if(aux != principal->fim){	//caso n esteja no fim
				inserir_FIFO(secundaria,aux->tamanho,aux->id,aux->freq);
				aux3 = aux;
				aux2->prox = aux->prox;
				aux = aux->prox;
				TAM = TAM+aux3->tamanho;
				free(aux3);
				
			}
			else {		//caso esteja
			aux2->prox = NULL;
			principal->fim = aux2;
			inserir_FIFO(secundaria,aux->tamanho,aux->id,aux->freq);
			TAM = TAM + aux->tamanho;
			free(aux);
			break;
			}
		}
	}
}

void aleatorio(fila *principal, fila *secundaria){
int i=0,x;
bloco *aux = principal->ini;
while(aux != NULL){		//contando quantos blocos tem
	i++;
	aux = aux->prox;
} 

srand( (unsigned)time(NULL));
x = rand()%i;

printf("ID: %d\n",x);
joga_na_secundaria(principal,secundaria,x);
}

void LFU(fila *principal, fila *secundaria){

	bloco *aux = principal->ini;
	int menor = aux->freq;
	int i=0;
	while(aux != NULL){
		if(aux->freq < menor){
			menor = aux->freq;
			i = aux->id;
		}
		aux = aux->prox;
	}
	aux = principal->ini;
	while(aux->id != i && aux != NULL){
		aux = aux->prox;
	}
	joga_na_secundaria(principal,secundaria,i);
}

void swap (fila *principal, fila *secundaria,int x,int id,int fr){
switch (escolha)
{
case 'f':
		joga_na_secundaria(principal,secundaria,principal->ini->id);	//liberando primeiro espaco
		while(x>0){
			bloco *novo = (bloco *) malloc(sizeof(bloco));
			novo->prox = NULL;
			novo->id = id;
			novo->freq = fr;
			if(x<=4){
				novo->tamanho = x;
				novo->freq = fr;
				x=-1;
			}
			else{
				novo->tamanho = 4;
				novo->freq = fr;
				x = x-4;
				joga_na_secundaria(principal,secundaria,principal->ini->id);
			}
			if(principal->ini == NULL) principal->ini = novo;
			else principal->fim->prox = novo;
			principal->fim = novo;
		}
	break;

	case 'l':
	aleatorio(principal,secundaria);
	while(x>0){
			bloco *novo = (bloco *) malloc(sizeof(bloco));
			novo->prox = NULL;
			novo->id = id;
			novo->freq = fr;
			if(x<=4){
				novo->tamanho = x;
				novo->freq = fr;
				x=-1;
			}
			else{
				novo->tamanho = 4;
				novo->freq = fr;
				x = x-4;
				joga_na_secundaria(principal,secundaria,principal->ini->id);
			}
			if(principal->ini == NULL) principal->ini = novo;
			else principal->fim->prox = novo;
			principal->fim = novo;
		}
	break;

	case 'w':
	LFU(principal,secundaria);
	while(x>0){
			bloco *novo = (bloco *) malloc(sizeof(bloco));
			novo->prox = NULL;
			novo->id = id;
			novo->freq = fr;
			if(x<=4){
				novo->tamanho = x;
				novo->freq = fr;
				x=-1;
			}
			else{
				novo->tamanho = 4;
				novo->freq = fr;
				x = x-4;
				joga_na_secundaria(principal,secundaria,principal->ini->id);
			}
			if(principal->ini == NULL) principal->ini = novo;
			else principal->fim->prox = novo;
			principal->fim = novo;
		}
	break; 
}
}

void sp (fila *principal,fila *secundaria,int id){	//// mover da segundaria pra primaria
	bloco *aux = secundaria->ini;
	bloco *aux2,*aux3;

	while(aux->id != id && aux != NULL){
		aux2 = aux;
		aux = aux->prox;
	}
	aux3 = aux;
	while (aux->id == id){
		alocar(principal,secundaria,aux->tamanho,aux->id,aux->freq);
		aux = aux->prox;
	}
	aux = aux3;

	while(aux->id == id && aux != NULL){	// ate tirar o programa da ram
		if(aux == secundaria->ini){		//caso seja o primeiro
		remover_FIFO(secundaria);
		if(secundaria->ini == NULL){continue;}	// evitando que aux aponte pra um endereco que foi removido
		else{aux = aux->prox;}
		}
		else {
			if(aux != secundaria->fim){	//caso n esteja no fim
				aux3 = aux;
				aux2->prox = aux->prox;
				aux = aux->prox;
				free(aux3);
				
			}
			else {		//caso esteja
			aux2->prox = NULL;
			secundaria->fim = aux2;
			free(aux);
			break;
			}
		}
	}	
}

void fechar_prog (fila *f, int id,int y){
	bloco *aux = f->ini, *aux2,*aux3;

	while(aux->id != id && aux != NULL){
		aux2 = aux;
		aux = aux->prox;
	}

	while(aux->id == id && aux != NULL){	// ate tirar o programa da fila
		if(aux == f->ini){		//caso seja o primeiro
		if(y==1){
			TAM = TAM + aux->tamanho;
		}
		remover_FIFO(f);
		if(f->ini == NULL){continue;}	// evitando que aux aponte pra um endereco que foi removido
		else{aux = aux->prox;}
		}
		else {
			if(aux != f->fim){	//caso n esteja no fim
				if(y==1){
				TAM = TAM + aux->tamanho;
				}
				aux3 = aux;
				aux2->prox = aux->prox;
				aux = aux->prox;
				free(aux3);
				
			}
			else {	
			if(y==1){
			TAM = TAM + aux->tamanho;
			}	
			aux2->prox = NULL;
			f->fim = aux2;
			free(aux);
			break;
			}
		}
	}	
}

int main (){

fila principal;
fila secundaria;

criar(&principal);
criar(&secundaria);

int x,fr,cont=0,y;
escolha = 'p';
printf ("digite o tamanho da memoria em kBytes\n");
scanf ("%d",&TAM);
px = TAM;

while (escolha != 'e'){
	printf ("a- Alocar memoria\nb- Limpar memorias\nc- Inserir da secundaria para a primaria\nd- Fechar programa\ne- Sair\n");
	fflush(stdin);
	scanf("%c",&escolha);
	y=0;
	switch (escolha)
	{
		case 'a':
			printf("Tamanho do programa %d: \n",cont);
			scanf("%d",&x);
			if(x>px){
				printf("|----Tamanho de programa nao suportado----|\n");
				return 0;
			}
			fflush(stdin);
			srand( (unsigned)time(NULL));
			fr = 1 + (rand()%100);
			alocar(&principal,&secundaria,x,cont,fr);
			printf("\nTamanho disponivel na memoria principal: %d\n",TAM);
			printf("Blocos memoria principal:\n");
			imprimir(&principal);
			printf("Blocos memoria secundaria:\n");
			imprimir(&secundaria);
			cont++;
		break;

		case 'b':
			esvaziar(&principal);
			esvaziar(&secundaria);
			imprimir(&principal);
			imprimir(&secundaria);
			cont = 0;
		break;

		case 'c':
		printf ("Programa a ser movido:\n");
		scanf("%d",&x);	
		sp(&principal,&secundaria,x);
		printf("\nTamanho disponivel na memoria principal: %d\n",TAM);
		printf("Blocos memoria principal:\n");
		imprimir(&principal);
		printf("Blocos memoria secundaria:\n");
		imprimir(&secundaria);
		break;

		case 'd':
		printf("De qual memoria vc deseja fechar o programa?\n1-PRIMARIA  2-SECUNDARIA\n");
		scanf("%d",&x);
		if(x == 1){
			printf("Programa a ser fechado:\n");
			scanf("%d",&x);
			y=1;
			fechar_prog(&principal,x,y);
		}
		else if(x == 2){
			printf("Programa a ser fechado:\n");
			scanf("%d",&x);
			fechar_prog(&secundaria,x,y);
		}
		printf("\nTamanho disponivel na memoria principal: %d\n",TAM);
		printf("Blocos memoria principal:\n");
		imprimir(&principal);
		printf("Blocos memoria secundaria:\n");
		imprimir(&secundaria);
		break;
	}
}
    return 0;
}