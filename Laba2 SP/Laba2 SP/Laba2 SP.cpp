#include <iostream>

using namespace std;

void BubbleSort(int* arr, int N)
{
	int k;
	_asm {
		mov ebx, arr
		mov   edi, 0
		mov   esi, N

		A : cmp   edi, esi
		je    B

		mov   ecx, 0
		mov   edx, N
		dec   edx

		A1 : cmp   ecx, edx
		je    B1

		mov eax, [ebx + 4 * ecx + 4]
		mov k, eax
		mov eax, [ebx + 4 * ecx]

		cmp	eax, k
		jle C

		mov[ebx + 4 * ecx + 4], eax
		mov eax, k
		mov[ebx + 4 * ecx], eax
		C :
		inc   ecx
			jmp   A1
			B1 :

		inc   edi
			jmp   A
			B :
	}
}

void OtherSort(int arr[], int N)
{
	int k;
	_asm {
		mov ebx, arr
		mov edx, 1

		A :	cmp edx, N
		jge B

		mov eax, [ebx + 4 * edx]
		mov k, eax
		mov eax, [ebx + 4 * edx - 4]

		cmp   eax, k
		jg    A1
		inc edx
		jmp   B1
		A1 :
		mov[ebx + 4 * edx], eax
			mov eax, k
			mov[ebx + 4 * edx - 4], eax

			cmp edx, 1
			jle C
			dec	edx
			C :
	B1:
		jmp A
			B :
	}
}

//void Other1Sort(int arr[], int N)
//{
//	int k;
//	_asm
//	{
//
//		mov edx, 1; 
//	A:    
//		push edx
//	C : 
//	    mov eax, [edx - 4]
//		mov k, eax
//		mov eax, [edx]
//		cmp eax,k
//
//		jb B
//		xchg eax, [edx]
//		sub edx, 4;
//	mov arr[edx], eax
//		jnz C
//	B : 
//	   pop edx
//		add edx, 1;
//	cmp edx, [edx * 4];
//	jb A
//	}
//}


int main()
{
	cout << "Enter 10 numbers:" << "\n";

	int Mass1[10];
	for (int i = 0; i < 10; i++) {
		cout << "[" << i + 1 << "]" << ": ";
		cin >> Mass1[i];
	}
	int Mass2[10];
	for (int i = 0; i < 10; i++) {
		Mass2[i]=Mass1[i];
	}

	int* p1 = Mass1, * p2 = Mass2;

	cout << "\nYour array before sort: " << "\n";

	for (int i = 0; i < 10; ++i) {
		cout << Mass1[i] << " ";
	}
	 
	cout << "\n";

	_asm {
		push 10
		push p1
		call BubbleSort
		pop eax
		pop eax
	}

	_asm {
		push 10
		push p2
		call OtherSort
		pop eax
		pop eax
	}

	cout << "After Bubble Sort:" << "\n";
	for (int i = 0; i < 10; i++)
	{
		cout << Mass1[i] << "\n";
	}

	cout <<"\n" << "After Other Sort:" << "\n";
	for (int i = 0; i < 10; i++)
	{
		cout << Mass2[i] <<"\n";
	}

	cout << endl;
}