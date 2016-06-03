#ifndef verificationH
#define verificationH
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*Функция проверяет Количество вершин*/
int checkAmount();

//Функция проверяет входные вершины
int checkInVertex(int N,int *S,int *F);

//Функция проверяет количество строк
int checkLines(int N);

//Функция проверяет смежные вершины и их вес
int checkEdges(int N, int* a, int* b, int* w);
#endif