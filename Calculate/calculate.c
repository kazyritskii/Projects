#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"charStack.h"
#include"intStack.h"
#include <math.h>
//#define doub 1
#define pi 3.141592653589793238462643383279502884197169399375105820974944592

/*������� ��������� �������� �� ������ ��������.
�-����������� ������.
���������� 1 ���� ��������, �OF ���� ���.*/
int IsDelimeter(char c)
{
	if (c == ' ')
		return 1;
	return EOF;
}

/*������� ��������� �������� �� ������ ������.
�-����������� ������.
���������� 1 ���� ��������, �OF ���� ���.*/
int isDigit(char c)
{
	if ((c >= '0') && (c <= '9'))
		return 1;
	return EOF;
}

/*������� ��������� �������� �� ������ ����������.
�-����������� ������.
���������� 1 ���� ��������, �OF ���� ���.*/
int IsOperator(char c)
{
	if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '(') || (c == ')') || (c == '^') || (c == 's') || (c == 'c') || (c=='l')||(c=='m'))
		return 1;
	return EOF;
}

/*������� ��������� ������� �� � ������ sin.
input-������.
i-������ ��������.
���������� 1-���� ����� ����� EOF*/
int IsSin(char* input, int i)
{
	if ((input[i + 1] == 'i') && (input[i + 2] == 'n'))
		return 1;
	return EOF;
}

/*������� ��������� ������� �� � ������ cos.
input-������.
i-������ ��������.
���������� 1-���� ����� ����� EOF*/
int IsCos(char* input, int i)
{
	if ((input[i + 1] == 'o') && (input[i + 2] == 's'))
		return 1;
	return EOF;
}

/*������� ��������� ������� �� � ������ ln.
input-������.
i-������ ��������.
���������� 1-���� ����� ����� EOF*/
int IsLn(char* input, int i)
{
	if (input[i + 1] == 'n')
		return 1;
	return EOF;
}

/*������� ��������� ������� �� � ������ log.
input-������.
i-������ ��������.
���������� 1-���� ����� ����� EOF*/
int IsLog(char* input, int i)
{
	if ((input[i + 1] == 'o') && (input[i + 2] == 'g'))
		return 1;
	return EOF;
}

/*������� ��������� ������� �� � ������ max.
input-������.
i-������ ��������.
���������� 1-���� ����� ����� EOF*/
int IsMax(char* input, int i)
{
	if ((input[i + 1] == 'a') && (input[i + 2] == 'x'))
		return 1;
	return EOF;
}

/*������� ���������� ��������� ����������.
s-��������.
���������� ����� �����-���������.*/
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

/*������� ��������� ������ �������� �������.
arr-������.
���� � ������ ���� ��� ������ ������, �� ���������� EOF, ����� 1.*/
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

