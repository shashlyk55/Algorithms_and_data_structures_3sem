#include <iostream>
#include <stdio.h>

#define V 6

#define INF 99999


/*
1.	Разработать приложение, для нахождения всех кратчайшие пути в орграфе, используя алгоритм Флойда-Уоршелла.
Строим матрицу  D0 = C  (матрица кратчайших путей между вершинами без промежуточных вершин).
После всех вычислений должны получиться матрицы D и S - кратчайших путей и последовательностей вершин.
*/

void printSolution(int dist[][V]);

void floydWarshall(int graph[][V])
{
    int routeVertex[V][V] =
    {
        {  0,  2,  3,  4,  5,  6},
        {  1,  0,  3,  4,  5,  6},
        {  1,  2,  0,  4,  5,  6},
        {  1,  2,  3,  0,  5,  6},
        {  1,  2,  3,  4,  0,  6},
        {  1,  2,  3,  4,  5,  0}
    };

    int dist[V][V], i, j, k;

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    for (k = 0; k < V; k++)
    {
        for (i = 0; i < V; i++)
        {
            for (j = 0; j < V; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    routeVertex[i][j] = k + 1;
                }
            }
        }
    }

    std::cout << "Кратчайшие пути до вершин:\n\n";
    printSolution(dist);
    std::cout << "\nПоследовательность вершин:\n\n";
    printSolution(routeVertex);
}

void printSolution(int dist[][V])
{
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                std::cout << "INF\t";
            else
                std::cout << dist[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    int graph[V][V] =
    {
        {  0, 28, 21, 59, 12, 27},
        {  7,  0, 24,INF, 21,  9},
        {  9, 32,  0, 13, 11,INF},
        {  8,INF,  5,  0, 16,INF},
        { 14, 13, 15, 10,  0, 22},
        { 15, 18,INF,INF,  6,  0}
    };

    floydWarshall(graph);

    return 0;
}