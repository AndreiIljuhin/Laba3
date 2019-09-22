// ConsoleApplication11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Лаболаторная работа №3 Андрея Ильюхина

// Максимальная рациональность
// Но можно было бы разгрузить тело основной функции, вынеся заполнения матрицы и некоторые алгоритмы в функции
// Но тогда придется переписывать 1/3 кода, а изначально я поленился это сделать
// Программа содержит все, кроме нахождения определителя и ранга матрицы (в процессе изучения, что это за фрукты, и как их готовить)
// Заливаю предварительный вариант (некоторые моменты не оптимизированы), и откладываю это дело на несколько дней, устал, есть другие дела
// Все используемые алгоритмы писал сам
// Представление матрицы, как одномерного динамического массива, нагуглил первой ссылкой, видел вариант с двойным указателем и представлением матрицы в виде [i][j],
// Не вдаваясь в подробности, но, думаю, этот вариант по сути более низкоуровневая форма представления, что не плохо

#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;
HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void saddle_point_indices_float_matrix(float*& matrix, short N, short M) {
	int max, min, index_max2, index_min2;
	bool b = 0;
	float max2, min2;

	cout << endl << "Индексы седловых точек: ";
	for (short i = 0; i < N; i++) { // Перебираю строки
		max2 = -1; min2 = 99;
		max = min = i * M;
		index_max2 = index_min2 = -1;
		for (short j = 0; j < M; j++) { // Ищу максимум и минимум
			if (matrix[i * M + j] < matrix[min])
				min = i * M + j;
			if (matrix[i * M + j] > matrix[max])
				max = i * M + j;
		}
		min = min - i * M;
		max = max - i * M;
		for (short q = 0; q < N; q++) { // Начинаю с 0 элемента соответствующих столбцов, ищу максимум и минимум
			if (matrix[q * M + min] > max2) {
				max2 = matrix[q * M + min];
				index_max2 = q * M + min;
			}
			if (matrix[q * M + max] < min2) {
				min2 = matrix[q * M + max];
				index_min2 = q * M + max;
			}
		}
		index_min2 = index_min2 - i * M;
		index_max2 = index_max2 - i * M;
		if (min == index_max2) { //Сравниваю максимум с минимумом и наоборот
			cout << "[" << i + 1 << "]" << "[" << min + 1 << "]" << "; ";
			b = 1;
		}
		if (max == index_min2) {
			cout << "[" << i + 1 << "]" << "[" << max + 1 << "]" << "; ";
			b = 1;
		}
	}
	if (!b) cout << "не найдены";
}

void rearrangement_of_rows_of_square_mattress(int*& matrix, short N, short n, short n2, bool type_start, bool type_end) { // 1 - строка, 0 - столбец
	int temp;

	if (type_start) {
		if (type_end) {
			for (int i = 0; i < N; i++) {
				temp = matrix[n * N + i];
				matrix[n * N + i] = matrix[n2 * N + i];
				matrix[n2 * N + i] = temp;
			}
		}
		else {
			for (int i = 0; i < N; i++) {
				temp = matrix[n * N + i];
				matrix[n * N + i] = matrix[i * N + n2];
				matrix[i * N + n2] = temp;
			}
		}
	}
	else {
		if (type_end) {
			for (int i = 0; i < N; i++) {
				temp = matrix[i * N + n];
				matrix[i * N + n] = matrix[n2 * N + i];
				matrix[n2 * N + i] = temp;
			}
		}
		else {
			for (int i = 0; i < N; i++) {
				temp = matrix[i * N + n];
				matrix[i * N + n] = matrix[i * N + n2];
				matrix[i * N + n2] = temp;
			}
		}
	}
}

