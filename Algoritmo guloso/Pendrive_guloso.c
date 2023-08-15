#include <stdio.h>
// criterio guloso = pegar os arquivos de menor tamanho parece ser a solução otima

int bubble(int x , int v[x]){
	int i, j, aux;
	 for (i = 1; i < x; i++) {  
 for (j = 0; j < x - 1; j++) {         
            if (v[j] > v[j + 1]) {
                aux      = v[j];   
                v[j]     = v[j + 1];
                v[j + 1] = aux;
				}
            }
			}
}

void organizando (int tamanho, int vet[],int c){
    int cont = 0;
    bubble(c,vet);
    while (tamanho != 0 && tamanho > vet[cont]){
        tamanho = tamanho - vet[cont];
        cont++;
    }
    printf ("A quantidade maxima de arquivos suportados no pendrive eh: %d",cont);
} 

int main (){

    int c,tamanhopendrive,cont,tamanhoarquivo;

    printf ("Digite o tamanho do pendrive em Kbytes\n");
    scanf("%d",&tamanhopendrive);
    printf ("Digite a quantidade de arquivos:\n");
    scanf("%d",&c);
    int vet[c];
    printf("Digite o tamanho de cada arquivo:\n");
    for (cont = 0; cont < c; cont++){
        scanf("%d",&tamanhoarquivo);
        vet[cont] = tamanhoarquivo;
    }
    organizando(tamanhopendrive,vet,c);


    //coloquei 1000kytes pro pendrive e testei com as 6 entradas do slide (deu 5 arquivos) ksksks
}