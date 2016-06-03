#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "verification.h"
#define Infinity -1
#define lenMax -2

/*������� �������� ������� ����������
N-���-�� ������
edges-������� ����������*/
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

/*������� ���� ���������� ���� �� ������� v
N-���-�� ������
edges-������� ����������*/
void findShortLen(int N,int** edges,int v,int** lenMin,char* x,int** h,int* k,int F)
{
	int i;
	for (i = 0; i < N; i++)			// ���������� ��� �������, ������� v, � ���� ��� ��� ���������� ����
	{
		if (edges[v][i] == 0)continue; // ������� i � v ���������
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
			if (x[i] == 0 && ((lenMin[0][i]>lenMin[0][v] + edges[v][i]) || (lenMin[0][i] == Infinity)) && lenMin[0][i] != lenMax) //���� ��� ������� i ��� �� ������ ���������� ���� � ����� ���� � i ������ ��� ������, ��
			{
				if (i == F)
					*k = *k + 1;
				lenMin[0][i] = lenMin[0][v] + edges[v][i];	//���������� ����� �������� ����� ���� �
														//������ lenMin �
				h[0][i] = v;	//����������, ��� v->i ����� ����������� ���� �� s->i
			}
	}
}

/*������� ��������� �������� ��������
N-���-�� ������
edges-������� ����������*/
void Deykstra(int N,int* k,int** edges, int**lenMin,int** h, int S,int F)
{
	int kk = 0;	//������� ������ ����� ����
	int w, v;
	int i;
	char *x; //������, ���������� ������� � ���� ��� ������ �������,
			 // x[i]=0 - ��� �� ������ ���������� ���� � i-� �������,
			 // x[i]=1 - ���������� ���� � i-� ������� ��� ������
	x = (char*)malloc(N*sizeof(char));
	memset(x, 0, N*sizeof(char));	// ��� ����������� ���� �� ��� ����� �������
	h[0][S] = 0; // s - ������ ����, ������� ���� ������� ������ �� ������������
	lenMin[0][S] = 0; // ���������� ���� �� s � s ����� 0
	x[S] = 1; // ��� ������� s ������ ���������� ����
	v = S;    // ������ s ������� ��������
	while (kk<N && v != -1)
	{
		findShortLen(N, edges, v, lenMin, x, h, k, F);
		// ���� �� ���� ���� ������������ ����� ����� ��������
		w = INT_MAX;  // ��� ������ ������ ��������� ����
		v = -1;            // � ����� ������ v - �������, � ������� ����� ������ ����� ���������� ����. ��� ������ ������� ��������
		for (i = N - 1; i >= 0; i--) // ���������� ��� �������.
		{
			if (x[i] == 0 && lenMin[0][i] <= w && lenMin[0][i] != Infinity && lenMin[0][i] != lenMax) // ���� ��� ������� �� ������ ���������� ���� � ���� ����� ���� � ������� i ������ ��� ���������, ��
			{
				v = i; // ������� �������� ���������� i-� �������
				w = lenMin[0][i];
			}
		}
		x[v] = 1;
		kk++;
	}
}

/*������� ������� ����� ����� �� ������� S �� ��� ���������
N-���-�� ������*/
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

/*������� �������� �������� ������
N-���-�� ������*/
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
	int *lenMin;  //lenMin[i] - ����� ����������� ���� �� ������� s � i
	int *h;  //h[i] - �������, �������������� i-� ������� �� ���������� ����
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
		lenMin[i] = Infinity; //������� ��� ���������� ���� �� s � i ����� �������������        
	}
	k = 0;	//������� ���������� ����� ����� ����
	Deykstra(N, &k, edges, &lenMin, &h, S, F);
	printOutput(N, S, F, k, h, lenMin);
	getchar();
	getchar();
}