#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/*Функция заполняет строку-массив шаблоном.
arr-указатель на массив.*/
void input(char *arr)
{
	while ((*arr = getchar()) != '\n')
	{
		arr++;
	}
	*arr = '\0';
}

/*Функция заполняет буфер длины шаблона текстом.
str-указатель на массив.
M-длина шаблона*/
void input2(char *str, int M)
{
	while (M != 0)
	{
		*str = getchar();
		str++;
		M--;
	}
	*str = '\0';
}

/*Функция заполняет массив смещений.
d-указатель на массив смещений.
arr-указатель на шаблон.
M-длина шаблона.*/
void displace(int* d, unsigned char* arr, int M)
{
	int i;
	for (i = 0; i < 256; i++)
		d[i] = M;
	for (i = 0; i < M - 1; i++)
		d[(unsigned char)arr[i]] = M - i - 1;
}

/*Функция заполняет строку новыми элементами.
str-текст.
d-колличество новых элементов.
i-номер последнего элемента.
M-длина шаблона.
Возвращает 0 если дошли до конца текста, иначе возвращает 1.*/
int input3(unsigned char* str, int d,int i,int M)
{
	while (d != 0)
	{
		if ((str[(i + 1) % M] = getchar()) == EOF)
			return 0;
		d--;
		i++;
	}
	return 1;
}

/*Функция сравнивает элементы шаблона с элементами строки и выводит номер каждого сравниваемого символа.
str-текст.
arr-шаблон.
d-массив смещений.
M-длина массива.
i-номер последнего элемента.*/
void seek_substring(unsigned char* str, unsigned char* arr, int* d,int M,int i)
{
	int j;
		j = M - 1;
		while (j >= 0)
		{
			if (arr[j] == str[i%M])
			{
				printf("%d ", i + 1);
				i--;
				j--;
			}
			else
			{
				printf("%d ", i + 1);
				break;
			}
		}
}

void main()
{
	int M,N,i,save,save2;
	unsigned char *arr;
	arr = (unsigned char*)malloc(17);
	unsigned char *str;
	str = (unsigned char*)malloc(17);
	int *d = (int*)malloc(sizeof(int) * 256);
	input(arr);
	M = strlen(arr);
	input2(str,M);
	N = strlen(str);
	displace(d, arr, M);
	if (N)
	{
		i = M - 1;
		do
		{
			seek_substring(str, arr, d, M, i);
			save= d[(unsigned)str[i%M]];
			save2 = i;
			i += d[(unsigned)str[i%M]];
		} while (input3(str, save, save2, M)!=0);
		
	}
	free(arr);
	free(str);
	getchar();
	getchar();
}