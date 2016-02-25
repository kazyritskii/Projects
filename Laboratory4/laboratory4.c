#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*Функция заполняет строку-массив исходной перестановкой.
arg1-указатель на массив.*/
void input(char *arr)
{
	while ((*arr = getchar()) != '\n')
	{
		arr++;
	}
	*arr = '\0';
}

/*Функция заполняет вспомогательный массив нулями.
arg1-указатель на массив*/
void input2(int *mas)
{
	int i=0;
	while(i!=10)
	{
		*mas = 0;
		mas++;
		i++;
	}
}

/*Функция проверяет состоит ли перестановка из символов 0123456789
arg1-указатель на массив.
Возвращает 1 если состоит.
Возвращает 0 в противном случае.*/
int check(char* arr)
{
	int Condition = 1;
	while (*arr != '\0')
	{
		if ((*arr<'0') || (*arr>'9'))
			Condition = 0;
		arr++;		
	}
	return Condition;
}

/*Функция проверяет является ли строка перестановкой символов 0123456789 и эти символы не повторяются.
arg1-указатель на массив.
Возвращает 1 если является.
Возвращает 0 в противном случае.*/
int check2(char* arr)
{
	int Condition = 1;
	int i;
	int *mas;
	mas= (int*)malloc(10);
	input2(mas);
	while (*arr != '\0')
	{
		mas[(*arr-'0')] = mas[(*arr-'0')] + 1;
		arr++;
	}
	for (i = 0; i < 10; i++)
	{
		if (mas[i] > 1)
			Condition = 0;
	}
	return Condition;
	free(mas);
}

/*Функция считает длину всей строки.
arg1-указатель на строку-массив.
Возвращает длину строки.*/
int Lenght(char *arr)
{
	int K = 0;
	while (*arr != '\0')
	{
		K++;
		arr++;
	}
	return K;
}

/*Функция получает и печатает следующую перестановку методом Дейкстры.
arg1-указатель на массив.
arg2-длина строки.*/
void Deykstra(char* arr, int len)
{
	int i;
	int cur=-1;
	char t;
	for (i = len - 2; i >= 0; i--)
	{
		if (arr[i] < arr[i + 1])
		{
			cur = i;
			break;
		}
	}
	if (cur < 0) return;
	for (i = len - 1; i > cur; i--)
	{
		if (arr[i] > arr[cur])
		{
			t = arr[cur];
			arr[cur] = arr[i];
			arr[i] = t;
			break;
		}
	}
	for (i = 0; i < ((len - cur) / 2); i++)
	{
		t = arr[cur + 1 + i];
		arr[cur + 1 + i] = arr[len - 1 - i];
		arr[len - 1 - i] = t;
	}
	for (i = 0; i < len; i++)
	{
		printf("%c", arr[i]);
	}
	printf("\n");
}

void main()
{
	int k;
	int cur = 1;
	int len;
	char *arr;
	arr = (char*)malloc(11);
	input(arr);
	scanf("%d", &k);
	if ((check(arr) == 0) || (check2(arr) == 0))
	{
		printf("bad input");
	}
	else
	{
		len = Lenght(arr);
		while (cur <= k)
		{
			Deykstra(arr, len);
			cur++;
		}
	}
	free(arr);
	getchar();
	getchar();
}