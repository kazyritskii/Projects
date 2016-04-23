#include "intStack.h"


/*функция добавляет элемент в стек.
head-голова стека.
value-добавляемый элемент.*/
void push2(Stack2 **head, type2 value)
{
	Stack2 *tmp;
	tmp = (Stack2*)malloc(sizeof(Stack2));
	tmp->next = *head;
	tmp->value = value;
	*head = tmp;
}

/*функция вынимает элемент из стека.
head-голова стека.
Возвращает элемент или
Возвращает EOF если в стеке нет элементов*/
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

/*Функция читает верхний элемент в стеке.
head-голова стека.
Возвращает значение элемента или EOF если элементов нет.*/
type2 peek2(const Stack2* head)
{
	if (head == NULL) {
		return EOF;
	}
	return head->value;
}

/*Функция считает колличество элементов в стеке.
head-голова стека.
Возвращает колличество элементов в стеке.*/
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

/*Функция освобождает память стека.
head-голова стека.*/
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