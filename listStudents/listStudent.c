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

/*������� ��������� ������ �������� student �� ����� file.
student-������ ��������.
file-���� �� �������� ����� ��������.
���������� ����������� ����������� ��������*/
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

/*������� ������� ������������ ����� ���� name � ��������� Student.
student-������ ��������.
size-����������� ��������� ���������.
���������� ������������ ����� ���� name.*/
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

/*������� ��������� ����� �� �������� ���� name �� k-��� �������� � ��������� student.
student1-������������ ���������.
student2-������������ ���������.
k-������ �������� ���� name �� �������� ���� ���������.
���������� 1 ���� ��� �������� �� k ����� � 0 � ��������� ������.*/
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

/*������� �������� ������ � ��������� ��� �� ��������.
arr-������ ��������
k-������ ������� ���� name �� �������� ���� ����������.
size-����������� ��������� �������.*/
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

/*������� �������� ������ � ��������� ��� �� ����������� ������.
arr-������ ��������
left-����� ������ ����������� �����
right-������ ������ ����������� �����*/
void quicksortGrade(Student* arr, int left, int right)
{
	float x;
	int i, j;
	Student t;
	i = left;
	j = right;
	x = arr[(left + right) / 2].grade; //������� �������
	do
	{
		while (arr[i].grade < x) //����� ����� �������� �������� ��� �������
			i++;
		while (x < arr[j].grade) //����� ������ �������� �������� ��� �������
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

/*������� �������� ������ � ��������� ��� �� ����������� ��������.
arr-������ ��������
left-����� ������ ����������� �����
right-������ ������ ����������� �����*/
void quicksortAge(Student* arr, int left, int right)
{
	int x;
	int i, j;
	Student t;
	i = left;
	j = right;
	x = arr[(left + right) / 2].age; //������� �������
	do
	{
		while (arr[i].age < x) //����� ����� �������� �������� ��� �������
			i++;
		while (x < arr[j].age) //����� ������ �������� �������� ��� �������
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

/*������� ���������� � ���� ��������� student.
student-������ ��������.
file-���� � ������� ���������� ������.*/
void printList(Student *student, FILE *file)
{
	fprintf(file, "%s %g %d\n", student->name, student->grade, student->age);
}

/*������� ������� ������ �������� � ����.
student-������ ��������.
name-��� �����, ���� �������� ������.
size-����������� ��������� � �������.*/
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

/*������� ����������� ������ ������� �������� student � ���� name.
students-������ ��������.
size-����������� ��������� �������.*/
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