void transposition_float_square_matrix(float*& matrix, short N) {
	float temp;

	for (short i = 0; i < N / 2; i++) {
		for (short j = 0; j < N / 2; j++) {
			temp = matrix[i * N + j]; // Левый верхний и правый нижний квадраты
			matrix[i * N + j] = matrix[(i + N/2) * N + j + N/2];
			matrix[(i + N / 2) * N + j + N / 2] = temp;
			temp = matrix[i * N + j + N / 2]; // Правый верхний и нижний левый квадраты
			matrix[i * N + j + N / 2] = matrix[(i + N / 2) * N + j];
			matrix[(i + N / 2) * N + j] = temp;
		}
	}
}

int highlight_square_matrix(int*& matrix, int*& matrix2, short m, short n) { // Выделяю квадратную матрицу, записываю адресс в пустой указатель, возвращаю размерность N2 новой квадратной матрицы
	int n2;

	if (n >= m)
		n2 = m;
	else
		n2 = n;
	do {
		matrix2 = new (nothrow) int[n2 * n2];
	} while (!matrix2);
	for (short i = 0; i < n2; i++) {
		for (short j = 0; j < n2; j++)
			matrix2[i * n2 + j] = matrix[i * m + j];
	}
	return n2;
}

void print_matrix(int*& matrix, short n, short m) {
	cout << "   ";
	for (short j = 0; j < m; j++) {
		cout.width(4);
		cout << j + 1;
	}
	cout << endl;
	for (short i = 0; i < n; i++) {
		cout.width(3);
		cout << endl << i + 1;
		for (short j = 0; j < m; j++) {
			cout.width(4);
			cout << matrix[i * m + j];
		}
	}
}

void print_float_square_matrix(float*& matrix, short n) {
	cout << "   ";
	for (short j = 0; j < n; j++) {
		cout.width(5);
		cout << j + 1;
	}
	cout << endl;
	for (short i = 0; i < n; i++) {
		cout.width(3);
		cout << endl << i + 1;
		for (short j = 0; j < n; j++) {
			if (j < n / 2 and i < n / 2) SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN);
			else if (j >= n / 2 and i < n / 2) SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED);
			else if (j < n / 2 and i >= n / 2) SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE | FOREGROUND_GREEN);
			else SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED | FOREGROUND_BLUE);
			cout.precision(2);
			cout.width(5);
			cout << matrix[i * n + j];
			SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		}
	}
}

void print_float_matrix(float*& matrix, short n, short m) {
	cout << "   ";
	for (short j = 0; j < m; j++) {
		cout.width(5);
		cout << j + 1;
	}
	cout << endl;
	for (short i = 0; i < n; i++) {
		cout.width(3);
		cout << endl << i + 1;
		for (short j = 0; j < m; j++) {
			cout.precision(2);
			cout.width(5);
			cout << matrix[i * m + j];
		}
	}
}

void rearrangement_of_lines(int*& matrix, short n1, short n2, short m) {
	int temp;

	for (int j = 0; j < m; j++) {
		temp = matrix[n1 * m + j];
		matrix[n1 * m + j] = matrix[n2 * m + j];
		matrix[n2 * m + j] = temp;
	}
}

