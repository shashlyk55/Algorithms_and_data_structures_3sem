#include<iostream>
using namespace std;

/*
����������� ����������� ��������� �����. ����������� ������� �� 3 �������� � ����� ������, ������� ������ ������������.
*/

void replace(int stolb1, int stolb2) {
	cout << "���� �� ������ " << stolb1 << " �� " << stolb2 << endl;
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

	cout << "������� ���������� ������: ";
	cin >> N;
	
	hanoy(N, 1, 2, 3);
}


