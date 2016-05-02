#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"intStack.h"

/*Структура списка
val-значение*/
typedef struct list
{
	int val;
	struct list *next;
}list;

/*функция обхода графа в глубину
k-индекс элемента
color-массив меток
edges-список сможностей
stack-указатель на стэк
возвращает 1, если обнаружен цикл, иначе 0*/
int dfs(int k,int* color,list* edges,Stack2** stack)
{
	list* buf;
	if (color[k-1] == 1)
		return 1;
	if (color[k-1] == 2)
		return 0;
	color[k - 1] = 1;
	buf = &edges[k - 1];
	while ((buf)&&(buf->val!=0))
	{
		if (dfs(buf->val, color, edges,stack) == 1)
			return 1;
		buf = buf->next;
	}
	push2(stack, k);
	color[k - 1] = 2;
	return 0;
}

/*Функция топологической сортировки
N-кол-во вершин
color-массив меток
edges-массив смежностей
stack-указатель на стэк
numbers-массив новых номеров
возвращает 0, если есть цикл, иначе 1*/
int top_sort(int N,int* color,list*edges,Stack2** stack,int*numbers)
{
	int cycle;//датчмк цикла
	int i;
	int deg;
	for (i = 1; i <= N; i++)
	{
		cycle = dfs(i, color, edges, stack);
		if (cycle == 1)
			return 0;
	}
	for (i = 0; i < N; i++)
	{
		deg = pop2(stack);
		numbers[i] = deg;
	}
	return 1;
}

void main()
{
	int N,M,i;
	int a,b;
	int k=0;
	int* color;
	list* edges;
	list* buf;
	Stack2* stack=NULL;
	Stack2** head = &stack;
	int* numbers;
	if (scanf("%d", &N) == EOF)
	{
		printf("bad number of lines");
		return;
	}
	else
	if ((N < 0) || (N>1000))//проверка входных данных
	{
		printf("bad number of vertices");
		return;
	}
	if(scanf("%d", &M)==EOF)
	{
		printf("bad number of lines");
		return;
	}
	if ((M<0) || (M>(N*(N + 1) / 2)))
	{
		printf("bad number of edges");
		return;
	}
	edges = (list*)malloc(N*sizeof(list));
	for (i = 0; i < N; i++)//обнуление массива и заполнение значений
	{
		edges[i].val = 0;
		edges[i].next = NULL;
	}
	for (i = 0; i < M; i++)//заполнение списков смежностей
	{
		if (scanf("%d %d", &a, &b) == EOF)
		{
			printf("bad number of lines");
			return;
		}
		else
		if ((a<1) || (a>N) || (b<1) || (b>N))
		{
			printf("bad vertex");
			return;
		}
		if (edges[a - 1].val == 0)
		{
			edges[a - 1].val = b;
		}
		else
		{
			buf = (list*)malloc(sizeof(list));
			buf->next = edges[a - 1].next;
			buf->val = b;
			edges[a - 1].next = buf;
		}
		k++;
	}
	if (k < M)
	{
		printf("bad number of lines");
		return;
	}
	color = (int*)malloc(N*sizeof(int));
	for (i = 0; i < N; i++)//обнуление меток
	{
		color[i] = 0;
	}
	numbers = (int*)malloc(N*sizeof(int));
	if (top_sort(N, color, edges, head, numbers) == 0)
	{
		printf("impossible to sort");
		return;
	}
	for (i = 0; i < N; i++)
	{
		printf("%d ", numbers[i]);
	}
	getchar();
	getchar();
}