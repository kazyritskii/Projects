#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*������� ��������� ������-������ �������� �������������.
arg1-��������� �� ������.*/
void input(char *arr)
{
	while ((*arr = getchar()) != '\n')
	{
		arr++;
	}
	*arr = '\0';
}

/*������� ��������� ��������������� ������ ������.
arg1-��������� �� ������*/
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

/*������� ��������� ������� �� ������������ �� �������� 0123456789
arg1-��������� �� ������.
���������� 1 ���� �������.
���������� 0 � ��������� ������.*/
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

/*������� ��������� �������� �� ������ ������������� �������� 0123456789 � ��� ������� �� �����������.
arg1-��������� �� ������.
���������� 1 ���� ��������.
���������� 0 � ��������� ������.*/
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

/*������� ������� ����� ���� ������.
arg1-��������� �� ������-������.
���������� ����� ������.*/
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

/*������� �������� � �������� ��������� ������������ ������� ��������.
arg1-��������� �� ������.
arg2-����� ������.*/
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