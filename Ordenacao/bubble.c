#include<stdio.h>
#include <stdlib.h>


int bubble(int x , int v[x]){
	int i, j, aux;
	 for (i = 1; i < x; i++) {  // cont
 for (j = 0; j < x - 1; j++) {  // andando pelos indice xd         
            if (v[j] > v[j + 1]) {
                aux      = v[j];   
                v[j]     = v[j + 1];
                v[j + 1] = aux;
				}
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
bubble(x, v);
printf("ordenado:\n");   

	for (i = 0; i < x; i++) 
  {
   printf("%d ", v[i]);
  }
}



