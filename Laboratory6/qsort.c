#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*������� �������� ������ � ��������� ��� �� �����������.
arg1-������
arg2-����� ������ ����������� �����
arg3-������ ������ ����������� �����*/
void quicksort(int* arr, int left, int right)
{
	int x, t;
	int i, j;
	i = left;
	j = right;
	x = arr[(left + right) / 2]; //������� �������
	do
	{
		while (arr[i] < x) //����� ����� �������� �������� ��� �������
			i++;
		while (x < arr[j]) //����� ������ �������� �������� ��� �������
			j--;
		if (i <= j)
		{
			t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
			i++;
			j--;
		}
	} while (i < j);
	if (left < j)
		quicksort(arr, left, j);
	if (i < right)
		quicksort(arr, i, right);
}

void main()
{
	int i;
	int len = 0;
	int *arr;
	scanf("%d", &len);
	if (len != 0)
	{
		arr = (int*)malloc(sizeof(int)*len);

		for (i = 0; i < len; i++)
		{
			scanf("%d", &arr[i]);
		}
		quicksort(arr, 0, (len-1));
		for (i = 0; i < len; i++)
		{
			printf("%d ", arr[i]);
		}
		free(arr);
	}
	else return;
	getchar();
	getchar();
}