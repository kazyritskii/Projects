#ifndef charStackH
#define charStackH
#include <stdio.h>
#include <stdlib.h>

typedef char type;

//Стек для символов.
typedef struct Stack 
{
	type value;
	struct Stack *next;
} Stack;

/*функция добавляет элемент строкового типа в стек.
head-голова стека.
value-добавляемый элемент.*/
void push(Stack **head, type value);

/*функция вынимает элемент строкового типа из стека.
head-голова стека.
Возвращает элемент или
Возвращает EOF если в стеке нет элементов*/
type pop(Stack **head);

/*Функция читает верхний элемент строкового типа в стеке.
head-голова стека.
Возвращает значение элемента или EOF если элементов нет.*/
type peek(const Stack* head);

/*Функция считает колличество элементов в стеке.
head-голова стека.
Возвращает колличество элементов в стеке.*/
int getSize(const Stack *head);

/*Функция освобождает память стека.
head-голова стека.*/
void freeHead(Stack** head);
#endif