// задание 1 из файла Domasnee_zadanie_1594661480.txt
// Выполните домашние задания после уроков 3, 4, 5
// Урок 5. Задание 2
/*
2.	Создать класс для работы с матрицами.
Предусмотреть, как минимум, функции для сложения матриц,
умножения матриц, транспонирования матриц, присваивания
матриц друг другу, установка и получение произвольного
элемента матрицы. Необходимо перегрузить соответствующие
операторы.
*/
#include <iostream>
#include <clocale>
#include <iomanip>
#include <ctime>
using namespace std;


// КЛАСС Строка матрицы
class MatrixRow {
private:
	size_t n_row{ 0 };
	int* row{ nullptr };

	// МЕТОД создания пустой строки таблицы матрицы в памяти (n>0)
	void create() {
	//	cout << " MatrixRow.create(){" << n_row << "}" << endl;
		if (n_row) row = new int[n_row]{ 0 };
		setValue();
	}

	// МЕТОД задания упорядоченных значений элементам массива
	void setValue() {
		static int count = 1;
		for (size_t i = 0; i < n_row; i++) {
			row[i] = i * count;
		}
		count *= 10;
	}

public:
	// КОНСТРУКТОР по умолчанию
	MatrixRow() {
	//	cout << " Конструктор MatrixRow() по умолчанию" << endl;
	}

	// КОНСТРУКТОР с параметрами
	MatrixRow(size_t n_) : n_row(n_) {
	//	cout << " Конструктор MatrixRow() с параметрами: n_row{" << n_row << "}" << endl;
		create();
	}

	// ДЕСТРУКТОР
	~MatrixRow() {
	//	cout << " Деструктор ~MatrixRow()";
		if (row) delete[] row;
	//	cout << " - выполнено (row)" << endl;
	}

	// МЕТОД индексации массива - перегрузки оператора []
	int& operator[](const size_t j) {
	//	cout << " Перегрузка оператора [] - int& operator[](const size_t j = " << j << ")" << endl;
		return row[j];
	}

	// Прототип дружественной функции вывода объекта на консоль - перегрузки оператора <<
	friend std::ostream& operator<<(std::ostream& out, const MatrixRow& matrixRow);

	// прототип дружественной функции сложения матриц - перегрузки оператора +
	friend MatrixRow operator+(const MatrixRow& matrixRow1, const MatrixRow& matrixRow2);

	// прототип дружественной функции сложения матриц - перегрузки оператора -
	friend MatrixRow operator-(const MatrixRow& matrixRow1, const MatrixRow& matrixRow2);
};


// Дружественная ФУНКЦИЯ вывода объекта на консоль - перегрузки оператора <<
std::ostream& operator<<(std::ostream& out, const MatrixRow& matrixRow) {
	if (matrixRow.row) {
		for (size_t j = 0; j < matrixRow.n_row; j++) {
			out << setw(12) << right << matrixRow.row[j];
		}
	}
	return out;
}


// Дружественная ФУНКЦИЯ сложения строк матриц - перегрузки оператора +
MatrixRow operator+(const MatrixRow& matrixRow1, const MatrixRow& matrixRow2) {
	MatrixRow matrixRow3(matrixRow1.n_row);
	if (matrixRow1.n_row == matrixRow2.n_row) {
		for (size_t j = 0; j < matrixRow3.n_row; j++) {
			matrixRow3.row[j] = matrixRow1.row[j] + matrixRow2.row[j];
		}
	}
	return matrixRow3;
}


// Дружественная ФУНКЦИЯ вычитания строк матриц - перегрузки оператора -
MatrixRow operator-(const MatrixRow& matrixRow1, const MatrixRow& matrixRow2) {
	MatrixRow matrixRow3(matrixRow1.n_row);
	if (matrixRow1.n_row == matrixRow2.n_row) {
		for (size_t j = 0; j < matrixRow3.n_row; j++) {
			matrixRow3.row[j] = matrixRow1.row[j] - matrixRow2.row[j];
		}
	}
	return matrixRow3;
}


// КЛАСС Матрицы
class Matrix {
private:
	size_t m{ 0 };
	size_t n{ 0 };
	MatrixRow** table{ nullptr };

	// МЕТОД создания пустой таблицы матрицы в памяти (m>0, n>0)
	void create() {
		table = new MatrixRow * [m] {nullptr};
		if (table) {
			for (size_t i = 0; i < m; i++) {
				table[i] = new MatrixRow{ n };
			}
		}
	}

public:
	// КОНСТРУКТОР по умолчанию
	Matrix() {
	//	cout << " Конструктор Matrix() по умолчанию" << endl;
	}

	// КОНСТРУКТОР с параметрами
	Matrix(size_t m_, size_t n_) : m(m_), n(n_) {
	//	cout << " Конструктор Matrix() с параметрами: m{" << m << "}, n{" << n << "}" << endl;
		create();
	}

