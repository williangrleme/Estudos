#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct aluno{
    char nome[30];
    char idade[3];
    char cod_matricula[10];
    char curso[20];
}aluno;

aluno estudante;
int contt,contb;

void Write(int op){
char c;

FILE *arquivo;
        if(arquivo == NULL){
        printf("nao conseguiu abrir o arquivo\n");
}

else {
do {
    if(op==1){  //inserindo em texto
        arquivo = fopen("Texto.txt","a+");
        fflush(stdin);
        printf("Nome:\n");
        gets(estudante.nome);
        strcat(estudante.nome,"\n");
        fputs(estudante.nome,arquivo);
        fclose(arquivo); 

        arquivo = fopen("Texto.txt","a+");
        fflush(stdin);
        printf("Idade:\n");
        gets(estudante.idade);
        strcat(estudante.idade,"\n");
        fputs(estudante.idade,arquivo);
        fclose(arquivo); 

        arquivo = fopen("Texto.txt","a+");
        fflush(stdin);
        printf("Codigo de matricula:\n");
        gets(estudante.cod_matricula);
        strcat(estudante.cod_matricula,"\n");
        fputs(estudante.cod_matricula,arquivo);
        fclose(arquivo); 

        arquivo = fopen("Texto.txt","a+");
        fflush(stdin);
        printf("Curso:\n");
        gets(estudante.curso);
        strcat(estudante.curso,"\n");
        fputs(estudante.curso,arquivo);
        fclose(arquivo); 
        contt++;

    }  

    else if(op==2){ //inserindo em binario
    arquivo = fopen("Binario.txt","ab+"); 
    fflush(stdin);
    printf("Nome:\n");
    gets(estudante.nome);
    strcat(estudante.nome,"\n");
    fflush(stdin);

    printf("Idade:\n");
    gets(estudante.idade);
    strcat(estudante.idade,"\n");
    fflush(stdin);

    printf("Codigo de matricula::\n");
    gets(estudante.cod_matricula);
    strcat(estudante.cod_matricula,"\n");
    fflush(stdin);

    printf("Curso:\n");
    gets(estudante.curso);
    strcat(estudante.curso,"\n");
    fflush(stdin);

    fwrite(&estudante,sizeof(aluno),1,arquivo);
    contb++;
    fclose(arquivo);
    getch();
    }

    fflush(stdin);
    printf("deseja continuar inserindo(s/n)?\n");
    scanf("%c",&c);
}while(c != 'n');
}
}

void pesquisar(int op){
    FILE *arquivo;
    char nome[30],linha[40];
    aluno aux;
    int i,x=0;

    if(op == 1){
        arquivo = fopen("Texto.txt", "r");
        if(arquivo == NULL){
            printf("nao conseguiu abrir\n"); 
        }
        else {
        fflush(stdin);
        printf("Nome a pesquisar:\n");
        gets(nome);
        strcat(nome,"\n");
    
        for(i=0; i <contt*4; i++){
            fgets(linha,40,arquivo);
            if(strcmp(nome,linha) == 0){
                printf("Encontrado na linha %d\n",i);
                x = 1;
            }
        }
    }
        if(x==0) {printf("Nao encontrado\n");}
    }
    else if(op == 2){
        arquivo = fopen("Binario.txt","rb");
        if(arquivo == NULL){
            printf("Nao conseguiu abrir\n");
        }
        else {
            fflush(stdin);
            printf("Nome a pesquisar\n");
            gets(nome);
            strcat(nome,"\n");
        }
        
        for(i=0;i<contb;i++){
            if(fread(&aux, sizeof(aluno),1,arquivo) != 1){
                if(feof(arquivo)){
                    break;
                }
            }
            if(strcmp(aux.nome,nome) == 0){
                printf("Encontrado no bloco %d\n",i);
                x = 1;
            }
        }
        if (x==0){
            printf("Nao encontrado\n");
        }
    }
    fclose(arquivo);
    getch();
}

int main (){
    contt = 0;
    contb = 0;

    int op,op2;
    do {
         printf("1-Inserir\n2-Remover\n3-Pesquisar\n0-Sair\n");
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            printf("1- Texto\n2-Binario\n");
            scanf("%d",&op2);
            Write(op2);
            break;
        
        case 2:
        printf("Qual deseja remover?\n1- Texto\n2-Binario\n");
        scanf("%d",&op2);
        if(op2 == 1){
            remove("Texto.txt");
            contt=0;
        }
        else if(op==2){
            remove("Binario.txt");
            contb=0;
        }
            break;

        case 3:
            printf("Em qual arquivo deseja procurar?\n1- Texto\n2-Binario\n");
            scanf("%d",&op2);
            pesquisar(op2);
            break;

        default:
            break;
        }
    }while(op != 0);

    return 0;
}