#include "intStack.h"


/*������� ��������� ������� � ����.
head-������ �����.
value-����������� �������.*/
void push2(Stack2 **head, type2 value)
{
	Stack2 *tmp;
	tmp = (Stack2*)malloc(sizeof(Stack2));
	tmp->next = *head;
	tmp->value = value;
	*head = tmp;
}

/*������� �������� ������� �� �����.
head-������ �����.
���������� ������� ���
���������� EOF ���� � ����� ��� ���������*/
type2 pop2(Stack2 **head)
{
	Stack2 *out;
	type2 value;
	if (*head == NULL)
	{
		return EOF;
	}
	out = *head;
	*head = (*head)->next;
	value = out->value;
	free(out);
	return value;
}

/*������� ������ ������� ������� � �����.
head-������ �����.
���������� �������� �������� ��� EOF ���� ��������� ���.*/
type2 peek2(const Stack2* head)
{
	if (head == NULL) {
		return EOF;
	}
	return head->value;
}

/*������� ������� ����������� ��������� � �����.
head-������ �����.
���������� ����������� ��������� � �����.*/
int getSize2(const Stack2 *head)
{
	int size = 0;
	while (head)
	{
		size++;
		head = head->next;
	}
	return size;
}

/*������� ����������� ������ �����.
head-������ �����.*/
void freeHead2(Stack2** head)
{
	Stack2 *tmp = NULL;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	free(*head);
}