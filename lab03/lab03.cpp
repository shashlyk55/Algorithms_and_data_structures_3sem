#include <iostream>
#include <limits.h>
#include <stdio.h>

#define V 9

/*
1.	Разработать приложение, реализующее алгоритм Дейктры для следующего графа.
2.	Пользователь указывает стартовую вершину. Ему выводится список расстояний до каждой вершины.
*/

int minDistance(int distance[], bool sptSet[]);
void printDistance(char name[], int distance[], int n, char startPoint);
void dijkstra(int graph[V][V], int src, char startPoint);

int main()
{
    setlocale(LC_ALL, "rus");

    int graph[9][9] =
    {
        //A  B  C  D  E  F  G  H  I
        { 0, 7,10, 0, 0, 0, 0, 0, 0}, // A
        { 7, 0, 0, 0, 0, 9,27, 0, 0}, // B
        {10, 0, 0, 0,31, 8, 0, 0, 0}, // C
        { 0, 0, 0, 0,32, 0, 0,17,21}, // D
        { 0, 0,31,32, 0, 0, 0, 0, 0}, // E
        { 0, 9, 8, 0, 0, 0, 0,11, 0}, // F
        { 0,27, 0, 0, 0, 0, 0, 0,15}, // G
        { 0, 0, 0,17, 0,11, 0, 0,15}, // H
        { 0, 0, 0,21, 0, 0,15,15, 0}, // I
    };

    char numCharV;
    int numIntV;

    bool try_01 = false;

    while (!try_01)
    {
        std::cout << "Введите вершину, от которой хотите узнать расстояния:\n";
        numCharV = getchar();
        switch (numCharV)
        {
        case 'A':
            try_01 = true;
            numIntV = 0;
            break;
        case 'B':
            try_01 = true;
            numIntV = 1;
            break;
        case 'C':
            try_01 = true;
            numIntV = 2;
            break;
        case 'D':
            try_01 = true;
            numIntV = 3;
            break;
        case 'E':
            try_01 = true;
            numIntV = 4;
            break;
        case 'F':
            try_01 = true;
            numIntV = 5;
            break;
        case 'G':
            try_01 = true;
            numIntV = 6;
            break;
        case 'H':
            try_01 = true;
            numIntV = 7;
            break;
        case 'I':
            try_01 = true;
            numIntV = 8;
            break;
        default:
            break;
        }
        system("cls");
    }
    dijkstra(graph, numIntV, numCharV);

    return 0;
}

int minDistance(int distance[], bool sptSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && distance[v] <= min)
            min = distance[v], min_index = v;

    return min_index;
}

// вывод расстояний
void printDistance(char name[], int distance[], int n, char startPoint)
{
    std::cout << "Расстояния до вершин\n";
    for (int i = 0; i < n; i++)
        std::cout << startPoint << " -> " << name[i] << " = " << distance[i] << std::endl;
}

// алгоритм Дейкстры
void dijkstra(int graph[V][V], int src, char startPoint)
{
    int distance[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++)
        distance[i] = INT_MAX, sptSet[i] = false;

    distance[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {

        int u = minDistance(distance, sptSet);

        sptSet[u] = true;

        for (int v = 0; v < V; v++)

            if (!sptSet[v] && graph[u][v] && distance[u] != INT_MAX
                && distance[u] + graph[u][v] < distance[v])

                distance[v] = distance[u] + graph[u][v];
    }

    char nameSymbol[9]{ 'A','B','C','D','E','F','G','H','I' };
    printDistance(nameSymbol, distance, V, startPoint);
}