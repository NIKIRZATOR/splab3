#include <iostream>
#include <ctime>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	long long n = 5;
	long long arr[n][n];

	cout<<"Начальная матрица"<<endl;
	for (int i = 0; i < n; i++)
	{
	for (int j = 0; j < n; j++)
	{
	arr[i][j] = rand() % 9 + 1;
	cout<<arr[i][j]<<" ";
	}
	cout<<endl;
	}

	long long *ptr_arr = &arr[0][0];
	long long *end_arr = &arr[n-1][n-1];

	asm(
	"mov $8, %%rax\n\t" 
	"mulq %[n]\n\t"
	"mov %[ptr_arr], %%rbx\n\t"

	"mov %%rbx, %%rcx\n\t" 
	"add %%rax, %%rcx\n\t"
	"add $8, %%rcx\n\t" 
	"push %%rcx\n\t" 
	"push %%rax\n\t" 
	"mov %[n], %%rcx\n\t" 
	"dec %%rcx\n\t" 
	"mulq %%rcx\n\t"
	"add %%rax, %[ptr_arr]\n\t"
	"mov %%rbx, %%rcx\n\t"

	"loop_start:\n\t"
	"add $8, %%rbx\n\t" 
	"pop %%rax\n\t" 
	"add %%rax, %%rcx\n\t" 
	"push %%rax\n\t" 

	"push (%%rbx)\n\t"
	"push (%%rcx)\n\t"
	"pop (%%rbx)\n\t"
	"pop (%%rcx)\n\t"



	"cmp %%rcx, %[ptr_arr]\n\t"
	"je next_iteration\n\t"
	"jmp loop_start\n\t"

	"next_iteration:\n\t"

	"add $8, %[ptr_arr]\n\t" 
	"mov %[ptr_arr], %%rax\n\t"
	"cmp %%rax, %[end_arr]\n\t" 

	"je end_asm\n\t"
	"pop %%rax\n\t" 
	"pop %%rbx\n\t" 
	"mov %%rbx, %%rcx\n\t"
	"add %%rax, %%rcx\n\t"
	"add $8, %%rcx\n\t"
	"push %%rcx\n\t" 
	"mov %%rbx, %%rcx\n\t" 
	"push %%rax\n\t" 
	"jmp loop_start\n\t" 
	"end_asm:\n\t"
	:
	:[ptr_arr]"m"(ptr_arr), [end_arr]"m"(end_arr), [n]"m"(n)
	:"%rax", "%rbx", "%rcx"
	);
	cout<<endl<<"--------------------------------"<<endl;
	cout<<"Транспонированная матрица"<<endl;
	for (int i = 0; i < n; i++)
	{
	for (int j = 0; j < n; j++)
	{
	cout<<arr[i][j]<<" ";
	}
	cout<<endl;
	}
	return 0;
}
