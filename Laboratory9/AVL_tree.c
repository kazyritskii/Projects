#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//Структура дерева.
typedef struct tree
{
	int val;
	int height;
	struct tree *left;
	struct tree *right;
}Tree;

/*Функция создает новую вершину дерева со значением Dig.
Dig-добавляемое число.
Возвращает указатель на новую вершину.*/
Tree* newTree(int Dig)
{
	Tree* head;
	head = (Tree*)malloc(sizeof(Tree));
	head->right = NULL;
	head->left = NULL;
	head->val = Dig;
	head->height = 1;
	return head;
}

/*Функция возвращает высоту поддерева, если поддерева нет, возвращает 0.
head-вершина поддерева.*/
int height(Tree* head)
{
	if (head)
		return head->height;
	else
		return 0;
}

/*Функция возвращает разницу высот левого и правого поддерева.
head-вершина дерева.*/
int balance(Tree* head)
{
	return (height(head->right) - height(head->left));
}

/*Функция пересчитывает высоту данной вершины после добавления нового элемента.
head-вершина дерева.*/
void fixHeight(Tree* head)
{
	int hl = height(head->left);
	int hr = height(head->right);
	if (hl > hr)
	{
		head->height = (hl+1);
	}
	else
		head->height = (hr+1);
}

/*Функция реализует малый правый поворот.
head-вершина дерева.
Возвращает указатель на новую вершину.*/
Tree* right(Tree* head)
{
	Tree* b = head->left;
	head->left = b->right;
	b->right = head;
	fixHeight(head);
	fixHeight(b);
	return b;
}

/*Функция реализует малый левый поворот.
head-вершина дерева.
Возвращает указатель на новую вершину.*/
Tree* left(Tree* head)
{
	Tree* b = head->right;
	head->right = b->left;
	b->left = head;
	fixHeight(head);
	fixHeight(b);
	return b;
}

/*Функция реализует ребалансировку дерева.
head-вершина дерева.
Возвращает указатель на новую вершину.*/
Tree* reBalance(Tree* head)
{
	fixHeight(head);
	if (balance(head) == 2)
	{
		if (balance(head->right) < 0)
			head->right = right(head->right);
		return left(head);
	}
	if (balance(head) == -2)
	{
		if (balance(head->left) > 0)
			head->left = left(head->left);
		return right(head);
	}
	return head;
}

/*Функция добавляет новый элемент дерева и совершает его балансировку если это нужно.
head-вершина дерева.
Dig-добавляемый элемент.
Возвращает указатель на вершину.*/
Tree* put(Tree *head, int Dig)
{
	if (!head)
	{
		head = newTree(Dig);
		return head;
	}
	else
	{
		if (Dig < head->val)
		{
			head->left = put(head->left, Dig);
		}
		else
		{
			head->right = put(head->right, Dig);
		}
		return reBalance(head);
	}
}

/*Функция проверяет является ли вершина листом.
head-вершина.
Возвращает 1, если вершина лист, в противном случае 0.*/
int isList(Tree* head)
{
	if ((!head->left) && (!head->right))
		return 1;
	return 0;
}

/*Функция удаляет дерево.
head-вершина.*/
void freeTree(Tree* head)
{
	if (isList(head) == 0)
	{
		if(head->left)
			freeTree(head->left);
		if(head->right)
			freeTree(head->right);
		free(head);
	}
	else
		free(head);
}

void main()
{
	int Dig=0;
	int N=0;
	Tree *head=NULL;
	scanf("%d", &N);
	if (N == 0)
		printf("%d", 0);
	else
	{
		while (N != 0)
		{
			scanf("%d", &Dig);
			head = put(head, Dig);
			N--;
		}
		printf("%d", head->height);
		freeTree(head);
	}
	getchar();
	getchar();
}