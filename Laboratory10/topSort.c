#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"intStack.h"

/*��������� ������
val-��������*/
typedef struct list
{
	int val;
	struct list *next;
}list;

/*������� ������ ����� � �������
k-������ ��������
color-������ �����
edges-������ ����������
stack-��������� �� ����
���������� 1, ���� ��������� ����, ����� 0*/
int dfs(int k,int* color,list* edges,Stack2** stack)
{
	list* buf;
	if (color[k-1] == 1)
		return 1;
	if (color[k-1] == 2)
		return 0;
	color[k - 1] = 1;
	buf = edges[k - 1].next;
	while (buf)
	{
		if (dfs(buf->val, color, edges,stack) == 1)
			return 1;
		buf = buf->next;
	}
	push2(stack, edges[k - 1].val);
	color[k - 1] = 2;
	return 0;
}

/*������� �������������� ����������
N-���-�� ������
color-������ �����
edges-������ ����������
stack-��������� �� ����
numbers-������ ����� �������
���������� 0, ���� ���� ����, ����� 1*/
int top_sort(int N,int* color,list*edges,Stack2** stack,int*numbers)
{
	int cycle;//������ �����
	int i;
	for (i = 1; i <= N; i++)
	{
		cycle = dfs(i, color, edges, stack);
		if (cycle == 1)
			return 0;
	}
	for (i = 0; i < N; i++)
	{
		numbers[pop2(stack)-1] = i+1;
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
	scanf("%d", &N);
	if ((N < 0) || (N>1000))//�������� ������� ������
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
	for (i = 0; i < N; i++)//��������� ������� � ���������� ��������
	{
		edges[i].val = i + 1;
		edges[i].next = NULL;
	}
	for (i = 0; i < M; i++)//���������� ������� ����������
	{
		scanf("%d %d", &a, &b);
		if ((a<1) || (a>N) || (b<1) || (b>N))
		{
			printf("bad vertex");
			return;
		}
		buf = &edges[a - 1];
		buf = (list*)malloc(sizeof(list));
		buf->next = edges[a - 1].next;
		buf->val = b;
		edges[a - 1].next = buf;
		k++;
	}
	if (k < M)
	{
		printf("bad number of lines");
		return;
	}
	color = (int*)malloc(N*sizeof(int));
	for (i = 0; i < N; i++)//��������� �����
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