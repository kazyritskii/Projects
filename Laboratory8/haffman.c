#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
/*Структура дерева.
val-символ
priority-частота встречаемости
code-код символа*/
typedef struct tree
{
	unsigned char val;
	float priority;
	char code[255];
	struct tree *left;
	struct tree *right;
}Tree;

/*Объединение сомвола
simb-символ
byte-битовое представление символа*/
union code
{
	unsigned char simb;

	struct byte
	{
		unsigned b1 : 1;
		unsigned b2 : 1;
		unsigned b3 : 1;
		unsigned b4 : 1;
		unsigned b5 : 1;
		unsigned b6 : 1;
		unsigned b7 : 1;
		unsigned b8 : 1;
	}byte;
};

/*Функция сортировки массива по возрастанию частоты встречаемости
simbols-массив символов
k-кол-во символов*/
Tree* sort(Tree* simbols, int k)
{
	Tree temp;
	int i;
	int j;
	for (i = 1; i < k; i++)
	{
		for (j = 0; j<k - 1; j++)
		{

			if (simbols[j].priority > simbols[j + 1].priority)
			{
				temp = simbols[j];
				simbols[j] = simbols[j + 1];
				simbols[j + 1] = temp;
			}
		}
	}
		
	return simbols;
}

/*Функция обнуления структур массива
simbols-массив структур*/
void null(Tree* simbols)
{
	int i;
	for (i = 0; i < 256; i++)
	{
		simbols[i].val = 0;
		simbols[i].priority = 0;
		simbols[i].left = NULL;
		simbols[i].right = NULL;
	}
}

/*Функция обнуления вершины дерева
node-указатель на вершину*/
void nullNode(Tree* node)
{
	node->val = 0;
	node->priority = 0;
	node->left = NULL;
	node->right = NULL;
}

/*Функция проверки вершины на лист
head-указатель на вершину
возвращает 1, если head-лист, иначе 0*/
int isList(Tree* head)
{
	if ((head->left == NULL) && (head->right == NULL))
		return 1;
	else return 0;
}

/*Рeкурсивная функция создания дерева Хаффмана
stack-массив вершин
k-кол-во уникальных символов
all-кол-во всех символов
возвращает указатель на дерево Хаффмана*/
Tree *makeTree(Tree *stack[], int k, int all)
{
	int i;
	int j;
	Tree *temp;
	temp = (Tree*)malloc(sizeof(Tree));
	temp->val = 0;
	temp->priority = stack[k]->priority + stack[k + 1]->priority;
	temp->code[0] = 0;
	temp->left = stack[k];
	temp->right = stack[k + 1];

	if ((all-k) == 2)
		return temp;
	else //внесение в массив в нужное место элемента дерева Хаффмана
	{
		for (i = k; i < all; i++)
		{
			if (temp->priority <= stack[i]->priority)
			{
				i--;
				for (j = k; j<i; j++)
					stack[j] = stack[j + 1];

				stack[i] = temp;
				break;
			}
		}
		if (i == all)
		{
			for (j = k; j<i; j++)
				stack[j] = stack[j + 1];

			stack[i-1] = temp;
		}
			
	}
	return makeTree(stack, k + 1, all);
}

/*Рекурсивная функция создания кода для каждого символа
root-указатель на вершину*/
void makeCodes(Tree *root)
{
	if (root->left)
	{
		strcpy(root->left->code, root->code);
		strcat(root->left->code, "0");
		makeCodes(root->left);
	}
	if (root->right)
	{
		strcpy(root->right->code, root->code);
		strcat(root->right->code, "1");
		makeCodes(root->right);
	}
}

