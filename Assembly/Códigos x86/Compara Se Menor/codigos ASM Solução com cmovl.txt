==========CODIGO 1===============

#include <iostream>

int main()
{
    int i = 0;
    _asm mov i, 25
    std::cout << "Valor de i: " << i;
}

===========CÓDIGO 2==============

#include <iostream>

int main()
{
    int i = 0;
    __asm {
            mov i, 55
    }
    std::cout << "Valor de i: " << i;
}

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
MenorASM proc export
	mov edx, dword ptr [esp+4] ; edx = *int -  recebe os valores
	mov ecx, dword ptr [esp+8] ; ecx = Count - contador
	mov eax, 7fffffffh ; eax assume que o menor é o máximo Inteiro
	cmp ecx, 0 ; Existem 0 items?
	jle Fim ; Caso sim, encerra.

LoopP:
	cmp dword ptr [edx], eax ; É *edx < eax?
	cmovl eax, dword ptr [edx]; Se sim, eax = edx
	add edx, 4 ; Mova * edx para o próximo int 
	dec ecx ; Decrementa contador
	jnz LoopP ; Loop se houver mais

Fim:
	ret ; Retorne com o menor em eax
	MenorASM endp
end

----------CMOVL-------------
https://docs.oracle.com/cd/E19120-01/open.solaris/817-5477/6mkuavhs7/index.html