#ifndef verificationH
#define verificationH
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*������� ��������� ���������� ������*/
int checkAmount();

//������� ��������� ������� �������
int checkInVertex(int N,int *S,int *F);

//������� ��������� ���������� �����
int checkLines(int N);

//������� ��������� ������� ������� � �� ���
int checkEdges(int N, int* a, int* b, int* w);
#endif