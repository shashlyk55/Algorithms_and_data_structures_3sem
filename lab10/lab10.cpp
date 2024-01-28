/* Муравьиный алгоритм для решения задачи коммивояжёра */

#include <locale>
#include <stdlib.h>
#include <iostream>
#include <malloc.h>

using namespace std;

/*
1.	Разработать приложение, которые будет находить минимальный путь обхода всех городов с муравьиного алгоритма.
2.	Пользователь определяет количество городов N.
3.	Генерируется расстояние между городами (Заполняется матрица).
4.	Пользователь определяет начальное значение феромонов на каждом ребре графа, значения альфа и бета, количество итераций алгоритма.
5.	На экран пользователю выводится на каждой итерации следующая информация:
a.	Номер итерации
b.	Лучший маршрут из вершин графа на данный момент из всех пройденных итераций.
c.	Расстояние данного маршрута.
*/

#define ALPHA	1					// вес фермента
#define BETTA	3					// коэффициент эвристики

#define T_MAX	100					// время жизни колонии
#define M		20					// количество муравьев в колонии
#define Q		100					// количество
#define RHO		0.5					// коэффициент испарения феромона

// структура ПУТЬ (длинна, массив вершин, количество вершин)
struct WAY_TYPE {
	int itabu;
	int length;
	int* tabu;
};

// вероятность перехода муравья ant в вершину to
double probability(int to, WAY_TYPE ant, double** pheromone, double** distance, int vertex) {
	// если вершина уже посещена, возвращаем 0
	for (int i = 0; i < ant.itabu; ++i) if (to == ant.tabu[i]) return 0;

	double sum = 0.0;
	int from = ant.tabu[ant.itabu - 1];
	// считаем сумму в знаминателе
	for (int j = 0; j < vertex; ++j) {
		int flag = 1;
		// проверяем, посещал ли муравей j вершину
		for (int i = 0; i < ant.itabu; ++i) if (j == ant.tabu[i]) flag = 0;
		// если нет, тогда прибавляем к общей сумме
		if (flag) sum += pow(pheromone[from][j], ALPHA) * pow(distance[from][j], BETTA);
	}
	// возвращаем значение вероятности
	return pow(pheromone[from][to], ALPHA) * pow(distance[from][to], BETTA) / sum;
}

// основная функция алгоритма поиска
WAY_TYPE AntColonyOptimization(double** distance0, int vertex, int start, int finish) {
	// инициализация данных о лучшем маршруте
	WAY_TYPE way;
	way.itabu = 0;
	way.length = -1;
	way.tabu = (int*)malloc(sizeof(int) * vertex);
	// инициализация данных о расстоянии и количестве феромона
	double** distance = NULL, ** pheromone = NULL;
	distance = (double**)malloc(sizeof(double*) * vertex);
	pheromone = (double**)malloc(sizeof(double*) * vertex);
	for (int i = 0; i < vertex; ++i) {
		distance[i] = (double*)malloc(sizeof(double) * vertex);
		pheromone[i] = (double*)malloc(sizeof(double) * vertex);
		for (int j = 0; j < vertex; ++j) {
			pheromone[i][j] = 1.0 / vertex;
			if (i != j) distance[i][j] = 1.0 / distance0[i][j];
		}
	}
	// инициализация муравьев
	WAY_TYPE ants[M];
	for (int k = 0; k < M; ++k) {
		ants[k].itabu = 0;
		ants[k].length = 0.0;
		ants[k].tabu = (int*)malloc(sizeof(int) * vertex);
		ants[k].tabu[ants[k].itabu++] = start;
	}

	// основной цикл
	for (int t = 0; t < T_MAX; ++t) {
		// цикл по муравьям
		for (int k = 0; k < M; ++k) {
			// поиск маршрута для k-го муравья
			do {
				int j_max = -1;
				double p_max = 0.0;
				for (int j = 0; j < vertex; ++j) {
					// Проверка вероятности перехода в вершину j
					if (ants[k].tabu[ants[k].itabu - 1] != j) {
						double p = probability(j, ants[k], pheromone, distance, vertex);
						if (p && p >= p_max) {
							p_max = p;
							j_max = j;
						}
					}
				}
				ants[k].length += distance0[ants[k].tabu[ants[k].itabu - 1]][j_max];
				ants[k].tabu[ants[k].itabu++] = j_max;
			} while (ants[k].tabu[ants[k].itabu - 1] != finish);
			// оставляем феромон на пути муравья
			for (int i = 0; i < ants[k].itabu - 1; ++i) {
				int from = ants[k].tabu[i % ants[k].itabu];
				int to = ants[k].tabu[(i + 1) % ants[k].itabu];
				pheromone[from][to] += Q / ants[k].length;
				pheromone[to][from] = pheromone[from][to];
			}
			// проверка на лучшее решение
			if (ants[k].length < way.length || way.length < 0) {
				way.itabu = ants[k].itabu;
				way.length = ants[k].length;
				for (int i = 0; i < way.itabu; ++i) way.tabu[i] = ants[k].tabu[i];
			}
			// обновление муравьев
			ants[k].itabu = 1;
			ants[k].length = 0.0;
		}
		// цикл по ребрам
		for (int i = 0; i < vertex; ++i)
			for (int j = 0; j < vertex; ++j)
				// обновление феромона для ребра (i, j)
				if (i != j) pheromone[i][j] *= (1 - RHO);
	}
	// возвращаем кратчайший маршрут
	return way;
}

// точка входа в программу
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");

	/*

	*/

	int map[5][5] = { { INT_MAX, 25, 40, 31, 27},
					{ 5, INT_MAX, 17, 30, 25},
					{ 19, 15, INT_MAX, 6, 1},
					{ 9, 50, 24, INT_MAX, 6 },
					{ 22, 8, 7, 10, INT_MAX } };

	double** D = NULL;
	int N = 0, A = 2, B = 4;

	N = 5;

	D = (double**)malloc(sizeof(double*) * N);
	for (int i = 0; i < N; ++i) {
		D[i] = (double*)malloc(sizeof(double) * N);
		for (int j = 0; j < N; ++j) D[i][j] = map[i][j];
	}

	WAY_TYPE way = AntColonyOptimization(D, N, --A, --B);

	cout << "Длинна пути: " << way.length << endl;
	cout << "Путь: " << ++way.tabu[0];
	for (int i = 1; i < way.itabu; ++i) cout << " -> " << ++way.tabu[i];

	return 0;
}