void rearrangement_of_all_lines(int*& matrix, short n, short m) { // Улучшенная сортировка строк пузырьком
	int i = 0;
	double d;
	do {
		d = 0;
		for (int j = 0; j < n - i - 1; j++) {
			if (matrix[j * m] > matrix[(j + 1) * m]) {
				rearrangement_of_lines(matrix, j, j + 1, m);
				d = 1;
			}
		}
		i++;
	} while (d);
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int* matrix = 0;
	short N, M; // N - строки, M - столбцы
	srand(time(0));
	short counter = 0;

	cout << "Введите размерность матрицы - количество строк N (не больше 100), потом количество столбцов M (не больше 15): ";
	do {
		cin >> N >> M;
		if (!(N > 0 and N <= 100 and M > 0 and M <= 15))
			cout << "Введите правильное значение: ";
		else {
			matrix = new (nothrow) int[N * M];
			if (!matrix) {
				cout << "Ошибка выделения памяти, введите значения меньше: ";
				N = 0;
			}
		}
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	} while (!(N > 0 and N <= 100 and M > 0 and M <= 15));

	cout << endl << "Если хотите ввести матрицу вручную, введите '1': ";
	cin >> counter;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	if (counter == 1) {
		int x;
		cout << "Вводите значения от 0 до 99" << endl;
		for (short i = 0; i < N; i++) {
			for (short j = 0; j < M; j++) {
				cout << "Строка " << i + 1 << " столбец " << j + 1 << ":";
				do {
					cin >> x;
					if (!(x >= 0 and x < 100))
						cout << "Попробуйте еще раз: ";
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
				} while (!(x >= 0 and x < 100));
				matrix[i * M + j] = x;
			}
		}
	}
	else {
		for (short i = 0; i < N; i++) {
			for (short j = 0; j < M; j++)
				matrix[i * M + j] = rand() % 100;
		}
	}
	cout << endl;

	print_matrix(matrix, N, M);

	rearrangement_of_all_lines(matrix, N, M);
	cout << endl << endl << "Сортировка строк матрицы..." << endl << endl;
	print_matrix(matrix, N, M);
	cout << endl << endl;

	system("Pause");

	cout << endl << "Выделяем квадратную матрицу:" << endl << endl;
	int* matrix2 = 0;
	int N2 = highlight_square_matrix(matrix, matrix2, M, N);
	print_matrix(matrix2, N2, N2);

	delete[] matrix;
	matrix = 0;

	do {
		cout << endl << endl << "Определим, является ли полученная матрица магической, ортонормированной," << endl << "ввести элементы вручную '1' ";
		cin >> counter;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		if (counter == 1) {
			int x;
			cout << "Вводите значения от -99 до 99" << endl;
			for (short i = 0; i < N2; i++) {
				for (short j = 0; j < N2; j++) {
					cout << "Строка " << i + 1 << " столбец " << j + 1 << ":";
					do {
						cin >> x;
						if (!(x > -100 and x < 100))
							cout << "Попробуйте еще раз: ";
						cin.clear();
						cin.ignore(cin.rdbuf()->in_avail());
					} while (!(x > -100 and x < 100));
					matrix2[i * N2 + j] = x;
				}
			}
		}
		else {
			for (short i = 0; i < N2; i++) {
				for (short j = 0; j < N2; j++)
					matrix2[i * N2 + j] = rand() % 199 - 99;
			}
			cout << endl; print_matrix(matrix2, N2, N2); cout << endl << endl;
		}
		counter = 0;
		for (int i = 0; i < N2; i++) {
			int sumN = 0, sumM = 0;
			for (int j = 0; j < N2; j++) {
				sumN = sumN + matrix2[j * N2 + i];
				sumM = sumM + matrix2[i * N2 + j];
			}
			if (sumN == sumM) counter++;
		}
		if (counter == N2)
			cout << endl << "Матрица является магическим квадратом" << endl << endl;
		else
			cout << endl << "Матрица не является магическим квадратом" << endl << endl;
		counter = 0;
		for (int i = 0; i < N2; i++) {
			int compositionN = 0, compositionM = 0;
			for (int j = 0; j < N2; j++) {
				compositionN = compositionN + matrix2[j * N2 + i] * matrix2[j * N2 + i];
				compositionM = compositionM + matrix2[i * N2 + j] * matrix2[i * N2 + j];
			}
			if (compositionN == compositionM == 1) counter++;
		}
		if (counter == N2)
			cout << "Матрица является ортонормированной" << endl;
		else
			cout << "Матрица не является ортонормированной" << endl;
		cout << endl << "Заного заполнить матрицу и повторить проверку '1' ";
		cin >> counter;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	} while (counter == 1);

	delete[] matrix2;
	matrix2 = 0;


	float* matrix3 = 0;
	cout << endl << "Создать действительную квадратную матрицу <разбить на 4 квадрата, переставить крест-накрест> порядка N(четн, от 2 до 10): ";
	N = 0;
	do {
		cin >> N;
		if (!(N > 1 and N <= 10 and N % 2 == 0))
			cout << "Введите правильное значение: ";
		else {
			matrix3 = new (nothrow) float[N * N];
			if (!matrix3) {
				cout << "Ошибка выделения памяти, введите значения меньше: ";
				N = 0;
			}
		}
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	} while (!(N > 1 and N <= 10 and N % 2 == 0));
	for (short i = 0; i < N; i++) {
		for (short j = 0; j < N; j++)
			matrix3[i * N + j] = (rand() % 100) / (float)(rand() % 10 + 1);
	}
	cout << endl;
	print_float_square_matrix(matrix3, N);

	transposition_float_square_matrix(matrix3, N); // Меняю элементы крест-накрест
	cout << endl << endl;
	print_float_square_matrix(matrix3, N);

	delete[] matrix3;
	matrix3 = 0;

	cout << endl << endl << "Создать квадратную целочисленную матрицу <заполнить змейкой> порядка N(от 1 до 15)" << endl << "И заполнить ее целыми числами от 1 до N^2. N: ";
	do {
		cin >> N;
		if (!(N > 0 and N <= 15))
			cout << "Введите правильное значение: ";
		else {
			matrix = new (nothrow) int[N * N];
			if (!matrix) {
				cout << "Ошибка выделения памяти, введите значения меньше: ";
				N = 0;
			}
		}
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	} while (!(N > 0 and N <= 15));

	for (short i = 0; i < N; i++) {
		for (short j = 0; j < N; j++)
			matrix[i * N + j] = 0;
	}
	counter = 1;
	short counter2 = 0;
	N2 = N;
	while (N2 > 0) { // Заполняю змейкой
		for (short i = N - N2 - counter2; i < N - counter2; i++) { // Верхняя строка
			matrix[counter2 * N + i] = counter;
			counter++;
		}
		for (short i = N - N2 - counter2 + 1; i < N - counter2; i++) { // Правый столбец
			matrix[N * i + N - counter2 - 1] = counter;
			counter++;
		}
		for (short i = 2 + counter2; i <= N2 + counter2; i++) { // Нижняя строка
			matrix[N * (N - counter2) - i] = counter;
			counter++;
		}
		for (short i = 1 + counter2; i < N2 + counter2 - 1; i++) { // левый столбец
			matrix[N * (N - i) - N + counter2] = counter;
			counter++;
		}
		counter2++;
		N2 = N2 - 2;
	}
	N2 = N;

	cout << endl;
	print_matrix(matrix, N, N);
	cout << endl << endl << "Минимальный элемент ниже побочной диагонали: " << matrix[1 * N + N - 1] << endl;


	cout << endl << "Создать действительную матрицу <найти седловые точки> размерности N * M(N от 1 до 30, M от 1 до 15): ";
	N = M = 0;
	do {
		cin >> N >> M;
		if (!(N > 0 and N <= 20 and M > 0 and M <= 15))
			cout << "Введите правильное значение: ";
		else {
			matrix3 = new (nothrow) float[N * M];
			if (!matrix3) {
				cout << "Ошибка выделения памяти, введите значения меньше: ";
				N = 0;
			}
		}
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	} while (!(N > 0 and N <= 20 and M > 0 and M <= 15));

	cout << endl << "Если хотите ввести матрицу вручную, введите 1: ";
	cin >> counter;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	if (counter == 1) {
		float x;
		cout << "Вводите вещественные значения от 0 до 99" << endl;
		for (short i = 0; i < N; i++) {
			for (short j = 0; j < M; j++) {
				cout << "Строка " << i + 1 << " столбец " << j + 1 << ":";
				do {
					cin >> x;
					if (!(x >= 0 and x < 100))
						cout << "Попробуйте еще раз: ";
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
				} while (!(x >= 0 and x < 100));
				matrix3[i * M + j] = x;
			}
		}
	}
	else {
		for (short i = 0; i < N; i++) {
			for (short j = 0; j < M; j++)
				matrix3[i * M + j] = (rand() % 100) / (float)(rand() % 10 + 1);
		}
	}
	cout << endl;
	print_float_matrix(matrix3, N, M);
	cout << endl;

	saddle_point_indices_float_matrix(matrix3, N, M);
	cout << endl;

	delete[] matrix3;
	matrix3 = 0;

	system("Pause");

	N = N2;
	cout << endl << "Старая квадратная матрица" << endl << endl;
	print_matrix(matrix, N, N);
	cout << endl << endl << "Разворачиваем матрицу относительно оси x" << endl << endl;
	for (short i = 0; i < N / 2; i++)
		rearrangement_of_lines(matrix, i, N - i - 1, N);
	print_matrix(matrix, N, N);
	cout << endl << endl;

	system("Pause");

	while (!matrix2)
		matrix2 = new (nothrow) int[N * N];
	for (short i = 0; i < N; i++) {
		for (short j = 0; j < N; j++) {
			matrix2[i * N + j] = rand() % 3 + 1;
			if (!(rand() % 10)) matrix2[i * N + j] = 0; // Присваивается 0 с шансом 1/10
		}
	}
	cout << endl << "Вторая матрица" << endl << endl;
	print_matrix(matrix2, N, N);

	for (short i = 0; i < N; i++) {
		int composition = 1;
		for (short j = 0; j < N; j++)
			composition = matrix2[i * N + j] * composition;
		for (short j = 0; j < N; j++)
			matrix[j * N + i] = matrix[j * N + i] + composition;
	}
	cout << endl << endl << "Матрица, полученная прибавлением к элементам каждого столбца первой матрицы" << endl << "произведения элементов соответствующих строк второй матрицы" << endl << endl;
	print_matrix(matrix, N, N);

	delete[] matrix2;
	matrix2 = 0;

	cout << endl << endl << "Переставляя строки и столбцы числовой квадратной матрицы порядка N, добиться того," << endl << "чтобы наибольший элемент (один из них) оказался в верхнем левом углу." << endl << endl;
	bool type_start = 1, type_end = 1, door = 0, choice = 1;
	short n1, n2;
	cout << "Автоматически '0', вручную '1' ";
	cin >> door;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	if (door) {
		choice = 0;
		while (door) {
			n1 = n2 = 0;
			cout << "Поменять '1' - строку, '0' - столбец "; cin >> type_start;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "под номером: ";
			while (!(n1 > 0 and n1 <= N)) {
				cin >> n1;
				if (!(n1 > 0 and n1 <= N))
					cout << "Введите корректный номер: ";
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
			}
			cout << "на '1' - строку, '0' - столбец "; cin >> type_end;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "под номером: ";
			while (!(n2 > 0 and n2 <= N)) {
				cin >> n2;
				if (!(n2 > 0 and n2 <= N))
					cout << "Введите корректный номер: ";
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
			}
			rearrangement_of_rows_of_square_mattress(matrix, N, n1 - 1, n2 - 1, type_start, type_end);
			cout << endl << "Полученная матрица" << endl;
			print_matrix(matrix, N, N);
			cout << endl << endl << "Продолжить перестановку '1', перейти к следующей части программы '0' ";
			cin >> door;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "Может быть, сделать автоматически? '1' - Хорошо, '0' - Не ";
			cin >> choice;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			if (choice) door = 0;
		}
	}
	if (choice) {
		counter = 0;
		int maxi = 0, maxj = 0;
		for (short i = 0; i < N; i++) {
			for (short j = 0; j < N; j++) {
				if (matrix[i * N + j] > matrix[maxi * N + maxj]) {
					maxi = i;
					maxj = j;
				}
			}
		}
		if (maxi) {
			rearrangement_of_lines(matrix, 0, maxi, N);
			counter++;
		}
		if (maxj) {
			rearrangement_of_rows_of_square_mattress(matrix, N, 0, maxj, 0, 0);
			counter++;
		}
		if (!counter)
			cout << "Новая матрица за 0 шагов" << endl << endl;
		else if (counter == 1)
			cout << "Новая матрица за 1 шаг" << endl << endl;
		else
			cout << "Новая матрица за 2 шага" << endl << endl;
		print_matrix(matrix, N, N);
	}

	delete[] matrix;
	matrix = 0;

	cout << endl << endl << "Порядок новой матрицы <проверка на симметричность> N*N(не больше 15): ";
	do {
		cin >> N;
		if (!(N > 0 and N <= 15))
			cout << "Введите правильное значение: ";
		else {
			matrix = new (nothrow) int[N * N];
			if (!matrix) {
				cout << "Ошибка выделения памяти, введите значениt меньше: ";
				N = 0;
			}
		}
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	} while (!(N > 0 and N <= 15));

	cout << endl << "Если хотите ввести матрицу вручную, введите '1': ";
	cin >> counter;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	if (counter == 1) {
		int x;
		cout << "Вводите целые значения от 0 до 99" << endl;
		for (short i = 0; i < N; i++) {
			for (short j = 0; j < N; j++) {
				cout << "Строка " << i + 1 << " столбец " << j + 1 << ":";
				do {
					cin >> x;
					if (!(x >= 0 and x < 100))
						cout << "Попробуйте еще раз: ";
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
				} while (!(x >= 0 and x < 100));
				matrix[i * N + j] = x;
			}
		}
	}
	else {
		for (short i = 0; i < N; i++) {
			for (short j = 0; j < N; j++)
				matrix[i * N + j] = rand() % 100;
		}
	}
	cout << endl;
	print_matrix(matrix, N, N);
	cout << endl << endl;

	counter = counter2 = 0;
	for (short i = 0; i < N; i++) {
		for (short j = i + 1; j < N; j++) {
			if (matrix[i * N + j] != matrix[j * N + i]) counter++;
			if (matrix[i * N + j - i - 1] != matrix[N * (N - j + i + 1) - 1 - i]) counter2++;
		}
	}
	if (counter) cout << "Матрица не симметрична относительно главной диагонали" << endl;
	else cout << "Матрица симметрична относительно главной диагонали" << endl;
	if (counter2) cout << endl << "Матрица не симметрична относительно побочной диагонали" << endl;
	else cout << endl << "Матрица симметрична относительно побочной диагонали" << endl;

	cout << endl << "В квадратной числовой матрице порядка N найти произведение ненулевых диагональных элементов" << endl << "Введите порядок N(1..15), чтобы создать новую матрицу, '0', чтобы использовать старую ";
	do {
		cin >> N2;
		if (!(N2 >= 0 and N2 <= 15))
			cout << "Введите правильное значение: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
	} while (!(N2 >= 0 and N2 <= 15));

	if (N2) {
		delete[] matrix;
		N = N2;
		do {
			matrix = new (nothrow) int[N * N];
		} while (!matrix);
		for (short i = 0; i < N; i++) {
			for (short j = 0; j < N; j++)
				matrix[i * N + j] = rand() % 5;
		}
		cout << endl << "Новая матрица" << endl << endl;
		print_matrix(matrix, N, N);
		cout << endl;
	}
	long long composition = 1;
	for (short i = 0; i < N; i++) {
		if (matrix[i * N + i] != 0) composition = composition * matrix[i * N + i]; // Главная
		if (matrix[i * N + N - 1 - i] != 0) composition = composition * matrix[i * N + N - 1 - i]; // Побочная
	}
	cout << endl << "Произведение ненулевых диагональных элементов = " << composition << endl << endl;

	cout << "Спасибо, что использовали мою программу =)" << endl;
	
	delete[] matrix;

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
