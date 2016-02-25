#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*функция получает массив и сортирует его по возрастанию.
arg1-массив
arg2-левый индекс сортируемой части
arg3-правый индекс сортируемой части*/
void quicksort(int* arr, int left, int right)
{
	int x, t;
	int i, j;
	i = left;
	j = right;
	x = arr[(left + right) / 2]; //средний элемент
	do
	{
		while (arr[i] < x) //Поиск слева элемента большего чем средний
			i++;
		while (x < arr[j]) //Поиск справа элемента меньшего чем средний
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