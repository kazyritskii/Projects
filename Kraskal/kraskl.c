#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct edge_t {
	int n1, n2;  // направление
	int w;      // вес ребра
} edge_t;

typedef struct set_t {
	struct set_t *p;  
} set_t;

// ‘ункци€ "сравнени€" двух ребер, используема€ дл€ сортировки
int cmpw(edge_t *a, edge_t *b)
{
	if (a->w > b->w) return 1;
	if (a->w < b->w) return -1;
	return 0;
}

set_t* get_set_id(set_t* s)
{
	if (s == s->p)
		return s;
	else {
		set_t *p = get_set_id(s->p);
		s->p = p;
		return p;
	}
}

set_t* join_sets(set_t *a, set_t *b)
{
	a->p = b;
	return a;
}

//‘ункци€ вывода ребер
void take_edge(int edge_id, edge_t *E)
{
	printf("%d %d\n", E[edge_id].n1, E[edge_id].n2);
}

void main()
{
	int i;
	int k = 0;
	int NS;      
	set_t *sets; // массив вершин
	int M;      // кол-во ребер
	edge_t *E;   // массив ребер
	int N;      // кол-во вершин
	if (scanf("%d", &N) == EOF)
	{
		printf("bad number of lines");
		return;
	}
	else
		if ((N < 0) || (N>5000))//проверка входных данных
		{
			printf("bad number of vertices");
			return;
		}
	if (scanf("%d", &M) == EOF)
	{
		printf("bad number of lines");
		return;
	}
	if ((M<0) || (M>(N*(N + 1) / 2)))
	{
		printf("bad number of edges");
		return;
	}
	E = (edge_t*)malloc((M + 1) * sizeof(edge_t));
	sets = (set_t*)malloc((N + 1) * sizeof(set_t));
	for (i = 1; i <= M; i++)
	{
		if (scanf("%d %d %d", &E[i].n1, &E[i].n2, &E[i].w) == EOF)
		{
			printf("bad number of lines");
			return;
		}
		else
		{
			if ((E[i].n1<1) || (E[i].n1>N) || (E[i].n2<1) || (E[i].n2>N))
			{
				printf("bad vertex");
				return;
			}
			if ((E[i].w<0) || (E[i].w>INT_MAX))
			{
				printf("bad length");
				return;
			}
		}
	}
	qsort(&E[1], M, sizeof(edge_t), (int(*)(const void*, const void*)) cmpw);
	NS = N;
	for (i = 1; i <= NS; i++)
		sets[i].p = &sets[i];
	for (i = 1; NS > 1 && i <= M; i++)
	{
		// если ребро не может быть добавлено в дерево, переходим к следующему
		if (get_set_id(&sets[E[i].n1]) == get_set_id(&sets[E[i].n2]))
			continue;
		// ƒобавл€ем ребро к дереву
		join_sets(get_set_id(&sets[E[i].n1]), get_set_id(&sets[E[i].n2]));
		NS--;
		k++;
		E[k] = E[i];
	}
	if (NS != 1)
		printf("no spanning tree");
	else
	{
		for (i = 1; i <= k; i++)
		{
			take_edge(i, E);
		}
	}
	getchar();
	getchar();
	free(E);
	free(sets);
}