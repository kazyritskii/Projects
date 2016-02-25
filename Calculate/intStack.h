#ifndef intStackH
#define intStackH
#include <stdio.h>
#include <stdlib.h>

typedef double type2;

//Стек для чисел.
typedef struct Stack2
{
	type2 value;
	struct Stack2 *next;
} Stack2;

/*функция добавляет элемент в стек.
head-голова стека.
value-добавляемый элемент.*/
void push2(Stack2 **head, type2 value);

/*функция вынимает элемент из стека.
head-голова стека.
Возвращает элемент или
Возвращает EOF если в стеке нет элементов*/
type2 pop2(Stack2 **head);

/*Функция читает верхний элемент в стеке.
head-голова стека.
Возвращает значение элемента или EOF если элементов нет.*/
type2 peek2(const Stack2* head);

/*Функция считает колличество элементов в стеке.
head-голова стека.
Возвращает колличество элементов в стеке.*/
int getSize2(const Stack2 *head);

/*Функция освобождает память стека.
head-голова стека.*/
void freeHead2(Stack2** head);
#endif
