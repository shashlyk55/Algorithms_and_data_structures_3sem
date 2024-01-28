#include <iostream>
#include <queue>
#include <map>
#include <stack>

using namespace std;

/*
1.	����������� ����������, ����������� �������� ������� � ������ � ������� � ������� ������������������ �����, ��������������� ����.
2.	������� ������� ����������� ������ � ������ �� ����������.
3.	������ ��������� � ������������� ����������: ������������ �������� ����� � ������� ������ �����, ������� ��������� � ������ ���������.
4.	�������� ������� ����� ����������� � �� ��������������. ��������  ����������� �������� ����� � ���������� �-������� ��� ������� �������.
*/

void BFS(int matrix[10][10]);
void DFS(int matrix[10][10]);

int main()
{
	setlocale(LC_ALL, "rus");
	// ������ ����
	int arrayAdge[22][2] =
	{
		{1,2},{2,1},
		{1,5},{5,1},
		{2,7},{7,2},
		{2,8},{8,2},
		{3,8},{8,3},
		{4,6},{6,4},
		{4,9},{9,4},
		{5,6},{6,5},
		{6,9},{9,6},
		{7,8},{8,7},
		{9,10},{10,9}
	};

	//������� ���������
	int matrixAdjacency[10][10] =
	{
		{0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
		{0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
	};

	// ������ ���������
	int** arrayNode = new int* [10];
	arrayNode[0] = new int [2] {2, 5};
	arrayNode[1] = new int [3] {1, 7, 8};
	arrayNode[2] = new int [1] {8};
	arrayNode[3] = new int [2] {6, 9};
	arrayNode[4] = new int [2] {1, 6};
	arrayNode[5] = new int [3] {4, 5, 9};
	arrayNode[6] = new int [2] {2, 8};
	arrayNode[7] = new int [3] {2, 3, 7};
	arrayNode[8] = new int [3] {4, 6, 10};
	arrayNode[9] = new int [1] {9};

	cout << "\n����� ����� � ������:\t";
	BFS(matrixAdjacency);
	cout << "\n\n����� ����� � �������:\t";
	DFS(matrixAdjacency);

	cout << endl << endl;
	system("pause");

	return 0;
}

void BFS(int matrix[10][10])
{
	queue<int> Queue;

	int nodes[10];

	for (int i = 0; i < 10; i++)
		nodes[i] = 0;

	// 0 - ������� �� ��������
	// 1 - ������� � �������
	// 2 - ������� ��������

	Queue.push(0);

	while (!Queue.empty())
	{
		int node = Queue.front();
		Queue.pop();
		nodes[node] = 2;

		for (int j = 0; j < 10; j++)
		{
			if (matrix[node][j] == 1 && nodes[j] == 0)
			{
				Queue.push(j);
				nodes[j] = 1;
			}
		}
		cout << node + 1 << " ";
	}
}

void DFS(int matrix[10][10])
{
	stack<int> Stack;

	int nodes[10];

	for (int i = 0; i < 10; i++) nodes[i] = 0;

	// 0 - ������� �� ��������
	// 1 - ������� � �������
	// 2 - ������� ��������

	Stack.push(0);

	while (!Stack.empty())
	{
		int node = Stack.top();
		Stack.pop();
		if (nodes[node] == 2) continue;
		nodes[node] = 2;
		for (int j = 9; j >= 0; j--)
		{
			if (matrix[node][j] == 1 && nodes[j] != 2)
			{
				Stack.push(j);
				nodes[j] = 1;
			}
		}
		cout << node + 1 << " ";
	}
}