	// КОНСТРУКТОР копирования
	Matrix(const Matrix& matrix) {
	//	cout << " Конструктор Matrix() копирования: m{" << matrix.m << "}, n{" << matrix.n << "}" << endl;
		m = matrix.m;
		n = matrix.n;
		create();
		if (m && n) {
			if (table) {
				for (size_t i = 0; i < m; i++) {
					if (table[i]) {
						for (size_t j = 0; j < n; j++) {
							(*table[i])[j] = (*matrix.table[i])[j];
						}
					}
				}
			}
		}
	}

	// ДЕСТРУКТОР
	~Matrix() {
	//	cout << " Деструктор ~Matrix()";
		if (table) {
			for (size_t i = 0; i < m; i++) {
				if (table[i]) delete table[i];
			}
			delete[] table;
		}
	//	cout << " - выполнено (table)" << endl;
	}

	// МЕТОД транспонирования матрицы
	void transpose() {
		Matrix matrix(n, m);
		if (table && matrix.table) {
			for (size_t i = 0; i < matrix.m; i++) {
				for (size_t j = 0; j < matrix.n; j++) {
					(*matrix.table[i])[j] = (*table[j])[i];
				}
			}
		}
		this->~Matrix();
		*this = matrix;
		matrix.table = nullptr;
	}

	// МЕТОД индексации массива - перегрузки оператора []
	MatrixRow& operator[](const size_t i) {
	//	cout << " Перегрузка оператора [] - MatrixRow*& operator[](const size_t i = " << i << ")" << endl;
		return *table[i];
	}

	// МЕТОД присваивания значений таблицы перегрузкой оператора =
	void operator=(const Matrix& matrix) {
	//	cout << " Присваивание перегрузкой оператора = : m{" << matrix.m << "}, n{" << matrix.n << "}" << endl;
		this->m = matrix.m;
		this->n = matrix.n;
		create();
		if (m && n) {
			if (table) {
				for (size_t i = 0; i < m; i++) {
					if (table[i]) {
						for (size_t j = 0; j < n; j++) {
							(*table[i])[j] = (*matrix.table[i])[j];
						}
					}
				}
			}
		}
	}

	// прототип дружественной функции вывода объекта на консоль - перегрузки оператора <<
	friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);

	// прототип дружественной функции сложения матриц - перегрузки оператора +
	friend Matrix operator+(const Matrix& matrix1, const Matrix& matrix2);

	// прототип дружественной функции вычитания матриц - перегрузки оператора -
	friend Matrix operator-(const Matrix& matrix1, const Matrix& matrix2);

	// прототип дружественной функции произведения матриц - перегрузки оператора *
	friend Matrix operator*(const Matrix& matrix1, const Matrix& matrix2);
};
// Конец КЛАССА Матрицы


// Дружественная ФУНКЦИЯ вывода объекта на консоль - перегрузки оператора <<
std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
	if (matrix.table) {
		for (size_t i = 0; i < matrix.m; i++) {
			if (matrix.table[i]) {
				for (size_t j = 0; j < matrix.n; j++) {
					out << setw(12) << right << (*matrix.table[i])[j];
				}
			}
			out << std::endl;
		}
	}
	return out;
}


// Дружественная ФУНКЦИЯ сложения матриц - перегрузки оператора +
Matrix operator+(const Matrix& matrix1, const Matrix& matrix2) {
	Matrix matrix3(matrix1.m, matrix1.n);
	if ((matrix1.m == matrix2.m) && (matrix1.n == matrix2.n)) {
		if (matrix1.table && matrix2.table && matrix3.table) {
			for (size_t i = 0; i < matrix1.m; i++) {
				if (matrix1.table[i] && matrix2.table[i] && matrix3.table[i]) {
					for (size_t j = 0; j < matrix1.n; j++) {
						(*matrix3.table[i])[j] = (*matrix1.table[i])[j] + (*matrix2.table[i])[j];
					}
				}
				else {
					cout << " ОШИБКА !!! Строка " << i << " таблицы матрицы отсутствует в памяти !!!" << endl;
					exit(5);
				}
			}
		}
		else {
			cout << " ОШИБКА !!! Таблица матрицы отсутствует в памяти !!!" << endl;
			exit(5);
		}
	}
	else {
		cout
			<< " ОШИБКА !!! Размеры матриц не равны (m: "
			<< matrix1.m
			<< " <> "
			<< matrix2.m
			<< ", n: "
			<< matrix1.n
			<< " <> "
			<< matrix2.n
			<< ")!!!" << endl;
		exit(5);
	}
	return matrix3;
}