/*Рекурсивная функция записи дерева Хаффмана в файл
head-указатель на вершину
file-указатель на файл*/
void writeTree(Tree *head, FILE* file)
{
	union code code1;
	if (isList(head)==0)
	{
		fputs("0", file);//пишем 0 если не лист
		writeTree(head->left,file);
		writeTree(head->right,file);
	}
	else
	{
		fputs("1", file);//пишем 1 и код символа если лист
		code1.simb = head->val;		
		fputc(code1.byte.b1 + '0', file);
		fputc(code1.byte.b2 + '0', file);
		fputc(code1.byte.b3 + '0', file);
		fputc(code1.byte.b4 + '0', file);
		fputc(code1.byte.b5 + '0', file);
		fputc(code1.byte.b6 + '0', file);
		fputc(code1.byte.b7 + '0', file);
		fputc(code1.byte.b8 + '0', file);
	}
}

/*Рекурсивная функция создания дерева Хаффмана при декодировании
head-указатель на вершину
file-указатель на файл*/
void createTree(Tree* head, FILE *file)
{
	int simb;
	int i;
	int j;
	Tree *node1,*node2;
	char arr[8];
	union code code1;
	if ((simb = getc(file)) == '0')//если 0, то создаем новую вершину
	{
		node1 = (Tree*)malloc(sizeof(Tree));
		nullNode(node1);
		node1->code[0] = 0;
		head->left = node1;
		createTree(head->left, file);
		node2 = (Tree*)malloc(sizeof(Tree));
		nullNode(node2);
		node2->code[0] = 0;
		head->right = node2;
		createTree(head->right, file);
	}
	else//если 1, то считываем код символа
	{
		j = 0;
		for (i = 0; i < 8; i++)
		{
			arr[j] = fgetc(file);
			if (j == 7)
			{
				code1.byte.b1 = arr[0] - '0';
				code1.byte.b2 = arr[1] - '0';
				code1.byte.b3 = arr[2] - '0';
				code1.byte.b4 = arr[3] - '0';
				code1.byte.b5 = arr[4] - '0';
				code1.byte.b6 = arr[5] - '0';
				code1.byte.b7 = arr[6] - '0';
				code1.byte.b8 = arr[7] - '0';
				head->val = code1.simb;
			}
			j++;
		}
	}
}

/*Рекурсивная функция поиска листа с нужным кодом
head-указатель на вершину
code[]-код
возвращает символ,если его код равен искомому, иначе возвращает EOF*/
int findList(Tree* head, char code[255])
{
	int simb1;
	int simb2;
	if (isList(head) == 0)//если не лист, ищем слева и справа
	{
		simb1=findList(head->left,code);
		simb2=findList(head->right,code);
	}
	else//если лист, сравниваем код символа и входной код
	{
		if (strcmp(code,head->code)==0)
		{
			return head->val;
		}
		else
			return EOF;
	}
	if (simb1!=EOF)
		return simb1;
	else
		if (simb2!=EOF)
			return simb2;
		else
			return EOF;
}

/*Функция удаляет дерево.
head-вершина.*/
void freeTree(Tree* head)
{
	if (isList(head) == 0)
	{
		if (head->left)
			freeTree(head->left);
		if (head->right)
			freeTree(head->right);
		free(head);
	}
	else
		free(head);
}

