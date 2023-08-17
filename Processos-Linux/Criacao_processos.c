#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//srand((unsigned)time(NULL));
//x = rand()%90;

int px = 1;

typedef struct processo{
    char USER[50];
    char NOME[50];
    int PPID,PID,UID,GID; 
    int NI,PRI;
    float MEM,CPU;
    char STAT;
    struct processo *prox;
    struct arvore *proxAR;
}processo;

typedef struct arvore{
    struct processo *raiz;
}arvore;

void criar(arvore *a){
    a->raiz = NULL;
}

void inicializacao (arvore *a){

    processo *systemd;
    systemd = malloc(sizeof(processo));

    strcpy(systemd->NOME, "Systemd");
    strcpy(systemd->USER, "Kernel");

    systemd->UID = 1;
    systemd->PID = px;
    systemd->PPID = 1;
    systemd->GID = 0;
    systemd->NI = -12;
    systemd->PRI = 20 + systemd->NI;
    systemd->STAT = 'r';
    systemd->MEM = 0.0;
    systemd->CPU = 0.0;
    systemd->prox = NULL;
    systemd->proxAR = NULL;

    a->raiz = systemd;
}

void fork(processo *pai, arvore *a){
    
    processo *filho;
    arvore *a1;
    filho = malloc(sizeof(processo));
    strcpy(filho->NOME, pai->NOME);
    strcpy(filho->USER,pai->USER);

    filho->UID = pai->UID;
    filho->PID = ++px;
    filho->PPID = pai->PID;
    filho->GID = pai->GID;
    filho->NI = pai->NI;
    filho->PRI = pai->PRI;
    filho->STAT = pai->STAT;
    filho->MEM = pai->MEM;
    filho->CPU = pai->CPU;
    filho->prox = NULL;
    filho->proxAR = NULL;

    if(pai->proxAR == NULL){    //se o processo n tiver a arvore de filhos dele
        a1 = malloc(sizeof(arvore));
        a1->raiz = filho;
        pai->proxAR = a1;
    }
    else {          //se ja tem filho
        processo *aux2;
        aux2 =  pai->proxAR->raiz; //raiz da arvore de filhos
        while(aux2->prox != NULL){  //acha lugar pro irmao
            aux2= aux2->prox;
        }
        aux2->prox = filho;
    }

}

void top (arvore *a){

    processo *aux = a->raiz;

    printf(" ----------------------------------------------------------------------------\n");
    printf("|NOME|    |PID|   |PPID|  |USER| |UID| |GID| |NI|  |PRI|  |CPU|  |MEM|  |STAT|   \n");
    printf(" ----------------------------------------------------------------------------\n");
    func(aux);

}

void func(processo *aux){
    printf("%s    %d        %d     %s   %d     %d    %d     %d    %.1f    %.1f     %c\n",aux->NOME,aux->PID,aux->PPID, aux->USER,aux->UID,aux->GID,aux->NI,aux->PRI,aux->CPU, aux->MEM,aux->STAT);
        if(aux->proxAR != NULL){
            funca(aux->proxAR);
        }
        if (aux->prox != NULL){
            func(aux->prox);
        }
}

void funca(arvore *a){
    printf("%s    %d        %d     %s   %d     %d    %d     %d    %.1f    %.1f     %c\n",a->raiz->NOME,a->raiz->PID,a->raiz->PPID, a->raiz->USER,a->raiz->UID,a->raiz->GID,a->raiz->NI,a->raiz->PRI,a->raiz->CPU, a->raiz->MEM,a->raiz->STAT);
        if(a->raiz->proxAR != NULL){
            funca(a->raiz->proxAR);
        }
        if(a->raiz->prox != NULL){
            func(a->raiz->prox);
        }
}

processo* busca(processo *a,int id){
    processo *aux;
    aux = a;
    if(aux->PID==id)
    {
        return aux;
    }
    else {
    if(aux->proxAR != NULL && aux->proxAR->raiz->PID <= id){
        return busca(aux->proxAR->raiz,id);
    }
     if(aux->prox != NULL && aux->prox->PID <= id){
        return busca(aux->prox,id);
        }
    }   
    printf("AAA %d\n",aux->PID);
    return NULL;
}

void criacao_processos(arvore *a)
{
    processo *aux;
    int id;
    printf("PID do processo a sofrer o fork();\n");
    scanf("%d",&id);
    aux = busca(a->raiz,id);
    if(aux != NULL){
        fork(aux,a);   
    }
    else {
        printf("PID nao encontrado\n");
    }
}

int main (){
    arvore a;  
    criar (&a);
    int op = 1;

    inicializacao(&a);
    printf("-------------------------\n");
    printf("1-Criacao de processos\n2-Top ()\n0-Sair\n");
    printf("------------------------- \n");

    while(op != 0){
        scanf("%d",&op);
        switch (op)
        {
    case 1:
        criacao_processos(&a);
        break;

    case 2:
        top(&a);
        break;

    default:
        break;
        }
    }
    return 0;
}