// Дружественная ФУНКЦИЯ вычитания матриц - перегрузки оператора -
Matrix operator-(const Matrix& matrix1, const Matrix& matrix2) {
	Matrix matrix3(matrix1.m, matrix1.n);
	if ((matrix1.m == matrix2.m) && (matrix1.n == matrix2.n)) {
		if (matrix1.table && matrix2.table && matrix3.table) {
			for (size_t i = 0; i < matrix1.m; i++) {
				if (matrix1.table[i] && matrix2.table[i] && matrix3.table[i]) {
					for (size_t j = 0; j < matrix1.n; j++) {
						(*matrix3.table[i])[j] = (*matrix1.table[i])[j] - (*matrix2.table[i])[j];
					}
				}
				else {
					cout << " ОШИБКА !!! Строка " << i << " таблицы матрицы отсутствует в памяти !!!" << endl;
					exit(5);
				}
			}
		}
		else {
			cout << " ОШИБКА !!! Таблица матрицы отсутствует в памяти !!!" << endl;
			exit(5);
		}
	}
	else {
		cout
			<< " ОШИБКА !!! Размеры матриц не равны (m: "
			<< matrix1.m
			<< " <> "
			<< matrix2.m
			<< ", n: "
			<< matrix1.n
			<< " <> "
			<< matrix2.n
			<< ")!!!" << endl;
		exit(5);
	}
	return matrix3;
}


// Дружественная ФУНКЦИЯ произведения матриц - перегрузки оператора *
Matrix operator*(const Matrix& matrix1, const Matrix& matrix2) {
	Matrix matrix3(matrix1.m, matrix2.n);
	if (matrix1.n == matrix2.m) {
		if (matrix1.table && matrix2.table && matrix3.table) {
			for (size_t i = 0; i < matrix3.m; i++) {
				for (size_t j = 0; j < matrix3.n; j++) {
					(*matrix3.table[i])[j] = 0;
					for (size_t k = 0; k < matrix1.n; k++) {
						(*matrix3.table[i])[j] += ((*matrix1.table[i])[k] * (*matrix2.table[k])[j]);
					}
				}
			}
		}
		else {
			cout << " ОШИБКА !!! Таблица матрицы отсутствует в памяти !!!" << endl;
			exit(5);
		}
	}
	else {
		cout
			<< " ОШИБКА !!! Количество столбцов Матрицы 1 n{"
			<< matrix1.n
			<< "} не равно количеству строк Матрицы 2 m{"
			<< matrix2.m
			<< "}!!!" << endl;
		exit(5);
	}
	return matrix3;
}


// ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "ru");

/*
	//-------------------------------------------------------------------

	MatrixRow mr1;
	cout << " Строка матрицы mr1:" << endl;
	cout << mr1 << endl;
	cout << endl;

	MatrixRow mr2(5);
	mr2.setValue();
	cout << " Строка матрицы mr2:" << endl;
	cout << mr2 << endl;
	cout << endl;

	cout << " Элемент строки матрицы mr2[1] = " << mr2[1] << endl;
	cout << endl;

	mr2[1] = 7;
	cout << " Присвоим элементу строки матрицы значение: mr2[1] = 7" << endl;
	cout << " Элемент строки матрицы mr2[1] = " << mr2[1] << endl;
	cout << endl;


	mr1 = mr2;
	cout << " Строка матрицы mr1 = mr2:" << endl;
	cout << mr1 << endl;
	cout << endl;

	cout << "--------------------------------------------------------------------------------" << endl << endl;
*/
		
	Matrix m1;
	cout << " Матрица m1:" << endl;
	cout << m1 << endl;
	cout << endl;

	size_t m = 3;
	size_t n = 5;
	Matrix m2(m, n);
	cout << " Матрица m2:" << endl;
	cout << m2 << endl;
	cout << endl;

	cout << " Проверка работы индексации двумерного массива" << endl;
	cout << " Результат: m2[1][1] == " << m2[1][1] << endl;
	cout << " Присвоим значение: m2[1][1] = 11" << endl;
	m2[1][1] = 11;
	cout << " Результат: m2[1][1] == " << m2[1][1] << endl;
	cout << " Матрица m2:" << endl;
	cout << m2 << endl;
	cout << endl;

	m1 = m2;
	cout << " Матрица m1 = m2:" << endl;
	cout << m1 << endl;
	cout << endl;

	Matrix m3 = m2;
	cout << " Матрица m3 = m2:" << endl;
	cout << m3 << endl;
	cout << endl;

	m1 = m2 + m3;
	cout << " Матрица m1 = m2 + m3:" << endl;
	cout << m1 << endl;
	cout << endl;

	m3 = m2 - m1;
	cout << " Матрица m3 = m2 - m1:" << endl;
	cout << m3 << endl;
	cout << endl;

	cout << " Транспонируем матрицу m3" << endl;
	m3.transpose();
	cout << " Матрица m3:" << endl;
	cout << m3 << endl;
	cout << endl;

	cout << " Матрица m2:" << endl;
	cout << m2 << endl;
	cout << endl;

	m1 = m2 * m3;
	cout << " Матрица m1 = m2 * m3:" << endl;
	cout << m1 << endl;
	cout << endl;

//	cout << " Конец main()" << endl;
	return 0;
}
// Конец ГЛАВНОЙ ФУНКЦИИ