/*������� ����������� ������� ������ � ������ �������� �������� �������.
input-������� ������.
output-����������� ������.
len-����� ������� ������.
���������� EOF ���� ������� ������ �����������.*/
int RPN(char* input, char* output, size_t len)
{
	int i;
	Stack *operStack = NULL; //���� ��� �������� ����������
	for (i = 0; i < len; i++) //��� ������� ������� � ������� ������
	{
		if (IsDelimeter(input[i]) == 1) //���� ���������� ������, ������ ������� ������ �����������
		{
			printf("syntax error");
			freeHead(&operStack);
			return EOF;
		}
		if (IsOperator(input[i]) == 1) //���� ��������
		{
			if (input[i] == '(')		//���� ������ - ����������� ������
				push(&operStack, input[i]); //���������� � � ����
			else if (input[i] == ')')	//���� ������ - ����������� ������
			{
				char s = pop(&operStack);	//���������� ��� ��������� �� ����������� ������ � ������
				while (s != '(')
				{
					int k = getSize(operStack);
					if (k == 0)	//���� � ����� ��� ���������, � �� ����������� ������ �� �����, ������ ������� ������ �����������
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
			else //���� ����� ������ ��������
			{
				if (input[i] == 's') //���� s ��������� sin ��� ��� ���
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
				if (input[i] == 'c')	//���� c ��������� cos ��� ��� ���
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
				if (input[i] == 'l')	//���� l ��������� ln ��� ��� log ��� ������
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
				if (input[i] == 'm')	//���� m ��������� max ��� ��� ���
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
				if (getSize(operStack) != 0) //���� � ����� ���� ��������
					while ((GetPriority(input[i]) <= GetPriority(peek(operStack)))&&(peek(operStack)!=EOF))//� ���� ��������� ������ ��������� ������ ��� ����� ���������� ��������� �� ������� �����
					{
						*output = pop(&operStack); //�� ��������� ��������� �������� �� ����� � ������ � ����������
						output++;
						*output = ' ';
						output++;
					} 
				push(&operStack, input[i]); //���� ���� ����, ��� �� ��������� ��������� ���� - ��������� ���������� �� ������� �����
			}
		}
		else
			if (isDigit(input[i]) == 1) //���� ������ - �����, �� ��������� ��� �����
			{
				{
					while ((input[i] != ',') && (IsOperator(input[i]) == EOF) && (isDigit(input[i]) == 1))	//������ �� ����������� ��� ���������, ��� �� �������� �����
					{
							*output = input[i]; //��������� ������ ����� ����� � ����� ������
							output++;
							i++;				//��������� � ���������� �������
							if (i == len) break; //���� ������ - ���������, �� ������� �� �����
					}
					*output = ' '; //���������� ����� ����� ������ � ������ � ����������
					output++;
					if ((input[i]) != ',')
					{
						i--;	//������������ �� ���� ������ �����, � ������� ����� ����������

					} 
				}
			}
			else //���� ����� ������ ������, ������ ������� ������ �����������.
			{
				printf("syntax error");
				freeHead(&operStack);
				return EOF;
			}
	}

	//����� ������ �� ���� ��������, ���������� �� ����� ��� ���������� ��� ��������� � ������
	while (getSize(operStack) != 0)
	{
		*output = pop(&operStack); //�� ��������� ��������� �������� �� ����� � ������ � ����������
		output++;
		*output = ' ';
		output++;
	}
	output--;
	*output = '\0';
	return 1;
}

/*������� ��������� �������� ���������.
input-������� ������ � ���.
len-����� ������� ������.
���������� �����-�������� ��������� ��� EOF ���� ������� ������ �����������.*/
type2 Counting(char* input, size_t len)
{
	type2 result, a, b;
	size_t len2;
	int i;
	Stack2 *temp = NULL; //C��� ��� �������
	char* str;
	str = (char*)malloc(998);
	result = 0;
	for (i = 0; i < len; i++) //��� ������� ������� � ������
	{
		if (isDigit(input[i]) == 1)	//���� ������ - �����, �� ������ ��� ����� � ���������� �� ������� �����
		{
			*str = '\0';
			while ((IsDelimeter(input[i]) == EOF) && (IsOperator(input[i]) == EOF)) //���� �� �����������
			{
				len2 = strlen(str);
				str[len2] = input[i];		//���������� ����� � ����� ������, �������� �� ������ �������
				str[len2 + 1] = '\0';
				i++;
				if (i == len) break;
			}
			push2(&temp, atoi(str)); //���������� � ���� ������ � ���� �����
			i--;
		}
		else if ((IsOperator(input[i]) == 1)||(input[i]=='e')) //���� ������ - ��������
		{
			a = pop2(&temp);		//����� ��� ��������� �������� �� �����
			b = pop2(&temp);
			if ((b == EOF) && (input[i]!='s') && (input[i] != 'c') && (input[i] != 'e') && (input[i] != 'l'))	//���� ������� ���, ������ ������� ������ �����������
			{
				printf("syntax error");
				freeHead2(&temp);
				free(str);
				return EOF;
			}
			switch (input[i]) //���������� ��� ���� ��������, �������� ���������
			{
			case '+': result = (b + a); break;
			case '-': result = (b - a); break;
			case '*': result = (b * a); break;
			case '/': if (a == 0)		//���� ������� �� ����, ������� ������
			{
				printf("division by zero");
				freeHead2(&temp);
				free(str);
				return EOF;
			}
					  else result = (b / a); break;
			case '(': 					//���� ����������� ������,������ ������� ������ �����������
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
			push2(&temp, result); //��������� ���������� ���������� ������� � ����
		}
	}
	result = peek2(temp);
	freeHead2(&temp);
	free(str);
	return result;//�������� ��������� ���� ���������� �� ����� � ���������� ���
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