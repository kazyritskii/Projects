#include "verification.h"

/*Функция проверяет Количество вершин*/
int checkAmount()
{
	int N;
	if (scanf("%d", &N) == EOF)
	{
		printf("bad number of lines");
		return EOF;
	}
	else
		if ((N < 0) || (N>5000))//проверка входных данных
		{
			printf("bad number of vertices");
			return EOF;
		}
		else
			return N;
}

/*Функция проверяет входные вершины
N-Кол-во вершин*/
int checkInVertex(int N,int* S,int* F)
{
	if (scanf("%d %d", S, F) == EOF)
	{
		printf("bad number of lines");
		return EOF;
	}
	else
		if ((*S<1) || (*S>N) || (*F<1) || (*F>N))
		{
			printf("bad vertex");
			return EOF;
		}
		else
			return *S;
}

/*Функция проверяет количество строк
N-Кол-во вершин*/
int checkLines(int N)
{
	int M;
	if (scanf("%d", &M) == EOF)
	{
		printf("bad number of lines");
		return EOF;
	}
	else
		if ((M<0) || (M>(N*(N + 1) / 2)))
		{
			printf("bad number of edges");
			return EOF;
		}
		else
			return M;
}

/*Функция проверяет смежные вершины и их вес
N-Кол-во вершин*/
int checkEdges(int N, int* a, int* b, int* w)
{
	if (scanf("%d %d %d", a, b, w) == EOF)
	{
		printf("bad number of lines");
		return EOF;
	}
	else 
	{
		if ((*a<1) || (*a>N) || (*b<1) || (*b>N))
		{
			printf("bad vertex");
			return EOF;
		}
		if ((*w<0) || (*w>INT_MAX))
		{
			printf("bad length");
			return EOF;
		}
	}
	return *w;
}