void main()
{
	FILE *inFile, *buffer, *outFile, *buffer2;
	int prm;//параметр
	int simb=0;//символ
	int i;
	int j;
	int all = 0;//общее кол-во символов
	int k = 0;//кол-во уникальных символов
	int amount[256] = { 0 };//счетчик встречаемости символов
	int fsize = 0;//длина файла
	int tail;//длина хвоста
	char arr[8];
	char code[255] = { 0 };
	int len;
	Tree *simbols;//массив структур
	Tree **stack;//массив вершин
	Tree *head;//голова дерева Хаффмана
	union code code1;
	inFile = fopen("in.txt", "rb");
	if (inFile)
	{
		prm = fgetc(inFile);
		if (prm == 'c')//если c,то кодирование
		{
			simbols = (Tree*)malloc(256 * sizeof(Tree));
			null(simbols);
			fread(&prm, 2, 1, inFile);
			while ((fread(&simb,1,1,inFile)) != 0)//до конца файла считываем символы
			{
				for (i = 0; i < 256; i++)
				{
					if ((simbols[i].val == 0)&&(amount[i]==0))
					{
						simbols[i].val = simb;
						amount[i] = 1;
						k++; all++;
						break;
					}

					if (simb == simbols[i].val)
					{
						amount[i]++;
						all++;
						break;
					}

				}
			}
			if (k == 0)//если кол-во символов равно 0, заканчиваем работу
				return;
			simbols = (Tree*)realloc(simbols, k*sizeof(Tree));
			for (i = 0; i < k; i++)
				simbols[i].priority = (float)amount[i] / all;//считаем частоту встречаемости для каждого символа
			simbols = sort(simbols, k);
			stack = (Tree**)malloc(k*sizeof(Tree*));
			for (i = 0; i < k; i++) //в массив указателей заносим адреса вершин
				stack[i] = &simbols[i];
			if (k > 1)//если уникальных символов > 1, то создаем дерево
				head = makeTree(stack, 0, k);
			else //иначе код символа 0
			{
				head = stack[0];
				head->code[0] = '0';
				head->code[1] = 0;
			}
			makeCodes(head);//генерируем код для каждого символа
			buffer = fopen("buffer.txt", "w");
			rewind(inFile);
			fread(&prm, 3, 1, inFile);
			writeTree(head, buffer);//открываем буфер и записываем дерево в бинарном виде
			while ((fread(&simb, 1, 1, inFile)) != 0)//кодируем каждый символ
			{
				for (int i = 0; i < k; i++)
				{
					if (simb == simbols[i].val)
					{
						fputs(simbols[i].code, buffer);
					}
				}
			}
			fclose(buffer);
			buffer = fopen("buffer.txt", "r");
			while ((simb = fgetc(buffer)) != EOF)	//Считаем размер бинарного файла(количество символов в нём)
				fsize++;
			tail = fsize % 8;//находим остаток, количество символов не кратных 8 (хвост)
			rewind(buffer);
			buffer2 = fopen("buffer2.txt", "w");
			code1.simb = (char)(tail);//записываем в буфер размер хвоста
			fputc(code1.byte.b1 + '0', buffer2);
			fputc(code1.byte.b2 + '0', buffer2);
			fputc(code1.byte.b3 + '0', buffer2);
			fputc(code1.byte.b4 + '0', buffer2);
			fputc(code1.byte.b5 + '0', buffer2);
			fputc(code1.byte.b6 + '0', buffer2);
			fputc(code1.byte.b7 + '0', buffer2);
			fputc(code1.byte.b8 + '0', buffer2);
			for (i = 0; i < fsize; i++)
			{
				simb = fgetc(buffer);
				fputc(simb, buffer2);
			}
			fclose(buffer);
			fclose(buffer2);
			buffer = fopen("buffer2.txt", "r");
			outFile = fopen("out.txt", "wb");
			fsize = fsize + 8;
			j = 0;
			for (i = 0; i < fsize - tail; i++)//пишем в файл символы побайтово
			{
				arr[j] = fgetc(buffer);
				if (j == 7)
				{
					code1.byte.b1 = arr[0] - '0';
					code1.byte.b2 = arr[1] - '0';
					code1.byte.b3 = arr[2] - '0';
					code1.byte.b4 = arr[3] - '0';
					code1.byte.b5 = arr[4] - '0';
					code1.byte.b6 = arr[5] - '0';
					code1.byte.b7 = arr[6] - '0';
					code1.byte.b8 = arr[7] - '0';
					fwrite(&code1.simb, 1, 1, outFile);
					j = -1;
				}
				j++;
			}
			if (tail != 0)
			{
				j = 0;
				for (i = 0; i <= tail; i++)	//Записываем хвост
				{
					arr[j] = fgetc(buffer);
					if (j == tail)
					{
						code1.byte.b1 = arr[0] - '0';
						code1.byte.b2 = arr[1] - '0';
						code1.byte.b3 = arr[2] - '0';
						code1.byte.b4 = arr[3] - '0';
						code1.byte.b5 = arr[4] - '0';
						code1.byte.b6 = arr[5] - '0';
						code1.byte.b7 = arr[6] - '0';
						code1.byte.b8 = arr[7] - '0';
						fwrite(&code1.simb, 1, 1, outFile);
					}
					j++;
				}
			}
			_fcloseall();
			free(simbols);
			free(stack);
			remove("buffer.txt");
			remove("buffer2.txt");
		}
		else
			if (prm == 'd')//если d, то декодирование
			{
				fread(&prm, 2, 1, inFile);
				buffer = fopen("buffer.txt", "w");
				while ((fread(&simb, 1, 1, inFile)) != 0)//читаем каждый символ и записываем в буфер в бинарном виде
				{
					code1.simb = simb;
					fputc(code1.byte.b1 + '0', buffer);
					fputc(code1.byte.b2 + '0', buffer);
					fputc(code1.byte.b3 + '0', buffer);
					fputc(code1.byte.b4 + '0', buffer);
					fputc(code1.byte.b5 + '0', buffer);
					fputc(code1.byte.b6 + '0', buffer);
					fputc(code1.byte.b7 + '0', buffer);
					fputc(code1.byte.b8 + '0', buffer);
				}
				fclose(buffer);
				buffer = fopen("buffer.txt", "r");
				while ((simb = fgetc(buffer)) != EOF)	//Считаем размер бинарного файла(количество символов в нём)
					fsize++;
				fsize = fsize - 8;
				rewind(buffer);
				j = 0;
				for (i = 0; i < 8; i++)//считываем размер хвоста
				{
					arr[j] = fgetc(buffer);
					if (j == 7)
					{
						code1.byte.b1 = arr[0] - '0';
						code1.byte.b2 = arr[1] - '0';
						code1.byte.b3 = arr[2] - '0';
						code1.byte.b4 = arr[3] - '0';
						code1.byte.b5 = arr[4] - '0';
						code1.byte.b6 = arr[5] - '0';
						code1.byte.b7 = arr[6] - '0';
						code1.byte.b8 = arr[7] - '0';
						tail = (int)code1.simb;
					}
					j++;
				}
				if (tail != 0)
					tail = 8 - tail;
				buffer2 = fopen("buffer2.txt", "w");
				for (i = 0; i < fsize - tail; i++)//удаляем лишние символы из буфера
				{
					simb = fgetc(buffer);
					fputc(simb, buffer2);
				}
				fclose(buffer);
				fclose(buffer2);
				buffer = fopen("buffer2.txt", "r");
				head = (Tree*)malloc(sizeof(Tree));
				nullNode(head);
				head->code[0] = 0;
				createTree(head, buffer);//создаем дерево Хаффмана
				if (isList(head) == 1)//если голова-лист, то код 0
				{
					head->code[0] = '0';
					head->code[1] = 0;
				}
				makeCodes(head);//генерируем каждому символу код
				outFile = fopen("out.txt", "wb");
				while ((simb = getc(buffer)) != EOF)//читаем символ
				{
					len = strlen(code);//смотрим длину кода
					code[len] = simb;//добавляем символ в код
					if ((prm=findList(head, code))!=EOF)//если нашли символ с таким кодом, то пишем символ в файл
					{
						fwrite(&prm, 1, 1, outFile);
						for (i = 0; i <= len; i++)//обнуляем код
						{
							code[i] = 0;
						}
					}
				}
				_fcloseall();
				freeTree(head);
				remove("buffer.txt");
				remove("buffer2.txt");
			}
	}
}