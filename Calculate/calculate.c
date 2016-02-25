#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"charStack.h"
#include"intStack.h"
#include <math.h>
//#define doub 1
#define pi 3.141592653589793238462643383279502884197169399375105820974944592

/*Функция проверяет является ли символ пробелом.
с-проверяемый символ.
возвращает 1 если является, ЕOF если нет.*/
int IsDelimeter(char c)
{
	if (c == ' ')
		return 1;
	return EOF;
}

/*Функция проверяет является ли символ цифрой.
с-проверяемый символ.
возвращает 1 если является, ЕOF если нет.*/
int isDigit(char c)
{
	if ((c >= '0') && (c <= '9'))
		return 1;
	return EOF;
}

/*Функция проверяет является ли символ оператором.
с-проверяемый символ.
возвращает 1 если является, ЕOF если нет.*/
int IsOperator(char c)
{
	if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '(') || (c == ')') || (c == '^') || (c == 's') || (c == 'c') || (c=='l')||(c=='m'))
		return 1;
	return EOF;
}

/*Функция проверяет записан ли в строке sin.
input-строка.
i-индекс элемента.
возвращает 1-если синус иначе EOF*/
int IsSin(char* input, int i)
{
	if ((input[i + 1] == 'i') && (input[i + 2] == 'n'))
		return 1;
	return EOF;
}

/*Функция проверяет записан ли в строке cos.
input-строка.
i-индекс элемента.
возвращает 1-если синус иначе EOF*/
int IsCos(char* input, int i)
{
	if ((input[i + 1] == 'o') && (input[i + 2] == 's'))
		return 1;
	return EOF;
}

/*Функция проверяет записан ли в строке ln.
input-строка.
i-индекс элемента.
возвращает 1-если синус иначе EOF*/
int IsLn(char* input, int i)
{
	if (input[i + 1] == 'n')
		return 1;
	return EOF;
}

/*Функция проверяет записан ли в строке log.
input-строка.
i-индекс элемента.
возвращает 1-если синус иначе EOF*/
int IsLog(char* input, int i)
{
	if ((input[i + 1] == 'o') && (input[i + 2] == 'g'))
		return 1;
	return EOF;
}

/*Функция проверяет записан ли в строке max.
input-строка.
i-индекс элемента.
возвращает 1-если синус иначе EOF*/
int IsMax(char* input, int i)
{
	if ((input[i + 1] == 'a') && (input[i + 2] == 'x'))
		return 1;
	return EOF;
}

/*Функция определяет приоритет операторов.
s-оператор.
Возвращает целое число-приоритет.*/
int GetPriority(char s)
{
	switch (s)
	{
	case '(': return 0; break;
	case ')': return 1; break;
	case '+': return 2; break;
	case '-': return 3; break;
	case '*': return 4; break;
	case '/': return 4; break;
	case '^': return 5; break;
	case 's': return 6; break;
	case 'c': return 6; break;
	case 'e': return 6; break;
	case 'l': return 6; break;
	case 'm': return 6; break;
	default: return 7; break;
	}
}

/*Функция заполняет массив исходной строкой.
arr-массив.
Если в строке идут две скобки подряд, то возвращает EOF, иначе 1.*/
int input(char* arr)
{
	char c;
	while ((*arr = getchar()) != '\n')
	{
		arr--;
		c = *arr;
		arr++;
		if ((c == '(') && (*arr == ')'))
		{
			printf("syntax error");
			return EOF;
		}
		arr++;
	}
	*arr = '\0';
	return 1;
}

/*Функция преобразует входную строку в строку обратной польской нотации.
input-входная строка.
output-заполняемая строка.
len-длина входной строки.
Возвращает EOF если входная строка некорректна.*/
int RPN(char* input, char* output, size_t len)
{
	int i;
	Stack *operStack = NULL; //Стек для хранения операторов
	for (i = 0; i < len; i++) //Для каждого символа в входной строке
	{
		if (IsDelimeter(input[i]) == 1) //Если встретился пробел, значит входная строка некорректна
		{
			printf("syntax error");
			freeHead(&operStack);
			return EOF;
		}
		if (IsOperator(input[i]) == 1) //Если оператор
		{
			if (input[i] == '(')		//Если символ - открывающая скобка
				push(&operStack, input[i]); //Записываем её в стек
			else if (input[i] == ')')	//Если символ - закрывающая скобка
			{
				char s = pop(&operStack);	//Выписываем все операторы до открывающей скобки в строку
				while (s != '(')
				{
					int k = getSize(operStack);
					if (k == 0)	//Если в стеке нет элементов, и до открывающей скобки не дошли, значит входная строка некорректна
					{
						printf("syntax error");
						freeHead(&operStack);
						return EOF;
					}
					*output = s;
					output++;
					*output = ' ';
					output++;
					s = pop(&operStack);
				}
			}
			else //Если любой другой оператор
			{
				if (input[i] == 's') //Если s проверяем sin это или нет
				{
					if (IsSin(input, i) != EOF)
					{
						i = i + 2;
						input[i] = 's';
					}
					else
					{
						printf("syntax error");
						freeHead(&operStack);
						return EOF;
					}
				}
				if (input[i] == 'c')	//Если c проверяем cos это или нет
				{
					if (IsCos(input, i) != EOF)
					{
						i = i + 2;
						input[i] = 'c';
					}
					else
					{
						printf("syntax error");
						freeHead(&operStack);
						return EOF;
					}
				}
				if (input[i] == 'l')	//Если l проверяем ln это или log или ошибка
				{
					if (IsLn(input, i) != EOF)
					{
						i = i + 1;
						input[i] = 'e';
					}
					else
						if (IsLog(input, i) != EOF)
						{
							i = i + 2;
							input[i] = 'l';
						}
						else
						{
							printf("syntax error");
							freeHead(&operStack);
							return EOF;
						}
				}
				if (input[i] == 'm')	//Если m проверяем max это или нет
				{
					if (IsMax(input, i) != EOF)
					{
						i = i + 2;
						input[i] = 'm';
					}
					else
					{
						printf("syntax error");
						freeHead(&operStack);
						return EOF;
					}
				}
				if (getSize(operStack) != 0) //Если в стеке есть элементы
					while ((GetPriority(input[i]) <= GetPriority(peek(operStack)))&&(peek(operStack)!=EOF))//И если приоритет нашего оператора меньше или равен приоритету оператора на вершине стека
					{
						*output = pop(&operStack); //То добавляем последний оператор из стека в строку с выражением
						output++;
						*output = ' ';
						output++;
					} 
				push(&operStack, input[i]); //Если стек пуст, или же приоритет оператора выше - добавляем операторов на вершину стека
			}
		}
		else
			if (isDigit(input[i]) == 1) //Если символ - цифра, то считываем все число
			{
				{
					while ((input[i] != ',') && (IsOperator(input[i]) == EOF) && (isDigit(input[i]) == 1))	//Читаем до разделителя или оператора, что бы получить число
					{
							*output = input[i]; //Добавляем каждую цифру числа к нашей строке
							output++;
							i++;				//Переходим к следующему символу
							if (i == len) break; //Если символ - последний, то выходим из цикла
					}
					*output = ' '; //Дописываем после числа пробел в строку с выражением
					output++;
					if ((input[i]) != ',')
					{
						i--;	//Возвращаемся на один символ назад, к символу перед оператором

					} 
				}
			}
			else //Если любой другой символ, значит входная строка некорректна.
			{
				printf("syntax error");
				freeHead(&operStack);
				return EOF;
			}
	}

	//Когда прошли по всем символам, выкидываем из стека все оставшиеся там операторы в строку
	while (getSize(operStack) != 0)
	{
		*output = pop(&operStack); //То добавляем последний оператор из стека в строку с выражением
		output++;
		*output = ' ';
		output++;
	}
	output--;
	*output = '\0';
	return 1;
}

