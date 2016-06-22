#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/*Функция обнуляет матрицу смежностей
N-Кол-во вершин
edges-матрица смежностей*/
void nullMaze(int N, char** maze)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			maze[i][j] = 0;
		}
	}
}
/*Функция реализует перебор и поиск пути
maze - массив лабиринта
х - первая координата
y - вторая координата
N - Кол-во вершин*/
int mazeSolve(char** maze, int x, int y, int N)
{
	if (x == N - 1 && y == N - 1)
	{
		maze[x][y] = '*';
		return 1;
	}
	if (x<0 || y<0 || x>N - 1 || y>N - 1)
		return 0;
	if (maze[x][y] != '0')
		return 0;
	maze[x][y] = '*';
	if (mazeSolve(maze, x - 1, y, N))
		return 1;
	if (mazeSolve(maze, x + 1, y, N))
		return 1;
	if (mazeSolve(maze, x, y-1, N))
		return 1;
	if (mazeSolve(maze, x, y+1, N))
		return 1;
	maze[x][y] = '0';
	return 0;
}

void main(int argc, char* argv[])
{
	int i,j;
	int N;
	FILE *in, *out;
	char **maze;
	if (argv[1])
	{
		in = fopen(argv[1], "r");
		if (in)
		{
			fscanf(in, "%d\n", &N);
			maze = (char**)malloc(N*sizeof(char*));
			for (i = 0; i < N; i++)
			{
				maze[i] = (char*)malloc(N*sizeof(char));
			}
			nullMaze(N, maze);
			for (i = 0; i < N; i++)
			{
				for (j = 0; j < N; j++)
				{
					fscanf(in, "%c ", &maze[i][j]);
				}
			}
			if (mazeSolve(maze, 0, 0, N))
			{
				if (argv[2])
				{
					out = fopen(argv[2], "w");
					if (out)
					{
						for (i = 0; i < N; i++)
						{
							for (j = 0; j < N; j++)
							{
								fprintf(out, "%c ", maze[i][j]);
							}
							fprintf(out, "\n");
						}
					}
				}
			}
			else
			{
				if (argv[2])
				{
					out = fopen(argv[2], "w");
					if (out)
					{
						fprintf(out, "not route");
					}
				}
			}
		}
	}
}