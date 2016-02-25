#ifndef charStackH
#define charStackH
#include <stdio.h>
#include <stdlib.h>

typedef char type;

//���� ��� ��������.
typedef struct Stack 
{
	type value;
	struct Stack *next;
} Stack;

/*������� ��������� ������� ���������� ���� � ����.
head-������ �����.
value-����������� �������.*/
void push(Stack **head, type value);

/*������� �������� ������� ���������� ���� �� �����.
head-������ �����.
���������� ������� ���
���������� EOF ���� � ����� ��� ���������*/
type pop(Stack **head);

/*������� ������ ������� ������� ���������� ���� � �����.
head-������ �����.
���������� �������� �������� ��� EOF ���� ��������� ���.*/
type peek(const Stack* head);

/*������� ������� ����������� ��������� � �����.
head-������ �����.
���������� ����������� ��������� � �����.*/
int getSize(const Stack *head);

/*������� ����������� ������ �����.
head-������ �����.*/
void freeHead(Stack** head);
#endif