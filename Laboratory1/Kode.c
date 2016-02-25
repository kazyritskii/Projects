#include <stdio.h>
#include <stdlib.h>

/*Функция заполняет строку-массив исходныи числом.
arg1-указатель на массив.*/
void input(char *Digit)
{
	while ((*Digit = getchar()) != '\n')
	{
		Digit++;
	}
	*Digit = 'z';
}

/*Функция проверяет основания систем счисления, лежат ли они от 2 до 16.
arg1-основание исходной сс.
arg2-основание конечной сс.
Возвращает 1 если они лежат от 2 до 16,
возвращает 0 если не лежат.*/
int CheckBasis(int a1, int a2) 
{
	int Condition=1;
	if ((a1 < 2) || (a1>16) || (a2 < 2) || (a2>16))
	{
		Condition = 0;
	}
	return Condition;
}

/*Проверяет является ли строка а1-ричной записью.
arg1-основание исходной сс.
arg2-указатель на массив-строку исходного числа.
Возвращает 1 если строка является a1-ричной записью,
в противном случае возвращает 0.*/
int CheckDigit(int a1, char *Digit )
{
	int Condition=1;
	if (*Digit == '.')
	{
		Condition = 0;
	}
	while (*Digit != 'z')
	{
		if ((*Digit >= a1)&&(*Digit!='.'))
		{
			Condition = 0;
		}
		Digit++;
	}
	if (*(Digit - 1) == '.')
	{
		Condition = 0;
	}
	return Condition;
}

/*Считает количество точек в строке.
arg1-указатель на массив-строку.
Возвращает 1, если в строке одна точка или их нет,
в противном случае возвращает 0.*/
int CheckPoint(char *Digit)
{
	int Condition = 1;
	int k = 0;
	while (*Digit != 'z')
	{
		if (*Digit == '.')
		{
			k++;
		}
		Digit++;
	}
	if (k > 1)
	{
		Condition = 0;
	}
	return Condition;
}

/*Функция переводит массив заполненный символами в массив чисел.
arg1-указатель на массив.*/
void revers(char *Digit)
{
	while (*Digit != 'z')
	{
		if ((*Digit >= '0') && (*Digit <= '9'))
		{
			*Digit = *Digit - '0';
		}
		else
			if ((*Digit >= 'A') && (*Digit <= 'F'))
			{
				*Digit = *Digit - 'A' + 10;
			}
			else
				if ((*Digit >= 'a') && (*Digit <= 'f'))
				{
					*Digit = *Digit - 'a' + 10;
				}
		Digit++;
	}
}

/*Функция считает длину всей строки.
arg1-указатель на строку-массив.
Возвращает длину строки.*/
int Lenght(char *Digit)
{
	int K = 0;
	while (*Digit !='z')
	{
		K++;
		Digit++;
	}
	return K;
}

/*Функция считает длину строки до точки, т.е.длину целой части числа.
arg1-указатель на строку.
Возвращает длину целой части числа.*/
int intLen(char *Digit)
{
	int K = 0;
	while ((*Digit != '.')&&(*Digit!='z'))
	{
		K++;
		Digit++;
	}
	return K;
}

/*Функция возводит число а1 в степень len.
arg1-основание исходной сс.
arg2-разряд цифры.
Возвращает число digDeg равное arg1 в степени arg2.*/
long double degree(int a1, int len)
{
	long double digDeg = 1;
	int i;
	if (len != 0)
	{
		for (i = 0; i < len; i++)
		{
			digDeg = digDeg*a1;
		}
	}
	return digDeg;
}

/*Функция переводит целую часть исходного числа в 10-ричную сс.
arg1-указатель на строку-массив.
arg2-основание исходной сс.
Возвращает целую часть исходного числа в 10-ричной сс.*/
long long int intTransfer10(char *Digit,int a1)
{
	long long int newDigit=0;
	int intLenght=intLen(Digit)-1;
	while ((*Digit != '.') && (*Digit != 'z'))
	{
		newDigit = newDigit + (*Digit * (long long int)degree(a1, intLenght));
		Digit++;
		intLenght--;
	}
	return newDigit;
}

/*Функция переводит дробную часть исходного числа в 10-ричную сс.
arg1-указатель на строку-массив.
arg2-основание исходной сс.
Возвращает дробную часть исходного числа в 10-ричной сс.*/
double floTransfer10(char *Digit, int a1)
{
	double newDigit=0;
	int floLenght = 1;
	if (Lenght(Digit) - intLen(Digit) != 0)
	{
		while (*Digit != '.') {
			Digit++;
		}
		Digit++;
		while (*Digit != 'z')
		{
			newDigit = newDigit + ((double)*Digit / degree(a1, floLenght));
			Digit++;
			floLenght++;
		}
	}
	return newDigit;
}

/*Функция переводит целую и дробную часть числа в 10-ричной записи в а2-ричную запись.
arg1-целая часть в 10-ричной записи.
arg2-дробная часть в 10-ричной записи.
arg3-основание конечной сс.
Возвращает указатель на строку-массив чсила в а2-ричной записи.*/
char* Transfer( long long int intDig, double floDig,int a2)
{
	char *Digit;
	Digit = (char*)malloc(200);
	char* Bgn = Digit;
	int k = 0;
	if (intDig == 0)
	{
		*Digit = 0;
		Digit++;
	}
	else
	{
		while (intDig != 0)
		{
			*Digit = intDig % a2;
			intDig = intDig / a2;
			Digit++;
		}
	}
		if (floDig != 0)
		{
			*Digit = '.';
			Digit++;
			while ((floDig != 0) && (k != 12))
			{
				*Digit = (int)(floDig*a2);
				floDig = (floDig*a2) - (int)(floDig*a2);
				Digit++;
				k++;
			}
		}
	*Digit = 'z';
	return Bgn;
}

/*Функция переводит массив заполненный числами в массив символов.
arg1-указатель на массив.*/
void revers2(char* Digit)
{
	while (*Digit != 'z')
	{
		if ((*Digit >= 0) && (*Digit <= 9))
		{
			*Digit = *Digit + '0';
		}
		else
			if ((*Digit >= 10) && (*Digit <= 15))
			{
				*Digit = *Digit + 'A' - 10;
			}
			else
				if ((*Digit >= 'a') && (*Digit <= 'f'))
				{
					*Digit = *Digit + 'a' - 10;
				}
		Digit++;
	}
}

/*Функция выводит строку-массив.
arg1-указатель на новый массив*/
void conclus(char *Digit)
{
	int i;
	for (i = intLen(Digit) - 1; i >= 0; i--)
	{
		printf("%c", Digit[i]);
	}
	if (Lenght(Digit) - intLen(Digit) != 0)
	{
		while (*Digit != '.') {
			Digit++;
		}
		while (*Digit != 'z')
		{
			printf("%c", *Digit);
			Digit++;
		}
	}
}

void main() 
{
	int b1;
	int b2;
	char *Digit;
	Digit = (char*)malloc(25);
	scanf_s("%d %d\n", &b1 ,&b2);
	input(Digit);
	revers(Digit);
	if ((CheckBasis(b1,b2) == 0) || (CheckDigit(b1,Digit) == 0)||(CheckPoint(Digit)==0))
	{
		printf("bad input");
	}
	else
	{
		Digit = Transfer(intTransfer10(Digit, b1), floTransfer10(Digit, b1), b2);
		revers2(Digit);
		conclus(Digit);
	}
	getchar();
	getchar();
}