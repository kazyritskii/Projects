#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*������� �������� ����� ������� � ���� ��������.
arg1-������
arg2-������������ �������
arg3-����� �������*/
void Sift(int* a, int i, int len)
{
	int left, right, max;
	int t;
	i++;
	while ((left = 2 * i) <= len)
	{
		right = (left + 1 <= len) ? left + 1 : i;
		if ((a[i - 1] >= a[left - 1]) && (a[i - 1] >= a[right - 1]))
			return;
		max = (a[left - 1] >= a[right - 1]) ? left : right;
		t = a[i - 1];
		a[i - 1] = a[max - 1];
		a[max - 1] = t;
		i = max;
	}
}

/*������� �������� ���� ������ � ���� �������� � ��������� �� �����������.
arg1-������
arg2-����� �������*/
void heap_sort(int* arr, int len)
{
	int i;
	int t;
	for (i = (len / 2); i >= 0; i--)
	{
		Sift(arr, i, len);
	}
	if (arr[0] == arr[len])
	{
		return;
	}
	else
	{

		for (i = (len - 1); i > 0; i--)
		{
			t = arr[0];
			arr[0] = arr[i];
			arr[i] = t;
			Sift(arr, 0, i);
		}
	}
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
		heap_sort(arr, len);
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