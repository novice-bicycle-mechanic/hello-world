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
#include <iostream>
#include <clocale>
#include <iomanip>
#include <ctime>
using namespace std;


// ����� ������ �������
class MatrixRow {
private:
	size_t n_row{ 0 };
	int* row{ nullptr };

	// ����� �������� ������ ������ ������� ������� � ������ (n>0)
	void create() {
	//	cout << " MatrixRow.create(){" << n_row << "}" << endl;
		if (n_row) row = new int[n_row]{ 0 };
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
	//	cout << " ����������� MatrixRow() �� ���������" << endl;
	}

	// ����������� � �����������
	MatrixRow(size_t n_) : n_row(n_) {
	//	cout << " ����������� MatrixRow() � �����������: n_row{" << n_row << "}" << endl;
		create();
	}

	// ����������
	~MatrixRow() {
	//	cout << " ���������� ~MatrixRow()";
		if (row) delete[] row;
	//	cout << " - ��������� (row)" << endl;
	}

	// ����� ���������� ������� - ���������� ��������� []
	int& operator[](const size_t j) {
	//	cout << " ���������� ��������� [] - int& operator[](const size_t j = " << j << ")" << endl;
		return row[j];
	}

	// �������� ������������� ������� ������ ������� �� ������� - ���������� ��������� <<
	friend std::ostream& operator<<(std::ostream& out, const MatrixRow& matrixRow);

	// �������� ������������� ������� �������� ������ - ���������� ��������� +
	friend MatrixRow operator+(const MatrixRow& matrixRow1, const MatrixRow& matrixRow2);

	// �������� ������������� ������� �������� ������ - ���������� ��������� -
	friend MatrixRow operator-(const MatrixRow& matrixRow1, const MatrixRow& matrixRow2);
};


// ������������� ������� ������ ������� �� ������� - ���������� ��������� <<
std::ostream& operator<<(std::ostream& out, const MatrixRow& matrixRow) {
	if (matrixRow.row) {
		for (size_t j = 0; j < matrixRow.n_row; j++) {
			out << setw(12) << right << matrixRow.row[j];
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
	//	cout << " ����������� Matrix() �� ���������" << endl;
	}

	// ����������� � �����������
	Matrix(size_t m_, size_t n_) : m(m_), n(n_) {
	//	cout << " ����������� Matrix() � �����������: m{" << m << "}, n{" << n << "}" << endl;
		create();
	}

	// ����������� �����������
	Matrix(const Matrix& matrix) {
	//	cout << " ����������� Matrix() �����������: m{" << matrix.m << "}, n{" << matrix.n << "}" << endl;
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
	//	cout << " ���������� ~Matrix()";
		if (table) {
			for (size_t i = 0; i < m; i++) {
				if (table[i]) delete table[i];
			}
			delete[] table;
		}
	//	cout << " - ��������� (table)" << endl;
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
	MatrixRow& operator[](const size_t i) {
	//	cout << " ���������� ��������� [] - MatrixRow*& operator[](const size_t i = " << i << ")" << endl;
		return *table[i];
	}

	// ����� ������������ �������� ������� ����������� ��������� =
	void operator=(const Matrix& matrix) {
	//	cout << " ������������ ����������� ��������� = : m{" << matrix.m << "}, n{" << matrix.n << "}" << endl;
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


// ������������� ������� ������ ������� �� ������� - ���������� ��������� <<
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
					cout << " ������ !!! ������ " << i << " ������� ������� ����������� � ������ !!!" << endl;
					exit(5);
				}
			}
		}
		else {
			cout << " ������ !!! ������� ������� ����������� � ������ !!!" << endl;
			exit(5);
		}
	}
	else {
		cout
			<< " ������ !!! ������� ������ �� ����� (m: "
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
					cout << " ������ !!! ������ " << i << " ������� ������� ����������� � ������ !!!" << endl;
					exit(5);
				}
			}
		}
		else {
			cout << " ������ !!! ������� ������� ����������� � ������ !!!" << endl;
			exit(5);
		}
	}
	else {
		cout
			<< " ������ !!! ������� ������ �� ����� (m: "
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
			cout << " ������ !!! ������� ������� ����������� � ������ !!!" << endl;
			exit(5);
		}
	}
	else {
		cout
			<< " ������ !!! ���������� �������� ������� 1 n{"
			<< matrix1.n
			<< "} �� ����� ���������� ����� ������� 2 m{"
			<< matrix2.m
			<< "}!!!" << endl;
		exit(5);
	}
	return matrix3;
}


// ������� �������
int main() {
	setlocale(LC_ALL, "ru");

/*
	//-------------------------------------------------------------------

	MatrixRow mr1;
	cout << " ������ ������� mr1:" << endl;
	cout << mr1 << endl;
	cout << endl;

	MatrixRow mr2(5);
	mr2.setValue();
	cout << " ������ ������� mr2:" << endl;
	cout << mr2 << endl;
	cout << endl;

	cout << " ������� ������ ������� mr2[1] = " << mr2[1] << endl;
	cout << endl;

	mr2[1] = 7;
	cout << " �������� �������� ������ ������� ��������: mr2[1] = 7" << endl;
	cout << " ������� ������ ������� mr2[1] = " << mr2[1] << endl;
	cout << endl;


	mr1 = mr2;
	cout << " ������ ������� mr1 = mr2:" << endl;
	cout << mr1 << endl;
	cout << endl;

	cout << "--------------------------------------------------------------------------------" << endl << endl;
*/
		
	Matrix m1;
	cout << " ������� m1:" << endl;
	cout << m1 << endl;
	cout << endl;

	size_t m = 3;
	size_t n = 5;
	Matrix m2(m, n);
	cout << " ������� m2:" << endl;
	cout << m2 << endl;
	cout << endl;

	cout << " �������� ������ ���������� ���������� �������" << endl;
	cout << " ���������: m2[1][1] == " << m2[1][1] << endl;
	cout << " �������� ��������: m2[1][1] = 11" << endl;
	m2[1][1] = 11;
	cout << " ���������: m2[1][1] == " << m2[1][1] << endl;
	cout << " ������� m2:" << endl;
	cout << m2 << endl;
	cout << endl;

	m1 = m2;
	cout << " ������� m1 = m2:" << endl;
	cout << m1 << endl;
	cout << endl;

	Matrix m3 = m2;
	cout << " ������� m3 = m2:" << endl;
	cout << m3 << endl;
	cout << endl;

	m1 = m2 + m3;
	cout << " ������� m1 = m2 + m3:" << endl;
	cout << m1 << endl;
	cout << endl;

	m3 = m2 - m1;
	cout << " ������� m3 = m2 - m1:" << endl;
	cout << m3 << endl;
	cout << endl;

	cout << " ������������� ������� m3" << endl;
	m3.transpose();
	cout << " ������� m3:" << endl;
	cout << m3 << endl;
	cout << endl;

	cout << " ������� m2:" << endl;
	cout << m2 << endl;
	cout << endl;

	m1 = m2 * m3;
	cout << " ������� m1 = m2 * m3:" << endl;
	cout << m1 << endl;
	cout << endl;

//	cout << " ����� main()" << endl;
	return 0;
}
// ����� ������� �������
