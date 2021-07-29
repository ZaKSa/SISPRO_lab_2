#include<iostream>
#include<fstream>
#include<cstring>
#include<conio.h>
#include<cstdlib>

using namespace std;

//8)	(-53/a + d-4*a)/(1 +a*b)

int main()
{

		int a, b, d, null = 0, err_pop =0, ofs = 0, result;

		cout << "Enter a> ";
		cin >> a;
		cout << "Enter b> ";
		cin >> b;
		cout << "Enter d> ";
		cin >> d; 

		__asm
		{
			mov eax, a; помещаем a в регистр eax
			jo error_ofs; ошибка переполнения
			test eax, eax;

			mov ebx, b; помещаем b в регистр ebx
			jo error_ofs; ошибка переполнения
			imul ebx; ebx = a*b
			inc eax; eax = a*b + 1

			push eax ;кладем содержимое eax в стек

			mov eax, a; eax = a
			imul eax, 4; eax = 4a
				jo error_pop;
			mov ebx, d; edx = d
				jo error_pop;
				sub ebx, eax; ebx = d-4a
			push ebx; кладем содержимое ebx в стек
			mov ebx, a; ebx = a
			
			mov eax, -53; eax = -53

			add ebx, 0;

			cdq
			idiv ebx; ebx = -53/a
			jo error_pop;

			pop ebx;

			add eax, ebx; eax = -53/a + d -4a
			jo error_pop;
			pop ebx;
			
			add ebx, 0;
			jz division_by_zero;
			jo error_ofs; 
			cdq
			idiv ebx;
			mov result, eax;


			jmp e2;
		error_ofs:; флаг ошибки переполнения
			mov edx, ofs; edx = ofs
			inc edx;
		mov ofs, edx;
	e2:
			jmp e0;
		error_pop:; 
			pop eax;
			mov edx, ofs; edx = ofs
				inc edx;

			mov ofs, edx;
	e0:
			jmp e1;
		division_by_zero:; флаг ошибки деления на ноль
			mov edx, null; edx = zero
			inc edx;
		mov null, edx;
	e1:
		}
		if (ofs == 1 || err_pop == 1)
			cout << endl << "Out of size" << endl;
		else if (null == 1)
			cout << "Division by zero" << endl;
		
		else if ((1 + a * b) != 0 && a != 0 && null == 0 && ofs == 0) {
			cout << "Result asm> " << result;
			cout << endl << "Result c++> " << (-53 / a + d - 4 * a) / (1 + a * b);
		}
	
	return 0;
}