#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "verification.h"
#define Infinity -1
#define lenMax -2

/*Функция обнуляет матрицу смежностей
N-Кол-во вершин
edges-матрица смежностей*/
void nullEgdes(int N, int** edges)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			edges[i][j] = 0;
		}
	}
}

/*Функция ищет кратчайшие пути из вершины v
N-Кол-во вершин
edges-матрица смежностей*/
void findShortLen(int N,int** edges,int v,int** lenMin,char* x,int** h,int* k,int F)
{
	int i;
	for (i = 0; i < N; i++)			// Перебираем все вершины, смежные v, и ищем для них кратчайший путь
	{
		if (edges[v][i] == 0)continue; // Вершины i и v несмежные
		if (lenMin[0][i] == lenMin[0][v] + edges[v][i])
			*k=*k+1;
		if (x[i] == 0 && (((lenMin[0][v]>INT_MAX / 2) && (edges[v][i] >(INT_MAX - lenMin[0][v]))) || ((edges[v][i] > INT_MAX / 2) && (lenMin[0][v] > (INT_MAX - edges[v][i])))))
		{
			if (lenMin[0][i] == Infinity)
			{
				if (i == F)
					*k = *k + 1;
				lenMin[0][i] = lenMax;
				h[0][i] = v;
			}
		}
		else
			if (x[i] == 0 && ((lenMin[0][i]>lenMin[0][v] + edges[v][i]) || (lenMin[0][i] == Infinity)) && lenMin[0][i] != lenMax) //Если для вершины i еще не найден кратчайший путь и новый путь в i короче чем старый, то
			{
				if (i == F)
					*k = *k + 1;
				lenMin[0][i] = lenMin[0][v] + edges[v][i];	//запоминаем более короткую длину пути в
														//массив lenMin и
				h[0][i] = v;	//запоминаем, что v->i часть кратчайшего пути из s->i
			}
	}
}

/*Функция реализует алгоритм Дейкстры
N-Кол-во вершин
edges-матрица смежностей*/
void Deykstra(int N,int* k,int** edges, int**lenMin,int** h, int S,int F)
{
	int kk = 0;	//счетчик вершин равен нулю
	int w, v;
	int i;
	char *x; //Массив, содержащий единицы и нули для каждой вершины,
			 // x[i]=0 - еще не найден кратчайший путь в i-ю вершину,
			 // x[i]=1 - кратчайший путь в i-ю вершину уже найден
	x = (char*)malloc(N*sizeof(char));
	memset(x, 0, N*sizeof(char));	// нет кратчайшего пути ни для одной вершины
	h[0][S] = 0; // s - начало пути, поэтому этой вершине ничего не предшествует
	lenMin[0][S] = 0; // Кратчайший путь из s в s равен 0
	x[S] = 1; // Для вершины s найден кратчайший путь
	v = S;    // Делаем s текущей вершиной
	while (kk<N && v != -1)
	{
		findShortLen(N, edges, v, lenMin, x, h, k, F);
		// Ищем из всех длин некратчайших путей самый короткий
		w = INT_MAX;  // Для поиска самого короткого пути
		v = -1;            // В конце поиска v - вершина, в которую будет найден новый кратчайший путь. Она станет текущей вершиной
		for (i = N - 1; i >= 0; i--) // Перебираем все вершины.
		{
			if (x[i] == 0 && lenMin[0][i] <= w && lenMin[0][i] != Infinity && lenMin[0][i] != lenMax) // Если для вершины не найден кратчайший путь и если длина пути в вершину i меньше уже найденной, то
			{
				v = i; // текущей вершиной становится i-я вершина
				w = lenMin[0][i];
			}
		}
		x[v] = 1;
		kk++;
	}
}

/*Функция выводит длины путей из вершины S во все остальные
N-Кол-во вершин*/
void printShortLen(int N,int* lenMin)
{
	int i;
	for (i = 0; i < N; i++)
	{
		if (lenMin[i] == Infinity)
			printf("oo ");
		else
			if (lenMin[i] == lenMax)
				printf("INT_MAX+ ");
			else
				printf("%d ", lenMin[i]);
	}
}

/*Функция печатает выходные данные
N-Кол-во вершин*/
void printOutput(int N, int S, int F, int k,int* h,int* lenMin)
{
	int i;
	printShortLen(N, lenMin);
	printf("\n");
	if (S == F)
	{
		printf("%d", S + 1);
	}
	else
	{
		if (lenMin[F] == Infinity)
			printf("no path");
		else
			if ((k > 1) && (lenMin[F] == lenMax))
			{
				printf("overflow");
			}
			else
			{
				i = F;
				while (i != S)
				{
					printf("%d ", i + 1);
					i = h[i];
				}
				printf("%d ", i + 1);
			}
	}
}

void main()
{
	int i;
	int a = 0;
	int b=0;
	int w=0;
	int N, M;
	int S=0;
	int F=0;
	int k;
	int **edges;
	int *lenMin;  //lenMin[i] - длина кратчайшего пути от вершины s в i
	int *h;  //h[i] - вершина, предшествующая i-й вершине на кратчайшем пути
	N=checkAmount();
	if (N == EOF)
		return;
	if (checkInVertex(N,&S,&F) == EOF)
		return;
	M = checkLines(N);
	if (M == EOF)
		return;
	S = S - 1;
	F = F - 1;
	edges = (int**)malloc(N*sizeof(int*));
	for (i = 0; i < N; i++)
	{
		edges[i] = (int*)malloc(N*sizeof(int));
	}
	nullEgdes(N, edges);
	lenMin = (int*)malloc(N*sizeof(int));
	h = (int*)malloc(N*sizeof(int));
	for (i = 0; i < M; i++)
	{
		if (checkEdges(N, &a, &b, &w) == EOF)
			return;
		edges[a - 1][b - 1] = w;
		edges[b - 1][a - 1] = w;
	}
	for (i = 0; i < N; i++)
	{
		lenMin[i] = Infinity; //Сначала все кратчайшие пути из s в i равны бесконечности        
	}
	k = 0;	//счетчик кратчайших путей равен нулю
	Deykstra(N, &k, edges, &lenMin, &h, S, F);
	printOutput(N, S, F, k, h, lenMin);
	getchar();
	getchar();
}