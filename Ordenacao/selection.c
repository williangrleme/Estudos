#include<stdio.h>
#include <stdlib.h>

int selection(int x , int v[x]){
	int i, j, min, aux;
	for (i = 0; i < x; i++) { 
 	min=i;
 for (j = i + 1; j < x ; j++) {  
            if (v[j] < v[min]) {
            	min=j;
				}
				}
               if(min != i){
 				aux = v[min];
 				v[min] = v[i];
 				v[i] = aux;
				}		
            }
} 
int main ()
{
int x, i,c;	
    printf("insira o tamanho do vetor:\n");
	scanf("%d", &x);
	int v[x];
    printf("insira valores no vetor\n");
	for (i = 0; i < x; i++)
  {
      scanf("%d",&c);
      v[i] = c;
  }
    printf ("desordenado:\n");
  	for (i = 0; i < x; i++)
  {
   printf("%d ", v[i]); 
  }

printf("\n");   
selection(x,v);
printf("ordenado:\n");   

	for (i = 0; i < x; i++) 
  {
   printf("%d ", v[i]);
  }
}
