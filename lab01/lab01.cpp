#include<iostream>
using namespace std;

/*
Реализовать головоломку Ханойская башня. Головоломка состоит из 3 столюцов и числа дисков, которое вводит пользователь.
*/

void replace(int stolb1, int stolb2) {
	cout << "диск со столба " << stolb1 << " на " << stolb2 << endl;
}

void hanoy(int n, int stolb1, int stolb2, int temp) {
	if (n == 0) {
		return;
	}
	hanoy(n - 1, stolb1, temp, stolb2);

	replace(stolb1, stolb2);

	hanoy(n - 1, temp, stolb2, stolb1);
}

void main() {

	setlocale(LC_ALL, "ru");

	int N;

	cout << "Введите количество дисков: ";
	cin >> N;
	
	hanoy(N, 1, 2, 3);
}


