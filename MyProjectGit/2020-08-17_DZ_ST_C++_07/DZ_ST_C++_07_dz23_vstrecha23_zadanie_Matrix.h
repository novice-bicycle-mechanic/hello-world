// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Matrix.h
//
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
#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>

namespace spaceMatrix
{
	static int initCount{ 0 };

	// КЛАСС Строка матрицы
	class MatrixRow {
	private:
		size_t n_row{ 0 };
		int* row{ nullptr };

		// МЕТОД создания пустой строки таблицы матрицы в памяти (n>0)
		void create() {
			//	std::cout << " MatrixRow.create(){" << n_row << "}" << std::endl;
			if (n_row) row = new int[n_row] { 0 };
			setValue();
		}

		// МЕТОД задания упорядоченных значений элементам массива
		void setValue() {
			int count = initCount;
			for (size_t i = 0; i < n_row; i++) {
				row[i] = i * count;
			}
		}

	public:
		// КОНСТРУКТОР по умолчанию
		MatrixRow() {
			//	std::cout << " Конструктор MatrixRow() по умолчанию" << std::endl;
		}

		// КОНСТРУКТОР с параметрами
		MatrixRow(size_t n_) : n_row(n_) {
			//	std::cout << " Конструктор MatrixRow() с параметрами: n_row{" << n_row << "}" << std::endl;
			create();
		}

		// ДЕСТРУКТОР
		~MatrixRow() {
			//	std::cout << " Деструктор ~MatrixRow()";
			if (row) delete[] row;
			//	std::cout << " - выполнено (row)" << std::endl;
		}

		// МЕТОД индексации массива - перегрузки оператора []
		int& operator[](const size_t j) { return row[j]; }

		// Прототип дружественной функции вывода объекта на консоль - перегрузки оператора <<
		friend std::ostream& operator<<(std::ostream& out, const MatrixRow& matrixRow);

		// прототип дружественной функции сложения матриц - перегрузки оператора +
		friend MatrixRow operator+(const MatrixRow& matrixRow1, const MatrixRow& matrixRow2);

		// прототип дружественной функции сложения матриц - перегрузки оператора -
		friend MatrixRow operator-(const MatrixRow& matrixRow1, const MatrixRow& matrixRow2);
	};


	// КЛАСС Матрицы
	class Matrix {
	private:
		size_t m{ 0 };
		size_t n{ 0 };
		MatrixRow** table{ nullptr };

		// МЕТОД создания пустой таблицы матрицы в памяти (m>0, n>0)
		void create() {
			initCount = 0;
			table = new MatrixRow * [m] {nullptr};
			if (table) {
				for (size_t i = 0; i < m; i++) {
					++initCount;
					table[i] = new MatrixRow{ n };
				}
			}
		}

	public:
		// КОНСТРУКТОР по умолчанию
		Matrix() {
			//	std::cout << " Конструктор Matrix() по умолчанию" << std::endl;
		}

		// КОНСТРУКТОР с параметрами
		Matrix(size_t m_, size_t n_) : m(m_), n(n_) {
			//	std::cout << " Конструктор Matrix() с параметрами: m{" << m << "}, n{" << n << "}" << std::endl;
			create();
		}

		// КОНСТРУКТОР копирования
		Matrix(const Matrix& matrix) {
			//	std::cout << " Конструктор Matrix() копирования: m{" << matrix.m << "}, n{" << matrix.n << "}" << std::endl;
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
			//	std::cout << " Деструктор ~Matrix()";
			if (table) {
				for (size_t i = 0; i < m; i++) {
					if (table[i]) delete table[i];
				}
				delete[] table;
			}
			//	std::cout << " - выполнено (table)" << std::endl;
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
		MatrixRow& operator[](const size_t i) { return *table[i]; }

		// МЕТОД присваивания значений таблицы перегрузкой оператора =
		void operator=(const Matrix& matrix) {
			//	std::cout << " Присваивание перегрузкой оператора = : m{" << matrix.m << "}, n{" << matrix.n << "}" << std::endl;
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



	// КЛАСС Test для проверки работы namespace при совпадении идентификаторов типа
	class Test : public Matrix {
	public:
		Test(size_t m_, size_t n_) : Matrix( m_, n_) {}
	};

}