#include<iostream>

using namespace std;


/*
1.	Разработать приложение, для нахождения минимального остовного дерева с помощью алгоритма Прима.
2.	Разработать приложение, для нахождения минимального остовного дерева с помощью алгоритма Краскала
3.	В обоих случаях вывести на экран остовное дерево (это может быть список ребер, это может быть матрица или графически отрисовать и т.д.)
*/


#include <Windows.h>
#include <iostream>
using namespace std;

void PrimaFunct();
void Kraskl();
int interconnected(int i);
void unionCompos(int i, int j);

#define Y 8
int infCost = INT_MAX;
int visited[Y];

int Matrix[Y][Y] =
{
	{-1, 2, -1, 8, 2, -1, -1, -1 },
	{2, -1, 3, 10, 5, -1, -1, -1},
	{-1, 3, -1, -1, 12, -1, -1, 7},
	{8, 10, -1, -1, 14, 3, 1, -1},
	{2, 5, 12, 14, -1, 11, 4, 8},
	{-1, -1, -1, 3, 11, -1, 6, -1},
	{-1, -1, -1, 1, 4, 6, -1, 9},
	{-1, -1, 7, -1, 8, -1, 9, -1}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Prima:\n";
	PrimaFunct();

	cout << endl;

	cout << "Kraskal:\n";
	Kraskl();
}

void PrimaFunct()
{
	int** arr = new int* [Y];
	for (int i = 0; i < Y; i++) {
		arr[i] = new int[Y];
	}

	bool visited[8];
	for (int i = 0; i < 8; i++)
	{
		visited[i] = false;
	}
	visited[0] = true;

	for (int l = 0; l < 7; l++) {
		int minHor = infCost;
		int minVer = infCost;
		for (int i = 0; i < 8; i++)
		{
			if (visited[i])
			{
				for (int j = 0; j < 8; j++)
				{
					if (!visited[j] && Matrix[i][j] > -1 && (minVer == infCost || Matrix[i][j] < Matrix[minVer][minHor]))
					{
						minVer = i, minHor = j;
					}
				}
			}
		}
		visited[minHor] = true;
		cout << minVer + 1 << ' ' << minHor + 1 << endl;
	}
}

void Kraskl()
{
	int min;
	int edgesCount = 0;
	for (int i = 0; i < Y; i++)
	{
		visited[i] = i;
	}

	while (edgesCount < Y - 1)
	{
		min = infCost;
		int a = infCost, b = infCost;
		for (int i = 0; i < Y; i++)
		{
			for (int j = 0; j < Y; j++)
			{
				if (interconnected(i) != interconnected(j) && Matrix[i][j] < min && Matrix[i][j] != 0)
				{
					min = Matrix[i][j];
					a = i;
					b = j;
				}
			}
		}
		unionCompos(a, b);
		edgesCount++;
		cout << a + 1 << "---" << b + 1 << endl;
	}
}

int interconnected(int i)
{
	while (visited[i] != i)
	{
		i = visited[i];
	}
	return i;
}

void unionCompos(int i, int j)
{
	int a = interconnected(i);
	int b = interconnected(j);
	visited[a] = b;
}