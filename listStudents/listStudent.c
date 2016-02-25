#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct Student {
	char *name;
	float grade;
	int age;
} Student;

/*Функция заполняет массив структур student из файла file.
student-массив структур.
file-файл из которого берем значения.
возвращает колличество заполненных структур*/
int input(Student* student, FILE *file)
{
	int i,size;
	size = 0;
	char buffer[128];
	for (i = 0; i < 500; i++)
	{

		if (fscanf(file,"%s %g %d\n", buffer,&student[i].grade,&student[i].age)!=EOF)
		{
			student[i].name = (char*)malloc(strlen(buffer) + 1);
			strcpy(student[i].name, buffer);
			size++;
		}
		else break;
	}
	return size;
}

/*Функция считает максимальную длину поля name в структуре Student.
student-массив структур.
size-колличество элементов структуры.
возвращает максимальную длину поля name.*/
int maxLen(Student *student, int size)
{
	int i;
	int max = strlen(student->name);
	for (i = 0; i < size; i++)
	{
		if (max < strlen(student[i].name))
			max = strlen(student[i].name);
	}
	return max;
}

/*Функция проверяет равны ли элементы поля name до k-ого элемента в структуре student.
student1-сравниваемая структура.
student2-сравниваемая структура.
k-индекс элемента поля name до которого идет сравнение.
возвращает 1 если все элементы до k равны и 0 в противном случае.*/
int check(Student student1,Student student2, int k)
{
	int cur=1;
	while (k >= 0)
	{
		if (student1.name[k] == student2.name[k])
		{
			k--;
		}
		else
		{
			cur = 0;
			break;
		}
	}
	return cur;
}

/*функция получает массив и сортирует его по алфавиту.
arr-массив структур
k-индекс символа поля name по которому идет сортировка.
size-колличество элементов массива.*/
void bubble_sortName(Student* arr, int k,int size)
{
	int i, j;
	Student x;
	for (i = 0; i < size - 1; i++)
	{
		for (j = size - 1; j > i; j--)
		{
			if ((arr[j - 1].name[k] > arr[j].name[k])&& (check(arr[j-1], arr[j], k - 1) == 1))
			{
				x = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = x;
			}
		}
	}
}

/*функция получает массив и сортирует его по возрастанию оценки.
arr-массив структур
left-левый индекс сортируемой части
right-правый индекс сортируемой части*/
void quicksortGrade(Student* arr, int left, int right)
{
	float x;
	int i, j;
	Student t;
	i = left;
	j = right;
	x = arr[(left + right) / 2].grade; //средний элемент
	do
	{
		while (arr[i].grade < x) //Поиск слева элемента большего чем средний
			i++;
		while (x < arr[j].grade) //Поиск справа элемента меньшего чем средний
			j--;
		if (i <= j)
		{
			t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;


			i++;
			j--;
		}
	} while (i < j);
	if (left < j)
		quicksortGrade(arr, left, j);
	if (i < right)
		quicksortGrade(arr, i, right);
}

/*функция получает массив и сортирует его по возрастанию возраста.
arr-массив структур
left-левый индекс сортируемой части
right-правый индекс сортируемой части*/
void quicksortAge(Student* arr, int left, int right)
{
	int x;
	int i, j;
	Student t;
	i = left;
	j = right;
	x = arr[(left + right) / 2].age; //средний элемент
	do
	{
		while (arr[i].age < x) //Поиск слева элемента большего чем средний
			i++;
		while (x < arr[j].age) //Поиск справа элемента меньшего чем средний
			j--;
		if (i <= j)
		{
			t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
			i++;
			j--;
		}
	} while (i < j);
	if (left < j)
		quicksortAge(arr, left, j);
	if (i < right)
		quicksortAge(arr, i, right);
}

/*Функция записывает в файл структуру student.
student-массив структур.
file-файл в который проводится запись.*/
void printList(Student *student, FILE *file)
{
	fprintf(file, "%s %g %d\n", student->name, student->grade, student->age);
}

/*Функция выводит массив структур в файл.
student-массив структур.
name-имя файла, куда проходит запись.
size-колличество элементов в массиве.*/
void output(Student *student, char* name,int size)
{
	FILE *file;
	int i;
	file = fopen(name, "w");
	for (i = 0; i < size; i++)
	{
		printList(&student[i],file);
	}
	fclose(file);
}

/*Функция освобождает память массива структур student и поля name.
students-массив структур.
size-колличество элементов массива.*/
void freeArray(Student* students, int size) 
{
	int i;
	for (i = 0; i < size; i++) 
	{
		free(students[i].name);
	}
	free(students);
}

void main()
{
	int i, size,len;
	FILE *file;
	Student * students;
	students = (Student*)malloc(sizeof(Student) * 500);
	file = fopen("in.txt", "r");
	if (file)
	{
		size = input(students,file);
		len = maxLen(students, size);
		for (i = 0; i < len; i++)
		{
			bubble_sortName(students,i,size);
		}
		output(students, "out1.txt",size);
		quicksortGrade(students, 0, size - 1);
		output(students, "out2.txt", size);
		quicksortAge(students, 0, size - 1);
		output(students, "out3.txt", size);
	}
	fclose(file);
	freeArray(students, size);
}