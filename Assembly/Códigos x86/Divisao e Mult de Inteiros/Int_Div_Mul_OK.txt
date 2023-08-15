‎Codificação: Multiplicação‎ ‎e Divisão‎‎ de Inteiros mantendo Sinal.
Passar dados entre funções C++ e funções Assembly usando ponteiros.

Windows Console Application
Arquivo C++
Arquivo Assembly
Projeto - Build Dependencies - Build Customizations... MASM
Arquivo ASM - MASM

======================
CÓDIGO C
ProgDivMul.cpp

#include <iostream>
extern "C" int IntMulDiv(int a, int b, int* prod, int* quo, int* rem);
int main()
{

	int a = -27, b = 0;
	int prod = 0, quo = 0, rem = 0;
	int rf;

		rf = IntMulDiv(a, b, &prod, &quo, &rem);

	printf("Entradas-> a : %4d b:	%4d\n", a, b);
	printf("Saidas-> Retorno FuncASM: %4d  Produto:   %4d    Quociente: %4d   Resto:  %4d\n", rf, prod, quo, rem);

	return 0;

}

==========================
CÓDIGO ASM
DivMul.asm

.386
.model flat,c 	

.code
IntMulDiv proc

			push ebp     ;pilha ebp
			mov ebp,esp  ;topo pilha
			push ebx     ;pilha ebx

			mov ecx,[ebp+8]		;ecx ='a'
			mov edx,[ebp+12]	;edx ='b'

			 or edx, edx
			 jz DivInvalido

			 imul edx,ecx   ;edx = 'a'*'b'  multiplica

			 mov ebx,[ebp+16]  ; ebx ='prod'   define o ebx como a posição de memoria da pilha
			 mov [ebx],edx     ; salva a multiplicação na pilha

			 xor eax,eax  ;zera EAX

			 mov eax,ecx			;eax ='a'
			 cdq				;edx:eax contains dividend - (convert doubleword to quadword) estende EAX para EDX

			idiv dword ptr[ebp+12]

			mov ebx,[ebp+20]
			mov [ebx],eax
			mov ebx,[ebp+24]
			mov [ebx],edx
			mov eax,1

DivInvalido:
			pop ebx
			pop ebp
			ret
IntMulDiv  endp
			end