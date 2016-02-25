#include "charStack.h"


/*функция добавляет элемент строкового типа в стек.
head-голова стека.
value-добавляемый элемент.*/
void push(Stack **head, type value) 
{
	Stack *tmp;
	tmp = (Stack*)malloc(sizeof(Stack));
	tmp->next = *head;
	tmp->value = value;
	*head = tmp;
}

/*функция вынимает элемент строкового типа из стека.
head-голова стека.
Возвращает элемент или
Возвращает EOF если в стеке нет элементов*/
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

/*Функция читает верхний элемент строкового типа в стеке.
head-голова стека.
Возвращает значение элемента или EOF если элементов нет.*/
type peek(const Stack* head) 
{
	if (head == NULL) {
		return EOF;
	}
	return head->value;
}

/*Функция считает колличество элементов в стеке.
head-голова стека.
Возвращает колличество элементов в стеке.*/
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

/*Функция освобождает память стека.
head-голова стека.*/
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