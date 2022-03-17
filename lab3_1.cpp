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

	if (n<=1)
	{
	cout<< "Размер массива меньше 1"<<endl;
	return -1;
	}

	asm(
	"mov $8, %%rax\n\t" // Поместили 8 в rax
	"mulq %[n]\n\t" // Умножили rax на n (получили сдвиг для перехода по строкам)
	"mov %[ptr_arr], %%rbx\n\t"// Поместили указатель на начало матрицы в rbx
	"mov %%rbx, %%rcx\n\t" // Поместили указатель на начало матрицы в rcx
	"add %%rax, %%rcx\n\t" // Прибавили к rcx содержимое rax (сдвинули указатель вниз на одну строку)
	"add $8, %%rcx\n\t" // Прибавили к rcx 8 (сдвинули указатель вправо на один столбец)
	"push %%rcx\n\t" // Поместили в стек rcx (адрес следующего элемента главной диагонали)
	"push %%rax\n\t" // Поместили в стек rax (сдвиг для перехода по строкам)
	"mov %[n], %%rcx\n\t" // Поместили в rcx значение n
	"dec %%rcx\n\t" // Уменьшили на 1 значение rcx (получили в rcx n-1)
	"mulq %%rcx\n\t" // Умножили rax (сдвиг для перехода по строкам) на rcx (n-1)
	"add %%rax, %[ptr_arr]\n\t"// Прибавили к ptr_array содержимое rax (получили указатель на первый элемент последней строки матрицы)
	"mov %%rbx, %%rcx\n\t" // Вернули в rcx указатель на начало матрицы 
	"loop_start:\n\t"
	"add $8, %%rbx\n\t" // Увеличили адрес в rbx на 8 (переместились на один элемент вправо)
	"pop %%rax\n\t" // Взяли в rax из стека смещение на следующую строку
	"add %%rax, %%rcx\n\t" // Увеличили значение в rcx на смещение на следующую строку (переместились вниз на один элемент)
	"push %%rax\n\t" // Вернули в стек смещение на следующую строку
	"push (%%rbx)\n\t" // Обмен значений элементов матрицы через стек
	"push (%%rcx)\n\t"
	"pop (%%rbx)\n\t"
	"pop (%%rcx)\n\t"



	"cmp %%rcx, %[ptr_arr]\n\t"// Проверили что не достугнута последняя строка матрицы
	"je next_iteration\n\t" // Если достигнута - переход на next_iteration
	"jmp loop_start\n\t" // Если НЕ достигнута - переход на start_loop 
	"next_iteration:\n\t"
	"add $8, %[ptr_arr]\n\t" // Сдвинули указатель на один элемент последней строки матрицы вправо
	"mov %[ptr_arr], %%rax\n\t"// Переместили указатель в rax
	"cmp %%rax, %[end_arr]\n\t" // Проверили что достигнут конец матрицы
	"je end_asm\n\t" // Если достигнут - завершение, иначе продолжение
	"pop %%rax\n\t" // Взяли в rax из стека смещение на следующую строку
	"pop %%rbx\n\t" // Взяли в rbx из стека указатель на следующий элемент главной диагонали, он станет началом новой "усеченной" матрицы
	"mov %%rbx, %%rcx\n\t" // Поместили в rcx указатель на следующий элемент главной диагонали
	"add %%rax, %%rcx\n\t" // Сдвинули указатель в rcx на одну строку вниз
	"add $8, %%rcx\n\t" // Сдвинули указатель в rcx на один элемент вправо
	"push %%rcx\n\t" // Вернули rcx в стек
	"mov %%rbx, %%rcx\n\t" // Поместили в rcx значение из rbx
	"push %%rax\n\t" // Вернули rax в стек
	"jmp loop_start\n\t" // Переход на loop_start
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
