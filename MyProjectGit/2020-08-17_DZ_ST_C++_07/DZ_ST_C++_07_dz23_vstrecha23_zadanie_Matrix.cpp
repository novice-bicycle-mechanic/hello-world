// DZ_ST_C++_07_dz23_vstrecha23_zadanie_Matrix.cpp
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
#include "DZ_ST_C++_07_dz23_vstrecha23_zadanie_Matrix.h"


namespace math
{
	// ������������� ������� ������ ������� �� ������� - ���������� ��������� <<
	std::ostream& operator<<(std::ostream& out, const MatrixRow& matrixRow) {
		if (matrixRow.row) {
			for (size_t j = 0; j < matrixRow.n_row; j++) {
				out << std::setw(12) << std::right << matrixRow.row[j];
			}
		}
		return out;
	}


	// ������������� ������� �������� ����� ������ - ���������� ��������� +
	MatrixRow operator+(const MatrixRow& matrixRow1, const MatrixRow& matrixRow2) {
		MatrixRow matrixRow3(matrixRow1.n_row);
		if (matrixRow1.n_row == matrixRow2.n_row) {
			for (size_t j = 0; j < matrixRow3.n_row; j++) {
				matrixRow3.row[j] = matrixRow1.row[j] + matrixRow2.row[j];
			}
		}
		return matrixRow3;
	}


	// ������������� ������� ��������� ����� ������ - ���������� ��������� -
	MatrixRow operator-(const MatrixRow& matrixRow1, const MatrixRow& matrixRow2) {
		MatrixRow matrixRow3(matrixRow1.n_row);
		if (matrixRow1.n_row == matrixRow2.n_row) {
			for (size_t j = 0; j < matrixRow3.n_row; j++) {
				matrixRow3.row[j] = matrixRow1.row[j] - matrixRow2.row[j];
			}
		}
		return matrixRow3;
	}

	//------------------------------------------------------------------------------------

	// ������������� ������� ������ ������� �� ������� - ���������� ��������� <<
	std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
		if (matrix.table) {
			for (size_t i = 0; i < matrix.m; i++) {
				if (matrix.table[i]) {
					for (size_t j = 0; j < matrix.n; j++) {
						out << std::setw(12) << std::right << (*matrix.table[i])[j];
					}
				}
				out << std::endl;
			}
		}
		return out;
	}


	// ������������� ������� �������� ������ - ���������� ��������� +
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
						std::cout << " ������ !!! ������ " << i << " ������� ������� ����������� � ������ !!!" << std::endl;
						exit(5);
					}
				}
			}
			else {
				std::cout << " ������ !!! ������� ������� ����������� � ������ !!!" << std::endl;
				exit(5);
			}
		}
		else {
			std::cout
				<< " ������ !!! ������� ������ �� ����� (m: "
				<< matrix1.m
				<< " <> "
				<< matrix2.m
				<< ", n: "
				<< matrix1.n
				<< " <> "
				<< matrix2.n
				<< ")!!!" << std::endl;
			exit(5);
		}
		return matrix3;
	}


	// ������������� ������� ��������� ������ - ���������� ��������� -
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
						std::cout << " ������ !!! ������ " << i << " ������� ������� ����������� � ������ !!!" << std::endl;
						exit(5);
					}
				}
			}
			else {
				std::cout << " ������ !!! ������� ������� ����������� � ������ !!!" << std::endl;
				exit(5);
			}
		}
		else {
			std::cout
				<< " ������ !!! ������� ������ �� ����� (m: "
				<< matrix1.m
				<< " <> "
				<< matrix2.m
				<< ", n: "
				<< matrix1.n
				<< " <> "
				<< matrix2.n
				<< ")!!!" << std::endl;
			exit(5);
		}
		return matrix3;
	}


	// ������������� ������� ������������ ������ - ���������� ��������� *
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
				std::cout << " ������ !!! ������� ������� ����������� � ������ !!!" << std::endl;
				exit(5);
			}
		}
		else {
			std::cout
				<< " ������ !!! ���������� �������� ������� 1 n{"
				<< matrix1.n
				<< "} �� ����� ���������� ����� ������� 2 m{"
				<< matrix2.m
				<< "}!!!" << std::endl;
			exit(5);
		}
		return matrix3;
	}
}