/*Функция вычисляет значение выражения.
input-входная строка в ОПН.
len-длина входной строки.
Возвращает число-значение выражения или EOF если входная строка некорректна.*/
type2 Counting(char* input, size_t len)
{
	type2 result, a, b;
	size_t len2;
	int i;
	Stack2 *temp = NULL; //Cтек для решения
	char* str;
	str = (char*)malloc(998);
	result = 0;
	for (i = 0; i < len; i++) //Для каждого символа в строке
	{
		if (isDigit(input[i]) == 1)	//Если символ - цифра, то читаем все число и записываем на вершину стека
		{
			*str = '\0';
			while ((IsDelimeter(input[i]) == EOF) && (IsOperator(input[i]) == EOF)) //Пока не разделитель
			{
				len2 = strlen(str);
				str[len2] = input[i];		//Записываем число в новой строке, добавляя по одному символу
				str[len2 + 1] = '\0';
				i++;
				if (i == len) break;
			}
			push2(&temp, atoi(str)); //Записываем в стек строку в виде числа
			i--;
		}
		else if ((IsOperator(input[i]) == 1)||(input[i]=='e')) //Если символ - оператор
		{
			a = pop2(&temp);		//Берем два последних значения из стека
			b = pop2(&temp);
			if ((b == EOF) && (input[i]!='s') && (input[i] != 'c') && (input[i] != 'e') && (input[i] != 'l'))	//Если символа нет, значит входная строка некорректна
			{
				printf("syntax error");
				freeHead2(&temp);
				free(str);
				return EOF;
			}
			switch (input[i]) //Производим над ними действие, согласно оператору
			{
			case '+': result = (b + a); break;
			case '-': result = (b - a); break;
			case '*': result = (b * a); break;
			case '/': if (a == 0)		//Если деление на ноль, вывести ошибку
			{
				printf("division by zero");
				freeHead2(&temp);
				free(str);
				return EOF;
			}
					  else result = (b / a); break;
			case '(': 					//Если открывающая скобка,значит входная строка некорректна
				printf("syntax error");
				freeHead2(&temp);
				free(str);
				return EOF;
				break;
			case '^': result = (type2)pow((double)b, (double)a); break;
			case 's': result = (type2)sin((double)a*pi/180); push2(&temp, b); break;
			case 'c': result = (type2)cos((double)a*pi / 180); push2(&temp, b); break;
			case 'e': result = (type2)log((double)a); push2(&temp, b); break;
			case 'l': result = (type2)log10((double)a); push2(&temp, b); break;
			case 'm': if (b > a) { result = b; }
					  else result = a; break;
			}
			push2(&temp, result); //Результат вычисления записываем обратно в стек
		}
	}
	result = peek2(temp);
	freeHead2(&temp);
	free(str);
	return result;//Забираем результат всех вычислений из стека и возвращаем его
}

void main()
{
	size_t Len, len2;
	int bool;
	type2 result;
	char* arr;
	char* str;
	arr = (char*)malloc(1001);
	if (input(arr) != EOF)
	{
		Len = strlen(arr);
		if (Len == 0)
		{
			printf("syntax error");
		}
		else
		{
			str = (char*)malloc(Len * 2);
			bool = RPN(arr, str, Len);
			if (bool != EOF)
			{
				len2 = strlen(str);
				result = Counting(str, len2);
				if (result != EOF)
				{
					/*if (doub != 1)
					{
						printf("%d", (int)result);
					} else*/
					printf("%f", result);
				}
			}
			free(str);
		}
	}
	free(arr);
	getchar();
	getchar();
}