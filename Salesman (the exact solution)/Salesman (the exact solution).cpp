#include <iostream>
#include <time.h>
using namespace std;

bool nextPer(int *per, int N)  //Поиск следующей перетсановки алгоритмом Дейкстры
{
	int j;
	int buffer;
	do  // повторяем пока не будет найдено следующее размещение
	{
		j = N - 1;
		while (j != -1 && per[j] >= per[j + 1])
			j--;
		if (j == -1)
			return false; // больше размещений нет
		int k = N - 1;
		while (per[j] >= per[k])
			k--;
		int buffer = per[j];
		per[j] = per[k];
		per[k] = buffer;
		int l = j + 1, r = N - 1; // сортируем оставшуюся часть последовательности
		while (l < r)
		{
			int buffer = per[l];
			per[l] = per[r];
			per[r] = buffer;
			r--;
			l++;
		}
	} while (j > N - 1);
	return true;
}

int prices(int** P, int* per, int N) // По определенному перебору мы считаем цену всего пути
{
	int prices = 0;
	for (int i = 0; i < N - 1; i++)
		prices += P[per[i]][per[i + 1]];
	prices += P[per[N - 1]][per[0]];
	return prices;
}

int* func(int** P, int N, int start)
{
	//Массив перестановок должен быть упорядоченным, чтобы потом правильно посчитать все перестановки
	int* per;// Массив с перестановками
	per = new int[N];
	for (int i = 1; i < start; i++)
		per[i] = i - 1;
	per[0] = start - 1;
	for (int i = start; i < N; i++)
		per[i] = i;
	int min = prices(P, per, N);
	int* minp = new int[N];
	for (int i = 0; i < N; i++)
		minp[i] = per[i];
	do //Перебором находим минимальный по стоимости путь
	{
		if (prices(P, per, N) < min)
		{
			for (int i = 0; i < N; i++)
				minp[i] = per[i];
			min = prices(P, per, N);
		}
	} while (nextPer(&per[1], N - 1));
	return minp;
}
int main()
{
	setlocale(LC_CTYPE, "rus");
	int N, start, ** P;
	cout << "N = ";
	cin >> N;
	cout << "start = ";
	cin >> start;
	P = new int*[N];
	for (int i = 0; i < N; i++)
		P[i] = new int[N];
	/**/
	srand(time(0));
	for (int i = 0; i < N; i++) { //Случайная матрица стоимостей
		for (int j = 0; j < N; j++)
			if (i == j) {
				P[i][j] = 0;
				cout << P[i][j] << " ";
			}
			else {
				P[i][j] = rand() % 9 + 1;
				cout << P[i][j] << " ";
			}
		cout << endl;
	}
	cout << endl;
	/**/
	/*for (int i = 0; i < N; i++) { //Для ввода своей матрицы стоимостей
		for (int j = 0; j < N; j++)
			cin >> P[i][j];
	}*/
	int* minp = func(P, N, start);
	cout << "Минимальный путь = ";
	for (int i = 0; i < N; i++) //Вывод
		cout << minp[i] + 1 << "->";
	cout << minp[0] + 1;
	cout << endl << "Минимальная цена = " << prices(P, minp, N);
}