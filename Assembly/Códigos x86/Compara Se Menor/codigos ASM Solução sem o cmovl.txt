===========IDENTIFICAR MENOR VALOR DE UMA MATRIZ==============
-------IdentificaMenor.cpp---------
#include <iostream>
using namespace std;
extern "C" int MenorASM(int* i, int count);

int main() {
	int arr[] = { 4, 2, -6, 4, 5, 1, 8, 9, 5, -5 }; //define os valores
	cout << "Menor valor: " << MenorASM(arr, 10) << endl;
	cin.get();
	return 0;
}
-------MenorASM.asm-----------------
.model flat, c
.data
.code

MenorASM proc
	mov edx, dword ptr [esp+4] ;edx = *int - recebe valores 
	mov ecx, dword ptr [esp+8] ;ecx = count - tamanho da matriz
	mov eax, dword ptr [edx]   ;eax armazena o primeiro valor da matriz
	cmp ecx, 0                 ;existem 0 elementos na matriz?
	jle Fim                    ; JLE - Salta se ECX < ou = a 0 - caso sim, encerra o programa 

LoopP:
	cmp dword ptr [edx], eax   ;*edx < eax?
	jnle Maior		   ;JNLE - Salta se EAX > ou = a EDX*
	mov eax, dword ptr [edx]   ;movimentação condicional se menor - se sim, eax = edx
Maior:
	add edx, 4                 ;movimentação de edx* para o proximo valor int
	dec ecx                    ;decrementa o contador
	jnz LoopP                  ;loop se houver mais valores na pilha

Fim:
	ret                        ;retorna o menor em EAX
	MenorASM endp
end