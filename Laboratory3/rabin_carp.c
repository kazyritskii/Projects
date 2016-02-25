#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*Функция заполняет строку-массив шаблоном.
arr-указатель на массив.*/
void input( char *arr)
{
	while ((*arr = getchar()) != '\n')
	{
		arr++;
	}
	*arr = '\0';
}

/*Функция заполняет буфер длины шаблона текстом.
arr-указатель на массив.
M-длина шаблона*/
void input2(char *arr, int M)
{
	while (M != 0)
	{
		*arr = getchar();
		arr++;
		M--;
	}
	*arr = '\0';
}

/*Функция считает длину всей строки.
Digit-указатель на строку-массив.
Возвращает длину строки.*/
int strl(unsigned char *Digit)
{
	int K = 0;
	while (*Digit != '\0')
	{
		K++;
		Digit++;
	}
	return K;
}

/*Функция возводит число 3 в степень a.
a-степень.
Возвращает число digDeg равное 3 в степени a.*/
int degree(int a)
{
	long int digDeg;
	switch (a)
	{
		case 0:digDeg = 1; break;
		case 1:digDeg = 3; break;
		case 2:digDeg = 9; break;
		case 3:digDeg = 27; break;
		case 4:digDeg = 81; break;
		case 5:digDeg = 243; break;
		case 6:digDeg = 729; break;
		case 7:digDeg = 2187; break;
		case 8:digDeg = 6561; break;
		case 9:digDeg = 19683; break;
		case 10:digDeg = 59049; break;
		case 11:digDeg = 177147; break;
		case 12:digDeg = 531441; break;
		case 13:digDeg = 1594323; break;
		case 14:digDeg = 4782969; break;
		case 15:digDeg = 14348907; break;
	}
	return digDeg;
}

/*Функция считает хеш-функцию для шаблона
arr-указатель на массив.
M-длина шаблона.
Возвращает значение хеш-функции.*/
int Hesh(unsigned char* arr,int M)
{
	int i, t_arr;
	t_arr = 0;
	for (i = 0; i < M; i++)
	{
		t_arr = t_arr + ((arr[i] % 3)*degree(i));
	}
	return t_arr;
}

/*Функция считает хеш-функцию для строки.
arr-указатель на массив.
M-длина шаблона.
i-индекс нового элемента.
t_k-старое значение хеш-функции.
Dig-значение удаленного элемента.
Возвращает значение хеш-функции буфера.*/
int HeshStr(unsigned char* str, int M,int i,int t_k, unsigned char Dig)
{
	t_k = (t_k - (Dig % 3)) / 3 + (str[i%M] % 3)*degree((M - 1));
	return t_k;
}

/*Функция посимвольно сравнивает элементы шаблона и буфера.
str-указатель на буфер.
arr-указатель на шаблон.
z-индекс последнего элемента.
М-длина шаблона.*/
void Robin_Carp(unsigned char* str, unsigned char* arr,int z,int M)
{
	int i, j;
			j = z;
			for (i = 0; i < M; i++)
			{
				if (arr[i] == str[(j-M+1)%M])
				{
					printf(" %d", z-M + i + 2);
				}
				else
				{
					printf(" %d", z-M + i + 2);
					break;
				}
				j++;
			}				
}

void main()
{
	int i, M,t_arr,t_k;
	unsigned char Dig;
	unsigned char *arr;
	arr = (unsigned char*)malloc(17);
	unsigned char *str;
	str = (unsigned char*)malloc(17);
	input(arr);
	M = strl(arr);
	input2(str,M);
	t_arr = Hesh(arr, M);
	t_k = Hesh(str, M);
	printf("%d", t_arr);
	i = M - 1;
	if (t_arr == t_k)
	{
		Robin_Carp(str, arr, i, M);
	}
	i++;
	Dig = str[0];
	while ((str[i % M] = getchar()) != EOF)
	{
		t_k = HeshStr(str,M,i,t_k,Dig);
		if (t_arr == t_k)
		{
			Robin_Carp(str, arr, i, M);
		}
		i++;
		Dig = str[(i - M) % M];
	}
	free(arr);
	free(str);
	getchar();
	getchar();
}