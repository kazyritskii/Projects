#include "charStack.h"


/*������� ��������� ������� ���������� ���� � ����.
head-������ �����.
value-����������� �������.*/
void push(Stack **head, type value) 
{
	Stack *tmp;
	tmp = (Stack*)malloc(sizeof(Stack));
	tmp->next = *head;
	tmp->value = value;
	*head = tmp;
}

/*������� �������� ������� ���������� ���� �� �����.
head-������ �����.
���������� ������� ���
���������� EOF ���� � ����� ��� ���������*/
type pop(Stack **head) 
{
	Stack *out;
	type value;
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

/*������� ������ ������� ������� ���������� ���� � �����.
head-������ �����.
���������� �������� �������� ��� EOF ���� ��������� ���.*/
type peek(const Stack* head) 
{
	if (head == NULL) {
		return EOF;
	}
	return head->value;
}

/*������� ������� ����������� ��������� � �����.
head-������ �����.
���������� ����������� ��������� � �����.*/
int getSize(const Stack *head) 
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
void freeHead(Stack** head)
{
	Stack *tmp=NULL;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	free(*head);
}