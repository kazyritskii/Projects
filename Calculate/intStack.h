#ifndef intStackH
#define intStackH
#include <stdio.h>
#include <stdlib.h>

typedef double type2;

//���� ��� �����.
typedef struct Stack2
{
	type2 value;
	struct Stack2 *next;
} Stack2;

/*������� ��������� ������� � ����.
head-������ �����.
value-����������� �������.*/
void push2(Stack2 **head, type2 value);

/*������� �������� ������� �� �����.
head-������ �����.
���������� ������� ���
���������� EOF ���� � ����� ��� ���������*/
type2 pop2(Stack2 **head);

/*������� ������ ������� ������� � �����.
head-������ �����.
���������� �������� �������� ��� EOF ���� ��������� ���.*/
type2 peek2(const Stack2* head);

/*������� ������� ����������� ��������� � �����.
head-������ �����.
���������� ����������� ��������� � �����.*/
int getSize2(const Stack2 *head);

/*������� ����������� ������ �����.
head-������ �����.*/
void freeHead2(Stack2** head);
#endif
