// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Matrix.h
//
// ������� 1 �� ����� Domasnee_zadanie_1594661480.txt
// ��������� �������� ������� ����� ������ 3, 4, 5
// ���� 5. ������� 2
/*
2.	������� ����� ��� ������ � ���������.
�������������, ��� �������, ������� ��� �������� ������,
��������� ������, ���������������� ������, ������������
������ ���� �����, ��������� � ��������� �������������
�������� �������. ���������� ����������� ���������������
���������.
*/
#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>

namespace math
{
	// ����� ������ �������
	class MatrixRow {
	private:
		size_t n_row{ 0 };
		int* row{ nullptr };

		// ����� �������� ������ ������ ������� ������� � ������ (n>0)
		void create() {
			//	std::cout << " MatrixRow.create(){" << n_row << "}" << std::endl;
			if (n_row) row = new int[n_row] { 0 };
			setValue();
		}

		// ����� ������� ������������� �������� ��������� �������
		void setValue() {
			static int count = 1;
			for (size_t i = 0; i < n_row; i++) {
				row[i] = i * count;
			}
			count *= 10;
		}

	public:
		// ����������� �� ���������
		MatrixRow() {
			//	std::cout << " ����������� MatrixRow() �� ���������" << std::endl;
		}

		// ����������� � �����������
		MatrixRow(size_t n_) : n_row(n_) {
			//	std::cout << " ����������� MatrixRow() � �����������: n_row{" << n_row << "}" << std::endl;
			create();
		}

		// ����������
		~MatrixRow() {
			//	std::cout << " ���������� ~MatrixRow()";
			if (row) delete[] row;
			//	std::cout << " - ��������� (row)" << std::endl;
		}

		// ����� ���������� ������� - ���������� ��������� []
		int& operator[](const size_t j) { return row[j]; }

		// �������� ������������� ������� ������ ������� �� ������� - ���������� ��������� <<
		friend std::ostream& operator<<(std::ostream& out, const MatrixRow& matrixRow);

		// �������� ������������� ������� �������� ������ - ���������� ��������� +
		friend MatrixRow operator+(const MatrixRow& matrixRow1, const MatrixRow& matrixRow2);

		// �������� ������������� ������� �������� ������ - ���������� ��������� -
		friend MatrixRow operator-(const MatrixRow& matrixRow1, const MatrixRow& matrixRow2);
	};


	// ����� �������
	class Matrix {
	private:
		size_t m{ 0 };
		size_t n{ 0 };
		MatrixRow** table{ nullptr };

		// ����� �������� ������ ������� ������� � ������ (m>0, n>0)
		void create() {
			table = new MatrixRow * [m] {nullptr};
			if (table) {
				for (size_t i = 0; i < m; i++) {
					table[i] = new MatrixRow{ n };
				}
			}
		}

	public:
		// ����������� �� ���������
		Matrix() {
			//	std::cout << " ����������� Matrix() �� ���������" << std::endl;
		}

		// ����������� � �����������
		Matrix(size_t m_, size_t n_) : m(m_), n(n_) {
			//	std::cout << " ����������� Matrix() � �����������: m{" << m << "}, n{" << n << "}" << std::endl;
			create();
		}

		// ����������� �����������
		Matrix(const Matrix& matrix) {
			//	std::cout << " ����������� Matrix() �����������: m{" << matrix.m << "}, n{" << matrix.n << "}" << std::endl;
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

		// ����������
		~Matrix() {
			//	std::cout << " ���������� ~Matrix()";
			if (table) {
				for (size_t i = 0; i < m; i++) {
					if (table[i]) delete table[i];
				}
				delete[] table;
			}
			//	std::cout << " - ��������� (table)" << std::endl;
		}

		// ����� ���������������� �������
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

		// ����� ���������� ������� - ���������� ��������� []
		MatrixRow& operator[](const size_t i) { return *table[i]; }

		// ����� ������������ �������� ������� ����������� ��������� =
		void operator=(const Matrix& matrix) {
			//	std::cout << " ������������ ����������� ��������� = : m{" << matrix.m << "}, n{" << matrix.n << "}" << std::endl;
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

		// �������� ������������� ������� ������ ������� �� ������� - ���������� ��������� <<
		friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);

		// �������� ������������� ������� �������� ������ - ���������� ��������� +
		friend Matrix operator+(const Matrix& matrix1, const Matrix& matrix2);

		// �������� ������������� ������� ��������� ������ - ���������� ��������� -
		friend Matrix operator-(const Matrix& matrix1, const Matrix& matrix2);

		// �������� ������������� ������� ������������ ������ - ���������� ��������� *
		friend Matrix operator*(const Matrix& matrix1, const Matrix& matrix2);
	};
	// ����� ������ �������
}
